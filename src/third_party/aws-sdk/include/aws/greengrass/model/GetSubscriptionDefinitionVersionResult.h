﻿/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */

#pragma once
#include <aws/greengrass/Greengrass_EXPORTS.h>
#include <aws/core/utils/memory/stl/AWSString.h>
#include <aws/greengrass/model/SubscriptionDefinitionVersion.h>
#include <utility>

namespace Aws
{
template<typename RESULT_TYPE>
class AmazonWebServiceResult;

namespace Utils
{
namespace Json
{
  class JsonValue;
} // namespace Json
} // namespace Utils
namespace Greengrass
{
namespace Model
{
  class AWS_GREENGRASS_API GetSubscriptionDefinitionVersionResult
  {
  public:
    GetSubscriptionDefinitionVersionResult();
    GetSubscriptionDefinitionVersionResult(const Aws::AmazonWebServiceResult<Aws::Utils::Json::JsonValue>& result);
    GetSubscriptionDefinitionVersionResult& operator=(const Aws::AmazonWebServiceResult<Aws::Utils::Json::JsonValue>& result);


    /**
     * The ARN of the subscription definition version.
     */
    inline const Aws::String& GetArn() const{ return m_arn; }

    /**
     * The ARN of the subscription definition version.
     */
    inline void SetArn(const Aws::String& value) { m_arn = value; }

    /**
     * The ARN of the subscription definition version.
     */
    inline void SetArn(Aws::String&& value) { m_arn = std::move(value); }

    /**
     * The ARN of the subscription definition version.
     */
    inline void SetArn(const char* value) { m_arn.assign(value); }

    /**
     * The ARN of the subscription definition version.
     */
    inline GetSubscriptionDefinitionVersionResult& WithArn(const Aws::String& value) { SetArn(value); return *this;}

    /**
     * The ARN of the subscription definition version.
     */
    inline GetSubscriptionDefinitionVersionResult& WithArn(Aws::String&& value) { SetArn(std::move(value)); return *this;}

    /**
     * The ARN of the subscription definition version.
     */
    inline GetSubscriptionDefinitionVersionResult& WithArn(const char* value) { SetArn(value); return *this;}


    /**
     * The time, in milliseconds since the epoch, when the subscription definition
     * version was created.
     */
    inline const Aws::String& GetCreationTimestamp() const{ return m_creationTimestamp; }

    /**
     * The time, in milliseconds since the epoch, when the subscription definition
     * version was created.
     */
    inline void SetCreationTimestamp(const Aws::String& value) { m_creationTimestamp = value; }

    /**
     * The time, in milliseconds since the epoch, when the subscription definition
     * version was created.
     */
    inline void SetCreationTimestamp(Aws::String&& value) { m_creationTimestamp = std::move(value); }

    /**
     * The time, in milliseconds since the epoch, when the subscription definition
     * version was created.
     */
    inline void SetCreationTimestamp(const char* value) { m_creationTimestamp.assign(value); }

    /**
     * The time, in milliseconds since the epoch, when the subscription definition
     * version was created.
     */
    inline GetSubscriptionDefinitionVersionResult& WithCreationTimestamp(const Aws::String& value) { SetCreationTimestamp(value); return *this;}

    /**
     * The time, in milliseconds since the epoch, when the subscription definition
     * version was created.
     */
    inline GetSubscriptionDefinitionVersionResult& WithCreationTimestamp(Aws::String&& value) { SetCreationTimestamp(std::move(value)); return *this;}

    /**
     * The time, in milliseconds since the epoch, when the subscription definition
     * version was created.
     */
    inline GetSubscriptionDefinitionVersionResult& WithCreationTimestamp(const char* value) { SetCreationTimestamp(value); return *this;}


    /**
     * Information about the subscription definition version.
     */
    inline const SubscriptionDefinitionVersion& GetDefinition() const{ return m_definition; }

    /**
     * Information about the subscription definition version.
     */
    inline void SetDefinition(const SubscriptionDefinitionVersion& value) { m_definition = value; }

    /**
     * Information about the subscription definition version.
     */
    inline void SetDefinition(SubscriptionDefinitionVersion&& value) { m_definition = std::move(value); }

    /**
     * Information about the subscription definition version.
     */
    inline GetSubscriptionDefinitionVersionResult& WithDefinition(const SubscriptionDefinitionVersion& value) { SetDefinition(value); return *this;}

    /**
     * Information about the subscription definition version.
     */
    inline GetSubscriptionDefinitionVersionResult& WithDefinition(SubscriptionDefinitionVersion&& value) { SetDefinition(std::move(value)); return *this;}


    /**
     * The ID of the subscription definition version.
     */
    inline const Aws::String& GetId() const{ return m_id; }

    /**
     * The ID of the subscription definition version.
     */
    inline void SetId(const Aws::String& value) { m_id = value; }

    /**
     * The ID of the subscription definition version.
     */
    inline void SetId(Aws::String&& value) { m_id = std::move(value); }

    /**
     * The ID of the subscription definition version.
     */
    inline void SetId(const char* value) { m_id.assign(value); }

    /**
     * The ID of the subscription definition version.
     */
    inline GetSubscriptionDefinitionVersionResult& WithId(const Aws::String& value) { SetId(value); return *this;}

    /**
     * The ID of the subscription definition version.
     */
    inline GetSubscriptionDefinitionVersionResult& WithId(Aws::String&& value) { SetId(std::move(value)); return *this;}

    /**
     * The ID of the subscription definition version.
     */
    inline GetSubscriptionDefinitionVersionResult& WithId(const char* value) { SetId(value); return *this;}


    /**
     * The token for the next set of results, or ''null'' if there are no additional
     * results.
     */
    inline const Aws::String& GetNextToken() const{ return m_nextToken; }

    /**
     * The token for the next set of results, or ''null'' if there are no additional
     * results.
     */
    inline void SetNextToken(const Aws::String& value) { m_nextToken = value; }

    /**
     * The token for the next set of results, or ''null'' if there are no additional
     * results.
     */
    inline void SetNextToken(Aws::String&& value) { m_nextToken = std::move(value); }

    /**
     * The token for the next set of results, or ''null'' if there are no additional
     * results.
     */
    inline void SetNextToken(const char* value) { m_nextToken.assign(value); }

    /**
     * The token for the next set of results, or ''null'' if there are no additional
     * results.
     */
    inline GetSubscriptionDefinitionVersionResult& WithNextToken(const Aws::String& value) { SetNextToken(value); return *this;}

    /**
     * The token for the next set of results, or ''null'' if there are no additional
     * results.
     */
    inline GetSubscriptionDefinitionVersionResult& WithNextToken(Aws::String&& value) { SetNextToken(std::move(value)); return *this;}

    /**
     * The token for the next set of results, or ''null'' if there are no additional
     * results.
     */
    inline GetSubscriptionDefinitionVersionResult& WithNextToken(const char* value) { SetNextToken(value); return *this;}


    /**
     * The version of the subscription definition version.
     */
    inline const Aws::String& GetVersion() const{ return m_version; }

    /**
     * The version of the subscription definition version.
     */
    inline void SetVersion(const Aws::String& value) { m_version = value; }

    /**
     * The version of the subscription definition version.
     */
    inline void SetVersion(Aws::String&& value) { m_version = std::move(value); }

    /**
     * The version of the subscription definition version.
     */
    inline void SetVersion(const char* value) { m_version.assign(value); }

    /**
     * The version of the subscription definition version.
     */
    inline GetSubscriptionDefinitionVersionResult& WithVersion(const Aws::String& value) { SetVersion(value); return *this;}

    /**
     * The version of the subscription definition version.
     */
    inline GetSubscriptionDefinitionVersionResult& WithVersion(Aws::String&& value) { SetVersion(std::move(value)); return *this;}

    /**
     * The version of the subscription definition version.
     */
    inline GetSubscriptionDefinitionVersionResult& WithVersion(const char* value) { SetVersion(value); return *this;}

  private:

    Aws::String m_arn;

    Aws::String m_creationTimestamp;

    SubscriptionDefinitionVersion m_definition;

    Aws::String m_id;

    Aws::String m_nextToken;

    Aws::String m_version;
  };

} // namespace Model
} // namespace Greengrass
} // namespace Aws
