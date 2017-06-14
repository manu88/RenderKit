//
//  TestElement.cpp
//  RenderKit
//
//  Created by Manuel Deneu on 14/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "TestElement.hpp"
#include "Element.hpp"

bool TestElement::start()
{
    HTMLBlockElement b;
    assert(b.type == HTMLBlockElement::Unknown);
    assert(b.tag.empty());
    assert(b.backgroundColor == GXColorInvalid);
    assert(b.size == ESizeInvalid);
    assert(b.text.empty());
    assert(b.src.empty());
    assert(b._children.empty());
    assert(b._parent == nullptr);
    assert(b._node == nullptr);
    assert(b.realSize == GXSizeInvalid);
    
    
    return true;
}
