//
//  CSSDeclaration.hpp
//  RenderKit
//
//  Created by Manuel Deneu on 14/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef CSSDeclaration_hpp
#define CSSDeclaration_hpp


#include <mycss/declaration/myosi.h>
#include <GXColor.hpp>

class CSSDeclaration
{
public:
    CSSDeclaration( const mycss_declaration_entry_t *decl );
    ~CSSDeclaration();
    
    
    
    mycss_property_type_t getType() const noexcept;
    
    GXColor parseBackgroundColor() const noexcept;
    float parseBlockWidth() const noexcept;
    float parseBlockHeight() const noexcept;
    
    
    const mycss_declaration_entry_t *_decl;
    
    static GXColor parseBackgroundColor(const mycss_declaration_entry_t* node);
    
private:
    static float parseFloatIntAttribute( const  mycss_declaration_entry_t* node ) noexcept;
    static float parseBlockWidth( const mycss_declaration_entry_t* node) noexcept;
    static float parseBlockHeight( const mycss_declaration_entry_t* node) noexcept;
};

#endif /* CSSDeclaration_hpp */
