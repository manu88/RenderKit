//
//  HTMLParser.cpp
//  RenderKit
//
//  Created by Manuel Deneu on 10/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include <ctype.h>
#include <assert.h>


#include <modest/finder/thread.h>
#include <modest/render/tree.h>
#include <modest/render/tree_node.h>
#include <modest/render/binding.h>
#include <modest/glue.h>

#include "HTMLParser.hpp"

HTMLParser::HTMLParser():
_finder     ( nullptr ),
_renderNode ( nullptr )
{
    _modest = modest_create();
    assert(_modest);
    assert(modest_init(_modest) == 0);
    

    _cssParser = mycss_create();
    assert(_cssParser);
    assert(mycss_init( _cssParser ) == 0);
    
    
}

HTMLParser::~HTMLParser()
{
    if( _finderThread)
    {
        modest_finder_thread_destroy( _finderThread, true);
        _finderThread = nullptr;
    }
    if (_finder)
    {
        modest_finder_destroy(_finder, true);
        _finder = nullptr;
    }
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
        _modest = nullptr;
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

myhtml_tree_t * HTMLParser::parse_html(const char* data, size_t data_size)
{
    myhtml_t* myhtml = myhtml_create();
    mystatus_t status = myhtml_init(myhtml, MyHTML_OPTIONS_DEFAULT, 1, 0);
    
    assert(status == 0);
    
    myhtml_tree_t* tree = myhtml_tree_create();
    status = myhtml_tree_init(tree, myhtml);
    
    assert(status == 0);
    
    myhtml_callback_tree_node_insert_set(tree, modest_glue_callback_myhtml_insert_node, _modest);
    //myhtml_callback_tree_node_insert_set(tree, cai, cai_ctx);
    status = myhtml_parse(tree, MyENCODING_UTF_8, data, data_size);
    assert(status == 0);
    
    return tree;
}


mycss_entry_t* HTMLParser::parseCSS(const char* data, size_t data_size)
{
    
    assert(_cssParser);
    // base init
    

    // currenr entry work init
    mycss_entry_t *entry = mycss_entry_create();
    mystatus_t status = mycss_entry_init( _cssParser, entry);
    
    assert(status==0);
    
    status = mycss_parse(entry, MyENCODING_UTF_8, data, data_size);
    assert(status==0);
    
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
    

    if( parseCSS())
    {
        printf("Has CSS declarations \n");
    }

    
    
    /* crteate and init Finder */
    _finder = modest_finder_create();
    
    mystatus_t status = modest_finder_init( _finder );
    
    assert(status == MyCORE_STATUS_OK);
    
    /* create and init Thread Finder with two thread */
    _finderThread = modest_finder_thread_create();
    modest_finder_thread_init( _finder, _finderThread, FinderThreadsNum );
    
    /* get stylesheet */
    mycss_stylesheet_t *stylesheet = mycss_entry_stylesheet(_modest->mycss_entry);
    
    if( stylesheet)
    {
        /* comparison selectors and tree nodes */
        status = modest_finder_thread_process(_modest, _finderThread, _modest->myhtml_tree->node_html, stylesheet->sel_list_first);
        assert(status == MyCORE_STATUS_OK);
    }
    
    

    return _modest->myhtml_tree;// && _modest->mycss_entry;
}

bool HTMLParser::parseCSS()
{
    assert(_modest);
    
    myhtml_collection_t *collection = myhtml_get_nodes_by_tag_id( _modest->myhtml_tree, NULL, MyHTML_TAG_STYLE, NULL);
    
    
    if(collection && collection->list && collection->length)
    {
        myhtml_tree_node_t *text_node = myhtml_node_child(collection->list[0]);
        
        if(text_node)
        {
            const char* cssStyle = myhtml_node_text(text_node, NULL);
            printf("Style : '%s' \n" , cssStyle);
            if( cssStyle )
            {
                _modest->mycss_entry = parseCSS( cssStyle, strlen( cssStyle));
                
                return _modest->mycss_entry != nullptr;
                //mycss_entry_
                
            }
            
        }
    }
     // no syle node found
    
    _modest->mycss_entry = parseCSS( "", 0);
    
    return false;
}



bool HTMLParser::render()
{
    
    modest_render_tree_t *render = modest_render_tree_create();
    assert(modest_render_tree_init(render) == 0);
    
    _renderNode = modest_render_binding( _modest, render, _modest->myhtml_tree);
    
    return _renderNode != nullptr ;
}
