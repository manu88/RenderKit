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

class HTMLNodeCollection
{
public:
    HTMLNodeCollection( myhtml_collection_t *collection);
    ~HTMLNodeCollection();
    
    bool isValid() const noexcept
    {
        return _collection != nullptr;
    }
    
    size_t getSize() const noexcept;
    
    myhtml_collection_t *_collection;
};

#endif /* HTMLNodeCollection_hpp */
