//
//  AppDelegate.cpp
//  RenderKit
//
//  Created by Manuel Deneu on 10/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "AppDelegate.hpp"
#include "CLApplication.hpp"

void AppDelegate::applicationWillLoad( CLApplication* app)
{
    app->setName("WebKit");
    
    app->pushView(&_webView);
    
    if(_webView.openFile("/Users/manueldeneu/Documents/projets/dev/RenderKit/test2.html"))
    {
        app->setName(_webView.getTitle());
        app->getCurrentView()->setNeedsRedraw();
    }
}

void AppDelegate::applicationDidLoad( CLApplication* app)
{
    
}

void AppDelegate::applicationWillStop( CLApplication* app)
{
    
}
