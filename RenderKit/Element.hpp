//
//  Element.hpp
//  RenderKit
//
//  Created by Manuel Deneu on 11/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef Element_hpp
#define Element_hpp

#include "GXColor.hpp"
#include "GXGeometry.hpp"

#include <myhtml/myhtml.h>

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
    GXColor backgroundColor;
    GXSize  size;
};

#endif /* Element_hpp */
