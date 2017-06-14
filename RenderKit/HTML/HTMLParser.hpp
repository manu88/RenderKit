//
//  HTMLParser.hpp
//  RenderKit
//
//  Created by Manuel Deneu on 10/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef HTMLParser_hpp
#define HTMLParser_hpp

#include <string>
#include <modest/modest.h>
#include <modest/render/tree_node.h>
#include <modest/finder/finder.h> // modest_finder_t
#include <modest/finder/myosi.h> // modest_finder_thread_t



class HTMLParser
{
public:
    
    enum{ FinderThreadsNum = 2};
    
    HTMLParser();
    ~HTMLParser();
    
    std::string getTitle() const;
    
    bool parseContent( const std::string &buf);
    bool parseContent( const char* buf , size_t len);
    
    bool render();
    
    mycss_t* _cssParser;
    modest_t *_modest;
    modest_finder_t* _finder;
    modest_finder_thread_t *_finderThread;
    modest_render_tree_node_t * _renderNode;
    
private:
    myhtml_tree_t * parse_html(const char* data, size_t data_size);
    bool parseCSS();
    mycss_entry_t * parseCSS(const char* data, size_t data_size);
    
    
    void parseHTML();

};

#endif /* HTMLParser_hpp */
