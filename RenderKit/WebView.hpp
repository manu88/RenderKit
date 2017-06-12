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
#include "HTMLRenderer.hpp"

class HTMLParser;

class WebView : public VKView
{
public:
    WebView();
    ~WebView();
    
    std::string getTitle() const;
    
    
    bool openFile( const std::string &file);
private:
    void paint( GXContext*  , const GXRect& ) override;
    
    HTMLParser *_parser;
    HTMLRenderer _renderer;
};

#endif /* WebView_hpp */
