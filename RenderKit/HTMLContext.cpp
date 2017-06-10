//
//  HTMLContext.cpp
//  RenderKit
//
//  Created by Manuel Deneu on 10/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "HTMLContext.hpp"

#include <myhtml/myhtml.h>
#include <myhtml/serialization.h>
#include <mycss/mycss.h>
#include <mycss/selectors/init.h>
#include <mycss/declaration/init.h>
#include <mycss/declaration/entry.h>
#include <mycss/declaration/serialization.h>


/*static*/ HTMLContext* HTMLContext::_intance = nullptr;

HTMLContext::HTMLContext()
{
    
}

HTMLContext::~HTMLContext()
{
    
}
