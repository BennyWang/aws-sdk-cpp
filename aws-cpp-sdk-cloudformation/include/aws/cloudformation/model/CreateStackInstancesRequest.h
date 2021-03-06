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
#include <aws/cloudformation/CloudFormation_EXPORTS.h>
#include <aws/cloudformation/CloudFormationRequest.h>
#include <aws/core/utils/memory/stl/AWSString.h>
#include <aws/core/utils/memory/stl/AWSVector.h>
#include <aws/cloudformation/model/StackSetOperationPreferences.h>
#include <utility>
#include <aws/core/utils/UUID.h>

namespace Aws
{
namespace CloudFormation
{
namespace Model
{

  /**
   */
  class AWS_CLOUDFORMATION_API CreateStackInstancesRequest : public CloudFormationRequest
  {
  public:
    CreateStackInstancesRequest();
    
    // Service request name is the Operation name which will send this request out,
    // each operation should has unique request name, so that we can get operation's name from this request.
    // Note: this is not true for response, multiple operations may have the same response name,
    // so we can not get operation's name from response.
    inline virtual const char* GetServiceRequestName() const override { return "CreateStackInstances"; }

    Aws::String SerializePayload() const override;

  protected:
    void DumpBodyToUrl(Aws::Http::URI& uri ) const override;

  public:

    /**
     * <p>The name or unique ID of the stack set that you want to create stack
     * instances from.</p>
     */
    inline const Aws::String& GetStackSetName() const{ return m_stackSetName; }

    /**
     * <p>The name or unique ID of the stack set that you want to create stack
     * instances from.</p>
     */
    inline void SetStackSetName(const Aws::String& value) { m_stackSetNameHasBeenSet = true; m_stackSetName = value; }

    /**
     * <p>The name or unique ID of the stack set that you want to create stack
     * instances from.</p>
     */
    inline void SetStackSetName(Aws::String&& value) { m_stackSetNameHasBeenSet = true; m_stackSetName = std::move(value); }

    /**
     * <p>The name or unique ID of the stack set that you want to create stack
     * instances from.</p>
     */
    inline void SetStackSetName(const char* value) { m_stackSetNameHasBeenSet = true; m_stackSetName.assign(value); }

    /**
     * <p>The name or unique ID of the stack set that you want to create stack
     * instances from.</p>
     */
    inline CreateStackInstancesRequest& WithStackSetName(const Aws::String& value) { SetStackSetName(value); return *this;}

    /**
     * <p>The name or unique ID of the stack set that you want to create stack
     * instances from.</p>
     */
    inline CreateStackInstancesRequest& WithStackSetName(Aws::String&& value) { SetStackSetName(std::move(value)); return *this;}

    /**
     * <p>The name or unique ID of the stack set that you want to create stack
     * instances from.</p>
     */
    inline CreateStackInstancesRequest& WithStackSetName(const char* value) { SetStackSetName(value); return *this;}


    /**
     * <p>The names of one or more AWS accounts that you want to create stack instances
     * in the specified region(s) for.</p>
     */
    inline const Aws::Vector<Aws::String>& GetAccounts() const{ return m_accounts; }

    /**
     * <p>The names of one or more AWS accounts that you want to create stack instances
     * in the specified region(s) for.</p>
     */
    inline void SetAccounts(const Aws::Vector<Aws::String>& value) { m_accountsHasBeenSet = true; m_accounts = value; }

    /**
     * <p>The names of one or more AWS accounts that you want to create stack instances
     * in the specified region(s) for.</p>
     */
    inline void SetAccounts(Aws::Vector<Aws::String>&& value) { m_accountsHasBeenSet = true; m_accounts = std::move(value); }

    /**
     * <p>The names of one or more AWS accounts that you want to create stack instances
     * in the specified region(s) for.</p>
     */
    inline CreateStackInstancesRequest& WithAccounts(const Aws::Vector<Aws::String>& value) { SetAccounts(value); return *this;}

    /**
     * <p>The names of one or more AWS accounts that you want to create stack instances
     * in the specified region(s) for.</p>
     */
    inline CreateStackInstancesRequest& WithAccounts(Aws::Vector<Aws::String>&& value) { SetAccounts(std::move(value)); return *this;}

    /**
     * <p>The names of one or more AWS accounts that you want to create stack instances
     * in the specified region(s) for.</p>
     */
    inline CreateStackInstancesRequest& AddAccounts(const Aws::String& value) { m_accountsHasBeenSet = true; m_accounts.push_back(value); return *this; }

    /**
     * <p>The names of one or more AWS accounts that you want to create stack instances
     * in the specified region(s) for.</p>
     */
    inline CreateStackInstancesRequest& AddAccounts(Aws::String&& value) { m_accountsHasBeenSet = true; m_accounts.push_back(std::move(value)); return *this; }

    /**
     * <p>The names of one or more AWS accounts that you want to create stack instances
     * in the specified region(s) for.</p>
     */
    inline CreateStackInstancesRequest& AddAccounts(const char* value) { m_accountsHasBeenSet = true; m_accounts.push_back(value); return *this; }


    /**
     * <p>The names of one or more regions where you want to create stack instances
     * using the specified AWS account(s). </p>
     */
    inline const Aws::Vector<Aws::String>& GetRegions() const{ return m_regions; }

    /**
     * <p>The names of one or more regions where you want to create stack instances
     * using the specified AWS account(s). </p>
     */
    inline void SetRegions(const Aws::Vector<Aws::String>& value) { m_regionsHasBeenSet = true; m_regions = value; }

    /**
     * <p>The names of one or more regions where you want to create stack instances
     * using the specified AWS account(s). </p>
     */
    inline void SetRegions(Aws::Vector<Aws::String>&& value) { m_regionsHasBeenSet = true; m_regions = std::move(value); }

    /**
     * <p>The names of one or more regions where you want to create stack instances
     * using the specified AWS account(s). </p>
     */
    inline CreateStackInstancesRequest& WithRegions(const Aws::Vector<Aws::String>& value) { SetRegions(value); return *this;}

    /**
     * <p>The names of one or more regions where you want to create stack instances
     * using the specified AWS account(s). </p>
     */
    inline CreateStackInstancesRequest& WithRegions(Aws::Vector<Aws::String>&& value) { SetRegions(std::move(value)); return *this;}

    /**
     * <p>The names of one or more regions where you want to create stack instances
     * using the specified AWS account(s). </p>
     */
    inline CreateStackInstancesRequest& AddRegions(const Aws::String& value) { m_regionsHasBeenSet = true; m_regions.push_back(value); return *this; }

    /**
     * <p>The names of one or more regions where you want to create stack instances
     * using the specified AWS account(s). </p>
     */
    inline CreateStackInstancesRequest& AddRegions(Aws::String&& value) { m_regionsHasBeenSet = true; m_regions.push_back(std::move(value)); return *this; }

    /**
     * <p>The names of one or more regions where you want to create stack instances
     * using the specified AWS account(s). </p>
     */
    inline CreateStackInstancesRequest& AddRegions(const char* value) { m_regionsHasBeenSet = true; m_regions.push_back(value); return *this; }


    /**
     * <p>Preferences for how AWS CloudFormation performs this stack set operation.</p>
     */
    inline const StackSetOperationPreferences& GetOperationPreferences() const{ return m_operationPreferences; }

    /**
     * <p>Preferences for how AWS CloudFormation performs this stack set operation.</p>
     */
    inline void SetOperationPreferences(const StackSetOperationPreferences& value) { m_operationPreferencesHasBeenSet = true; m_operationPreferences = value; }

    /**
     * <p>Preferences for how AWS CloudFormation performs this stack set operation.</p>
     */
    inline void SetOperationPreferences(StackSetOperationPreferences&& value) { m_operationPreferencesHasBeenSet = true; m_operationPreferences = std::move(value); }

    /**
     * <p>Preferences for how AWS CloudFormation performs this stack set operation.</p>
     */
    inline CreateStackInstancesRequest& WithOperationPreferences(const StackSetOperationPreferences& value) { SetOperationPreferences(value); return *this;}

    /**
     * <p>Preferences for how AWS CloudFormation performs this stack set operation.</p>
     */
    inline CreateStackInstancesRequest& WithOperationPreferences(StackSetOperationPreferences&& value) { SetOperationPreferences(std::move(value)); return *this;}


    /**
     * <p>The unique identifier for this stack set operation. </p> <p>The operation ID
     * also functions as an idempotency token, to ensure that AWS CloudFormation
     * performs the stack set operation only once, even if you retry the request
     * multiple times. You might retry stack set operation requests to ensure that AWS
     * CloudFormation successfully received them.</p> <p>If you don't specify an
     * operation ID, the SDK generates one automatically. </p> <p>Repeating this stack
     * set operation with a new operation ID retries all stack instances whose status
     * is <code>OUTDATED</code>. </p>
     */
    inline const Aws::String& GetOperationId() const{ return m_operationId; }

    /**
     * <p>The unique identifier for this stack set operation. </p> <p>The operation ID
     * also functions as an idempotency token, to ensure that AWS CloudFormation
     * performs the stack set operation only once, even if you retry the request
     * multiple times. You might retry stack set operation requests to ensure that AWS
     * CloudFormation successfully received them.</p> <p>If you don't specify an
     * operation ID, the SDK generates one automatically. </p> <p>Repeating this stack
     * set operation with a new operation ID retries all stack instances whose status
     * is <code>OUTDATED</code>. </p>
     */
    inline void SetOperationId(const Aws::String& value) { m_operationIdHasBeenSet = true; m_operationId = value; }

    /**
     * <p>The unique identifier for this stack set operation. </p> <p>The operation ID
     * also functions as an idempotency token, to ensure that AWS CloudFormation
     * performs the stack set operation only once, even if you retry the request
     * multiple times. You might retry stack set operation requests to ensure that AWS
     * CloudFormation successfully received them.</p> <p>If you don't specify an
     * operation ID, the SDK generates one automatically. </p> <p>Repeating this stack
     * set operation with a new operation ID retries all stack instances whose status
     * is <code>OUTDATED</code>. </p>
     */
    inline void SetOperationId(Aws::String&& value) { m_operationIdHasBeenSet = true; m_operationId = std::move(value); }

    /**
     * <p>The unique identifier for this stack set operation. </p> <p>The operation ID
     * also functions as an idempotency token, to ensure that AWS CloudFormation
     * performs the stack set operation only once, even if you retry the request
     * multiple times. You might retry stack set operation requests to ensure that AWS
     * CloudFormation successfully received them.</p> <p>If you don't specify an
     * operation ID, the SDK generates one automatically. </p> <p>Repeating this stack
     * set operation with a new operation ID retries all stack instances whose status
     * is <code>OUTDATED</code>. </p>
     */
    inline void SetOperationId(const char* value) { m_operationIdHasBeenSet = true; m_operationId.assign(value); }

    /**
     * <p>The unique identifier for this stack set operation. </p> <p>The operation ID
     * also functions as an idempotency token, to ensure that AWS CloudFormation
     * performs the stack set operation only once, even if you retry the request
     * multiple times. You might retry stack set operation requests to ensure that AWS
     * CloudFormation successfully received them.</p> <p>If you don't specify an
     * operation ID, the SDK generates one automatically. </p> <p>Repeating this stack
     * set operation with a new operation ID retries all stack instances whose status
     * is <code>OUTDATED</code>. </p>
     */
    inline CreateStackInstancesRequest& WithOperationId(const Aws::String& value) { SetOperationId(value); return *this;}

    /**
     * <p>The unique identifier for this stack set operation. </p> <p>The operation ID
     * also functions as an idempotency token, to ensure that AWS CloudFormation
     * performs the stack set operation only once, even if you retry the request
     * multiple times. You might retry stack set operation requests to ensure that AWS
     * CloudFormation successfully received them.</p> <p>If you don't specify an
     * operation ID, the SDK generates one automatically. </p> <p>Repeating this stack
     * set operation with a new operation ID retries all stack instances whose status
     * is <code>OUTDATED</code>. </p>
     */
    inline CreateStackInstancesRequest& WithOperationId(Aws::String&& value) { SetOperationId(std::move(value)); return *this;}

    /**
     * <p>The unique identifier for this stack set operation. </p> <p>The operation ID
     * also functions as an idempotency token, to ensure that AWS CloudFormation
     * performs the stack set operation only once, even if you retry the request
     * multiple times. You might retry stack set operation requests to ensure that AWS
     * CloudFormation successfully received them.</p> <p>If you don't specify an
     * operation ID, the SDK generates one automatically. </p> <p>Repeating this stack
     * set operation with a new operation ID retries all stack instances whose status
     * is <code>OUTDATED</code>. </p>
     */
    inline CreateStackInstancesRequest& WithOperationId(const char* value) { SetOperationId(value); return *this;}

  private:

    Aws::String m_stackSetName;
    bool m_stackSetNameHasBeenSet;

    Aws::Vector<Aws::String> m_accounts;
    bool m_accountsHasBeenSet;

    Aws::Vector<Aws::String> m_regions;
    bool m_regionsHasBeenSet;

    StackSetOperationPreferences m_operationPreferences;
    bool m_operationPreferencesHasBeenSet;

    Aws::String m_operationId;
    bool m_operationIdHasBeenSet;
  };

} // namespace Model
} // namespace CloudFormation
} // namespace Aws
