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
#include "VKContextMenu.hpp"
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


class WebView : public VKView , public VKContextMenuController
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
    void contextMenuDidDismiss( VKContextMenu* ) override;
    void showContext( const GXPoint &at);
    bool handleFocus() override
    {
        return true;
    }
    bool keyPressed(  const GXKey &key ) override;
    bool touchEnded( const GXTouch &t) override;
    void paint( GXContext*  , const GXRect& ) override;
    void drawBlock(GXContext* context , HTMLBlockElement* block, const GXPoint &pos );
    
    static void computeContentHeight(GXContext* context , HTMLBlockElement* block);
    
    WebViewController* delegate;
    Document *_doc;
    DocumentParser _parser;
    HTMLRenderer _renderer;
    
    VKContextMenu* _menu;
    
};

#endif /* WebView_hpp */
