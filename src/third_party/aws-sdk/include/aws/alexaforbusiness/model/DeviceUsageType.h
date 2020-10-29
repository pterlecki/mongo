﻿/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */

#pragma once
#include <aws/alexaforbusiness/AlexaForBusiness_EXPORTS.h>
#include <aws/core/utils/memory/stl/AWSString.h>

namespace Aws
{
namespace AlexaForBusiness
{
namespace Model
{
  enum class DeviceUsageType
  {
    NOT_SET,
    VOICE
  };

namespace DeviceUsageTypeMapper
{
AWS_ALEXAFORBUSINESS_API DeviceUsageType GetDeviceUsageTypeForName(const Aws::String& name);

AWS_ALEXAFORBUSINESS_API Aws::String GetNameForDeviceUsageType(DeviceUsageType value);
} // namespace DeviceUsageTypeMapper
} // namespace Model
} // namespace AlexaForBusiness
} // namespace Aws
