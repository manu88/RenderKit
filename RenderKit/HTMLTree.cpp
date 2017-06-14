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
    assert( _modest && _modest->myhtml_tree);
    
    return myhtml_tag_name_by_id( _modest->myhtml_tree, _node->tag_id, NULL/*tag_length*/);
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



const mycss_declaration_entry_t* HTMLNode::parseDeclaration(myencoding_t encoding ,
                                                            mycss_declaration_t* declaration,
                                                            const HTMLAttribute & attribute) const noexcept
{
    assert(attribute.isValid());
    
    mystatus_t out_status = MyCORE_STATUS_ERROR;
    const mycss_declaration_entry_t *dec_entry = mycss_declaration_parse( declaration ,
                                                                   encoding,
                                                                   attribute._attr->value.data,
                                                                   attribute._attr->value.length,
                                                                   &out_status);
    
    if( out_status == 0)
    {
        return dec_entry;
    }
    
    return nullptr;
}

HTMLAttribute HTMLNode::getAttributeByName( const std::string &name) const noexcept
{
    assert( isValid( ));
    return HTMLAttribute( myhtml_attribute_by_key( _node, name.c_str(), name.size()) );
}


HTMLAttribute HTMLNode::getAttribute( const std::string &key) const noexcept
{
    HTMLAttribute attr(nullptr);
    
    myhtml_tree_attr_t * at = myhtml_node_attribute_first( _node );
    
    while (at)
    {
        const char* k = myhtml_attribute_key(at, NULL);
        if( strcmp(k, key.c_str()) == 0)
        {
            attr._attr = at;
            return attr;
        }
    }
    
    return attr;
}
