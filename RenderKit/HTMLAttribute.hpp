//
//  HTMLAttribute.hpp
//  RenderKit
//
//  Created by Manuel Deneu on 12/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef HTMLAttribute_hpp
#define HTMLAttribute_hpp

#include <string>
#include <myhtml/myhtml.h>

class HTMLAttribute
{
public:
    
    HTMLAttribute(myhtml_tree_attr_t * attr):
    _attr(attr)
    {}
    
    bool isValid() const noexcept
    {
        return _attr != nullptr;
    }
    
    std::string getName() const noexcept;
    const char* getValue() const noexcept;
    size_t getValueLength() const noexcept;
    
    myhtml_tree_attr_t * _attr;
};

#endif /* HTMLAttribute_hpp */
