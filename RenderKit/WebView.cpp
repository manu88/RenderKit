//
//  WebView.cpp
//  RenderKit
//
//  Created by Manuel Deneu on 10/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "WebView.hpp"
#include "HTMLParser.hpp"
#include "FileSystem.hpp"
#include "HTMLRenderer.hpp"
WebView::WebView():
_parser(nullptr)
{
    background = GXColors::White;
}

WebView::~WebView()
{
    if( _parser)
    {
        delete _parser;
    }
}

std::string WebView::getTitle() const
{
    return _parser->getTitle();
}

bool WebView::openFile( const std::string &file)
{
    if( !_parser)
    {
        _parser = new HTMLParser();
    }
    
    const std::string html = FileSystem::getFileText( file);

    
    
    bool ret = _parser->parseContent(html.c_str(), strlen(html.c_str()));
    
    if( ret)
    {
        if( !_parser->render())
        {
            ret = false;
        }
        
    }
    return ret;
}

void WebView::paint( GXContext* ctx , const GXRect& rect )
{
    printf("Paint webView \n");
    HTMLRenderer renderer;
    
    assert(renderer.render( _parser));
}
