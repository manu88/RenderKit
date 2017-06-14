//
//  UnitTestClass.cpp
//  RenderKit
//
//  Created by Manuel Deneu on 14/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "UnitTestClass.hpp"


/*static*/ std::vector<UnitTestClass*> UnitTestClass::_testList = std::vector<UnitTestClass*>();


UnitTestClass::UnitTestClass(const std::string &_name):
name(_name)
{
    
}

UnitTestClass::~UnitTestClass()
{
    
}

bool UnitTestClass::run()
{
    printf("Start %s test \n" , name.c_str());
    if(! start())
    {
        printf("Test %s FAILED, will assert \n" , name.c_str());
        return false;
    }
    
    return true;
}

/*static*/ bool UnitTestClass::runTests()
{
    UnitTestClass* t = nullptr;
    
    while ( !_testList.empty()  )
    {
        
        t = _testList.back();
        if(t)
        {
            t->run();
            _testList.pop_back();
            delete t;
        }
        
    }
    
    return true;
}
