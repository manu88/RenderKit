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
        }
        
    }
    return ret;
}

void WebView::paint( GXContext* ctx , const GXRect& rect )
{
    GXPoint p = GXPointMakeNull();
    
    printf("Paint webView \n");
    
    assert(_renderer.getRoot() );
    
    auto drawBlock = [rect] (GXContext* context , const HTMLBlockElement* block , const GXPoint &p)
    {
        context->beginPath();
        context->addRect(GXRectMake(p, block->size));
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
        else
        {
            context->setFillColor( block->backgroundColor);
        }
        
        context->fill();
        if( !block->text.empty())
        {
            context->setFontId( context->getFontManager().getFont("SanFranciscoDisplay-Regular.ttf") );
            
            
            context->setFillColor(GXColors::Black);
            
            context->setFontSize(20.f);
            //ctx->setStrokeColor(GXColors::Green);
            context->addText(GXPointMake(p.x, p.y + 10) , block->text);
        }
        
    };
    
    for ( const HTMLBlockElement* c : _renderer.getRoot()->_children)
    {
        assert(c->_parent);
        printf("\tGot child %s ", c->tag.c_str());
        printf(" text '%s' ",c->text.c_str() );
        printf(" size %i %i ",c->size.width , c->size.height );
        printf("\n");
        
        for ( const HTMLBlockElement* cc : c->_children)
        {
            assert(cc->_parent);
            printf("\t\tGot child %s ", cc->tag.c_str());
            printf(" text '%s' ",cc->text.c_str() );
            printf(" size %i %i ",cc->size.width , cc->size.height );
            printf("\n");
            
            for ( const HTMLBlockElement* ccc : cc->_children)
            {
                assert(ccc->_parent);
                printf("\t\t\tGot child %s", ccc->tag.c_str());
                printf(" text '%s' ",ccc->text.c_str() );
                printf(" size %i %i ",ccc->size.width , ccc->size.height );
                printf("\n");
                
                drawBlock(ctx , ccc , p);
                
                
                p.y += 40;
                for ( const HTMLBlockElement* cccc : ccc->_children)
                {
                    assert(cccc->_parent);
                    printf("\t\t\t\tGot child 4 %s", cccc->tag.c_str());
                    printf(" text '%s' ",cccc->text.c_str() );
                    printf(" size %i %i ",cccc->size.width , cccc->size.height );
                    printf("\n");
                    
                    drawBlock(ctx , cccc , p);
                    
                 
                    p.y+=cccc->size.height;
                    
                }
            }
        }
    }
    
}
