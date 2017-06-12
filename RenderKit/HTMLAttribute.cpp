//
//  HTMLAttribute.cpp
//  RenderKit
//
//  Created by Manuel Deneu on 12/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include <assert.h>
#include "HTMLAttribute.hpp"


std::string HTMLAttribute::getName() const noexcept
{
    assert(_attr);
    
    return myhtml_attribute_key(_attr, nullptr);
}
