//
//  MWrapper.hpp
//  RenderKit
//
//  Created by Manuel Deneu on 14/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef MWrapper_hpp
#define MWrapper_hpp

#include <modest/myosi.h> // modest_t

class MWrapper
{
public:
    ~MWrapper();
    modest_t* _modest;

    MWrapper();
};

#endif /* MWrapper_hpp */
