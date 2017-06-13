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

    bool refresh();
    bool openFile( const std::string &file);
    
    const std::string &getCurrentURL() const noexcept
    {
        return _currentURL;
    }
    
private:
    bool handleFocus() override
    {
        return true;
    }
    bool keyPressed(  const GXKey &key ) override;
    
    void paint( GXContext*  , const GXRect& ) override;
    void drawBlock(GXContext* context , HTMLBlockElement* block, const GXPoint &pos );
    
    
    std::string _currentURL;
    HTMLParser *_parser;
    HTMLRenderer _renderer;
};

#endif /* WebView_hpp */
