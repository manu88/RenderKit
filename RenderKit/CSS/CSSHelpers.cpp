//
//  CSSHelpers.cpp
//  RenderKit
//
//  Created by Manuel Deneu on 15/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include <assert.h>
#include <mycss/values/values.h> // mycss_values_length_t
#include <mycss/values/color.h> //mycss_values_color_name_by_id
#include "CSSHelpers.hpp"
#include "CSSColors.hpp"

static float convValueForceFloat( const mycss_values_number_t& v);
static float convValueForceFloat( const mycss_values_percentage_t& v);

float CSSHelpers::parseFloatIntAttribute( const mycss_declaration_entry_t* node ) noexcept
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

float CSSHelpers::parseGetFloat( const mycss_declaration_entry_t* node) noexcept
{
    assert(node);
    
    
    return parseFloatIntAttribute(node);
}



static GXColor parseColorAttr( const mycss_values_color_t* colorVal)
{
    assert(colorVal);
    GXColor retColor = GXColorInvalid;
    
    if( colorVal->type == MyCSS_VALUES_COLOR_TYPE_RGBA)
    {
        if(colorVal->type_value == MyCSS_VALUES_COLOR_TYPE_VALUE_PERCENTAGE)
        {
            
            
            retColor = GXColorMake( convValueForceFloat( colorVal->value.rgba_percentage.r),
                                   convValueForceFloat( colorVal->value.rgba_percentage.g),
                                   convValueForceFloat( colorVal->value.rgba_percentage.b),
                                   convValueForceFloat(colorVal->value.rgba_percentage.alpha.value.number)
                                   );
        }
        else if(colorVal->type_value == MyCSS_VALUES_COLOR_TYPE_VALUE_NUMBER)
        {
            
            
            retColor = GXColorMake( convValueForceFloat(colorVal->value.rgba_number.r),
                                   convValueForceFloat(colorVal->value.rgba_number.g),
                                   convValueForceFloat(colorVal->value.rgba_number.b),
                                   convValueForceFloat(colorVal->value.rgba_number.alpha.value.number)
                                   );
        }
        
    }
    else if( colorVal->type == MyCSS_VALUES_COLOR_TYPE_RGB)
    {
        
    }
    else if( colorVal->type == MyCSS_VALUES_COLOR_TYPE_NAMED)
    {
        size_t length;
        const char *name = mycss_values_color_name_by_id(colorVal->value.name_id, &length);
        
        if( GXColors::ColorsNames.count( name))
        {
            return GXColors::ColorsNames.at(name);
        }
        else
        {
            assert(false);// color to add to ColorsNames
        }
    }
    
    
    return retColor;
}

/*static*/ GXColor CSSHelpers::parseColor(const mycss_declaration_entry_t* node)
{
    assert(node);
    
    
    assert(node->value_type == MyCSS_PROPERTY_VALUE__COLOR);
    //mycss_values_color_type
    
    const mycss_values_color_t* colorVal = ( const mycss_values_color_t*) node->value;
    
    return parseColorAttr(colorVal);
}

GXColor CSSHelpers::parseBackgroundColor( const mycss_declaration_entry_t* node)
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
                
                return parseColorAttr(colorVal);
            }
            else
            {
                assert(false);
                
            }
        }
    }
    
    return retColor;
}


static float convValueForceFloat( const mycss_values_percentage_t& v)
{
    return (float) v.is_float? v.value.f : v.value.i /255.f;
}

static float convValueForceFloat( const mycss_values_number_t& v)
{
    return (float) v.is_float? v.value.f : v.value.i /255.f;
}
