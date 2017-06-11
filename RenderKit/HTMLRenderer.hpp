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

class HTMLParser;
class HTMLRenderer
{
public:
    HTMLRenderer();
    ~HTMLRenderer();
    
    bool render(HTMLParser* );
private:
    
    HTMLBlockElement addChild(modest* modest, const HTMLNode& node , modest_render_tree_node_t* parent);
    void node_serialization(modest* modest, modest_render_tree_node_t* node );
    
    GXColor parseBackgroundColor(const mycss_declaration_entry_t* node);
    
    float parseFloatIntAttribute( const  mycss_declaration_entry_t* node );
    float parseBlockWidth( const mycss_declaration_entry_t* node);
    float parseBlockHeight( const mycss_declaration_entry_t* node);
    
    static std::unordered_map<const char* , const GXColor> ColorsNames;
};

#endif /* HTMLRenderer_hpp */
