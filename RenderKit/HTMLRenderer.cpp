//
//  HTMLRenderer.cpp
//  RenderKit
//
//  Created by Manuel Deneu on 11/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//


#include <assert.h>
#include <ctype.h>
#include <functional>
#include <modest/declaration.h>

#include "CSSColors.hpp"
#include "HTMLRenderer.hpp"
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

HTMLRenderer::HTMLRenderer():
_root(nullptr)
{
    
}

HTMLRenderer::~HTMLRenderer()
{
    
}


bool HTMLRenderer::render( const GXSize& viewPortSize, HTMLParser* parser )
{
    assert(parser);
    assert(viewPortSize.height > 0 && viewPortSize.width > 0);
    
    printf("Render size %i %i \n" , viewPortSize.width , viewPortSize.height);
    
    
    if( _root)
    {
        delete _root;
        _root = nullptr;
    }
    
    
    assert(_root == nullptr);
    modest_render_tree_node_t* node = parser->_renderNode;
    size_t depth = 0;
    
    
    HTMLBlockElement* current = nullptr;
    while(node)
    {
        /* We skip html & body nodes */
        if( node->html_node)
        {
            const char *tag = myhtml_tag_name_by_id( parser->_modest->myhtml_tree, node->html_node->tag_id, NULL/*tag_length*/);
            if(  strcmp(tag, "html") == 0 || strcmp(tag, "body") == 0)
            {
                node = node->child;
                continue;
            }
        }
        
        /* **** **** **** **** **** **** **** **** **** **** */
        
        if( current == nullptr)
        {
            current = new HTMLBlockElement;
            current->_parent = nullptr;
            _root = current;
            
            
        }
        
        if(node_serialization(current , parser->_modest, node ))
        {
            
        }
        
        
        if(node->child)
        {
            depth++;
            node = node->child;
            
            
            
            //
            
            HTMLBlockElement* p = current;
            current = new HTMLBlockElement;
            //current->size = p->size;
            current->_parent = p;
            p->_children.push_back(current);
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
            
            HTMLBlockElement* parent = current->_parent;
            current = new HTMLBlockElement;
            //current->size = parent->size;
            current->_parent = parent;
            parent->_children.push_back(current);
        }
    }
    
    
    _root->size = { (float)viewPortSize.width  , (float)viewPortSize.height , false , false};
    
    
    return computeTree();
}

bool HTMLRenderer::computeTree()
{
    assert(_root);
    
    printf("\nCompute Tree\n");
    
    std::function<void(HTMLBlockElement*) > computeBlock = [&computeBlock] (HTMLBlockElement* block)
    {
        if( block->size.width == -1)
        {
            block->size.width = block->_parent->size.width;
            block->size.wPercent = block->_parent->size.wPercent;
        }
        
        if( block->size.wPercent)
        {
            block->size.width *= block->_parent->size.width / 100.f;
            block->size.wPercent = false;
            
            block->_parent->_xFloatRight = block->_parent->size.width;
        }
        
        float maxHeight = -1;
        for( HTMLBlockElement* c : block->_children)
        {
            computeBlock(c);
            
            if( c->size.height > maxHeight)
            {
                maxHeight =  c->size.height;
            }
        }
        
        if( block->size.height == -1)
        {
            //printf("Max Height = %f\n" , maxHeight);
            block->size.height = maxHeight;
            block->size.hPercent = false;
        }
    };
    
    assert(_root->size.width != -1 && _root->size.height != -1);
    
    computeBlock(_root);
    return true;
}

void HTMLRenderer::printBlockTree() const
{
    printf("List Root \n");
    assert(_root);
    
    //int tab = 0;
    std::function<void( const HTMLBlockElement* , int) > printBlock = [&printBlock] ( const HTMLBlockElement* block , int tab)
    {
        //assert(block->_parent);
        for(int i = 0 ; i< tab ; i++)
            printf("\t");
        
        printf("Got child (type %i) %s ", block->type , block->tag.c_str());
        printf("size w=%f %s h=%f %s %s",
               block->size.width,
               block->size.wPercent?"%" : "px" ,
               block->size.height ,
               block->size.hPercent?"%" : "px",
               block->drawFrame?"with frame":"");
        printf("\n");
        
        for ( const HTMLBlockElement* c : block->_children)
        {
            printBlock(c , tab+1);
        }
        
    };
    
    printBlock(_root , 0);
}


bool HTMLRenderer::addChild(HTMLBlockElement*block ,modest* modest, const HTMLNode& node , modest_render_tree_node_t* parent)
{
    myhtml_tree_node_t* htmlNode = node._node;
    
    assert(block);
    assert(block->_parent);
    
    assert(parent);
    assert(modest);
    assert(htmlNode);

    block->tag = node.getTagName();
    printf(" %s" , node.getTagName().c_str());

    
    /* Start class ATTR */
    HTMLAttribute attrClass = node.getAttributeByName("class");
    
    if( attrClass.isValid())
    {
        const char* classSel = attrClass.getValue();
        
        printf("Class : '%s'" , classSel);
    }
    /* END class ATTR */
    
    
    /* Start Style ATTR */
    
    mycss_declaration_entry_t *borderStyle = modest_declaration_by_type(modest, htmlNode, MyCSS_PROPERTY_TYPE_BORDER_STYLE);//MyCSS_PROPERTY_TYPE_BORDER);
    
    
    if( borderStyle)// && border->value)
    {
        block->drawFrame = true;
    }
    
    HTMLAttribute attr_style = node.getAttributeByName("style");

    if(attr_style.isValid())
    {
        
        const mycss_declaration_entry_t *dec_entry = node.parseDeclaration(MyENCODING_UTF_8,
                                                                           modest->mycss_entry->declaration,
                                                                           attr_style);
        
        const mycss_declaration_entry_t* next = dec_entry;
        while (next)
        {

            if( next->type == MyCSS_PROPERTY_TYPE_WIDTH)
            {
                block->size.width = parseBlockWidth(next);
                if( next->value_type == MyCSS_PROPERTY_WIDTH__LENGTH)
                {
                    //printf(" in pixels ");
                    block->size.wPercent = false;
                }
                else if( next->value_type == MyCSS_PROPERTY_WIDTH__PERCENTAGE)
                {
                    //printf(" in percents ");
                    block->size.wPercent = true;
                    
                }
                
            }
            else if( next->type == MyCSS_PROPERTY_TYPE_HEIGHT)
            {
                block->size.height = parseBlockHeight(next);
                
                if( next->value_type == MyCSS_PROPERTY_HEIGHT__LENGTH)
                {
                    //printf(" in pixels ");
                    block->size.hPercent = false;
                }
                else if( next->value_type == MyCSS_PROPERTY_HEIGHT__PERCENTAGE)
                {
                    //printf(" in percents ");
                    block->size.hPercent = true;
                    
                }
            }
            else if( next->type == MyCSS_PROPERTY_TYPE_BACKGROUND_IMAGE)
            {
                assert(false); // todo
            }
            else if( next->type == MyCSS_PROPERTY_TYPE_BACKGROUND)
            {
                const GXColor col =  parseBackgroundColor(next);
                
                block->backgroundColor = col;
            }
            else if (next->type == MyCSS_PROPERTY_TYPE_BORDER_STYLE)
            {
                //mycss_values_border_t
                block->drawFrame = true;
            }
            else if( next->type == MyCSS_PROPERTY_TYPE_FLOAT)
            {
                block->floatProp =(const mycss_property_float_t) next->value_type;
            }
            
            else
            {
                printf("Unknown prop  %x\n" , next->type);
                assert(false);
            }
            next = next->next;
        }
    }
    
    /* END Style ATTR */

    for ( const auto &iter : node )
    {
        assert(iter._node && iter._modest->myhtml_tree);

        const std::string text = iter.getText();
        
        if( !text.empty() && !is_empty(text.c_str()))
        {
            block->text = text;
        }

    }
    
    HTMLAttribute imgAttr = node.getAttributeByName("src");
    
    if( imgAttr.isValid())
    {
        const char* imgSrc = imgAttr.getValue();
        assert(imgSrc);
        //printf("Img res = '%s' \n" , imgSrc);
        block->src  = imgSrc;
        
    }

    return true;
    
}

bool HTMLRenderer::node_serialization( HTMLBlockElement* block , modest* modest, modest_render_tree_node_t* node )
{
    assert(block);
    
    modest_render_tree_node_t* n = node->parent;
    
    printf("\n");
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
            HTMLNode htmlNode(node->html_node , modest );
            
            block->type = HTMLBlockElement::Block;
            
            if(addChild(block, modest, htmlNode , node->parent))
            {
            
                if( !block->text.empty())
                {
                    //printf(" text '%s' ",block->text.c_str() );
                }
                if( block->backgroundColor != GXColorInvalid)
                {
                    printf(" backColor %f %f %f %f" ,
                           block->backgroundColor.r , block->backgroundColor.g , block->backgroundColor.b , block->backgroundColor.a );
                }
                if( block->size != ESizeInvalid )
                {
                    printf(" size %f %f" , block->size.width , block->size.height);
                }
                if(  block->size.height == -1  )
                {
                    printf("No size defined\n");
                }
            }
            break;
        }
        case MODEST_RENDER_TREE_NODE_TYPE_VIEWPORT:
            printf("viewport");
            block->type = HTMLBlockElement::Viewport;
            
            break;
            
        case MODEST_RENDER_TREE_NODE_TYPE_ANONYMOUS:
            printf("anonymous");
            break;
            
        default:
            break;
    }
    
    
    
    printf(">");
    
    return true;
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
        //printf(" in pixels ");
    }
    else if( node->value_type == MyCSS_PROPERTY_WIDTH__PERCENTAGE)
    {
        //printf(" in percents ");
    }
    
    return parseFloatIntAttribute(node);
}

float HTMLRenderer::parseBlockHeight( const mycss_declaration_entry_t* node)
{
    assert(node);
    
    if( node->value_type == MyCSS_PROPERTY_HEIGHT__LENGTH)
    {
        //printf(" in pixels ");
    }
    else if( node->value_type == MyCSS_PROPERTY_HEIGHT__PERCENTAGE)
    {
        //printf(" in percents ");
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
                    
                    if( CSSColor::ColorsNames.count( name))
                    {
                        retColor = CSSColor::ColorsNames.at(name);
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


