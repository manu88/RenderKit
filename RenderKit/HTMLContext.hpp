//
//  HTMLContext.hpp
//  RenderKit
//
//  Created by Manuel Deneu on 10/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef HTMLContext_hpp
#define HTMLContext_hpp


class HTMLContext
{
public:
    static HTMLContext* instance()
    {
        if( !_intance)
        {
            _intance = new HTMLContext();
        }
        return _intance;
    }
    
    ~HTMLContext();
private:
    HTMLContext();
    
    static HTMLContext* _intance;
};

#endif /* HTMLContext_hpp */
