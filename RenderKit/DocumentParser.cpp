//
//  DocumentParser.cpp
//  RenderKit
//
//  Created by Manuel Deneu on 15/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include <assert.h>
#include <modest/modest.h>


#include <modest/glue.h>
#include <modest/declaration.h>
#include <modest/node/serialization.h>
#include <myhtml/serialization.h>

#include "DocumentParser.hpp"
#include "Document.hpp"


#define DIE(msg, ...) do { fprintf(stderr, msg, ##__VA_ARGS__); exit(EXIT_FAILURE); } while(0)
#define check_status(msg, ...) do {if(status) DIE(msg, ##__VA_ARGS__);} while(0)

DocumentParser::DocumentParser():
_myhtml(nullptr),
_mycss(nullptr),
finder(nullptr),
finder_thread(nullptr),
stylesheet(nullptr)
{
    
}

DocumentParser::~DocumentParser()
{

    modest_finder_thread_destroy(finder_thread, true);
    modest_finder_destroy(finder, true);
    
    if( _myhtml)
    {
        myhtml_destroy( _myhtml);
    }
    if( _mycss)
    {
        mycss_destroy( _mycss, true);
    }
    
}

mystatus_t serialization_callback(const char* data, size_t len, void* ctx)
{
    printf("%.*s", (int)len, data);
    return MyCORE_STATUS_OK;
}

bool DocumentParser::createHTMLParser()
{
    if( _myhtml == nullptr)
    {
        _myhtml = myhtml_create();
        mystatus_t status = myhtml_init( _myhtml, MyHTML_OPTIONS_DEFAULT, 1, 0);
        
        check_status("Can't init MyHTML object\n");
        
        return status == 0;
    }
    
    return _myhtml;
}

myhtml_tree_t* DocumentParser::parse_html(const char* data, size_t data_size, myhtml_callback_tree_node_f cai, modest_t* modest)
{
    assert(createHTMLParser());
    
    myhtml_tree_t* tree = myhtml_tree_create();
    mystatus_t status = myhtml_tree_init(tree, _myhtml );
    
    check_status("Can't init MyHTML Tree object\n");
    
    myhtml_callback_tree_node_insert_set(tree, cai, modest);
    
    status = myhtml_parse(tree, MyENCODING_UTF_8, data, data_size);
    check_status("Can't parse HTML:\n%s\n", data);
    
    return tree;
}


bool DocumentParser::createCSSParser()
{
    if( _mycss == nullptr)
    {
        _mycss = mycss_create();
        mystatus_t status = mycss_init( _mycss );
        
        return status == 0;
    }
    
    return _mycss;
}

mycss_entry_t* DocumentParser::parse_css(const char* data, size_t data_size)
{
    assert(createCSSParser());

    mystatus_t status = 0;
    
    check_status("Can't init MyCSS object\n");
    
    // currenr entry work init
    mycss_entry_t *entry = mycss_entry_create();
    status = mycss_entry_init( _mycss, entry);
    
    check_status("Can't init MyCSS Entry object\n");
    
    status = mycss_parse(entry, MyENCODING_UTF_8, data, data_size);
    check_status("Can't parse CSS:\n%s\n", data);
    
    return entry;
}


myhtml_collection_t * DocumentParser::get_properties_and_print(modest_t* modest,
                                                               myhtml_tree_t* myhtml_tree,
                                                               mycss_entry_t *mycss_entry ,
                                                               myhtml_tree_node_t* node)
{
    myhtml_collection_t *collection = myhtml_get_nodes_by_tag_id(myhtml_tree, NULL, MyHTML_TAG_DIV, NULL);
    
    if(collection == NULL || collection->length < 1)
    {
        DIE("Can't find HTML nodes\n");
    }
    
    myhtml_tree_node_t* node_div =  node;//collection->list[0];

    myhtml_tree_attr_t * styleAttr = myhtml_attribute_by_key( node_div, "style", strlen("style"));

    printf("CSS stylesheet \n");
    
    printf("\t");
    mycss_declaration_entry_t *padding_left = modest_declaration_by_type(modest, node_div, MyCSS_PROPERTY_TYPE_PADDING_LEFT);
    mycss_declaration_serialization_entry_by_type(mycss_entry, padding_left, MyCSS_PROPERTY_TYPE_PADDING_LEFT, serialization_callback, NULL);
    
    printf("\n\t");
    mycss_declaration_entry_t *color = modest_declaration_by_type(modest, node_div, MyCSS_PROPERTY_TYPE_COLOR);
    mycss_declaration_serialization_entry_by_type(mycss_entry, color, MyCSS_PROPERTY_TYPE_COLOR, serialization_callback, NULL);
    
    printf("\n\t");
    mycss_declaration_entry_t *display = modest_declaration_by_type(modest, node_div, MyCSS_PROPERTY_TYPE_DISPLAY);
    mycss_declaration_serialization_entry_by_type(mycss_entry, display, MyCSS_PROPERTY_TYPE_DISPLAY, serialization_callback, NULL);
    
    printf("\n\t");
    mycss_declaration_entry_t *floatV = modest_declaration_by_type(modest, node_div, MyCSS_PROPERTY_TYPE_FLOAT);
    mycss_declaration_serialization_entry_by_type(mycss_entry, floatV, MyCSS_PROPERTY_TYPE_FLOAT, serialization_callback, NULL);
    printf("\n");
    
    if( styleAttr)
    {
        mycss_declaration_entry_t *dec_entry = mycss_declaration_parse( mycss_entry->declaration ,
                                                                       MyENCODING_UTF_8,
                                                                       styleAttr->value.data,
                                                                       styleAttr->value.length,
                                                                       NULL);

        printf("Style attr : \n");

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
    
    return collection;
}

void DocumentParser::print( Document &doc )
{
    
}

bool DocumentParser::load(Document &doc)
{
    const char *html = "<html><head><style type=\"text/css\">div {padding: 130px 3em; color: rgba(23 10 200 / 0.4) }</style></head><body><div style=\"float:right\"></div>";
    //const char *css = "div {padding: 130px 3em; color: rgba(23 10 200 / 0.4) }";
    

    mystatus_t status = 0;

    doc.getModest()->myhtml_tree = parse_html(html, strlen(html), modest_glue_callback_myhtml_insert_node, doc.getModest());
    
    
    
    myhtml_collection_t *c = myhtml_get_nodes_by_tag_id( doc.getModest()->myhtml_tree, NULL, MyHTML_TAG_STYLE, &status);
    assert(status == 0 && c && c->length == 1);
    
    myhtml_tree_node_t* styleNode = c->list[0];
    
    const char *css =  myhtml_node_text(styleNode->child, NULL);
    assert(css);
    
    doc.getModest()->mycss_entry = parse_css(css, strlen(css));
    
    stylesheet = mycss_entry_stylesheet( doc.getModest()->mycss_entry);
    
    
    finder = modest_finder_create();
    status = modest_finder_init(finder);
    
    check_status("Can't init Modest Finder object\n");
    
    
    finder_thread = modest_finder_thread_create();
    modest_finder_thread_init(finder, finder_thread, 2);
    
    
    status = modest_finder_thread_process( doc.getModest(),
                                           finder_thread,
                                           doc.getModest()->myhtml_tree->node_html,
                                           stylesheet->sel_list_first
                                          );
    
    check_status("Can't find by selectors with thread\n");
        
    printf("Incoming stylesheet:\n\t");
    printf("%s\n\n", css);

    printf("Incoming tree:\n\t");
    myhtml_serialization_tree_callback( doc.getModest()->myhtml_tree->node_html, serialization_callback, NULL);
    
    

    

    return true;
}
