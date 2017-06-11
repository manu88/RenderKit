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


/*static*/ std::unordered_map<const char* , const GXColor> HTMLRenderer::ColorsNames =
{
    { "red"  , GXColors::Red},
    { "blue" , GXColors::Blue}
};



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


bool HTMLRenderer::render(HTMLParser* parser )
{
    assert(parser);
    
    
    modest_render_tree_node_t* node = parser->_renderNode;
    size_t depth = 0;
    
    while(node)
    {
        
        node_serialization(parser->_modest, node );
        
        printf("\n");
        if(node->child)
        {
            depth++;
            node = node->child;
        }
        else
        {
            while(node != parser->_renderNode && node->next == NULL)
            {
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


HTMLBlockElement HTMLRenderer::addChild(modest* modest, const HTMLNode& node , modest_render_tree_node_t* parent)
{
    myhtml_tree_node_t* htmlNode = node._node;
    HTMLBlockElement block;
    assert(parent);
    assert(modest);
    assert(htmlNode);

    printf(" %s" , node.getTagName().c_str());
    
    
    const myhtml_tree_attr_t *attr_style = node.getAttributeByName("style");

    if(attr_style)
    {
        const mycss_declaration_entry_t *dec_entry = node.parseDeclaration(MyENCODING_UTF_8,modest->mycss_entry->declaration, attr_style);
        
        const mycss_declaration_entry_t* next = dec_entry;
        while (next)
        {
            
            if( next->type == MyCSS_PROPERTY_TYPE_WIDTH)
            {
                block.size.width = parseBlockWidth(next);
                printf("Width %i \n" , block.size.width );
   
            }
            else if( next->type == MyCSS_PROPERTY_TYPE_HEIGHT)
            {
                block.size.height = parseBlockHeight(next);
                printf("height %i \n" , block.size.height );
            }
            else if( next->type == MyCSS_PROPERTY_TYPE_BACKGROUND_IMAGE)
            {
                assert(false); // todo
            }
            else if( next->type == MyCSS_PROPERTY_TYPE_BACKGROUND)
            {
                const GXColor col =  parseBackgroundColor(next);
                
                block.backgroundColor = col;
                printf("GXColor = %f %f %f %f \n" , col.r , col.g , col.b  ,col.a );

            }//
            else
            {
                printf("Unknown prop  %x\n" , next->type);
                assert(false);
            }
            next = next->next;
        }
        
    }

    

    myhtml_tree_node_t* c = node._node->child;
    
    size_t c1 = 0;
    size_t c2 = 0;
    while (c)
    {
        c1++;
        const char* t = myhtml_node_text( c , NULL );
        if( t && !is_empty(t))
        {
            printf("Text1 '%s'\n" , t);
        }
        c = c->next;
    }
    
    for ( const auto &iter : node )
    {
        c2++;
        assert(iter._node && iter._tree);

        const std::string text = iter.getText();
        
        if( !text.empty() && !is_empty(text.c_str()))
        {
            printf("Text2 = '%s'\n" , text.c_str());
        }
        

    }
    assert( c1 == c2);
    return block;
}

void HTMLRenderer::node_serialization( modest* modest, modest_render_tree_node_t* node )
{

    modest_render_tree_node_t* n = node->parent;
    while (n)
    {
        printf("\t");
        n = n->parent;
    }
    printf("<");
    switch (node->type)
    {
        case MODEST_RENDER_TREE_NODE_TYPE_BLOCK:
        {
            printf("block");
            HTMLNode htmlNode(node->html_node , modest->myhtml_tree );
            
            addChild( modest, htmlNode , node->parent);
            break;
        }
        case MODEST_RENDER_TREE_NODE_TYPE_VIEWPORT:
            printf("viewport");
            break;
            
        case MODEST_RENDER_TREE_NODE_TYPE_ANONYMOUS:
            printf("anonymous");
            break;
            
        default:
            break;
    }
    
    
    
    printf(">");
}


/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */

/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */

float HTMLRenderer::parseFloatIntAttribute( const mycss_declaration_entry_t* node )
{
    assert(node);
    float retSize = -1;

    mycss_values_length_t* val = (mycss_values_length_t*) node->value;
    
    if( val->is_float)
    {
        const float *v = (float*) node->value;
        retSize = *v;
        
    }
    else
    {
        const int *v = (int*) node->value;
        retSize = (float)*v;
        
    }
    
    
    return retSize;
}
float  HTMLRenderer::parseBlockWidth( const mycss_declaration_entry_t* node)
{
    assert(node);

    
    if( node->value_type == MyCSS_PROPERTY_WIDTH__LENGTH)
    {
        printf(" in pixels ");
    }
    else if( node->value_type == MyCSS_PROPERTY_WIDTH__PERCENTAGE)
    {
        printf(" in percents ");
    }
    
    return parseFloatIntAttribute(node);
}

float HTMLRenderer::parseBlockHeight( const mycss_declaration_entry_t* node)
{
    assert(node);
    
    if( node->value_type == MyCSS_PROPERTY_HEIGHT__LENGTH)
    {
        printf(" in pixels ");
    }
    else if( node->value_type == MyCSS_PROPERTY_HEIGHT__PERCENTAGE)
    {
        printf(" in percents ");
        
    }
    
    return parseFloatIntAttribute(node);
}

GXColor HTMLRenderer::parseBackgroundColor( const mycss_declaration_entry_t* node)
{
    assert(node);
    GXColor retColor = GXColorInvalid;
    
    mycss_values_background_list_t *list =(mycss_values_background_list_t *) node->value;
    
    for(size_t i = 0; i < list->entries_length; i++)
    {
        mycss_values_background_t* bg = &list->entries[i];
        
        
        if(bg->color)
        {
            if( bg->color->value_type == MyCSS_PROPERTY_VALUE__COLOR)
            {
                mycss_values_color_t* colorVal = (mycss_values_color_t*)bg->color->value;
                
                if( colorVal->type == MyCSS_VALUES_COLOR_TYPE_NAMED)
                {
                    size_t length;
                    const char *name = mycss_values_color_name_by_id(colorVal->value.name_id, &length);
                    
                    if( ColorsNames.count( name))
                    {
                        retColor = ColorsNames.at(name);
                    }
                    else
                    {
                        assert(false);// color to add to ColorsNames
                    }
                }
                else if( colorVal->type == MyCSS_VALUES_COLOR_TYPE_RGBA)
                {
                    if(colorVal->type_value == MyCSS_VALUES_COLOR_TYPE_VALUE_PERCENTAGE)
                    {
                        printf("Color percent \n");
                        assert(false); // to do :)
                    }
                    else if(colorVal->type_value == MyCSS_VALUES_COLOR_TYPE_VALUE_NUMBER)
                    {
                        auto convValueCol = [](mycss_values_number_t& v)
                        {
                            return (float) v.is_float? v.value.f : v.value.i /255.f;
                        };
                        
                        retColor = GXColorMake( convValueCol(colorVal->value.rgba_number.r),
                                               convValueCol(colorVal->value.rgba_number.g),
                                               convValueCol(colorVal->value.rgba_number.b),
                                               convValueCol(colorVal->value.rgba_number.alpha.value.number)
                                               //colorVal->value.rgba_number.alpha.value.number.value.i / 255.f
                                               );
                    }
                }
            }
            else
            {
                assert(false);
                
            }
        }
    }
    
    return retColor;
}


