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




class HTMLParser
{
public:
    HTMLParser();
    ~HTMLParser();
    
    std::string getTitle() const;
    
    bool parseContent( const std::string &buf);
    bool parseContent( const char* buf , size_t len);
    
    bool render();
    
    modest_t *_modest;
    modest_render_tree_node_t * _renderNode;
    
private:
    
    void parseHTML();
    
    
    
    
    
    
};

#endif /* HTMLParser_hpp */
