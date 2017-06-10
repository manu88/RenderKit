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
    
    _webView.openFile("/Users/manueldeneu/Documents/projets/dev/RenderKit/test.html");
}

void AppDelegate::applicationDidLoad( CLApplication* app)
{
    
}

void AppDelegate::applicationWillStop( CLApplication* app)
{
    
}
