//
//  WebView.hpp
//  RenderKit
//
//  Created by Manuel Deneu on 10/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef WebView_hpp
#define WebView_hpp

#include <string>
#include "VKView.hpp"

class HTMLParser;

class WebView : public VKView
{
public:
    WebView();
    ~WebView();
    
    bool openFile( const std::string &file);
private:
    
    HTMLParser *_parser;
};

#endif /* WebView_hpp */
