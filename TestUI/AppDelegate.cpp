//
//  AppDelegate.cpp
//  RenderKit
//
//  Created by Manuel Deneu on 10/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "AppDelegate.hpp"
#include "CLApplication.hpp"
#include "FileSystem.hpp"

void AppDelegate::applicationWillLoad( CLApplication* app)
{
    app->setName("WebKit");
    
    app->setKeyboardResponder( &_webView);
    
    app->pushView(&_webView);

    const std::string file = "/Users/manueldeneu/Documents/projets/dev/RenderKit/test2.html";
    const std::string html = FileSystem::getFileText( file);
    
    
    doc = new Document;
    
    
    assert( _parser.parseContent(*doc, html));
    
    if(_webView.setDocument( doc))
    {
        
    }
    
    
}

void AppDelegate::applicationDidLoad( CLApplication* app)
{
    
}

void AppDelegate::applicationWillStop( CLApplication* app)
{
    delete doc;
}
