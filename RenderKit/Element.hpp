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
    size(GXSizeMakeNull()),
    _parent(nullptr)
    {}
    
    
    GXColor backgroundColor;
    GXSize  size;
    std::string text;
    
    std::vector<HTMLBlockElement*> _children;
    HTMLBlockElement *_parent;
};

#endif /* Element_hpp */
