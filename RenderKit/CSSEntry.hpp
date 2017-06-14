//
//  CSSEntry.hpp
//  RenderKit
//
//  Created by Manuel Deneu on 14/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef CSSEntry_hpp
#define CSSEntry_hpp

#include <mycss/declaration/myosi.h> //mycss_declaration_entry_t
#include <GXColor.hpp>

class CSSEntry
{
public:
    /* Parser helpers */
    static GXColor parseBackgroundColor(const mycss_declaration_entry_t* node);
    static float parseFloatIntAttribute( const  mycss_declaration_entry_t* node );
    static float parseBlockWidth( const mycss_declaration_entry_t* node);
    static float parseBlockHeight( const mycss_declaration_entry_t* node);
};

#endif /* CSSEntry_hpp */
