//
//  MWrapper.cpp
//  RenderKit
//
//  Created by Manuel Deneu on 14/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include <assert.h>
#include "MWrapper.hpp"

#include <modest/modest.h> // modest

MWrapper::MWrapper():
_modest ( modest_create())
{
    assert(_modest);
    assert(modest_init(_modest) == 0);
}

MWrapper::~MWrapper()
{
    myhtml_tree_destroy( _modest->myhtml_tree);
    mycss_entry_destroy( _modest->mycss_entry, true);
    
    modest_clean(_modest);
    modest_destroy(_modest , true);
}
