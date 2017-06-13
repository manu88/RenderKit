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
#include "FileSystem.hpp"

WebView::WebView():
_parser(nullptr)
{
    background = GXColors::White;
}

WebView::~WebView()
{
    if( _parser)
    {
        delete _parser;
    }
}

std::string WebView::getTitle() const
{
    return _parser->getTitle();
}


bool WebView::refresh()
{
    if( _currentURL.empty())
        return false;
    
    
    return openFile(getCurrentURL());
}

bool WebView::openFile( const std::string &file)
{
    if( !_parser)
    {
        _parser = new HTMLParser();
    }
    
    assert( _parser );
    
    const std::string html = FileSystem::getFileText( file);

    bool ret = _parser->parseContent(html.c_str(), strlen(html.c_str()));
    
    if( ret)
    {
        if( !_parser->render())
        {
            ret = false;
        }
        else
        {
            // we're ok
            printf("Parse OK \n");
            
            assert(_renderer.render( getSize(), _parser));
            
            _currentURL = file;
            _renderer.printBlockTree();
            
            CLApplication::instance()->setName( getTitle() );
            setNeedsRedraw();
        }
        
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
    
    printf("Paint %s block at %i %i " ,block->tag.c_str() , realPos.x , realPos.y);
    
    
    
    //GXSize realSize = GXSizeInvalid;

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
        printf("Float right");
        realPos.x = block->_parent->_xFloatRight - block->realSize.width;
        block->_parent->_xFloatRight -= block->realSize.width;
    }
    
    
    context->beginPath();
    printf(" Add rect %i %i %i %i " , realPos.x , realPos.y , block->realSize.width , block->realSize.height);
    context->addRect(GXRectMake( realPos, block->realSize));

    context->setFillColor( block->backgroundColor);

    context->fill();

    printf("\n");
    
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

