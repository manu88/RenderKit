//
//  HTMLRenderer.hpp
//  RenderKit
//
//  Created by Manuel Deneu on 11/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef HTMLRenderer_hpp
#define HTMLRenderer_hpp
#include <modest/render/tree.h> //modest_render_tree_node_t
#include <modest/modest.h>

#include "Element.hpp"
#include "HTMLTree.hpp"
#include "GXGeometry.hpp"


class HTMLParser;
class HTMLRenderer
{
public:
    HTMLRenderer();
    ~HTMLRenderer();
    
    bool render( const GXSize& viewPortSize, HTMLParser* );
    
    HTMLBlockElement* getRoot() const noexcept
    {
        return _root;
    }
    
    void printBlockTree() const;
private:
    
    bool computeTree();
    bool addChild(HTMLBlockElement*block , modest* modest, const HTMLNode& node );
    bool node_serialization( HTMLBlockElement* block , modest* modest, modest_render_tree_node_t* node );
    
    
    
    
    
    
    HTMLBlockElement* _root;
};

#endif /* HTMLRenderer_hpp */
