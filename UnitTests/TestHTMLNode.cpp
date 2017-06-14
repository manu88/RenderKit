//
//  TestHTMLNode.cpp
//  RenderKit
//
//  Created by Manuel Deneu on 14/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "TestHTMLNode.hpp"

#include "HTMLNode.hpp"

bool TestHTMLNode::start()
{
    HTMLNode node(nullptr , nullptr);
    assert(!node.isValid());
    assert(node._modest == nullptr);
    assert(node._node == nullptr);
    
    
    
    for (const HTMLNode& c: node )
    {
        (void)c;
        assert(false);
    }
    
    return true;
}
