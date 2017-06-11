//
//  HTMLParser.cpp
//  RenderKit
//
//  Created by Manuel Deneu on 10/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include <ctype.h>
#include <assert.h>
#include "HTMLParser.hpp"


static int is_empty(const char *s)
{
    while (*s != '\0') {
        if (!isspace(*s))
            return 0;
        s++;
    }
    return 1;
}


HTMLParser::HTMLParser()
{
    
}

HTMLParser::~HTMLParser()
{
    
}


bool HTMLParser::parseContent( const char* buf , size_t len)
{
    if( _htmlTree.parseContent(buf, len))
    {
        parseHTML();
        return true;
    }
    
    return false;
}

/*static*/ mystatus_t HTMLParser::serialization_callback(const char* data, size_t len, void* ctx)
{
    HTMLParser* self = reinterpret_cast<HTMLParser*>(ctx);
    assert(self);
    return self->tokenCallback(data, len);
    
}
mystatus_t HTMLParser::tokenCallback(const char* data, size_t len)
{
    printf("%.*s", (int)len, data);
    return MyCORE_STATUS_OK;
}

void HTMLParser::print_entries(mycss_entry_t* entry, mycss_declaration_entry_t* declr_entry)
{
    if(declr_entry == NULL)
        return;
    
    while(declr_entry)
    {
        printf("\t");
        mycss_declaration_serialization_entry(entry, declr_entry, serialization_callback, this);
        //printf("'%s'" , mycss_property_type_name(declr_entry->type));
        
        
        if(declr_entry->next)
            printf(";\n");
        else
            printf(";");
        
        declr_entry = declr_entry->next;
    }
}

void HTMLParser::parseHTML()
{
    myhtml_tree_node_t *node = _htmlTree._tree->node_html;
    printf("Result:\n");
    

    while(node)
    {
        const char *tag_name = myhtml_tag_name_by_id(_htmlTree._tree, myhtml_node_tag_id(node), NULL);
        if( tag_name && strcmp(tag_name, "div") == 0)
        {
            printf(" -> Start Div\n");
            //printf("TAG : '%s'" , tag_name);
        }
        
        const char* key = "style";
        myhtml_tree_attr_t *attr_style = myhtml_attribute_by_key(node, key, strlen(key));

        if(attr_style)
        {
            mycss_declaration_entry_t *dec_entry = mycss_declaration_parse(_cssParser.getEntry()->declaration,
                                                                           MyENCODING_UTF_8,
                                                                           attr_style->value.data,
                                                                           attr_style->value.length,
                                                                           NULL);
            
            if(dec_entry)
            {
                /*
                 printf("Node:\n\t");
                 myhtml_serialization_tree_callback(node, serialization_callback, NULL);
                 */
                printf("\nHas style:\n");
                print_entries(_cssParser.getEntry(), dec_entry);
                printf("\n\n");
            }
        }
        else
        {
            
            const char* txt = myhtml_node_text(node, NULL);
            if(txt && !is_empty(txt))
            {
                printf("TEXT '%s' \n" , txt );
            }
        }
        
        if(node->child)
        {
            //printf("-------- Child node\n");
            node = node->child;
        }
        else
        {
            while(node != _htmlTree._tree->node_html && node->next == NULL)
            {
                //printf("-------- Jump to parent\n");
                node = node->parent;
            }
            
            if(node == _htmlTree._tree->node_html )
            {
                break;
            }
            printf("-------- Next node\n");
            node = node->next;
        }
    }
}
