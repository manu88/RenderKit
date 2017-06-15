//
//  CSSDeclaration.cpp
//  RenderKit
//
//  Created by Manuel Deneu on 14/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include <assert.h>


#include "CSSDeclaration.hpp"
#include "CSSColors.hpp"
#include "CSSHelpers.hpp"




CSSDeclaration::CSSDeclaration( mycss_declaration_entry_t *decl):
_decl(decl)
{
    
}

CSSDeclaration::~CSSDeclaration()
{
    
}

mycss_property_type_t CSSDeclaration::getType() const noexcept
{
    assert(_decl);
    return _decl->type;
}

unsigned int CSSDeclaration::getValueType() const noexcept
{
    assert(_decl);
    return _decl->value_type;
}


GXColor CSSDeclaration::parseBackgroundColor() const noexcept
{
    return CSSHelpers::parseBackgroundColor( _decl );
}

GXColor CSSDeclaration::parseColor() const noexcept
{
    return CSSHelpers::parseColor(_decl);
}

float CSSDeclaration::parseBlockWidth() const noexcept
{
    return CSSHelpers::parseBlockWidth( _decl);
}

float CSSDeclaration::parseBlockHeight() const noexcept
{
    return CSSHelpers::parseBlockHeight(_decl);
}


/* **** **** **** **** **** **** **** **** **** **** **** **** */

