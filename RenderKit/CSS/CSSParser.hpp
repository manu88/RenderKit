//
//  CSSParser.hpp
//  RenderKit
//
//  Created by Manuel Deneu on 10/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef CSSParser_hpp
#define CSSParser_hpp

#include "Modest/myosi.h"

class CSSParser
{
public:
    CSSParser();
    ~CSSParser();
    
    mycss_entry_t* getEntry()
    {
        return _entry;
    }
private:
    
    mycss_entry_t* _entry;
    
};

#endif /* CSSParser_hpp */
