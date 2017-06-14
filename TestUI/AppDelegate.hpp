//
//  AppDelegate.hpp
//  RenderKit
//
//  Created by Manuel Deneu on 10/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef AppDelegate_hpp
#define AppDelegate_hpp

#include "CLApplicationDelegate.hpp"

#include "WebView.hpp"
#include "HTMLParser.hpp"
class AppDelegate : public CLApplicationDelegate
{
public:
    
    
protected:
    void applicationWillLoad( CLApplication* app) override;
    void applicationDidLoad( CLApplication* app) override;
    void applicationWillStop( CLApplication* app) override;
    
    WebView _webView;
    HTMLParser _parser;
};

#endif /* AppDelegate_hpp */
