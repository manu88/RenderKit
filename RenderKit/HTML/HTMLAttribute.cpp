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

const char* HTMLAttribute::getValue() const noexcept
{
    assert(_attr);
    
    return myhtml_attribute_value(_attr, nullptr);
}

size_t HTMLAttribute::getValueLength() const noexcept
{
    assert(_attr);
    
    size_t len = 0;
    
    if( myhtml_attribute_value(_attr, &len))
    {
        return len;
    }
    
    return 0;
}
