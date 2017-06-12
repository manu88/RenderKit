//
//  HTMLParser.cpp
//  RenderKit
//
//  Created by Manuel Deneu on 10/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include <ctype.h>
#include <assert.h>

#include <modest/render/tree.h>
#include <modest/render/tree_node.h>
#include <modest/render/binding.h>
#include <modest/glue.h>

#include "HTMLParser.hpp"

HTMLParser::HTMLParser():
_renderNode(nullptr)
{
    _modest = modest_create();
    assert(modest_init(_modest) == 0);
    
}

HTMLParser::~HTMLParser()
{
    if( _modest)
    {
        
        mycss_t *mycss = _modest->mycss_entry->mycss;
        mycss_entry_destroy( _modest->mycss_entry, true);
        mycss_destroy(mycss, true);
        
        myhtml_t* myhtml = _modest->myhtml_tree->myhtml;
        myhtml_tree_destroy( _modest->myhtml_tree);
        myhtml_destroy(myhtml);
        
        modest_clean(_modest);
        modest_destroy(_modest , true);
        
    }
}

std::string HTMLParser::getTitle() const
{
    std::string ret;
    
    myhtml_collection_t *collection = myhtml_get_nodes_by_tag_id( _modest->myhtml_tree, NULL, MyHTML_TAG_TITLE, NULL);
    
    
    if(collection && collection->list && collection->length)
    {
        myhtml_tree_node_t *text_node = myhtml_node_child(collection->list[0]);
        
        if(text_node)
        {
            const char* text = myhtml_node_text(text_node, NULL);
            
            if(text)
            {
                return text;
            }
        }
    }
    
    return ret;
}

static myhtml_tree_t * parse_html(const char* data, size_t data_size)
{
    myhtml_t* myhtml = myhtml_create();
    mystatus_t status = myhtml_init(myhtml, MyHTML_OPTIONS_DEFAULT, 1, 0);
    
    assert(status == 0);
    
    myhtml_tree_t* tree = myhtml_tree_create();
    status = myhtml_tree_init(tree, myhtml);
    
    assert(status == 0);
    
    status = myhtml_parse(tree, MyENCODING_UTF_8, data, data_size);
    assert(status == 0);
    
    return tree;
}


static mycss_entry_t * create_css_parser(void)
{
    // base init
    mycss_t *mycss = mycss_create();
    mystatus_t status = mycss_init(mycss);
    
    assert(status == 0);
    
    
    // currenr entry work init
    mycss_entry_t *entry = mycss_entry_create();
    status = mycss_entry_init(mycss, entry);
    
    assert(status == 0);
    
    
    return entry;
}

bool HTMLParser::parseContent( const std::string &buf)
{
    return parseContent(buf.c_str(), buf.size());
}

bool HTMLParser::parseContent( const char* buf , size_t len)
{
    assert(_modest);
    
    _modest->myhtml_tree = parse_html(buf, len);
    
    _modest->mycss_entry = create_css_parser();
    
    
    return _modest->myhtml_tree && _modest->mycss_entry;
}


static void traverse(modest_t* modest, myhtml_tree_t *html_tree )
{
    myhtml_tree_node_t *node = html_tree->node_html;
    
    
    /* run on a tree without recursion */
    while(node)
    {
        modest_glue_callback_myhtml_insert_node(modest->myhtml_tree, node, modest);
        
        if(node->child)
            node = node->child;
        else {
            while(node != html_tree->node_html && node->next == NULL)
                node = node->parent;
            
            if(node == html_tree->node_html)
                break;
            
            node = node->next;
        }
    }
}
bool HTMLParser::render()
{
    
    modest_render_tree_t *render = modest_render_tree_create();
    assert(modest_render_tree_init(render) == 0);
    
    traverse( _modest ,  _modest->myhtml_tree);
    
    
    
    _renderNode = modest_render_binding( _modest, render, _modest->myhtml_tree);
    
    return _renderNode != nullptr ;
}

