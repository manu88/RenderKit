#include <assert.h>
#include <stdio.h>

#include "FileSystem.hpp"
#include "HTMLRenderer.hpp"
#include "HTMLParser.hpp"

int main(int argc, const char * argv[])
{
    HTMLParser parser;
    
    const std::string html = FileSystem::getFileText( argv[1]);
    
    assert(parser.parseContent(html));
    assert(parser.render());
 
    printf("Title '%s'\n" , parser.getTitle().c_str());
    
    HTMLRenderer renderer;
    
    GXSize viewSize = GXSizeMake(1920, 1080);
    assert(renderer.render( viewSize, &parser));
    
    renderer.printBlockTree();

    return 0;
}


/*
 Copyright (C) 2016 Alexander Borisov
 
 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 
 Author: lex.borisov@gmail.com (Alexander Borisov)
 */
/*
#include <modest/modest.h>
#include <modest/finder/finder.h>
#include <modest/finder/thread.h>
#include <modest/glue.h>
#include <modest/declaration.h>
#include <modest/node/serialization.h>
#include <myhtml/serialization.h>

#define DIE(msg, ...) do { fprintf(stderr, msg, ##__VA_ARGS__); exit(EXIT_FAILURE); } while(0)
#define check_status(msg, ...) do {if(status) DIE(msg, ##__VA_ARGS__);} while(0)

mystatus_t serialization_callback(const char* data, size_t len, void* ctx)
{
    printf("%.*s", (int)len, data);
    return MyCORE_STATUS_OK;
}

myhtml_tree_t * parse_html(const char* data, size_t data_size, myhtml_callback_tree_node_f cai, void* cai_ctx)
{
    myhtml_t* myhtml = myhtml_create();
    mystatus_t status = myhtml_init(myhtml, MyHTML_OPTIONS_DEFAULT, 1, 0);
    
    check_status("Can't init MyHTML object\n");
    
    myhtml_tree_t* tree = myhtml_tree_create();
    status = myhtml_tree_init(tree, myhtml);
    
    check_status("Can't init MyHTML Tree object\n");
    
    myhtml_callback_tree_node_insert_set(tree, cai, cai_ctx);
    
    status = myhtml_parse(tree, MyENCODING_UTF_8, data, data_size);
    check_status("Can't parse HTML:\n%s\n", data);
    
    return tree;
}

mycss_entry_t * parse_css(const char* data, size_t data_size)
{
    // base init
    mycss_t *mycss = mycss_create();
    mystatus_t status = mycss_init(mycss);
    
    check_status("Can't init MyCSS object\n");
    
    // currenr entry work init
    mycss_entry_t *entry = mycss_entry_create();
    status = mycss_entry_init(mycss, entry);
    
    check_status("Can't init MyCSS Entry object\n");
    
    status = mycss_parse(entry, MyENCODING_UTF_8, data, data_size);
    check_status("Can't parse CSS:\n%s\n", data);
    
    return entry;
}

void get_properties_and_print(modest_t* modest, myhtml_tree_t* myhtml_tree, mycss_entry_t *mycss_entry)
{
    myhtml_collection_t *collection = myhtml_get_nodes_by_tag_id(myhtml_tree, NULL, MyHTML_TAG_DIV, NULL);
    if(collection == NULL || collection->length < 1) {
        DIE("Can't find HTML nodes\n");
    }
    
    myhtml_tree_node_t* node_div = collection->list[0];
    
    
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
                printf(" : float ");
            }
            printf("\n");
            next = next->next;
        }
    }
}

int main(int argc, const char * argv[])
{
    const char *html = "<div style=\"float:right\"></div>";
    const char *css = "div {padding: 130px 3em; color: rgba(23 10 200 / 0.4) }";
    

    modest_t *modest = modest_create();
    mystatus_t status = modest_init(modest);
    
    check_status("Can't init Modest object\n");
    
    modest->myhtml_tree = parse_html(html, strlen(html), modest_glue_callback_myhtml_insert_node, (void*)modest);
    modest->mycss_entry = parse_css(css, strlen(css));
    
    mycss_stylesheet_t *stylesheet = mycss_entry_stylesheet(modest->mycss_entry);
    

    modest_finder_t* finder = modest_finder_create();
    status = modest_finder_init(finder);
    
    check_status("Can't init Modest Finder object\n");
    

    modest_finder_thread_t *finder_thread = modest_finder_thread_create();
    modest_finder_thread_init(finder, finder_thread, 2);
    

    status = modest_finder_thread_process(modest, finder_thread, modest->myhtml_tree->node_html, stylesheet->sel_list_first);
    
    check_status("Can't find by selectors with thread\n");
    

    printf("Incoming stylesheet:\n\t");
    printf("%s\n\n", css);
    

    printf("Incoming tree:\n\t");
    myhtml_serialization_tree_callback(modest->myhtml_tree->node_html, serialization_callback, NULL);
    

    printf("\n\nResult for div node:\n");
    get_properties_and_print(modest, modest->myhtml_tree, modest->mycss_entry);
    

    modest_finder_thread_destroy(finder_thread, true);
    modest_finder_destroy(finder, true);
    

    mycss_stylesheet_destroy(stylesheet, true);
    

    myhtml_t* myhtml = modest->myhtml_tree->myhtml;
    myhtml_tree_destroy(modest->myhtml_tree);
    myhtml_destroy(myhtml);
    

    mycss_t* mycss = modest->mycss_entry->mycss;
    mycss_entry_destroy(modest->mycss_entry, true);
    mycss_destroy(mycss, true);
    
    modest_destroy(modest, true);
    
    return 0;
}


*/



