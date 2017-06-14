//
//  TestHTMLNodeCollection.cpp
//  RenderKit
//
//  Created by Manuel Deneu on 14/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "TestHTMLNodeCollection.hpp"
#include "HTMLNodeCollection.hpp"
bool TestHTMLNodeCollection::start()
{
    HTMLNodeCollection c1(nullptr);
    
    assert(!c1.isValid());
    
    return true;
}
