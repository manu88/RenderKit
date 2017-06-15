//
//  DocumentParser.hpp
//  RenderKit
//
//  Created by Manuel Deneu on 15/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef DocumentParser_hpp
#define DocumentParser_hpp

#include <modest/finder/finder.h>
#include <modest/finder/thread.h>
#include <string>
class Document;

class DocumentParser
{
public:
    DocumentParser();
    ~DocumentParser();
    
    bool load( Document & , const char* buffer , size_t bufLen);
    
    
    static void get_properties_and_print(modest_t* modest,mycss_entry_t *mycss_entry, myhtml_tree_node_t* node);
    
private:
    myhtml_tree_t *parse_html(const char* data, size_t data_size, myhtml_callback_tree_node_f cai, modest_t* modest);
    mycss_entry_t *parse_css(const char* data, size_t data_size);
    
    bool createHTMLParser();
    bool createCSSParser();
    bool createFinder();
    
    myhtml_t* _myhtml;
    mycss_t* _mycss;
    modest_finder_t* finder;
    modest_finder_thread_t *finder_thread;
    mycss_stylesheet_t *stylesheet;
};

#endif /* DocumentParser_hpp */
