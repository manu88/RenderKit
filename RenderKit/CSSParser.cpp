//
//  CSSParser.cpp
//  RenderKit
//
//  Created by Manuel Deneu on 10/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include <assert.h>
#include "CSSParser.hpp"


CSSParser::CSSParser()
{
    
    // base init
    mycss_t *mycss = mycss_create();
    mystatus_t status = mycss_init(mycss);
    
    assert(status == 0);
    
    // currenr entry work init
    _entry = mycss_entry_create();
    status = mycss_entry_init(mycss, _entry);
    
    assert(status == 0);

}

CSSParser::~CSSParser()
{
    mycss_t *mycss = _entry->mycss;
    mycss_entry_destroy(_entry, true);
    mycss_destroy(mycss, true);
    
}
