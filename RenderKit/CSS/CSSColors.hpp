//
//  CSSColors.hpp
//  RenderKit
//
//  Created by Manuel Deneu on 14/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef CSSColors_hpp
#define CSSColors_hpp

#include <unordered_map>
#include <GXColor.hpp>

namespace CSSColor
{
    const std::unordered_map<const char* , const GXColor> ColorsNames =
    {
        { "white"       , GXColors::White},
        { "red"         , GXColors::Red},
        { "blue"        , GXColors::Blue},
        { "green"       , GXColorMake( 0 , 0.5 , 0)},
        { "yellow"      , GXColorMake( 1.0 , 1. , 0)},
        { "magenta"     , GXColorMake(0.96, 0, 0.96)},
        { "cyan"        , GXColorMake(0., 1, 1)},
        { "gray"        , GXColorMakeWithWhite(0.5)},
        { "lightgray"   , GXColorMakeWithWhite(0.83)},
        
    };
};

#endif /* CSSColors_hpp */
