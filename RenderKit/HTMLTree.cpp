//
//  HTMLParser.cpp
//  RenderKit
//
//  Created by Manuel Deneu on 02/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include <assert.h>
#include "HTMLTree.hpp"



std::string HTMLNode::getTagName() const noexcept
{
    assert(_node);
    assert(_tree);
    
    return myhtml_tag_name_by_id( _tree, _node->tag_id, NULL/*tag_length*/);
}

bool HTMLNode::hasText() const noexcept
{
    return myhtml_node_text( _node , NULL ) != NULL;
}

std::string HTMLNode::getText() const noexcept
{
    assert(_node);
    const char* t = myhtml_node_text( _node , NULL );
    if( t)
    {
        return t;
    }
    return std::string();
}

const myhtml_tree_attr_t* HTMLNode::getAttributeByName( const std::string &name) const noexcept
{
    assert(_node);
    return myhtml_attribute_by_key( _node, name.c_str(), name.size());
}

const mycss_declaration_entry_t* HTMLNode::parseDeclaration(myencoding_t encoding , mycss_declaration_t* declaration, const myhtml_tree_attr_t * attribute) const noexcept
{
    
    mystatus_t out_status = MyCORE_STATUS_ERROR;
    const mycss_declaration_entry_t *dec_entry = mycss_declaration_parse( declaration ,
                                                                   encoding,
                                                                   attribute->value.data,
                                                                   attribute->value.length,
                                                                   &out_status);
    
    if( out_status == 0)
    {
        return dec_entry;
    }
    
    return nullptr;
}


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
