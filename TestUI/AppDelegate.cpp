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
    _webView.setDelegate( this );
    app->setName("WebKit");
    
    app->setKeyboardResponder( &_webView);
    
    app->pushView(&_webView);

    refreshRequest(_webView);
    
}

void AppDelegate::didLoadDocument( WebView& view)
{
    assert(view.getDocument());
    
    if( !view.getDocument()->getTitle().empty())
    {
        CLApplication::instance()->setName(view.getDocument()->getTitle());
    }
}

bool AppDelegate::refreshRequest( WebView& view)
{
    const std::string file = "/Users/manueldeneu/Documents/projets/dev/RenderKit/test4.html";
    const std::string html = FileSystem::getFileText( file);
    
    Document* lastDoc = view.getDocument();
    if( lastDoc)
    {
        delete lastDoc;
    }
    
    Document *doc = new Document();
    doc->setContent( html);
    
    _webView.openDocument( doc);
    
    return true;
}

void AppDelegate::applicationDidLoad( CLApplication* app)
{
    
}

void AppDelegate::applicationWillStop( CLApplication* app)
{

}
