//
//  CSSDeclaration.hpp
//  RenderKit
//
//  Created by Manuel Deneu on 14/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef CSSDeclaration_hpp
#define CSSDeclaration_hpp

#include <iterator>
#include <mycss/declaration/myosi.h> // mycss_declaration_entry_t
#include <GXColor.hpp>

class CSSDeclaration
{
public:
    CSSDeclaration( mycss_declaration_entry_t *decl );
    ~CSSDeclaration();
    
    
    bool isValid() const noexcept;
    mycss_property_type_t getType() const noexcept;
    unsigned int getValueType() const noexcept;
    
    GXColor getBackgroundColor() const noexcept;
    GXColor getColor() const noexcept;
    float parseBlockWidth() const noexcept;
    float parseBlockHeight() const noexcept;
    
    

    
    
    class Iterator : public std::iterator<std::forward_iterator_tag, CSSDeclaration>
    {
        friend class CSSDeclaration;
    private:
        Iterator( mycss_declaration_entry_t *decl):
        _decl(decl)
        {}
        
    public:
        bool operator!=( const Iterator& rhs)
        {
            return _decl != rhs._decl;
        }
        
        bool operator==( const Iterator& rhs)
        {
            return _decl == rhs._decl;
        }
        
        Iterator& operator++()
        {
            _decl = _decl->next;
            return *this;
        };
        
        CSSDeclaration operator*()
        {
            return CSSDeclaration( _decl );
        };
        
        mycss_declaration_entry_t *_decl;
    };
    
    const Iterator begin() const
    {
        return Iterator( _decl  );
    }
    
    const Iterator end() const
    {
        return Iterator(  nullptr );
    }
    
    
    mycss_declaration_entry_t *_decl;
    
private:
    
};

#endif /* CSSDeclaration_hpp */
