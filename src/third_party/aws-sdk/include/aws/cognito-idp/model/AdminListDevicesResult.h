﻿/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */

#pragma once
#include <aws/cognito-idp/CognitoIdentityProvider_EXPORTS.h>
#include <aws/core/utils/memory/stl/AWSVector.h>
#include <aws/core/utils/memory/stl/AWSString.h>
#include <aws/cognito-idp/model/DeviceType.h>
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
namespace CognitoIdentityProvider
{
namespace Model
{
  /**
   * <p>Lists the device's response, as an administrator.</p><p><h3>See Also:</h3>  
   * <a
   * href="http://docs.aws.amazon.com/goto/WebAPI/cognito-idp-2016-04-18/AdminListDevicesResponse">AWS
   * API Reference</a></p>
   */
  class AWS_COGNITOIDENTITYPROVIDER_API AdminListDevicesResult
  {
  public:
    AdminListDevicesResult();
    AdminListDevicesResult(const Aws::AmazonWebServiceResult<Aws::Utils::Json::JsonValue>& result);
    AdminListDevicesResult& operator=(const Aws::AmazonWebServiceResult<Aws::Utils::Json::JsonValue>& result);


    /**
     * <p>The devices in the list of devices response.</p>
     */
    inline const Aws::Vector<DeviceType>& GetDevices() const{ return m_devices; }

    /**
     * <p>The devices in the list of devices response.</p>
     */
    inline void SetDevices(const Aws::Vector<DeviceType>& value) { m_devices = value; }

    /**
     * <p>The devices in the list of devices response.</p>
     */
    inline void SetDevices(Aws::Vector<DeviceType>&& value) { m_devices = std::move(value); }

    /**
     * <p>The devices in the list of devices response.</p>
     */
    inline AdminListDevicesResult& WithDevices(const Aws::Vector<DeviceType>& value) { SetDevices(value); return *this;}

    /**
     * <p>The devices in the list of devices response.</p>
     */
    inline AdminListDevicesResult& WithDevices(Aws::Vector<DeviceType>&& value) { SetDevices(std::move(value)); return *this;}

    /**
     * <p>The devices in the list of devices response.</p>
     */
    inline AdminListDevicesResult& AddDevices(const DeviceType& value) { m_devices.push_back(value); return *this; }

    /**
     * <p>The devices in the list of devices response.</p>
     */
    inline AdminListDevicesResult& AddDevices(DeviceType&& value) { m_devices.push_back(std::move(value)); return *this; }


    /**
     * <p>The pagination token.</p>
     */
    inline const Aws::String& GetPaginationToken() const{ return m_paginationToken; }

    /**
     * <p>The pagination token.</p>
     */
    inline void SetPaginationToken(const Aws::String& value) { m_paginationToken = value; }

    /**
     * <p>The pagination token.</p>
     */
    inline void SetPaginationToken(Aws::String&& value) { m_paginationToken = std::move(value); }

    /**
     * <p>The pagination token.</p>
     */
    inline void SetPaginationToken(const char* value) { m_paginationToken.assign(value); }

    /**
     * <p>The pagination token.</p>
     */
    inline AdminListDevicesResult& WithPaginationToken(const Aws::String& value) { SetPaginationToken(value); return *this;}

    /**
     * <p>The pagination token.</p>
     */
    inline AdminListDevicesResult& WithPaginationToken(Aws::String&& value) { SetPaginationToken(std::move(value)); return *this;}

    /**
     * <p>The pagination token.</p>
     */
    inline AdminListDevicesResult& WithPaginationToken(const char* value) { SetPaginationToken(value); return *this;}

  private:

    Aws::Vector<DeviceType> m_devices;

    Aws::String m_paginationToken;
  };

} // namespace Model
} // namespace CognitoIdentityProvider
} // namespace Aws
