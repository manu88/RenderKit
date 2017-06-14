//
//  CSSEntry.cpp
//  RenderKit
//
//  Created by Manuel Deneu on 14/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include <assert.h>
#include "CSSEntry.hpp"
#include "CSSColors.hpp"

#include <mycss/values/values.h> // mycss_values_length_t
#include <mycss/values/color.h> //mycss_values_color_name_by_id

float CSSEntry::parseFloatIntAttribute( const mycss_declaration_entry_t* node )
{
    assert(node);
    float retSize = -1;
    
    mycss_values_length_t* val = (mycss_values_length_t*) node->value;
    
    if( val->is_float)
    {
        const float *v = (float*) node->value;
        retSize = *v;
        
    }
    else
    {
        const int *v = (int*) node->value;
        retSize = (float)*v;
        
    }
    
    
    return retSize;
}
float  CSSEntry::parseBlockWidth( const mycss_declaration_entry_t* node)
{
    assert(node);
    
    
    if( node->value_type == MyCSS_PROPERTY_WIDTH__LENGTH)
    {
        //printf(" in pixels ");
    }
    else if( node->value_type == MyCSS_PROPERTY_WIDTH__PERCENTAGE)
    {
        //printf(" in percents ");
    }
    
    return parseFloatIntAttribute(node);
}

float CSSEntry::parseBlockHeight( const mycss_declaration_entry_t* node)
{
    assert(node);
    
    if( node->value_type == MyCSS_PROPERTY_HEIGHT__LENGTH)
    {
        //printf(" in pixels ");
    }
    else if( node->value_type == MyCSS_PROPERTY_HEIGHT__PERCENTAGE)
    {
        //printf(" in percents ");
    }
    
    return parseFloatIntAttribute(node);
}

GXColor CSSEntry::parseBackgroundColor( const mycss_declaration_entry_t* node)
{
    assert(node);
    GXColor retColor = GXColorInvalid;
    
    mycss_values_background_list_t *list =(mycss_values_background_list_t *) node->value;
    
    for(size_t i = 0; i < list->entries_length; i++)
    {
        mycss_values_background_t* bg = &list->entries[i];
        
        if(bg->color)
        {
            if( bg->color->value_type == MyCSS_PROPERTY_VALUE__COLOR)
            {
                mycss_values_color_t* colorVal = (mycss_values_color_t*)bg->color->value;
                
                if( colorVal->type == MyCSS_VALUES_COLOR_TYPE_NAMED)
                {
                    size_t length;
                    const char *name = mycss_values_color_name_by_id(colorVal->value.name_id, &length);
                    
                    if( CSSColor::ColorsNames.count( name))
                    {
                        retColor = CSSColor::ColorsNames.at(name);
                    }
                    else
                    {
                        assert(false);// color to add to ColorsNames
                    }
                }
                else if( colorVal->type == MyCSS_VALUES_COLOR_TYPE_RGBA)
                {
                    if(colorVal->type_value == MyCSS_VALUES_COLOR_TYPE_VALUE_PERCENTAGE)
                    {
                        printf("Color percent \n");
                        assert(false); // to do :)
                    }
                    else if(colorVal->type_value == MyCSS_VALUES_COLOR_TYPE_VALUE_NUMBER)
                    {
                        auto convValueCol = [](mycss_values_number_t& v)
                        {
                            return (float) v.is_float? v.value.f : v.value.i /255.f;
                        };
                        
                        retColor = GXColorMake( convValueCol(colorVal->value.rgba_number.r),
                                               convValueCol(colorVal->value.rgba_number.g),
                                               convValueCol(colorVal->value.rgba_number.b),
                                               convValueCol(colorVal->value.rgba_number.alpha.value.number)
                                               //colorVal->value.rgba_number.alpha.value.number.value.i / 255.f
                                               );
                    }
                }
            }
            else
            {
                assert(false);
                
            }
        }
    }
    
    return retColor;
}
