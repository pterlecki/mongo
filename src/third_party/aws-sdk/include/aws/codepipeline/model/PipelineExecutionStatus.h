﻿/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */

#pragma once
#include <aws/codepipeline/CodePipeline_EXPORTS.h>
#include <aws/core/utils/memory/stl/AWSString.h>

namespace Aws
{
namespace CodePipeline
{
namespace Model
{
  enum class PipelineExecutionStatus
  {
    NOT_SET,
    InProgress,
    Stopped,
    Stopping,
    Succeeded,
    Superseded,
    Failed
  };

namespace PipelineExecutionStatusMapper
{
AWS_CODEPIPELINE_API PipelineExecutionStatus GetPipelineExecutionStatusForName(const Aws::String& name);

AWS_CODEPIPELINE_API Aws::String GetNameForPipelineExecutionStatus(PipelineExecutionStatus value);
} // namespace PipelineExecutionStatusMapper
} // namespace Model
} // namespace CodePipeline
} // namespace Aws
