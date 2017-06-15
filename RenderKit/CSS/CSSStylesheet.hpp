//
//  CSSStylesheet.hpp
//  RenderKit
//
//  Created by Manuel Deneu on 15/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef CSSStylesheet_hpp
#define CSSStylesheet_hpp

#include <mycss/myosi.h> //mycss_stylesheet_t

class CSSStylesheet
{
public:
    CSSStylesheet(mycss_stylesheet_t *stylesheet);
    ~CSSStylesheet();
    
    
    
    mycss_stylesheet_t *_stylesheet;
};

#endif /* CSSStylesheet_hpp */
