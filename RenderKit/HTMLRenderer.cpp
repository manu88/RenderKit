//
//  HTMLRenderer.cpp
//  RenderKit
//
//  Created by Manuel Deneu on 11/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//


#include <assert.h>
#include "HTMLRenderer.hpp"
#include "HTMLParser.hpp"
#include <ctype.h>


static int is_empty(const char *s)
{
    while (*s != '\0') {
        if (!isspace(*s))
            return 0;
        s++;
    }
    return 1;
}

HTMLRenderer::HTMLRenderer()
{
    
}

HTMLRenderer::~HTMLRenderer()
{
    
}


static mystatus_t serialization_callback(const char* data, size_t len, void* ctx)
{
    printf("%.*s", (int)len, data);
    return MyCORE_STATUS_OK;
}

bool HTMLRenderer::render(HTMLParser* parser )
{
    assert(parser);
    
    
    modest_render_tree_node_t* node = parser->_renderNode;
    size_t depth = 0;
    
    while(node)
    {
        for(size_t i = 0; i < depth; i++)
        {
            printf("\t");
            //        callback("\t", 1, context);
        }
        
        node_serialization(parser->_modest->myhtml_tree, node, serialization_callback, parser->_modest , nullptr);
        
        printf("\n");
        if(node->child) {
            depth++;
            node = node->child;
        }
        else {
            while(node != parser->_renderNode && node->next == NULL) {
                depth--;
                node = node->parent;
            }
            
            if(node == parser->_renderNode)
                break;
            
            node = node->next;
        }
    }
    
    
    return true;
}



void HTMLRenderer::node_serialization(myhtml_tree_t* html_tree, modest_render_tree_node_t* node, mycore_callback_serialize_f callback, modest* modest , void*context)
{
    callback("<", 1, context);
    
    switch (node->type) {
        case MODEST_RENDER_TREE_NODE_TYPE_BLOCK:
            callback("block", 5, context);
            break;
            
        case MODEST_RENDER_TREE_NODE_TYPE_VIEWPORT:
            callback("viewport", 8, context);
            break;
            
        case MODEST_RENDER_TREE_NODE_TYPE_ANONYMOUS:
            callback("anonymous", 9, context);
            break;
            
        default:
            break;
    }
    
    if(node->html_node)
    {
        size_t tag_length = 0;
        const char *tag_name = myhtml_tag_name_by_id(html_tree, node->html_node->tag_id, &tag_length);
        
        callback(" ", 1, context);
        callback(tag_name, tag_length, context);
        
        myhtml_tree_attr_t *attr_style = myhtml_attribute_by_key(node->html_node, "style", 5);
        
        if(attr_style)
        {
            //printf("Got attr style");
            mycss_declaration_entry_t *dec_entry = mycss_declaration_parse( modest->mycss_entry->declaration ,// css_entry->declaration,
                                                                           MyENCODING_UTF_8,
                                                                           attr_style->value.data,
                                                                           attr_style->value.length,
                                                                           NULL);
            //print_entries(modest->mycss_entry, dec_entry);
            
            mycss_declaration_entry_t* next = dec_entry;
            while (next)
            {
                
                if( next->type == MyCSS_PROPERTY_TYPE_WIDTH)
                {
                    printf("Has width prop : ");
                    //printf("Value type : %x\n" ,next->value_type );
                    if( next->value_type == MyCSS_PROPERTY_WIDTH__LENGTH)
                    {
                        printf(" in pixels");
                    }
                    else if( next->value_type == MyCSS_PROPERTY_WIDTH__PERCENTAGE)
                    {
                        printf(" in percents ");
                        
                    }
                    
                    mycss_values_length_t* val = (mycss_values_length_t*) next->value;
                    
                    if( val->is_float)
                    {
                        const float *v = (float*) next->value;
                        printf( " float value : %f" , *v);
                    }
                    else
                    {
                        const int *v = (int*) next->value;
                        printf( " int value : %i" , *v);
                    }
                    printf("\n");
                }
                else if( next->type == MyCSS_PROPERTY_TYPE_HEIGHT)
                {
                    printf("Has height prop\n");
                }
                else if( next->type == MyCSS_PROPERTY_TYPE_BACKGROUND_IMAGE)
                {
                    printf("Has BACKGROUND_IMAGE prop");
                }
                else if( next->type == MyCSS_PROPERTY_TYPE_BACKGROUND)
                {
                    printf("Has BACKGROUND SOLID prop");
                    
                    //const mycss_values_color_t* color = (const mycss_values_color_t*) next->value;
                    
                    
                    mycss_values_background_list_t *list =(mycss_values_background_list_t *) next->value;
                    
                    for(size_t i = 0; i < list->entries_length; i++)
                    {
                        mycss_values_background_t* bg = &list->entries[i];
                        
                        
                        if(bg->color)
                        {
                            if( bg->color->value_type == MyCSS_PROPERTY_VALUE__COLOR)
                            {
                                mycss_values_color_t* colorVal = (mycss_values_color_t*)bg->color->value;
                                
                                if( colorVal->type == MyCSS_VALUES_COLOR_TYPE_RGBA)
                                {
                                    if(colorVal->type_value == MyCSS_VALUES_COLOR_TYPE_VALUE_PERCENTAGE)
                                    {
                                        printf("Color percent \n");
                                    }
                                    else if(colorVal->type_value == MyCSS_VALUES_COLOR_TYPE_VALUE_NUMBER)
                                    {
                                        printf("Color Num r %i g %i b %i a %i\n" ,
                                               colorVal->value.rgba_number.r.value.i,
                                               colorVal->value.rgba_number.g.value.i,
                                               colorVal->value.rgba_number.b.value.i,
                                               colorVal->value.rgba_number.alpha.value.number.value.i
                                               );
                                    }
                                }
                            }
                        }
                    }
                    
                    
                }
                else
                {
                    printf("Unknown prop  %x\n" , next->type);
                }
                next = next->next;
            }
            
        }
        const char* txt = myhtml_node_text( node->html_node, NULL);
        if( txt && !is_empty(txt))
        {
            printf("Text = '%s'" , txt);
        }
        
    }
    
    
    
    callback(">", 1, context);
}

