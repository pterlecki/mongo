﻿/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */

#pragma once
#include <aws/apigateway/APIGateway_EXPORTS.h>
#include <aws/apigateway/APIGatewayRequest.h>
#include <aws/core/utils/memory/stl/AWSString.h>
#include <utility>

namespace Aws
{
namespace APIGateway
{
namespace Model
{

  /**
   * <p>Represents a request to get the integration configuration.</p><p><h3>See
   * Also:</h3>   <a
   * href="http://docs.aws.amazon.com/goto/WebAPI/apigateway-2015-07-09/GetIntegrationRequest">AWS
   * API Reference</a></p>
   */
  class AWS_APIGATEWAY_API GetIntegrationRequest : public APIGatewayRequest
  {
  public:
    GetIntegrationRequest();

    // Service request name is the Operation name which will send this request out,
    // each operation should has unique request name, so that we can get operation's name from this request.
    // Note: this is not true for response, multiple operations may have the same response name,
    // so we can not get operation's name from response.
    inline virtual const char* GetServiceRequestName() const override { return "GetIntegration"; }

    Aws::String SerializePayload() const override;


    /**
     * <p>[Required] The string identifier of the associated <a>RestApi</a>.</p>
     */
    inline const Aws::String& GetRestApiId() const{ return m_restApiId; }

    /**
     * <p>[Required] The string identifier of the associated <a>RestApi</a>.</p>
     */
    inline bool RestApiIdHasBeenSet() const { return m_restApiIdHasBeenSet; }

    /**
     * <p>[Required] The string identifier of the associated <a>RestApi</a>.</p>
     */
    inline void SetRestApiId(const Aws::String& value) { m_restApiIdHasBeenSet = true; m_restApiId = value; }

    /**
     * <p>[Required] The string identifier of the associated <a>RestApi</a>.</p>
     */
    inline void SetRestApiId(Aws::String&& value) { m_restApiIdHasBeenSet = true; m_restApiId = std::move(value); }

    /**
     * <p>[Required] The string identifier of the associated <a>RestApi</a>.</p>
     */
    inline void SetRestApiId(const char* value) { m_restApiIdHasBeenSet = true; m_restApiId.assign(value); }

    /**
     * <p>[Required] The string identifier of the associated <a>RestApi</a>.</p>
     */
    inline GetIntegrationRequest& WithRestApiId(const Aws::String& value) { SetRestApiId(value); return *this;}

    /**
     * <p>[Required] The string identifier of the associated <a>RestApi</a>.</p>
     */
    inline GetIntegrationRequest& WithRestApiId(Aws::String&& value) { SetRestApiId(std::move(value)); return *this;}

    /**
     * <p>[Required] The string identifier of the associated <a>RestApi</a>.</p>
     */
    inline GetIntegrationRequest& WithRestApiId(const char* value) { SetRestApiId(value); return *this;}


    /**
     * <p>[Required] Specifies a get integration request's resource identifier</p>
     */
    inline const Aws::String& GetResourceId() const{ return m_resourceId; }

    /**
     * <p>[Required] Specifies a get integration request's resource identifier</p>
     */
    inline bool ResourceIdHasBeenSet() const { return m_resourceIdHasBeenSet; }

    /**
     * <p>[Required] Specifies a get integration request's resource identifier</p>
     */
    inline void SetResourceId(const Aws::String& value) { m_resourceIdHasBeenSet = true; m_resourceId = value; }

    /**
     * <p>[Required] Specifies a get integration request's resource identifier</p>
     */
    inline void SetResourceId(Aws::String&& value) { m_resourceIdHasBeenSet = true; m_resourceId = std::move(value); }

    /**
     * <p>[Required] Specifies a get integration request's resource identifier</p>
     */
    inline void SetResourceId(const char* value) { m_resourceIdHasBeenSet = true; m_resourceId.assign(value); }

    /**
     * <p>[Required] Specifies a get integration request's resource identifier</p>
     */
    inline GetIntegrationRequest& WithResourceId(const Aws::String& value) { SetResourceId(value); return *this;}

    /**
     * <p>[Required] Specifies a get integration request's resource identifier</p>
     */
    inline GetIntegrationRequest& WithResourceId(Aws::String&& value) { SetResourceId(std::move(value)); return *this;}

    /**
     * <p>[Required] Specifies a get integration request's resource identifier</p>
     */
    inline GetIntegrationRequest& WithResourceId(const char* value) { SetResourceId(value); return *this;}


    /**
     * <p>[Required] Specifies a get integration request's HTTP method.</p>
     */
    inline const Aws::String& GetHttpMethod() const{ return m_httpMethod; }

    /**
     * <p>[Required] Specifies a get integration request's HTTP method.</p>
     */
    inline bool HttpMethodHasBeenSet() const { return m_httpMethodHasBeenSet; }

    /**
     * <p>[Required] Specifies a get integration request's HTTP method.</p>
     */
    inline void SetHttpMethod(const Aws::String& value) { m_httpMethodHasBeenSet = true; m_httpMethod = value; }

    /**
     * <p>[Required] Specifies a get integration request's HTTP method.</p>
     */
    inline void SetHttpMethod(Aws::String&& value) { m_httpMethodHasBeenSet = true; m_httpMethod = std::move(value); }

    /**
     * <p>[Required] Specifies a get integration request's HTTP method.</p>
     */
    inline void SetHttpMethod(const char* value) { m_httpMethodHasBeenSet = true; m_httpMethod.assign(value); }

    /**
     * <p>[Required] Specifies a get integration request's HTTP method.</p>
     */
    inline GetIntegrationRequest& WithHttpMethod(const Aws::String& value) { SetHttpMethod(value); return *this;}

    /**
     * <p>[Required] Specifies a get integration request's HTTP method.</p>
     */
    inline GetIntegrationRequest& WithHttpMethod(Aws::String&& value) { SetHttpMethod(std::move(value)); return *this;}

    /**
     * <p>[Required] Specifies a get integration request's HTTP method.</p>
     */
    inline GetIntegrationRequest& WithHttpMethod(const char* value) { SetHttpMethod(value); return *this;}

  private:

    Aws::String m_restApiId;
    bool m_restApiIdHasBeenSet;

    Aws::String m_resourceId;
    bool m_resourceIdHasBeenSet;

    Aws::String m_httpMethod;
    bool m_httpMethodHasBeenSet;
  };

} // namespace Model
} // namespace APIGateway
} // namespace Aws
