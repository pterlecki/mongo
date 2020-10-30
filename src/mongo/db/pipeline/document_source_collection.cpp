/**
 *    Copyright (C) 2018-present MongoDB, Inc.
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the Server Side Public License, version 1,
 *    as published by MongoDB, Inc.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    Server Side Public License for more details.
 *
 *    You should have received a copy of the Server Side Public License
 *    along with this program. If not, see
 *    <http://www.mongodb.com/licensing/server-side-public-license>.
 *
 *    As a special exception, the copyright holders give permission to link the
 *    code of portions of this program with the OpenSSL library under certain
 *    conditions as described in each individual source file and distribute
 *    linked combinations including the program with the OpenSSL library. You
 *    must comply with the Server Side Public License in all respects for
 *    all of the code used other than as permitted herein. If you modify file(s)
 *    with this exception, you may extend this exception to your version of the
 *    file(s), but you are not obligated to do so. If you do not wish to do so,
 *    delete this exception statement from your version. If you delete this
 *    exception statement from all source files in the program, then also delete
 *    it in the license file.
 */

#include "mongo/platform/basic.h"

#include "mongo/db/pipeline/document_source_collection.h"

#include "mongo/bson/bsonobj.h"
#include "mongo/db/pipeline/lite_parsed_document_source.h"
#include "mongo/db/stats/top.h"
#include "mongo/util/net/socket_utils.h"
#include "mongo/util/time_support.h"
#include "mongo/util/timer.h"

#include <algorithm>
#include <execution>
#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>

#include <aws/core/Aws.h>
#include <aws/core/auth/AWSCredentials.h>
#include <aws/s3/model/GetObjectRequest.h>
#include <aws/s3/model/HeadObjectRequest.h>
#include <aws/transfer/TransferHandle.h>
#include <aws/transfer/TransferManager.h>


using boost::intrusive_ptr;

namespace mongo {

REGISTER_DOCUMENT_SOURCE(collection,
                         DocumentSourceCollection::LiteParsed::parse,
                         DocumentSourceCollection::createFromBson);

const char* DocumentSourceCollection::getSourceName() const {
    return kStageName.rawData();
}

intrusive_ptr<DocumentSource> DocumentSourceCollection::createFromBson(
    BSONElement specElem, const intrusive_ptr<ExpressionContext>& pExpCtx) {
    uassert(40166,
            str::stream() << "$Collection must take a nested object or array but found: " << specElem,
            specElem.type() == BSONType::Object || specElem.type() == BSONType::Array);
    intrusive_ptr<DocumentSourceCollection> collection(new DocumentSourceCollection(pExpCtx));

    if (specElem.type() == BSONType::Array) {
        BSONObjBuilder specBuilder;
        specBuilder.append("data", specElem.Obj().getOwned());
        specBuilder.doneFast();
        collection->_collectionSpec = specBuilder.obj();
    } else {
        for (const auto& elem : specElem.embeddedObject()) {
            StringData fieldName = elem.fieldNameStringData();

            if ("data" == fieldName) {
                uassert(40167,
                        str::stream() << "format argument must be an array, but got " << elem
                                    << " of type " << typeName(elem.type()),
                        elem.type() == BSONType::Array);
            } else if ("format" == fieldName) {
                uassert(40167,
                        str::stream() << "format argument must be a string, but got " << elem
                                    << " of type " << typeName(elem.type()),
                        elem.type() == BSONType::String);
                uassert(40305, "only json format is supported", elem.str() == "json");
            } else if ("path" == fieldName) {
                uassert(40167,
                        str::stream() << "path argument must be a string, but got " << elem
                                    << " of type " << typeName(elem.type()),
                        elem.type() == BSONType::String);
            } else {
                uassert(40168, str::stream() << "unrecognized option to $collection: " << fieldName, "region" == fieldName || "threads" == fieldName || "keyId" == fieldName || "secretKey" == fieldName);
            }
        }
        // TODO: verify that the right fields are specified together

        collection->_collectionSpec = specElem.Obj().getOwned();
    }
    collection->_collectionType = (collection->_collectionSpec.hasField("data")) ? CollectionType::constant : CollectionType::file;
    return collection;
}

Status convert(const StringData& fieldName, const simdjson::dom::element& value, BSONObjBuilder& builder, bool subObject) {
    if (value.is_object()) {
        BSONObjBuilder* objBuilder = &builder;
        std::unique_ptr<BSONObjBuilder> subBuilder;
        if (subObject) {
            subBuilder.reset(new BSONObjBuilder(builder.subobjStart(fieldName)));
            objBuilder = subBuilder.get();
        }
        for (const auto& field : value.get_object()) {
            convert(field.key.data(), field.value, *objBuilder, true);
        }
    } else if (value.is_array()) {
        DecimalCounter<uint32_t> index;
        BSONObjBuilder* arrayBuilder = &builder;
        std::unique_ptr<BSONObjBuilder> subBuilder;
        if (subObject) {
            subBuilder.reset(new BSONObjBuilder(builder.subarrayStart(fieldName)));
            arrayBuilder = subBuilder.get();
        }
        for (const auto& field : value.get_array()) {
            convert(StringData{index}, field, *arrayBuilder, true);
            ++index;
        }
    } else if (value.is_string()) {
        builder.append(fieldName, value.get_string().first.data());
    } else if (value.is_int64()) {
        builder.appendNumber(fieldName, value.get_int64());
    } else if (value.is_uint64()) {
        builder.appendNumber(fieldName, value.get_uint64());
    } else if (value.is_double()) {
        builder.appendNumber(fieldName, value.get_double());
    } else if (value.is_bool()) {
        builder.appendBool(fieldName, value.operator bool());
    } else if (value.is_null()) {
        builder.appendNull(fieldName);
    }
    return Status::OK();
}

struct DownloadPart {
    int begin;
    int end;
    std::string path;
    std::string error;
};

bool downloadFile(std::shared_ptr<Aws::S3::S3Client>& s3Client,
                  const std::string& bucket,
                  const std::string& key,
                  DownloadPart& part) {
    auto tempPath = boost::filesystem::temp_directory_path() /
        boost::filesystem::unique_path("tempjson-%%%%-%%%%-%%%%-%%%%");
    part.path = tempPath.generic_string();

    Aws::S3::Model::GetObjectRequest object_request;
    object_request.WithBucket(bucket.c_str()).WithKey(key.c_str());
    if (part.begin != -1) {
        std::stringstream ss;
        ss << "bytes=" << part.begin << '-' << part.end;
        object_request.WithRange(ss.str().c_str());
    }
    auto outcome = s3Client->GetObject(object_request);

    if (!outcome.IsSuccess()) {
        part.error = outcome.GetError().GetExceptionName();
        return false;
    }

    try {
        auto& remoteObjStream = outcome.GetResult().GetBody();
        std::ofstream out;
        out.open(part.path, std::ios::binary);

        int bufferSize = 16 * 1024 * 1024;
        char* buffer = new char[bufferSize];
        while (remoteObjStream) {
            remoteObjStream.read(buffer, bufferSize);
            out.write(buffer, remoteObjStream.gcount());
        }
        out.close();
        delete buffer;
        return  true;
    }
    catch (...) {
        return false;
    }
}

DocumentSource::GetNextResult DocumentSourceCollection::doGetNext() {
    if (_collectionType == CollectionType::constant) {
        if (_dataArrayIterator == nullptr) {
            _dataArrayIterator = std::make_unique<BSONObjIterator>(_collectionSpec["data"].Obj());
        }
        if (_dataArrayIterator->more()) {
            BSONElement e = _dataArrayIterator->next();
            // TODO: error out if not an object
            return Document(e.Obj());
        }
    } else if (_collectionType == CollectionType::file) {
        if (_collectionSpec["format"].str() =="json") {
            if (_jsonFileIterator == nullptr) {
                auto path = _collectionSpec["path"].str();
                if (path.substr(0,2) == "s3") {
                    auto initTimer = Timer();
                    auto bucketEndIndex = path.find('/', 5);
                    std::string bucket = path.substr(5, bucketEndIndex - 5);
                    std::string key = path.substr(bucketEndIndex + 1);
                    std::string region = _collectionSpec["region"].str();
                    int dop = (_collectionSpec.hasField("threads"))?_collectionSpec["threads"].numberInt():1;

                    Aws::SDKOptions options;
                    Aws::InitAPI(options);
                    Aws::Client::ClientConfiguration clientConfig;
                    clientConfig.region = region;
                    Aws::Auth::AWSCredentials credentials(
                        _collectionSpec["keyId"].str().c_str(),
                        _collectionSpec["secretKey"].str().c_str());
                    _s3Client = std::make_shared<Aws::S3::S3Client>(credentials, clientConfig);
                    std::cout << "SDK init: " << initTimer.elapsed() << std::endl;

                    if (dop > 1) {
                        auto downloadTimer = Timer();
                        Aws::S3::Model::HeadObjectRequest headObj;
                        headObj.WithBucket(bucket.c_str()).WithKey(key.c_str());
                        auto outcome = _s3Client->HeadObject(headObj);
                        if (!outcome.IsSuccess()) {
                            uassert(40167, str::stream() << "Failed to load an s3 object. Bucket: "
                                << bucket << " Key: " << key << " Error: " << outcome.GetError().GetMessage().c_str(), false);
                            Aws::ShutdownAPI(options);
                        }
                        int length = outcome.GetResult().GetContentLength();

                        std::vector<DownloadPart> parts;
                        int partSize = std::ceil(length/dop);
                        parts.reserve(dop);
                        for (int i=0; i<dop; ++i) {
                            parts.push_back({i * partSize, (i + 1) * partSize - 1, ""});
                        }
                        parts[dop - 1].end = length;

                        std::for_each(
                            std::execution::par_unseq,
                            parts.begin(),
                            parts.end(),
                            [&](auto&& item) {
                                downloadFile(_s3Client, bucket, key, item);
                            }
                        );
                        std::cout << "Download: " << downloadTimer.elapsed() << std::endl;

                        auto fileConcatTimer = Timer();
                        path = parts[0].path;
                        std::ofstream outMain;
                        outMain.open(path, std::ios::binary | std::ios::app);
                        for (int i=1; i<dop; ++i) {
                            outMain.seekp(0, std::ios_base::end);
                            std::ifstream inPart(parts[i].path, std::ios_base::binary);
                            outMain << inPart.rdbuf();
                        }
                        outMain.close();
                        std::cout << "File contact: " << fileConcatTimer.elapsed() << std::endl;
                    } else {
                        auto downloadTimer = Timer();
                        DownloadPart part = {-1, -1, "", ""};
                        auto result = downloadFile(_s3Client, bucket, key, part);
                        if (!result) {
                            Aws::ShutdownAPI(options);
                            uassert(40167, str::stream() << "Failed to load an s3 object. Bucket: "
                                << bucket << " Key: " << key << " Error: " << part.error, false);
                        }
                        path = part.path;
                    std::cout << "Download: " << downloadTimer.elapsed() << std::endl;
                    }

                    auto shutdownTimer = Timer();
                    Aws::ShutdownAPI(options);
                    std::cout << "Shutdown: " << shutdownTimer.elapsed() << std::endl;
                }

                try {
                    std::cout << "JSON file to parse: " << path << std::endl;
                    _jsonParser.load_many(path).get(_jsonFileStream);
                    _jsonFileIterator = std::make_unique<simdjson::dom::document_stream::iterator>(
                        _jsonFileStream.begin());
                }
                catch (...) {
                    uassert(40167, str::stream() << "Failed to initiate parsing the file " << path, false);
                }
            }

            if (*_jsonFileIterator != _jsonFileStream.end()) {
                BSONObjBuilder bsonBuilder;
                simdjson::dom::element thisDoc;

                try {
                    auto doc = **_jsonFileIterator;                    
                    auto errorCode = doc.get(thisDoc);
                    if (errorCode) {
                        uassert(40167, str::stream() << "Error during parsing a document: " << errorCode, false);
                    }
                    convert("UNUSED", thisDoc, bsonBuilder, false);
                    ++(*_jsonFileIterator);
                }
                catch (...) {
                    uassert(40167, str::stream() << "Failed to parse a document", false);
                }

                return Document(bsonBuilder.obj());
            }
        } else {
            uassert(40167, str::stream() << "Unsupported format", false);
        }
    }
    return GetNextResult::makeEOF();
}

Value DocumentSourceCollection::serialize(boost::optional<ExplainOptions::Verbosity> explain) const {
    return Value(Document{{getSourceName(), _collectionSpec}});
}

}  // namespace mongo


                        /*
                        const auto executor = Aws::MakeShared<Aws::Utils::Threading::PooledThreadExecutor>("Downloading-File", _collectionSpec["threads"].numberInt());

                        Aws::Transfer::TransferManagerConfiguration transferConfig(executor.get());
                        transferConfig.s3Client = s3Client;
                        transferConfig.transferInitiatedCallback =
                            [&](const Aws::Transfer::TransferManager*, const std::shared_ptr<const Aws::Transfer::TransferHandle>& handle) {};
//                        transferConfig.downloadProgressCallback =
//                            [](const Aws::Transfer::TransferManager*, const std::shared_ptr<const Aws::Transfer::TransferHandle>& handle) {
//                                std::cout << handle->GetBytesTransferred() << " of " << handle->GetBytesTotalSize() << "\n";
//                            };

                        const auto transmanager = Aws::Transfer::TransferManager::Create(transferConfig);

                        auto transferHandle = transmanager->DownloadFile(bucket.c_str(), key.c_str(), path.c_str());
                        transferHandle->WaitUntilFinished();
                        if (transferHandle->GetStatus() != Aws::Transfer::TransferStatus::COMPLETED) {
                            uassert(40167, str::stream() << "Failed to read an s3 object to " << path, false);
                        }
                        */
