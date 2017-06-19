//
//  WebView.cpp
//  RenderKit
//
//  Created by Manuel Deneu on 10/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "CLApplication.hpp"
#include "WebView.hpp"

//#include "HTMLParser.hpp"


WebView::WebView():
_doc(nullptr),
delegate(nullptr)
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
    if( delegate)
        return delegate->refreshRequest( *this);
    
    return false;
}

bool WebView::openDocument( Document *doc)
{
    if( !doc)
        return false;
    
    
    if( _parser.load(*doc, doc->_docContent.c_str() , doc->_docContent.size()))
    {
        
        return setDocument( doc );
    }
    return false;
}

bool WebView::setDocument( Document *doc)
{
    _doc = doc;
    bool ret = false;
    
    if( _renderer.prepare(*doc))
    {
        
        assert(_renderer.render( getSize(), *doc));
        
        _renderer.printBlockTree();
        
        setNeedsRedraw();
        
        if( delegate)
        {
            delegate->didLoadDocument(*this);
        }
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

/*static*/ void WebView::computeContentHeight(GXContext* context , HTMLBlockElement* block)
{
    const GXPoint sP = GXPointMakeNull();
    GXSize min = GXSizeInvalid;
    GXSize max = GXSizeInvalid;
    context->getTextSize(sP, block->realSize.width, block->text, min , max);
    
    block->realSize.height = max.height;
    
    if( block->tagID == MyHTML_TAG_P)
    {
        float ascender = -1.f;
        float descender = -1.f;
        float lineh = -1.f;
        context->getTextMetrics( &ascender, &descender, &lineh);
        assert(lineh > 0);
        block->realSize.height += lineh *1.5;
    }
}

void WebView::drawBlock(GXContext* context , HTMLBlockElement* block , const GXPoint &pos )
{
    context->beginPath();
    assert(block->_parent || block == _renderer.getRoot());
    

    
    GXPoint realPos = pos;
    context->setFontId( context->getFontManager().getFont("SanFranciscoDisplay-Regular.ttf") );
    context->setFontSize(20.f);
    


    assert(block->size.width != -1 && block->size.wPercent == false);
    
    block->realSize.width = (int) block->size.width;
    block->realSize.height = (int) block->size.height;

    if( block->realSize.height == -1)
    {
        computeContentHeight(context , block);

    }
    
    
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
        if( block->frameWidth > 0)
        {
            context->setStrokeWidth(block->frameWidth );
        }
    }
    context->fill();
    if( block->drawFrame)
    {
        context->stroke();
    }
    

    if( !block->text.empty())
    {
        context->beginPath();
        context->setFillColor(GXColors::Black);
        GXPoint p = realPos;
        p.y+=15;
        context->addTextBox(p, block->realSize.width, block->text);
        //context->addText(p, block->text);
        printf("Draw text at %i %i  \n" , p.x , p.y );
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

