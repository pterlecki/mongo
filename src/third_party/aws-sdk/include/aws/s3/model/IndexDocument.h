﻿/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */

#pragma once
#include <aws/s3/S3_EXPORTS.h>
#include <aws/core/utils/memory/stl/AWSString.h>
#include <utility>

namespace Aws
{
namespace Utils
{
namespace Xml
{
  class XmlNode;
} // namespace Xml
} // namespace Utils
namespace S3
{
namespace Model
{

  /**
   * <p>Container for the <code>Suffix</code> element.</p><p><h3>See Also:</h3>   <a
   * href="http://docs.aws.amazon.com/goto/WebAPI/s3-2006-03-01/IndexDocument">AWS
   * API Reference</a></p>
   */
  class AWS_S3_API IndexDocument
  {
  public:
    IndexDocument();
    IndexDocument(const Aws::Utils::Xml::XmlNode& xmlNode);
    IndexDocument& operator=(const Aws::Utils::Xml::XmlNode& xmlNode);

    void AddToNode(Aws::Utils::Xml::XmlNode& parentNode) const;


    /**
     * <p>A suffix that is appended to a request that is for a directory on the website
     * endpoint (for example,if the suffix is index.html and you make a request to
     * samplebucket/images/ the data that is returned will be for the object with the
     * key name images/index.html) The suffix must not be empty and must not include a
     * slash character.</p>
     */
    inline const Aws::String& GetSuffix() const{ return m_suffix; }

    /**
     * <p>A suffix that is appended to a request that is for a directory on the website
     * endpoint (for example,if the suffix is index.html and you make a request to
     * samplebucket/images/ the data that is returned will be for the object with the
     * key name images/index.html) The suffix must not be empty and must not include a
     * slash character.</p>
     */
    inline bool SuffixHasBeenSet() const { return m_suffixHasBeenSet; }

    /**
     * <p>A suffix that is appended to a request that is for a directory on the website
     * endpoint (for example,if the suffix is index.html and you make a request to
     * samplebucket/images/ the data that is returned will be for the object with the
     * key name images/index.html) The suffix must not be empty and must not include a
     * slash character.</p>
     */
    inline void SetSuffix(const Aws::String& value) { m_suffixHasBeenSet = true; m_suffix = value; }

    /**
     * <p>A suffix that is appended to a request that is for a directory on the website
     * endpoint (for example,if the suffix is index.html and you make a request to
     * samplebucket/images/ the data that is returned will be for the object with the
     * key name images/index.html) The suffix must not be empty and must not include a
     * slash character.</p>
     */
    inline void SetSuffix(Aws::String&& value) { m_suffixHasBeenSet = true; m_suffix = std::move(value); }

    /**
     * <p>A suffix that is appended to a request that is for a directory on the website
     * endpoint (for example,if the suffix is index.html and you make a request to
     * samplebucket/images/ the data that is returned will be for the object with the
     * key name images/index.html) The suffix must not be empty and must not include a
     * slash character.</p>
     */
    inline void SetSuffix(const char* value) { m_suffixHasBeenSet = true; m_suffix.assign(value); }

    /**
     * <p>A suffix that is appended to a request that is for a directory on the website
     * endpoint (for example,if the suffix is index.html and you make a request to
     * samplebucket/images/ the data that is returned will be for the object with the
     * key name images/index.html) The suffix must not be empty and must not include a
     * slash character.</p>
     */
    inline IndexDocument& WithSuffix(const Aws::String& value) { SetSuffix(value); return *this;}

    /**
     * <p>A suffix that is appended to a request that is for a directory on the website
     * endpoint (for example,if the suffix is index.html and you make a request to
     * samplebucket/images/ the data that is returned will be for the object with the
     * key name images/index.html) The suffix must not be empty and must not include a
     * slash character.</p>
     */
    inline IndexDocument& WithSuffix(Aws::String&& value) { SetSuffix(std::move(value)); return *this;}

    /**
     * <p>A suffix that is appended to a request that is for a directory on the website
     * endpoint (for example,if the suffix is index.html and you make a request to
     * samplebucket/images/ the data that is returned will be for the object with the
     * key name images/index.html) The suffix must not be empty and must not include a
     * slash character.</p>
     */
    inline IndexDocument& WithSuffix(const char* value) { SetSuffix(value); return *this;}

  private:

    Aws::String m_suffix;
    bool m_suffixHasBeenSet;
  };

} // namespace Model
} // namespace S3
} // namespace Aws
