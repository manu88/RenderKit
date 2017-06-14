//
//  TestHTMLAttribute.cpp
//  RenderKit
//
//  Created by Manuel Deneu on 14/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "TestHTMLAttribute.hpp"
#include "HTMLAttribute.hpp"

bool TestHTMLAttribute::start()
{
    HTMLAttribute attr(nullptr);
    
    assert(!attr.isValid());

    HTMLAttribute attr2 = attr;
    assert(!attr2.isValid());
    
    HTMLAttribute attr3(attr);
    assert(!attr3.isValid());
    return true;
}
