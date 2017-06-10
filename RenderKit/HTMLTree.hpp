//
//  HTMLParser.hpp
//  RenderKit
//
//  Created by Manuel Deneu on 02/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef HTMLTree_hpp
#define HTMLTree_hpp

#include <myhtml/myhtml.h>

class HTMLTree
{
public:
    HTMLTree();
    ~HTMLTree();
    
    bool parseContent( const char* buf , size_t len);
    
    myhtml_tree_t *_tree;
    myhtml_t* _html;
private:
    
    
    
};

#endif /* HTMLTree_hpp */
