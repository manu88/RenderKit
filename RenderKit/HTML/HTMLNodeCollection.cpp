//
//  HTMLNodeCollection.cpp
//  RenderKit
//
//  Created by Manuel Deneu on 14/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include <assert.h>
#include <myhtml/myhtml.h>
#include "HTMLNodeCollection.hpp"


HTMLNodeCollection::HTMLNodeCollection( myhtml_collection_t *collection):
_collection(collection)
{
    
}

HTMLNodeCollection::~HTMLNodeCollection()
{
    if( _collection)
    {
        myhtml_collection_destroy( _collection);
        _collection = nullptr;
        
    }
}

size_t HTMLNodeCollection::getSize() const noexcept
{
    assert(isValid());

    return _collection->length;
}
