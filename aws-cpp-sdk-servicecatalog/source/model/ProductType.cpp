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

#include <aws/servicecatalog/model/ProductType.h>
#include <aws/core/utils/HashingUtils.h>
#include <aws/core/Globals.h>
#include <aws/core/utils/EnumParseOverflowContainer.h>

using namespace Aws::Utils;


namespace Aws
{
  namespace ServiceCatalog
  {
    namespace Model
    {
      namespace ProductTypeMapper
      {

        static const int CLOUD_FORMATION_TEMPLATE_HASH = HashingUtils::HashString("CLOUD_FORMATION_TEMPLATE");
        static const int MARKETPLACE_HASH = HashingUtils::HashString("MARKETPLACE");


        ProductType GetProductTypeForName(const Aws::String& name)
        {
          int hashCode = HashingUtils::HashString(name.c_str());
          if (hashCode == CLOUD_FORMATION_TEMPLATE_HASH)
          {
            return ProductType::CLOUD_FORMATION_TEMPLATE;
          }
          else if (hashCode == MARKETPLACE_HASH)
          {
            return ProductType::MARKETPLACE;
          }
          EnumParseOverflowContainer* overflowContainer = Aws::GetEnumOverflowContainer();
          if(overflowContainer)
          {
            overflowContainer->StoreOverflow(hashCode, name);
            return static_cast<ProductType>(hashCode);
          }

          return ProductType::NOT_SET;
        }

        Aws::String GetNameForProductType(ProductType enumValue)
        {
          switch(enumValue)
          {
          case ProductType::CLOUD_FORMATION_TEMPLATE:
            return "CLOUD_FORMATION_TEMPLATE";
          case ProductType::MARKETPLACE:
            return "MARKETPLACE";
          default:
            EnumParseOverflowContainer* overflowContainer = Aws::GetEnumOverflowContainer();
            if(overflowContainer)
            {
              return overflowContainer->RetrieveOverflow(static_cast<int>(enumValue));
            }

            return "";
          }
        }

      } // namespace ProductTypeMapper
    } // namespace Model
  } // namespace ServiceCatalog
} // namespace Aws
