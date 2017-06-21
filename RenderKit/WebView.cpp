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
delegate(nullptr),
_menu(nullptr)
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

bool WebView::touchEnded( const GXTouch &t)
{
    if( _menu)
        return  false;
    
    showContext(t.center);
    return true;
}

void WebView::contextMenuDidDismiss( VKContextMenu* menu)
{
    assert( _menu && _menu == menu);
    
    if( _menu->getSelectedIndex() >= 0)
    {
        if( _menu->getSelectedItem() == "quit")
        {
            CLApplication::instance()->quit();
        }
        else if( _menu->getSelectedItem() == "reload")
        {
            refresh();
        }
        printf("Selected : '%s'\n", _menu->getSelectedItem().c_str() );
    }
    
    delete _menu;
    _menu = nullptr;
}


void WebView::showContext( const GXPoint &at)
{
    if( _menu == nullptr)
    {
        
        VKWindow* win = getWindow();
        assert( win );
        
        _menu = new VKContextMenu();
        _menu->setController( this );
        
        const GXPoint c = getCoordsInParent(win) + at;
        
        _menu->setSize(GXSizeMake(getSize().width, 200));
        _menu->setPos( c  );
        _menu->setItems( { "reload" , "quit" , "option1" , "option2"} );
        win->pushContextMenu(_menu);
        
        CLApplication::instance()->getRunLoop()->dispatchAfter([win]()
                                                               {
                                                                   win->dismissCurrentContextMenu();
                                                               }, 4000);
        
        
    }
}

/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */
/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */

/*static*/ bool WebView::computeContentWidth(GXContext* context , HTMLBlockElement* block)
{
    if( block->text.empty())
        return false;
    
    assert(context);
    assert(block);
    
    const GXPoint sP = GXPointMakeNull();
    GXSize min = GXSizeInvalid;
    GXSize max = GXSizeInvalid;
    context->getTextSize(sP, block->realSize.width, block->text, min , max);
    
    block->realSize.width = max.width;
    block->explicitWidth = true;
    
    return true;
}

/*static*/ void WebView::computeContentHeight(GXContext* context , HTMLBlockElement* block)
{
    assert(context);
    assert(block);
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
    context->setFontSize(block->fontProps.size);
    context->setTextAlignement( block->fontProps.align);

    assert(block->size.width != -1 && block->size.wPercent == false);
    
    block->realSize.width = (int) block->size.width;
    block->realSize.height = (int) block->size.height;

    if( block->realSize.height == -1)
    {
        computeContentHeight(context , block);
    }
    if( !block->explicitWidth)
    {
        if(computeContentWidth(context , block))
        {
            printf("New Width = %i" , block->realSize.width);
        }
        else
        {
            return ;
        }
        
    }
    
    assert(block->explicitWidth);
    assert(block->size.wPercent == false);
    if( block->size.hPercent)
    {
        block->realSize.height *= block->_parent->size.height * 0.01f;
    }
    
    assert( block->realSize.height != -1);
    
    
    if( block->floatProp == MyCSS_PROPERTY_FLOAT_RIGHT)
    {
        realPos.x = block->_parent->_xFloat - block->realSize.width;
        block->_parent->_xFloat -= block->realSize.width;
    }
    else if( block->floatProp == MyCSS_PROPERTY_FLOAT_LEFT)
    {
        realPos.x = block->_parent->_xFloat;
        block->_parent->_xFloat += block->realSize.width;
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
        context->setTextAlignement( block->fontProps.align );
        context->setFillColor(block->fontProps.color);
        
        const GXPoint p = realPos;
        //p.y+=15;
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


static void drawBlock2(GXContext* ctx , const HTMLBlockElement* block , const GXPoint &pos )
{
    static std::vector<GXColor> Colors =
    {
        GXColors::Red,
        GXColors::Green,
        GXColors::LightGray,
        GXColors::Blue,
        GXColors::Gray
    };
    static size_t index = 0;
    
    ctx->beginPath();
    
    ctx->addRect(GXRectMake(GXPointMake(0, 0),block->attributes.totalSize));
    ctx->setFillColor( Colors[index++]);
    
    if( index >= Colors.size())
        index = 0;
    
    ctx->fill();
    ctx->beginPath();
    ctx->addRect(GXRectMake(GXPointMake(0, 0),block->attributes.contentSize));
    ctx->setFillColor( Colors[index++] );
    ctx->fill();
    
    if( index >= Colors.size())
        index = 0;
    
    for( const HTMLBlockElement*c : block->_children)
    {
        drawBlock2(ctx, c, GXPointMakeNull());
    }
    
    
}



void WebView::paint( GXContext* ctx , const GXRect& rect )
{
    assert(_renderer.getRoot() );
    
    _renderer.getRoot()->attributes.totalSize.width = getSize().width;
    
    
    reflow(ctx);

    
    drawBlock2(ctx , _renderer.getRoot() , GXPointMakeNull());
    
    

}

static const char* tagName( HTMLNode::TagID tag);



static void reflowBlock( GXContext* ctx , HTMLBlockElement* block)
{
    printf("Reflow block %x %s\n" , block->tagID , tagName(block->tagID));
    
    if( !block->_children.empty())
    {
        printf("\tChild : \n");
        for( HTMLBlockElement*c : block->_children)
        {
            reflowBlock(ctx, c);
            block->attributes.totalSize.height += c->attributes.contentSize.height;
        }
    }
    printf("Self : \n");
    
    if( !block->text.empty())
    {
        printf("Has text '%s  \n" , block->text.c_str());
        block->attributes.contentSize.height +=20;
        //block->attributes.size.height += 20;
    }
    if( block->attributes.totalSize.width == 0)
    {
        block->attributes.totalSize.width = block->_parent->attributes.totalSize.width;
    }
    block->attributes.totalSize.height += block->attributes.contentSize.height;
    
    if( block->attributes.contentSize.width == 0)
        
    printf("\t%s   TotalSize %i %i \n" , tagName(block->tagID), block->attributes.totalSize.width , block->attributes.totalSize.height);
    printf("\t%s ContentSize %i %i \n" , tagName(block->tagID), block->attributes.contentSize.width , block->attributes.contentSize.height);
}

bool WebView::reflow(GXContext* context)
{
    printf("################################################\n");
    printf("Start reflow \n");

    reflowBlock(context, _renderer.getRoot() );

    return false;
}


static const char* tagName( HTMLNode::TagID tag)
{
    switch (tag)
    {
        case MyHTML_TAG__UNDEF:
            return "undef";
        case MyHTML_TAG_BODY:
            return "body";
        case MyHTML_TAG_P:
            return "p";
        default:
            assert(false);
            break;
    }
    return "";
}
