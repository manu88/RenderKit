//
//  UnitTestClass.hpp
//  RenderKit
//
//  Created by Manuel Deneu on 14/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef UnitTestClass_hpp
#define UnitTestClass_hpp


#include <assert.h>
#include <stdio.h>
#include <vector>
#include <string>

class UnitTestClass
{
public:
    UnitTestClass(const std::string &_name);
    virtual ~UnitTestClass();
    
    bool run();
    
    
    const std::string name;
    
    static void addTest(UnitTestClass* test)
    {
        _testList.push_back(test);
    }
    
    static bool runTests()
    {
        for( UnitTestClass* t : _testList)
        {
            if(!t->run())
            {
                return false;
            }
        }
        return true;
    }
    
    static void clear()
    {
        std::for_each(_testList.begin(), _testList.end(), [](UnitTestClass* test)
                      {
                          delete test;
                          test = nullptr;
                      });
        
        _testList.clear();
    }
    
private:
    
    virtual bool start() = 0;
    
    
    static std::vector<UnitTestClass*> _testList;
};

#endif /* UnitTestClass_hpp */
