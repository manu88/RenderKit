//
//  CSSHelpers.hpp
//  RenderKit
//
//  Created by Manuel Deneu on 15/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef CSSHelpers_hpp
#define CSSHelpers_hpp


#include <mycss/declaration/myosi.h> // mycss_declaration_entry_t
#include <GXColor.hpp>

namespace CSSHelpers
{
    GXColor parseColor(const mycss_declaration_entry_t* node);
    GXColor parseBackgroundColor(const mycss_declaration_entry_t* node);
    float parseFloatIntAttribute( const  mycss_declaration_entry_t* node ) noexcept;
    float parseGetFloat( const mycss_declaration_entry_t* node) noexcept;
}

#endif /* CSSHelpers_hpp */
