//
//  Element.hpp
//  RenderKit
//
//  Created by Manuel Deneu on 11/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef Element_hpp
#define Element_hpp


#include <myhtml/myhtml.h>
#include <string>
#include <vector>
#include "GXColor.hpp"
#include "GXGeometry.hpp"
#include <mycss/property/const.h>


struct ESize
{
    float width;
    float height;
    
    bool wPercent;
    bool hPercent;
    
    inline bool operator==( const ESize& rhs) const
    {
        return    width == rhs.width && height == rhs.height
               && wPercent == rhs.wPercent && hPercent == rhs.hPercent ;
    }
    
    inline bool operator !=( const ESize& rhs) const
    {
        return !(*this == rhs);
    }
    
};

static constexpr ESize ESizeInvalid = { -1.f , -1.f , false , false};



class Element
{
public:
    Element();
    virtual ~Element();
    
};

class HTMLElement : public Element
{
public:
    HTMLElement();
    virtual ~HTMLElement()
    {}
    
    myhtml_tree_node_t *_node;
};

class HTMLBlockElement : public HTMLElement
{
public:
    HTMLBlockElement():
    backgroundColor(GXColorInvalid),
    size( ESizeInvalid ),
    floatProp( MyCSS_PROPERTY_FLOAT_UNSET ),
    _parent(nullptr)
    {}
    
    void reorder();

    std::string tag;
    GXColor backgroundColor;
    ESize  size;
    std::string text;
    std::string src;
    mycss_property_float_t floatProp;
    
    std::vector<HTMLBlockElement*> _children;
    HTMLBlockElement *_parent;
};

#endif /* Element_hpp */
