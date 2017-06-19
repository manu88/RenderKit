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

#include "GXGeometry.hpp"
#include "Document.hpp"
class HTMLNode;
class HTMLParser;

class HTMLRenderer
{
public:
    HTMLRenderer();
    ~HTMLRenderer();
    bool prepare(Document &doc);
    bool render( const GXSize& viewPortSize, Document& doc );
    
    HTMLBlockElement* getRoot() const noexcept
    {
        return _root;
    }
    
    void printBlockTree() const;
    
private:
    
    bool computeTree();
    bool addChild(HTMLBlockElement*block , const HTMLNode& node );
    static bool parseStyle( HTMLBlockElement*block , const CSSDeclaration& decl);
    bool serializeNode( HTMLBlockElement* block , modest* modest, modest_render_tree_node_t* node );
    
    modest_render_tree_t *_renderTree;
    HTMLBlockElement* _root;
};

#endif /* HTMLRenderer_hpp */
