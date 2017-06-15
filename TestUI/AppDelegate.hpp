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


class AppDelegate : public CLApplicationDelegate , public WebViewController
{
public:
    
    bool refreshRequest( WebView& ) override;
protected:
    void applicationWillLoad( CLApplication* app) override;
    void applicationDidLoad( CLApplication* app) override;
    void applicationWillStop( CLApplication* app) override;
    
    WebView _webView;
    
    

};

#endif /* AppDelegate_hpp */
