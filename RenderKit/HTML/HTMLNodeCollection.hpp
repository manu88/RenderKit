//
//  HTMLNodeCollection.hpp
//  RenderKit
//
//  Created by Manuel Deneu on 14/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef HTMLNodeCollection_hpp
#define HTMLNodeCollection_hpp

#include <myhtml/myosi.h>
#include <modest/myosi.h> // modest_t
#include "HTMLNode.hpp"


class HTMLNodeCollection
{
public:
    HTMLNodeCollection( myhtml_collection_t *collection , modest_t* modest);
    ~HTMLNodeCollection();
    
    bool isValid() const noexcept
    {
        return _collection != nullptr;
    }
    
    size_t getSize() const noexcept;
    HTMLNode at( size_t index) const noexcept;
    
    myhtml_collection_t *_collection;
    modest_t *_modest;
    
    
};

#endif /* HTMLNodeCollection_hpp */
