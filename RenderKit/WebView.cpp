//
//  WebView.cpp
//  RenderKit
//
//  Created by Manuel Deneu on 10/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "CLApplication.hpp"
#include "WebView.hpp"
#include "HTMLParser.hpp"


WebView::WebView():
_doc(nullptr)
{
    background = GXColors::White;
}

WebView::~WebView()
{
}

std::string WebView::getTitle() const
{
    return _doc->getTitle();
}


bool WebView::refresh()
{
    return setDocument( _doc );
}

bool WebView::setDocument( Document *doc)
{
    _doc = doc;
    bool ret = false;
    
    if( _renderer.prepare(*doc))
    {
        
        assert(_renderer.render( getSize(), *doc));
        
        _renderer.printBlockTree();
        
        CLApplication::instance()->setName( getTitle() );
        setNeedsRedraw();
        return true;
    }
    return ret;

}

bool WebView::keyPressed(  const GXKey &key )
{
    if (key.key == GXKey_R)
    {
        printf("Start Refresh \n");
        refresh();
        return true;
    }
    
    return false;
}

void WebView::paint( GXContext* ctx , const GXRect& rect )
{
    assert(_renderer.getRoot() );
    
    GXPoint p = GXPointMake(0, 0);
    
    printf("Paint webView \n");

    drawBlock(ctx , _renderer.getRoot(), p );

}


void WebView::drawBlock(GXContext* context , HTMLBlockElement* block , const GXPoint &pos )
{
    
    assert(block->_parent || block == _renderer.getRoot());
    
    GXPoint realPos = pos;
    context->setFontId( context->getFontManager().getFont("SanFranciscoDisplay-Regular.ttf") );
    context->setFontSize(20.f);
    


    assert(block->size.width != -1 && block->size.wPercent == false);
    
    block->realSize.width = (int) block->size.width;
    block->realSize.height = (int) block->size.height;

    if( block->realSize.height == -1)
        return;
    
    if( block->size.hPercent)
    {
        block->realSize.height *= block->_parent->size.height * 0.01f;
    }
    
    assert( block->realSize.height != -1);
    
    
    if( block->floatProp == MyCSS_PROPERTY_FLOAT_RIGHT)
    {
        realPos.x = block->_parent->_xFloatRight - block->realSize.width;
        block->_parent->_xFloatRight -= block->realSize.width;
    }
    
    
    context->beginPath();

    context->addRect(GXRectMake( realPos, block->realSize));

    context->setFillColor( block->backgroundColor);

    if( block->drawFrame)
    {
        context->setStrokeColor(GXColors::Black);
    }
    context->fill();
    if( block->drawFrame)
    {
        context->stroke();
    }
    

    
    
    GXPoint cPos = realPos;
    for (HTMLBlockElement* c : block->_children)
    {
        drawBlock(context , c , cPos );
        if( c->floatProp == MyCSS_PROPERTY_FLOAT_UNSET)
        {
            cPos.y += c->realSize.height;
        }
    }

}

