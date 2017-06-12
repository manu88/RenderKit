//
//  WebView.cpp
//  RenderKit
//
//  Created by Manuel Deneu on 10/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

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

bool WebView::openFile( const std::string &file)
{
    if( !_parser)
    {
        _parser = new HTMLParser();
    }
    
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
            assert(_renderer.render( getSize(), _parser));
            
            _renderer.printBlockTree();
        }
        
    }
    return ret;
}

void WebView::paint( GXContext* ctx , const GXRect& rect )
{

    GXPoint p = GXPointMake(0, 0);
    ctx->setFontId( ctx->getFontManager().getFont("SanFranciscoDisplay-Regular.ttf") );
    ctx->setFontSize(20.f);
    
    printf("Paint webView \n");
    
    assert(_renderer.getRoot() );
    
    std::function<void(GXContext*, HTMLBlockElement*)> drawBlock
    = [&drawBlock,rect , &p] (GXContext* context , HTMLBlockElement* block )
    {
        
        printf("Paint %s block at %i %i \n" ,block->tag.c_str() , p.x , p.y);
        context->beginPath();
        
        GXSize realSize = GXSizeInvalid;
        int heightToAdd = 0;
        
        assert(block->size.width != -1 && block->size.wPercent == false);
        realSize.width = (int) block->size.width;
        realSize.height = (int) block->size.height;

        if( block->size.height == -1 && !block->text.empty())
        {
            
            const GXPoint textPoint = GXPointMake(p.x +10, p.y + 10);
            const float textW = block->size.width-10;
            GXSize min = GXSizeInvalid;
            GXSize max = GXSizeInvalid;
            context->getTextSize(textPoint, textW, block->text, min, max);
            
            realSize.height = max.height;
            printf("Real Height for %s : %i\n" , block->tag.c_str() , realSize.height);
            heightToAdd = realSize.height;
        }
        
        assert( realSize.height != -1);
        
        if( !block->text.empty())
        {
            
        }
        context->addRect(GXRectMake(p, realSize));
        /*
        if( block->tag == "img")
        {
            context->setFillColor(GXColors::Green);
            printf("Draw image '%s' \n" ,block->src.c_str() );
            const GXImageHandle img = context->createImage( "/Users/manueldeneu/Documents/projets/dev/RenderKit/" +block->src  , GXimageFlags_None );
            
            if( img != GXImageInvalid)
            {
                printf("Create image ok \n");
                GXPaint imgPaint = context->imagePattern(GXPointMakeNull(), block->size, 0, img, 1.f);

                context->setFillPainter( imgPaint);
            }
            
        }
         
        else*/
        {
            context->setFillColor( block->backgroundColor);
        }
        
        context->fill();
        if( !block->text.empty())
        {
            context->setFillColor(GXColors::Black);
            const GXPoint textPoint = GXPointMake(p.x +10, p.y + 20);
            const float textW = block->size.width-10;

            context->addTextBox(textPoint, textW, block->text);
        }
        
        p.y += heightToAdd;
        for (HTMLBlockElement* c : block->_children)
        {
            
            if( c->floatProp == MyCSS_PROPERTY_FLOAT_UNSET)
            {
                
            }
            
            drawBlock(context , c );
            
            
            if( c->floatProp == MyCSS_PROPERTY_FLOAT_LEFT)
            {
                //p.x += c->size.width;
            }
            else if( c->floatProp == MyCSS_PROPERTY_FLOAT_RIGHT)
            {
                //p.x += c->size.width;
            }
            else
            {
                //p.y+=block->size.height;

            }

        }
        
        
    };
    
    
    drawBlock(ctx , _renderer.getRoot() );

}
