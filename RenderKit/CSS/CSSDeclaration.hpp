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

class CSSDeclaration
{
public:
    CSSDeclaration( mycss_declaration_entry_t *decl );
    ~CSSDeclaration();
    
    mycss_declaration_entry_t *_decl;
};

#endif /* CSSDeclaration_hpp */
