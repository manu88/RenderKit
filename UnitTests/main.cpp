//
//  main.cpp
//  RenderKit
//
//  Created by Manuel Deneu on 14/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include <stdio.h>
#include <assert.h>
#include "UnitTestClass.hpp"
#include "TestElement.hpp"

int main(int argc, const char * argv[])
{
    
    
    UnitTestClass::addTest( new TestElement() );
    
    assert(UnitTestClass::runTests());
    
    return 0;
}
