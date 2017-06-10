//
//  WebView.cpp
//  RenderKit
//
//  Created by Manuel Deneu on 10/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "WebView.hpp"
#include "HTMLTree.hpp"
#include "FileSystem.hpp"

WebView::WebView():
_tree(nullptr)
{
    background = GXColors::White;
}

WebView::~WebView()
{
    if( _tree)
    {
        delete _tree;
    }
}

bool WebView::openFile( const std::string &file)
{
    if( !_tree)
    {
        _tree = new HTMLTree();
    }
    
    const std::string html = FileSystem::getFileText( file);
    
    _tree->parseContent(html.c_str(), strlen(html.c_str()));
    
    return false;
}
