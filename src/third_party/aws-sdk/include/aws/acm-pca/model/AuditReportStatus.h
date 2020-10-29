﻿/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */

#pragma once
#include <aws/acm-pca/ACMPCA_EXPORTS.h>
#include <aws/core/utils/memory/stl/AWSString.h>

namespace Aws
{
namespace ACMPCA
{
namespace Model
{
  enum class AuditReportStatus
  {
    NOT_SET,
    CREATING,
    SUCCESS,
    FAILED
  };

namespace AuditReportStatusMapper
{
AWS_ACMPCA_API AuditReportStatus GetAuditReportStatusForName(const Aws::String& name);

AWS_ACMPCA_API Aws::String GetNameForAuditReportStatus(AuditReportStatus value);
} // namespace AuditReportStatusMapper
} // namespace Model
} // namespace ACMPCA
} // namespace Aws
