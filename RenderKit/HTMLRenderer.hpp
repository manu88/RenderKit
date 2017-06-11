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

class HTMLParser;
class HTMLRenderer
{
public:
    HTMLRenderer();
    ~HTMLRenderer();
    
    bool render(HTMLParser* );
private:
    
    void node_serialization(myhtml_tree_t* html_tree, modest_render_tree_node_t* node, mycore_callback_serialize_f callback, modest* modest , void*context);
};

#endif /* HTMLRenderer_hpp */
