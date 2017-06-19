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

#include <modest/glue.h>

#include "HTMLParser.hpp"
#include "Document.hpp"

HTMLParser::HTMLParser():
_finder     ( nullptr )
{
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
    /*
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
     */
}

myhtml_tree_t * HTMLParser::parse_html(Document& doc,const char* data, size_t data_size)
{
    assert(doc.getModest() );
    myhtml_t* myhtml = myhtml_create();
    mystatus_t status = myhtml_init(myhtml, MyHTML_OPTIONS_DEFAULT, 1, 0);
    
    assert(status == 0);
    
    myhtml_tree_t* tree = myhtml_tree_create();
    status = myhtml_tree_init(tree, myhtml);
    
    assert(status == 0);
    
    myhtml_callback_tree_node_insert_set(tree, modest_glue_callback_myhtml_insert_node, doc.getModest() );

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

bool HTMLParser::parseContent( Document &doc, const std::string &buf)
{
    return parseContent(doc, buf.c_str(), buf.size());
}

bool HTMLParser::parseContent( Document &doc, const char* buf , size_t len)
{
    printf("HTMLParser::parseContent\n");
    
    
    assert(doc.getModest());
    
    doc.getModest()->myhtml_tree = parse_html( doc , buf, len);
    

    if( parseCSS( doc))
    {

    }


    /* create and init Finder */
    _finder = modest_finder_create();
    
    mystatus_t status = modest_finder_init( _finder );
    
    assert(status == MyCORE_STATUS_OK);
    
    /* create and init Thread Finder with two thread */
    _finderThread = modest_finder_thread_create();
    modest_finder_thread_init( _finder, _finderThread, FinderThreadsNum );
    
    /* get stylesheet */
    mycss_stylesheet_t *stylesheet = mycss_entry_stylesheet( doc.getModest()->mycss_entry );
    
    if( stylesheet)
    {
        /* comparison selectors and tree nodes */
        status = modest_finder_thread_process( doc.getModest(),
                                              _finderThread,
                                              doc.getModest()->myhtml_tree->node_html,
                                              stylesheet->sel_list_first
                                              );
        assert(status == MyCORE_STATUS_OK);
    }
    
    

    return doc.getModest()->myhtml_tree;// && _modest->mycss_entry;
}

bool HTMLParser::parseCSS(Document& doc)
{
    assert(doc.getModest());
    
    const HTMLNodeCollection collect = doc.getNodesByTagID(MyHTML_TAG_STYLE);

    
    if(collect.isValid() && collect.getSize())//
    {
        
        const HTMLNode textNode = collect.at(0).getChild();
        
        
        if(textNode.isValid() && textNode.hasText())
        {
            const std::string &cssTxt = textNode.getText();
            
            doc.getModest()->mycss_entry = parseCSS( cssTxt.c_str(), cssTxt.size() );
        }
    }
    else
    {
        doc.getModest()->mycss_entry = parseCSS( "", 0);
    }
     // no syle node found
    
    
    
    return doc.getModest()->mycss_entry != nullptr;
}



