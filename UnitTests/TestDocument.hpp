//
//  TestDocument.hpp
//  RenderKit
//
//  Created by Manuel Deneu on 14/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef TestDocument_hpp
#define TestDocument_hpp

#include "UnitTestClass.hpp"



class TestDocument : public UnitTestClass
{
public:
    TestDocument():UnitTestClass("TestDocument"){}
    bool start() override;
};

#endif /* TestDocument_hpp */
