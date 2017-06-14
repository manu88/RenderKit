//
//  TestElement.hpp
//  RenderKit
//
//  Created by Manuel Deneu on 14/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef TestElement_hpp
#define TestElement_hpp

#include "UnitTestClass.hpp"



class TestElement : public UnitTestClass
{
public:
    TestElement():UnitTestClass("TestElement"){}
    bool start() override;
};

#endif /* TestElement_hpp */
