/*
 Copyright (C) 2015-2017 Alexander Borisov

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA

 Author: lex.borisov@gmail.com (Alexander Borisov)
*/

#ifndef MyCSS_VALUES_COLOR_CONST_H
#define MyCSS_VALUES_COLOR_CONST_H
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

enum mycss_values_color_id {
	MyCSS_VALUES_COLOR_ID_UNDEF                 = 0x0000,
	MyCSS_VALUES_COLOR_ID_ALICEBLUE             = 0x0001,
	MyCSS_VALUES_COLOR_ID_ANTIQUEWHITE          = 0x0002,
	MyCSS_VALUES_COLOR_ID_AQUA                  = 0x0003,
	MyCSS_VALUES_COLOR_ID_AQUAMARINE            = 0x0004,
	MyCSS_VALUES_COLOR_ID_AZURE                 = 0x0005,
	MyCSS_VALUES_COLOR_ID_BEIGE                 = 0x0006,
	MyCSS_VALUES_COLOR_ID_BISQUE                = 0x0007,
	MyCSS_VALUES_COLOR_ID_BLACK                 = 0x0008,
	MyCSS_VALUES_COLOR_ID_BLANCHEDALMOND        = 0x0009,
	MyCSS_VALUES_COLOR_ID_BLUE                  = 0x000a,
	MyCSS_VALUES_COLOR_ID_BLUEVIOLET            = 0x000b,
	MyCSS_VALUES_COLOR_ID_BROWN                 = 0x000c,
	MyCSS_VALUES_COLOR_ID_BURLYWOOD             = 0x000d,
	MyCSS_VALUES_COLOR_ID_CADETBLUE             = 0x000e,
	MyCSS_VALUES_COLOR_ID_CHARTREUSE            = 0x000f,
	MyCSS_VALUES_COLOR_ID_CHOCOLATE             = 0x0010,
	MyCSS_VALUES_COLOR_ID_CORAL                 = 0x0011,
	MyCSS_VALUES_COLOR_ID_CORNFLOWERBLUE        = 0x0012,
	MyCSS_VALUES_COLOR_ID_CORNSILK              = 0x0013,
	MyCSS_VALUES_COLOR_ID_CRIMSON               = 0x0014,
	MyCSS_VALUES_COLOR_ID_CURRENTCOLOR          = 0x0015,
	MyCSS_VALUES_COLOR_ID_CYAN                  = 0x0016,
	MyCSS_VALUES_COLOR_ID_DARKBLUE              = 0x0017,
	MyCSS_VALUES_COLOR_ID_DARKCYAN              = 0x0018,
	MyCSS_VALUES_COLOR_ID_DARKGOLDENROD         = 0x0019,
	MyCSS_VALUES_COLOR_ID_DARKGRAY              = 0x001a,
	MyCSS_VALUES_COLOR_ID_DARKGREEN             = 0x001b,
	MyCSS_VALUES_COLOR_ID_DARKGREY              = 0x001c,
	MyCSS_VALUES_COLOR_ID_DARKKHAKI             = 0x001d,
	MyCSS_VALUES_COLOR_ID_DARKMAGENTA           = 0x001e,
	MyCSS_VALUES_COLOR_ID_DARKOLIVEGREEN        = 0x001f,
	MyCSS_VALUES_COLOR_ID_DARKORANGE            = 0x0020,
	MyCSS_VALUES_COLOR_ID_DARKORCHID            = 0x0021,
	MyCSS_VALUES_COLOR_ID_DARKRED               = 0x0022,
	MyCSS_VALUES_COLOR_ID_DARKSALMON            = 0x0023,
	MyCSS_VALUES_COLOR_ID_DARKSEAGREEN          = 0x0024,
	MyCSS_VALUES_COLOR_ID_DARKSLATEBLUE         = 0x0025,
	MyCSS_VALUES_COLOR_ID_DARKSLATEGRAY         = 0x0026,
	MyCSS_VALUES_COLOR_ID_DARKSLATEGREY         = 0x0027,
	MyCSS_VALUES_COLOR_ID_DARKTURQUOISE         = 0x0028,
	MyCSS_VALUES_COLOR_ID_DARKVIOLET            = 0x0029,
	MyCSS_VALUES_COLOR_ID_DEEPPINK              = 0x002a,
	MyCSS_VALUES_COLOR_ID_DEEPSKYBLUE           = 0x002b,
	MyCSS_VALUES_COLOR_ID_DIMGRAY               = 0x002c,
	MyCSS_VALUES_COLOR_ID_DIMGREY               = 0x002d,
	MyCSS_VALUES_COLOR_ID_DODGERBLUE            = 0x002e,
	MyCSS_VALUES_COLOR_ID_FIREBRICK             = 0x002f,
	MyCSS_VALUES_COLOR_ID_FLORALWHITE           = 0x0030,
	MyCSS_VALUES_COLOR_ID_FORESTGREEN           = 0x0031,
	MyCSS_VALUES_COLOR_ID_FUCHSIA               = 0x0032,
	MyCSS_VALUES_COLOR_ID_GAINSBORO             = 0x0033,
	MyCSS_VALUES_COLOR_ID_GHOSTWHITE            = 0x0034,
	MyCSS_VALUES_COLOR_ID_GOLD                  = 0x0035,
	MyCSS_VALUES_COLOR_ID_GOLDENROD             = 0x0036,
	MyCSS_VALUES_COLOR_ID_GRAY                  = 0x0037,
	MyCSS_VALUES_COLOR_ID_GREEN                 = 0x0038,
	MyCSS_VALUES_COLOR_ID_GREENYELLOW           = 0x0039,
	MyCSS_VALUES_COLOR_ID_GREY                  = 0x003a,
	MyCSS_VALUES_COLOR_ID_HONEYDEW              = 0x003b,
	MyCSS_VALUES_COLOR_ID_HOTPINK               = 0x003c,
	MyCSS_VALUES_COLOR_ID_INDIANRED             = 0x003d,
	MyCSS_VALUES_COLOR_ID_INDIGO                = 0x003e,
	MyCSS_VALUES_COLOR_ID_IVORY                 = 0x003f,
	MyCSS_VALUES_COLOR_ID_KHAKI                 = 0x0040,
	MyCSS_VALUES_COLOR_ID_LAVENDER              = 0x0041,
	MyCSS_VALUES_COLOR_ID_LAVENDERBLUSH         = 0x0042,
	MyCSS_VALUES_COLOR_ID_LAWNGREEN             = 0x0043,
	MyCSS_VALUES_COLOR_ID_LEMONCHIFFON          = 0x0044,
	MyCSS_VALUES_COLOR_ID_LIGHTBLUE             = 0x0045,
	MyCSS_VALUES_COLOR_ID_LIGHTCORAL            = 0x0046,
	MyCSS_VALUES_COLOR_ID_LIGHTCYAN             = 0x0047,
	MyCSS_VALUES_COLOR_ID_LIGHTGOLDENRODYELLOW  = 0x0048,
	MyCSS_VALUES_COLOR_ID_LIGHTGRAY             = 0x0049,
	MyCSS_VALUES_COLOR_ID_LIGHTGREEN            = 0x004a,
	MyCSS_VALUES_COLOR_ID_LIGHTGREY             = 0x004b,
	MyCSS_VALUES_COLOR_ID_LIGHTPINK             = 0x004c,
	MyCSS_VALUES_COLOR_ID_LIGHTSALMON           = 0x004d,
	MyCSS_VALUES_COLOR_ID_LIGHTSEAGREEN         = 0x004e,
	MyCSS_VALUES_COLOR_ID_LIGHTSKYBLUE          = 0x004f,
	MyCSS_VALUES_COLOR_ID_LIGHTSLATEGRAY        = 0x0050,
	MyCSS_VALUES_COLOR_ID_LIGHTSLATEGREY        = 0x0051,
	MyCSS_VALUES_COLOR_ID_LIGHTSTEELBLUE        = 0x0052,
	MyCSS_VALUES_COLOR_ID_LIGHTYELLOW           = 0x0053,
	MyCSS_VALUES_COLOR_ID_LIME                  = 0x0054,
	MyCSS_VALUES_COLOR_ID_LIMEGREEN             = 0x0055,
	MyCSS_VALUES_COLOR_ID_LINEN                 = 0x0056,
	MyCSS_VALUES_COLOR_ID_MAGENTA               = 0x0057,
	MyCSS_VALUES_COLOR_ID_MAROON                = 0x0058,
	MyCSS_VALUES_COLOR_ID_MEDIUMAQUAMARINE      = 0x0059,
	MyCSS_VALUES_COLOR_ID_MEDIUMBLUE            = 0x005a,
	MyCSS_VALUES_COLOR_ID_MEDIUMORCHID          = 0x005b,
	MyCSS_VALUES_COLOR_ID_MEDIUMPURPLE          = 0x005c,
	MyCSS_VALUES_COLOR_ID_MEDIUMSEAGREEN        = 0x005d,
	MyCSS_VALUES_COLOR_ID_MEDIUMSLATEBLUE       = 0x005e,
	MyCSS_VALUES_COLOR_ID_MEDIUMSPRINGGREEN     = 0x005f,
	MyCSS_VALUES_COLOR_ID_MEDIUMTURQUOISE       = 0x0060,
	MyCSS_VALUES_COLOR_ID_MEDIUMVIOLETRED       = 0x0061,
	MyCSS_VALUES_COLOR_ID_MIDNIGHTBLUE          = 0x0062,
	MyCSS_VALUES_COLOR_ID_MINTCREAM             = 0x0063,
	MyCSS_VALUES_COLOR_ID_MISTYROSE             = 0x0064,
	MyCSS_VALUES_COLOR_ID_MOCCASIN              = 0x0065,
	MyCSS_VALUES_COLOR_ID_NAVAJOWHITE           = 0x0066,
	MyCSS_VALUES_COLOR_ID_NAVY                  = 0x0067,
	MyCSS_VALUES_COLOR_ID_OLDLACE               = 0x0068,
	MyCSS_VALUES_COLOR_ID_OLIVE                 = 0x0069,
	MyCSS_VALUES_COLOR_ID_OLIVEDRAB             = 0x006a,
	MyCSS_VALUES_COLOR_ID_ORANGE                = 0x006b,
	MyCSS_VALUES_COLOR_ID_ORANGERED             = 0x006c,
	MyCSS_VALUES_COLOR_ID_ORCHID                = 0x006d,
	MyCSS_VALUES_COLOR_ID_PALEGOLDENROD         = 0x006e,
	MyCSS_VALUES_COLOR_ID_PALEGREEN             = 0x006f,
	MyCSS_VALUES_COLOR_ID_PALETURQUOISE         = 0x0070,
	MyCSS_VALUES_COLOR_ID_PALEVIOLETRED         = 0x0071,
	MyCSS_VALUES_COLOR_ID_PAPAYAWHIP            = 0x0072,
	MyCSS_VALUES_COLOR_ID_PEACHPUFF             = 0x0073,
	MyCSS_VALUES_COLOR_ID_PERU                  = 0x0074,
	MyCSS_VALUES_COLOR_ID_PINK                  = 0x0075,
	MyCSS_VALUES_COLOR_ID_PLUM                  = 0x0076,
	MyCSS_VALUES_COLOR_ID_POWDERBLUE            = 0x0077,
	MyCSS_VALUES_COLOR_ID_PURPLE                = 0x0078,
	MyCSS_VALUES_COLOR_ID_REBECCAPURPLE         = 0x0079,
	MyCSS_VALUES_COLOR_ID_RED                   = 0x007a,
	MyCSS_VALUES_COLOR_ID_ROSYBROWN             = 0x007b,
	MyCSS_VALUES_COLOR_ID_ROYALBLUE             = 0x007c,
	MyCSS_VALUES_COLOR_ID_SADDLEBROWN           = 0x007d,
	MyCSS_VALUES_COLOR_ID_SALMON                = 0x007e,
	MyCSS_VALUES_COLOR_ID_SANDYBROWN            = 0x007f,
	MyCSS_VALUES_COLOR_ID_SEAGREEN              = 0x0080,
	MyCSS_VALUES_COLOR_ID_SEASHELL              = 0x0081,
	MyCSS_VALUES_COLOR_ID_SIENNA                = 0x0082,
	MyCSS_VALUES_COLOR_ID_SILVER                = 0x0083,
	MyCSS_VALUES_COLOR_ID_SKYBLUE               = 0x0084,
	MyCSS_VALUES_COLOR_ID_SLATEBLUE             = 0x0085,
	MyCSS_VALUES_COLOR_ID_SLATEGRAY             = 0x0086,
	MyCSS_VALUES_COLOR_ID_SLATEGREY             = 0x0087,
	MyCSS_VALUES_COLOR_ID_SNOW                  = 0x0088,
	MyCSS_VALUES_COLOR_ID_SPRINGGREEN           = 0x0089,
	MyCSS_VALUES_COLOR_ID_STEELBLUE             = 0x008a,
	MyCSS_VALUES_COLOR_ID_TAN                   = 0x008b,
	MyCSS_VALUES_COLOR_ID_TEAL                  = 0x008c,
	MyCSS_VALUES_COLOR_ID_THISTLE               = 0x008d,
	MyCSS_VALUES_COLOR_ID_TOMATO                = 0x008e,
	MyCSS_VALUES_COLOR_ID_TRANSPARENT           = 0x008f,
	MyCSS_VALUES_COLOR_ID_TURQUOISE             = 0x0090,
	MyCSS_VALUES_COLOR_ID_VIOLET                = 0x0091,
	MyCSS_VALUES_COLOR_ID_WHEAT                 = 0x0092,
	MyCSS_VALUES_COLOR_ID_WHITE                 = 0x0093,
	MyCSS_VALUES_COLOR_ID_WHITESMOKE            = 0x0094,
	MyCSS_VALUES_COLOR_ID_YELLOW                = 0x0095,
	MyCSS_VALUES_COLOR_ID_YELLOWGREEN           = 0x0096,
	MyCSS_VALUES_COLOR_ID_LAST_ENTRY            = 0x0098
}
typedef mycss_values_color_id_t;


enum mycss_values_color_function_id {
	MyCSS_VALUES_COLOR_FUNCTION_ID_UNDEF        = 0x0000,
	MyCSS_VALUES_COLOR_FUNCTION_ID_A            = 0x0001,
	MyCSS_VALUES_COLOR_FUNCTION_ID_ALPHA        = 0x0002,
	MyCSS_VALUES_COLOR_FUNCTION_ID_BLACKNESS    = 0x0003,
	MyCSS_VALUES_COLOR_FUNCTION_ID_BLEND        = 0x0004,
	MyCSS_VALUES_COLOR_FUNCTION_ID_BLENDA       = 0x0005,
	MyCSS_VALUES_COLOR_FUNCTION_ID_BLUE         = 0x0006,
	MyCSS_VALUES_COLOR_FUNCTION_ID_COLOR        = 0x0007,
	MyCSS_VALUES_COLOR_FUNCTION_ID_COLOR_MOD    = 0x0008,
	MyCSS_VALUES_COLOR_FUNCTION_ID_CONTRAST     = 0x0009,
	MyCSS_VALUES_COLOR_FUNCTION_ID_DEVICE_CMYK  = 0x000a,
	MyCSS_VALUES_COLOR_FUNCTION_ID_GRAY         = 0x000b,
	MyCSS_VALUES_COLOR_FUNCTION_ID_GREEN        = 0x000c,
	MyCSS_VALUES_COLOR_FUNCTION_ID_HSL          = 0x000d,
	MyCSS_VALUES_COLOR_FUNCTION_ID_HSLA         = 0x000e,
	MyCSS_VALUES_COLOR_FUNCTION_ID_HUE          = 0x000f,
	MyCSS_VALUES_COLOR_FUNCTION_ID_HWB          = 0x0010,
	MyCSS_VALUES_COLOR_FUNCTION_ID_LIGHTNESS    = 0x0011,
	MyCSS_VALUES_COLOR_FUNCTION_ID_RED          = 0x0012,
	MyCSS_VALUES_COLOR_FUNCTION_ID_RGB          = 0x0013,
	MyCSS_VALUES_COLOR_FUNCTION_ID_RGBA         = 0x0014,
	MyCSS_VALUES_COLOR_FUNCTION_ID_SATURATION   = 0x0015,
	MyCSS_VALUES_COLOR_FUNCTION_ID_SHADE        = 0x0016,
	MyCSS_VALUES_COLOR_FUNCTION_ID_TINT         = 0x0017,
	MyCSS_VALUES_COLOR_FUNCTION_ID_WHITENESS    = 0x0018,
	MyCSS_VALUES_COLOR_FUNCTION_ID_LAST_ENTRY   = 0x001a
}
typedef mycss_values_color_function_id_t;



#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyCSS_VALUES_COLOR_CONST_H */


