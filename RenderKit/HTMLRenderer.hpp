//
//  HTMLRenderer.hpp
//  RenderKit
//
//  Created by Manuel Deneu on 11/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef HTMLRenderer_hpp
#define HTMLRenderer_hpp
#include <modest/render/tree.h>
#include <modest/modest.h>

#include <unordered_map>

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
    
    const HTMLBlockElement* getRoot() const noexcept
    {
        return _root;
    }
    
    void printBlockTree() const;
private:
    
    bool addChild(HTMLBlockElement*block , modest* modest, const HTMLNode& node , modest_render_tree_node_t* parent);
    bool node_serialization( HTMLBlockElement* block , modest* modest, modest_render_tree_node_t* node );
    
    GXColor parseBackgroundColor(const mycss_declaration_entry_t* node);
    
    float parseFloatIntAttribute( const  mycss_declaration_entry_t* node );
    float parseBlockWidth( const mycss_declaration_entry_t* node);
    float parseBlockHeight( const mycss_declaration_entry_t* node);
    
    static std::unordered_map<const char* , const GXColor> ColorsNames;
    
    HTMLBlockElement* _root;
};

#endif /* HTMLRenderer_hpp */
