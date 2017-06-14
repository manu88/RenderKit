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
#include "TestHTMLAttribute.hpp"

int main(int argc, const char * argv[])
{
    
    
    UnitTestClass::addTest( new TestElement() );
    UnitTestClass::addTest( new TestHTMLAttribute() );
    
    UnitTestClass::runTests();

    UnitTestClass::clear();
    
    return 0;
}
