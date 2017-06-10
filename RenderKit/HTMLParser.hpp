//
//  HTMLParser.hpp
//  RenderKit
//
//  Created by Manuel Deneu on 10/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef HTMLParser_hpp
#define HTMLParser_hpp


#include "HTMLTree.hpp"
#include "CSSParser.hpp"

class HTMLParser
{
public:
    HTMLParser();
    ~HTMLParser();
    
    
    bool parseContent( const char* buf , size_t len);
private:
    
    void parseHTML();
    void print_entries(mycss_entry_t* entry, mycss_declaration_entry_t* declr_entry);
    
    CSSParser _cssParser;
    HTMLTree  _htmlTree;
};

#endif /* HTMLParser_hpp */
