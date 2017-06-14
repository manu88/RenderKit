//
//  TestHTMLNodeCollection.hpp
//  RenderKit
//
//  Created by Manuel Deneu on 14/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef TestHTMLNodeCollection_hpp
#define TestHTMLNodeCollection_hpp


#include "UnitTestClass.hpp"

class TestHTMLNodeCollection : public UnitTestClass
{
public:
    TestHTMLNodeCollection():UnitTestClass("TestHTMLNodeCollection"){}
    bool start() override;
};

#endif /* TestHTMLNodeCollection_hpp */
