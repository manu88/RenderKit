//
//  HTMLParser.cpp
//  RenderKit
//
//  Created by Manuel Deneu on 02/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include <assert.h>
#include "HTMLNode.hpp"
#include <modest/modest.h> // modest
#include <modest/declaration.h> // modest_declaration_by_type
#include "Constants.hpp"

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

HTMLNode HTMLNode::getChild() const noexcept
{
    assert(isValid());
    return HTMLNode( myhtml_node_child(_node) , _modest);
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

CSSDeclaration HTMLNode::parseDeclaration(myencoding_t encoding ,const HTMLAttribute & attribute) const noexcept
{
    assert(attribute.isValid());
    
    if( !_modest->mycss_entry)
        return nullptr;
    
    if( _modest->mycss_entry->declaration == nullptr)
        return nullptr;
    
    mystatus_t out_status = MyCORE_STATUS_ERROR;
    mycss_declaration_entry_t *dec_entry = mycss_declaration_parse( _modest->mycss_entry->declaration ,
                                                                         encoding,
                                                                         attribute._attr->value.data,
                                                                         attribute._attr->value.length,
                                                                         &out_status);
    
    if( out_status == 0)
    {
        return CSSDeclaration(dec_entry);
    }
    
    return CSSDeclaration(nullptr);
}

CSSDeclaration HTMLNode::getDeclarationByType( mycss_property_type_t type) const noexcept
{
    return CSSDeclaration( modest_declaration_by_type(_modest, _node, type) );
}

static mystatus_t serialization_callback(const char* data, size_t len, void* ctx)
{
    printf("%.*s", (int)len, data);
    return MyCORE_STATUS_OK;
}


void HTMLNode::printCSSProperties() const noexcept
{
    printf("######## start CSSProperties \n");
    
    modest_t* modest = _modest;
    
    mycss_entry_t *mycss_entry = _modest->mycss_entry;
    myhtml_tree_node_t* node = _node;
    printf("Style CSS stylesheet \n");
    
    printf("\t");
    mycss_declaration_entry_t *padding_left = modest_declaration_by_type(modest, node, MyCSS_PROPERTY_TYPE_PADDING_LEFT);
    mycss_declaration_serialization_entry_by_type(mycss_entry, padding_left, MyCSS_PROPERTY_TYPE_PADDING_LEFT, serialization_callback, NULL);
    
    printf("\n\t");
    mycss_declaration_entry_t *color = modest_declaration_by_type(modest, node, MyCSS_PROPERTY_TYPE_COLOR);
    mycss_declaration_serialization_entry_by_type(mycss_entry, color, MyCSS_PROPERTY_TYPE_COLOR, serialization_callback, NULL);
    
    printf("\n\t");
    mycss_declaration_entry_t *display = modest_declaration_by_type(modest, node, MyCSS_PROPERTY_TYPE_DISPLAY);
    mycss_declaration_serialization_entry_by_type(mycss_entry, display, MyCSS_PROPERTY_TYPE_DISPLAY, serialization_callback, NULL);
    
    printf("\n\t");
    mycss_declaration_entry_t *floatV = modest_declaration_by_type(modest, node, MyCSS_PROPERTY_TYPE_FLOAT);
    mycss_declaration_serialization_entry_by_type(mycss_entry, floatV, MyCSS_PROPERTY_TYPE_FLOAT, serialization_callback, NULL);
    printf("\n");
    
    const char* kStyle = TagNames::Style;
    
    myhtml_tree_attr_t * styleAttr = myhtml_attribute_by_key( node, kStyle, strlen(kStyle));
    
    if( mycss_entry && styleAttr)
    {
        mycss_declaration_entry_t *dec_entry = mycss_declaration_parse( mycss_entry->declaration ,
                                                                       MyENCODING_UTF_8,
                                                                       styleAttr->value.data,
                                                                       styleAttr->value.length,
                                                                       NULL);
        if( !dec_entry)
        {
            printf("No tag Style attr \n");
            return;
        }
        printf("tag Style attr : \n");
        
        const mycss_declaration_entry_t* next = dec_entry;
        while (next)
        {
            printf("\tGot declaration %i " , next->type);
            if( next->type == MyCSS_PROPERTY_TYPE_FLOAT)
            {
                mycss_property_float_t floatProp =(const mycss_property_float_t) next->value_type;
                printf(" : float " );
                if( floatProp == MyCSS_PROPERTY_FLOAT_LEFT)
                {
                    printf(" left");
                }
                else if( floatProp == MyCSS_PROPERTY_FLOAT_RIGHT)
                {
                    printf(" right");
                }
                
                printf("\n");
            }
            printf("\n");
            next = next->next;
        }
    }
    
    printf("######## end CSSProperties \n");
    
}
