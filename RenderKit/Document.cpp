//
//  Document.cpp
//  RenderKit
//
//  Created by Manuel Deneu on 14/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include <assert.h>
#include "Document.hpp"
#include "HTMLNode.hpp"

Document::Document():
_renderNode(nullptr)
{
    _modest.reset(new MWrapper() );
}

Document::Document(Document& )
{
    assert(false);// to investigate ...
}

Document& Document::operator=( const Document &rhs)
{
    _modest = rhs._modest;
    return *this;
}

Document::~Document()
{

}

bool Document::isValid() const noexcept
{
    return _modest.get();
}

std::string Document::getTitle() const
{
    std::string ret;
    
    HTMLNodeCollection titleCollect = getNodesByTagID( MyHTML_TAG_TITLE );
    
    if (titleCollect.isValid() && titleCollect.getSize() )
    {
        const HTMLNode nText = titleCollect.at(0).getChild();
        
        if( nText.isValid() && nText.hasText())
        {
            return nText.getText();
        }
    }
    
    return "";
    
}

HTMLNodeCollection Document::getNodesByTagID(myhtml_tag_id_t tagId) const noexcept
{
    assert(isValid());
    
    HTMLNodeCollection collect(nullptr , _modest.get()->_modest);
    
    if( !_modest.get())
    {
        return collect;
    }
    
    mystatus_t status = MyCORE_STATUS_ERROR;
    myhtml_collection_t *c = myhtml_get_nodes_by_tag_id( _modest.get()->_modest->myhtml_tree, NULL, tagId, &status);
    
    if( status)
    {
        collect._collection = c;
    }
    
    return collect;
}
