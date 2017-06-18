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

#include "Document.hpp"
#include "DocumentParser.hpp"
class HTMLParser;


class WebView;
class WebViewController
{
public:
    virtual ~WebViewController(){}
    
    virtual bool refreshRequest( WebView& )
    {
        return false;
    }
    
    virtual void didLoadDocument( WebView& )
    {}
protected:
    WebViewController(){}
};


class WebView : public VKView
{
public:
    WebView();
    ~WebView();
    
    std::string getTitle() const;

    bool refresh();
    bool openDocument( Document *);
    bool setDocument( Document *);
    Document* getDocument()
    {
        return _doc;
    }
    
    void setDelegate( WebViewController* ctl)
    {
        delegate = ctl;
    }
    
private:
    bool handleFocus() override
    {
        return true;
    }
    bool keyPressed(  const GXKey &key ) override;
    
    void paint( GXContext*  , const GXRect& ) override;
    void drawBlock(GXContext* context , HTMLBlockElement* block, const GXPoint &pos );
    
    static void computeContentheight(GXContext* context , HTMLBlockElement* block);
    
    WebViewController* delegate;
    Document *_doc;
    DocumentParser _parser;
    HTMLRenderer _renderer;
    
};

#endif /* WebView_hpp */
