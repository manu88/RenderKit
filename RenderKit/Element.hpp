//
//  Element.hpp
//  RenderKit
//
//  Created by Manuel Deneu on 11/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef Element_hpp
#define Element_hpp


//#include <myhtml/myhtml.h>
#include <string>
#include <vector>
#include "GXColor.hpp"
#include "GXGeometry.hpp"
#include <mycss/property/const.h> // for MyCSS_PROPERTY_FLOAT_UNSET and others
#include "HTMLNode.hpp"


struct FontProperties
{
    float size;
};

static const FontProperties DefaultProperties =
{ .size = 10.f };


/* **** **** **** **** **** **** **** **** **** **** **** **** */

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

class HTMLBlockElement
{
public:
    
    typedef enum
    {
        Unknown  = 0,
        Viewport = 1,
        Block    = 2,
    } Type;
    
    
    HTMLBlockElement();
    ~HTMLBlockElement();
    void reorder();
    
    

    /* Parsed from HTML/CSS code*/
    
    
    Type type;
    //std::string tag;
    GXColor backgroundColor;
    bool drawFrame;
    float frameWidth;
    ESize  size;
    std::string text;
    std::string src;
    mycss_property_float_t floatProp;
    
    std::vector<HTMLBlockElement*> _children;
    HTMLBlockElement *_parent;

    int _xFloatRight;
    /* Defined by reflow/draw*/
    
    GXSize realSize;
    FontProperties fontProps;
    
    HTMLNode::TagID tagID;
    
    
};

#endif /* Element_hpp */
