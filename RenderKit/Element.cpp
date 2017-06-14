//
//  Element.cpp
//  RenderKit
//
//  Created by Manuel Deneu on 11/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "Element.hpp"



HTMLBlockElement::HTMLBlockElement():
_node(nullptr),
type(Unknown),
backgroundColor(GXColorInvalid),
drawFrame(false),
size( ESizeInvalid ),
floatProp( MyCSS_PROPERTY_FLOAT_UNSET ),
_parent(nullptr),
realSize(GXSizeInvalid)
{
    
}


HTMLBlockElement::~HTMLBlockElement()
{
    std::for_each(_children.begin(), _children.end(), [](HTMLBlockElement* block)
                  {
                      delete block;
                      block = nullptr;
                  });
    
    _children.clear();
    
}

struct ChildComparor
{
    bool operator() (const HTMLBlockElement* lhs, const HTMLBlockElement* rhs) const
    {
        /*
         order:
         lhs rhs
         1   0
         2   1
         3   2
         */
        printf("Compare %p (%x) with  %p (%x)\n " ,lhs, lhs->floatProp , rhs,rhs->floatProp);
        return false; //lhs->getZPos() > rhs->getZPos();
    }
};

void HTMLBlockElement::reorder()
{
    printf("Start reoder\n");
    for( const HTMLBlockElement* c : _children)
    {
        printf("Child %p \n" , (void*)c);
    }
    std::sort(_children.begin() , _children.end(), ChildComparor() );
}
