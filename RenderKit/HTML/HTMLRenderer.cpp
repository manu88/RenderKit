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
#include <modest/render/binding.h>

#include "CSSEntry.hpp"
#include "CSSColors.hpp"
#include "HTMLRenderer.hpp"
#include "HTMLParser.hpp"
#include "HTMLNode.hpp"

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
_renderTree(nullptr),
_root(nullptr)
{}

HTMLRenderer::~HTMLRenderer()
{}


bool HTMLRenderer::prepare(Document &doc)
{
    printf("HTMLRenderer::prepare\n");
    if( _renderTree)
    {
        //modest_render_tree_clean_all(_render);
        //modest_render_tree_destroy(_render , true);
        //_render = nullptr;
    }
    else
    {
        _renderTree = modest_render_tree_create();
        assert(modest_render_tree_init( _renderTree ) == 0);
    }
    
    doc._renderNode = modest_render_binding( doc._modest, _renderTree, doc._modest->myhtml_tree);
    
    return doc._renderNode != nullptr ;
}


bool HTMLRenderer::render( const GXSize& viewPortSize, Document& doc )
{
    printf("HTMLRenderer::render\n");
    assert(doc._modest);
    assert(viewPortSize.height > 0 && viewPortSize.width > 0);
    
    if( _root)
    {
        delete _root;
        _root = nullptr;
    }
    
    
    assert(_root == nullptr);
    modest_render_tree_node_t* node = doc._renderNode;
    size_t depth = 0;
    
    
    HTMLBlockElement* current = nullptr;
    while(node)
    {
        /* We skip html & body nodes */
        if( node->html_node)
        {
            const char *tag = myhtml_tag_name_by_id( doc._modest->myhtml_tree, node->html_node->tag_id, NULL/*tag_length*/);
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
        
        if(node_serialization(current , doc._modest, node ))
        {
            
        }
        
        if(node->child)
        {
            depth++;
            node = node->child;

            HTMLBlockElement* p = current;
            current = new HTMLBlockElement;
            //current->size = p->size;
            current->_parent = p;
            p->_children.push_back(current);
        }
        else
        {
            while(node != doc._renderNode && node->next == NULL)
            {
                depth--;
                node = node->parent;
            }
            
            if(node == doc._renderNode)
                break;
            
            node = node->next;
            
            HTMLBlockElement* parent = current->_parent;
            current = new HTMLBlockElement;

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


bool HTMLRenderer::addChild(HTMLBlockElement*block ,modest* modest, const HTMLNode& node )
{

    assert(block);
    assert(block->_parent); // just checking tree consistency
    assert(node.isValid());
    //assert(parentNode.isValid());
    assert(modest);
    

    myhtml_tree_node_t* htmlNode = node._node;
    assert(htmlNode);
    



    
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
                block->size.width =  CSSEntry::parseBlockWidth(next);
                if( next->value_type == MyCSS_PROPERTY_WIDTH__LENGTH)
                {
                    block->size.wPercent = false;
                }
                else if( next->value_type == MyCSS_PROPERTY_WIDTH__PERCENTAGE)
                {
                    block->size.wPercent = true;
                }
                
            }
            else if( next->type == MyCSS_PROPERTY_TYPE_HEIGHT)
            {
                block->size.height = CSSEntry::parseBlockHeight(next);
                
                if( next->value_type == MyCSS_PROPERTY_HEIGHT__LENGTH)
                {
                    block->size.hPercent = false;
                }
                else if( next->value_type == MyCSS_PROPERTY_HEIGHT__PERCENTAGE)
                {
                    block->size.hPercent = true;
                    
                }
            }
            else if( next->type == MyCSS_PROPERTY_TYPE_BACKGROUND_IMAGE)
            {
                assert(false); // todo
            }
            else if( next->type == MyCSS_PROPERTY_TYPE_BACKGROUND)
            {
                const GXColor col =  CSSEntry::parseBackgroundColor(next);
                
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

    for ( const HTMLNode& iter : node )
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
        block->src  = imgSrc;
        
    }

    return true;
    
}

bool HTMLRenderer::node_serialization( HTMLBlockElement* block , modest* modest, modest_render_tree_node_t* node )
{
    assert(block);
    
    switch (node->type)
    {
        case MODEST_RENDER_TREE_NODE_TYPE_BLOCK:
        {

            HTMLNode htmlNode(node->html_node , modest );
            
            block->type = HTMLBlockElement::Block;
            
            if( addChild(block, modest, htmlNode ) )
            {
                if( !block->text.empty())
                {
                    //printf(" text '%s' ",block->text.c_str() );
                }
                if( block->backgroundColor != GXColorInvalid)
                {
                }
                if( block->size != ESizeInvalid )
                {

                }
                if(  block->size.height == -1  )
                {

                }
            }
            break;
        }
        case MODEST_RENDER_TREE_NODE_TYPE_VIEWPORT:

            block->type = HTMLBlockElement::Viewport;
            
            break;
            
        case MODEST_RENDER_TREE_NODE_TYPE_ANONYMOUS:

            break;
            
        default:
            break;
    }
    
    
    

    
    return true;
}


/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */

/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */




