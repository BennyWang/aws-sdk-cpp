﻿/*
* Copyright 2010-2017 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* Licensed under the Apache License, Version 2.0 (the "License").
* You may not use this file except in compliance with the License.
* A copy of the License is located at
*
*  http://aws.amazon.com/apache2.0
*
* or in the "license" file accompanying this file. This file is distributed
* on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
* express or implied. See the License for the specific language governing
* permissions and limitations under the License.
*/

#pragma once
#include <aws/pinpoint/Pinpoint_EXPORTS.h>
#include <aws/pinpoint/PinpointRequest.h>
#include <aws/core/utils/memory/stl/AWSString.h>
#include <aws/pinpoint/model/WriteEventStream.h>
#include <utility>

namespace Aws
{
namespace Pinpoint
{
namespace Model
{

  /**
   * PutEventStream Request
   */
  class AWS_PINPOINT_API PutEventStreamRequest : public PinpointRequest
  {
  public:
    PutEventStreamRequest();
    
    // Service request name is the Operation name which will send this request out,
    // each operation should has unique request name, so that we can get operation's name from this request.
    // Note: this is not true for response, multiple operations may have the same response name,
    // so we can not get operation's name from response.
    inline virtual const char* GetServiceRequestName() const override { return "PutEventStream"; }

    Aws::String SerializePayload() const override;


    /**
     * ApplicationId
     */
    inline const Aws::String& GetApplicationId() const{ return m_applicationId; }

    /**
     * ApplicationId
     */
    inline void SetApplicationId(const Aws::String& value) { m_applicationIdHasBeenSet = true; m_applicationId = value; }

    /**
     * ApplicationId
     */
    inline void SetApplicationId(Aws::String&& value) { m_applicationIdHasBeenSet = true; m_applicationId = std::move(value); }

    /**
     * ApplicationId
     */
    inline void SetApplicationId(const char* value) { m_applicationIdHasBeenSet = true; m_applicationId.assign(value); }

    /**
     * ApplicationId
     */
    inline PutEventStreamRequest& WithApplicationId(const Aws::String& value) { SetApplicationId(value); return *this;}

    /**
     * ApplicationId
     */
    inline PutEventStreamRequest& WithApplicationId(Aws::String&& value) { SetApplicationId(std::move(value)); return *this;}

    /**
     * ApplicationId
     */
    inline PutEventStreamRequest& WithApplicationId(const char* value) { SetApplicationId(value); return *this;}


    /**
     * EventStream to write.
     */
    inline const WriteEventStream& GetWriteEventStream() const{ return m_writeEventStream; }

    /**
     * EventStream to write.
     */
    inline void SetWriteEventStream(const WriteEventStream& value) { m_writeEventStreamHasBeenSet = true; m_writeEventStream = value; }

    /**
     * EventStream to write.
     */
    inline void SetWriteEventStream(WriteEventStream&& value) { m_writeEventStreamHasBeenSet = true; m_writeEventStream = std::move(value); }

    /**
     * EventStream to write.
     */
    inline PutEventStreamRequest& WithWriteEventStream(const WriteEventStream& value) { SetWriteEventStream(value); return *this;}

    /**
     * EventStream to write.
     */
    inline PutEventStreamRequest& WithWriteEventStream(WriteEventStream&& value) { SetWriteEventStream(std::move(value)); return *this;}

  private:

    Aws::String m_applicationId;
    bool m_applicationIdHasBeenSet;

    WriteEventStream m_writeEventStream;
    bool m_writeEventStreamHasBeenSet;
  };

} // namespace Model
} // namespace Pinpoint
} // namespace Aws
