//
//  HTMLParser.cpp
//  RenderKit
//
//  Created by Manuel Deneu on 02/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include <assert.h>
#include "HTMLTree.hpp"


HTMLTree::HTMLTree():
_tree(nullptr),
_html(nullptr)
{
    
}

HTMLTree::~HTMLTree()
{
    if( _tree)
    {
        myhtml_tree_destroy( _tree);
        _tree = nullptr;
    }
    if( _html)
    {
        myhtml_destroy(_html);
        _html = nullptr;
    }
}


bool HTMLTree::parseContent( const char* buf , size_t len)
{
    assert(buf);
    assert( !_tree );
    assert( !_html);
    if( !_html)
    {
        _html = myhtml_create();
        mystatus_t status = myhtml_init( _html, MyHTML_OPTIONS_DEFAULT, 1, 0);
        assert(status == MyCORE_STATUS_OK);
    }
    
    if( !_tree )
    {
        _tree = myhtml_tree_create();
        mystatus_t status = myhtml_tree_init( _tree, _html);
        assert(status == MyCORE_STATUS_OK);
    }
    if( buf && len)
    {
        mystatus_t status = myhtml_parse( _tree, MyENCODING_UTF_8, buf, len);
        assert(status == MyCORE_STATUS_OK);
        return true;
    }
    return false;
}
