//
//  HTMLParser.cpp
//  RenderKit
//
//  Created by Manuel Deneu on 10/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "HTMLParser.hpp"


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

void HTMLParser::print_entries(mycss_entry_t* entry, mycss_declaration_entry_t* declr_entry)
{
    if(declr_entry == NULL)
        return;
    
    while(declr_entry)
    {
        printf("\t");
        //mycss_declaration_serialization_entry(entry, declr_entry, serialization_callback, NULL);
        
        
        mycss_declaration_typ
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
    
    /* run on a tree without recursion */
    while(node)
    {
        
        myhtml_tree_attr_t *attr_style = myhtml_attribute_by_key(node, "style", 5);
        
        
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
                printf("\nDeclaration:\n");
                print_entries(_cssParser.getEntry(), dec_entry);
                printf("\n\n");
            }
        }
        else
        {
            const char* txt = myhtml_node_text(node, NULL);
            if(txt)// && !is_empty(txt))
            {
                printf("TEXT '%s' \n" , txt );
            }
        }
        
        if(node->child)
            node = node->child;
        else {
            while(node != _htmlTree._tree->node_html && node->next == NULL)
                node = node->parent;
            
            if(node == _htmlTree._tree->node_html )
                break;
            
            node = node->next;
        }
    }
}
