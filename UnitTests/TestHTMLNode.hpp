//
//  TestHTMLNode.hpp
//  RenderKit
//
//  Created by Manuel Deneu on 14/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef TestHTMLNode_hpp
#define TestHTMLNode_hpp

#include "UnitTestClass.hpp"

class TestHTMLNode : public UnitTestClass
{
public:
    TestHTMLNode():UnitTestClass("TestHTMLNode"){}
    bool start() override;
};

#endif /* TestHTMLNode_hpp */
