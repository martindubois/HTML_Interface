
// Product  HTML_Interface

/// \author KMS - Martin Dubois, P.Eng.
/// \file   Includes/HI/CSS_Colors.h

#pragma once

// Includes
/////////////////////////////////////////////////////////////////////////////

#include <HI/Document.h>

namespace HI
{

    class CSS_ColorInfo;

    typedef enum
    {
        COLOR_ALICE_BLUE              = 0xf0f8ff,
        COLOR_ANTIQUE_WHITE           = 0xfaebd7,
        COLOR_AQUA                    = 0x00ffff,
        COLOR_AQUAMARINE              = 0x7fffd4,
        COLOR_AZURE                   = 0xf0ffff,
        COLOR_BEIGE                   = 0xf5f5dc,
        COLOR_BISQUE                  = 0xffe4c4,
        COLOR_BLACK                   = 0x000000,
        COLOR_BLANCHED_ALMOND         = 0xffebcd,
        COLOR_BLUE                    = 0x0000ff,
        COLOR_BLUE_VIOLET             = 0x8a2be2,
        COLOR_BROWN                   = 0xa52a2a,
        COLOR_BURLY_WOOD              = 0xdeb887,
        COLOR_CADET_BLUE              = 0x5f9ea0,
        COLOR_CHARTREUSE              = 0x7f7700,
        COLOR_CHOCOLATE               = 0xd2691e,
        COLOR_CORAL                   = 0xff7f50,
        COLOR_CORNFLOWER_BLUE         = 0x6495ed,
        COLOR_CORNSILK                = 0xfff8dc,
        COLOR_CRIMSON                 = 0xdc143c,
        COLOR_CYAN                    = 0x00ffff,
        COLOR_DARK_BLUE               = 0x00008b,
        COLOR_DARK_CYAN               = 0x008b8b,
        COLOR_DARK_COLDEN_ROD         = 0xb8860b,
        COLOR_DARK_GRAY               = 0xa9a9a9,
        COLOR_DARK_GREEN              = 0x006400,
        COLOR_DARK_KHAKI              = 0xbdb76b,
        COLOR_DARK_MAGENTA            = 0x8b008b,
        COLOR_DARK_OLIVE_GREEN        = 0x556b2f,
        COLOR_DARK_ORANGE             = 0xff8c00,
        COLOR_DARK_ORCHID             = 0x9932cc,
        COLOR_DARK_RED                = 0x8b0000,
        COLOR_DARK_SALMON             = 0xe9967a,
        COLOR_DARK_SEA_GREEN          = 0x8fbc8f,
        COLOR_DARK_SLATE_BLUE         = 0x483d8b,
        COLOR_DARK_SLATE_GRAY         = 0x2f4f4f,
        COLOR_DARK_TURQUOISE          = 0x00ced1,
        COLOR_DARK_VIOLET             = 0x9400d3,
        COLOR_DEEP_PINK               = 0xff1493,
        COLOR_DEEP_SKY_BLUE           = 0x00bfff,
        COLOR_DIM_GRAY                = 0x696969,
        COLOR_DODGER_BLUE             = 0x1e90ff,
        COLOR_FIRE_BRICK              = 0xb22222,
        COLOR_FLORAL_WHITE            = 0xfffaf0,
        COLOR_FOREST_GREEN            = 0x228b22,
        COLOR_FUCHSIA                 = 0xff00ff,
        COLOR_GAINSBORO               = 0xdcdcdc,
        COLOR_GHOST_WHITE             = 0xf8f8ff,
        COLOR_GOLD                    = 0xffd700,
        COLOR_GOLDEN_ROD              = 0xdaa520,
        COLOR_GRAY                    = 0x808080,
        COLOR_GREEN                   = 0x008000,
        COLOR_GREEN_YELLOW            = 0xadff2f,
        COLOR_HONEY_DEW               = 0xf0fff0,
        COLOR_HOT_PINK                = 0xff69b4,
        COLOR_INDIAN_RED              = 0xcd5c5c,
        COLOR_INDIGO                  = 0x4b0082,
        COLOR_IVORY                   = 0xfffff0,
        COLOR_KHAKI                   = 0xf0e68c,
        COLOR_KMS_BLUE                = 0x005c87,
        COLOR_KMS_GREEN               = 0x83c54b,
        COLOR_LAVENDER                = 0xe6e6fa,
        COLOR_LAVENDER_BLUSH          = 0xfff0f5,
        COLOR_LAWN_GREEN              = 0x7cfc00,
        COLOR_LEMON_CHIFFON           = 0xfffacd,
        COLOR_LIGHT_BLUE              = 0xadd8e6,
        COLOR_LIGHT_CORAL             = 0xf08080,
        COLOR_LIGHT_CYAN              = 0xe0ffff,
        COLOR_LIGHT_GOLDEN_ROD_YELLOW = 0xfafad2,
        COLOR_LIGHT_GRAY              = 0xd3d3d3,
        COLOR_LIGHT_GREEN             = 0x90ee90,
        COLOR_LIGHT_PINK              = 0xffb6c1,
        COLOR_LIGHT_SALMON            = 0xffa07a,
        COLOR_LIGHT_SEA_GREEN         = 0x20b2aa,
        COLOR_LIGHT_SKY_BLUE          = 0x87cefa,
        COLOR_LIGHT_SLATE_GRAY        = 0x778899,
        COLOR_LIGHT_STEEL_BLUE        = 0xb0c4de,
        COLOR_LIGHT_YELLOW            = 0xffffe0,
        COLOR_LIME                    = 0x00ff00,
        COLOR_LIME_GREEN              = 0x32cd32,
        COLOR_LINEN                   = 0xfaf0e6,
        COLOR_MAGENTA                 = 0xff00ff,
        COLOR_MAROON                  = 0x800000,
        COLOR_MEDIUM_AQUA_MARINE      = 0x66cdaa,
        COLOR_MEDIUM_BLUE             = 0x0000cd,
        COLOR_MEDIUM_ORCHID           = 0xba55d3,
        COLOR_MEDIUM_PURPLE           = 0x9370db,
        COLOR_MEDIUM_SEA_GREEN        = 0x3cb371,
        COLOR_MEDIUM_SLATE_BLUE       = 0x7b68ee,
        COLOR_MEDIUM_SPRING_GREEN     = 0x00fa9a,
        COLOR_MEDIUM_TURQUOISE        = 0x48d1cc,
        COLOR_MEDIUM_VIOLET_RED       = 0xc71585,
        COLOR_MIDNIGHT_BLUE           = 0x191970,
        COLOR_MINT_CREAM              = 0xf5fffa,
        COLOR_MISTY_ROSE              = 0xffe4e1,
        COLOR_MOCCASIN                = 0xffe4b5,
        COLOR_NAVAJO_WHITE            = 0xffdead,
        COLOR_NAVY                    = 0x000080,
        COLOR_OLD_LACE                = 0xfdf5e6,
        COLOR_OLIVE                   = 0x808000,
        COLOR_OLIVE_DRAB              = 0x6b8e23,
        COLOR_ORANGE                  = 0xffa500,
        COLOR_ORAGE_RED               = 0xff4500,
        COLOR_ORCHID                  = 0xda70d6,
        COLOR_PALE_GOLDEN_ROD         = 0xeee8aa,
        COLOR_PALE_GREEN              = 0x98fb98,
        COLOR_PALE_TURQUOISE          = 0xafeeee,
        COLOR_PALE_VIOLET_RED         = 0xdb7093,
        COLOR_PAPAYA_WHIP             = 0xffefd5,
        COLOR_PEACH_PUFF              = 0xffdab9,
        COLOR_PERU                    = 0xcd853f,
        COLOR_PINK                    = 0xffc0cb,
        COLOR_PLUM                    = 0xdda0dd,
        COLOR_POWDER_BLUE             = 0xb0e0e6,
        COLOR_PURPLE                  = 0x800080,
        COLOR_REBECCA_PURPLE          = 0x663399,
        COLOR_RED                     = 0xff0000,
        COLOR_ROSY_BROWN              = 0xbc8f8f,
        COLOR_ROYAL_BLUE              = 0x4169e1,
        COLOR_SADDLE_BROWN            = 0x8b4513,
        COLOR_SALMON                  = 0xfa8072,
        COLOR_SANDY_BROWN             = 0xf4a460,
        COLOR_SEA_GREEN               = 0x2e8b57,
        COLOR_SEA_SHELL               = 0xfff5ee,
        COLOR_SIENNA                  = 0xa0522d,
        COLOR_SILVER                  = 0xc0c0c0,
        COLOR_SKY_BLUE                = 0x87ceeb,
        COLOR_SLATE_BLUE              = 0x6a5acd,
        COLOR_SLATE_GRAY              = 0x708090,
        COLOR_SNOW                    = 0xfffafa,
        COLOR_SPRING_GREEN            = 0x00ff7f,
        COLOR_STEEL_BLUE              = 0x4682b4,
        COLOR_TAN                     = 0xd2b48c,
        COLOR_TEAL                    = 0x008080,
        COLOR_THISTLE                 = 0xd8bfd8,
        COLOR_TOMATO                  = 0xff6347,
        COLOR_TURQUOISE               = 0x40e0d0,
        COLOR_VIOLET                  = 0xee82ee,
        COLOR_WHEAT                   = 0xf5deb3,
        COLOR_WHITE                   = 0xffffff,
        COLOR_WHITE_SMOKE             = 0xf5f5f5,
        COLOR_YELLOW                  = 0xffff00,
        COLOR_YELLOW_GREEN            = 0x9acd32,

        COLOR_QTY = 142
    }
    CSS_Color;

    /// \brief CSS_Colors
    class CSS_Colors
    {

    public:

        typedef enum
        {
            ORDER_BLUE ,
            ORDER_GREEN,
            ORDER_RED  ,
            ORDER_WHITE,

            ORDER_NAME,

            ORDER_QTY
        }
        Order;

        static bool FindByIdName(CSS_ColorInfo * aOut, const char * aIdName);

        static bool FindByIndex(CSS_ColorInfo * aOut, uint32_t aIndex);

        static bool FindByName(CSS_ColorInfo * aOut, const char * aName);

        static bool FindByValue(CSS_ColorInfo * aOut, CSS_Color aValue);

        static void GetFirst(CSS_ColorInfo * aOut, Order aOrder = ORDER_NAME);

        static void GetLast(CSS_ColorInfo * aOut, Order aOrder = ORDER_NAME);

        static bool GetNext(CSS_ColorInfo * aInOut);

        static bool GetPrevious(CSS_ColorInfo * aInOut);

    };

    /// \brief CSS_Color
    class CSS_ColorInfo
    {

    public:

        uint8_t GetBlue() const;

        uint8_t GetGreen() const;

        uint8_t GetRed() const;

        const char      * mIdName ;
        uint16_t          mIndex  ;
        uint16_t          mIndexBy;
        const char      * mName   ;
        CSS_Colors::Order mOrder  ;
        CSS_Color         mValue  ;

    };

}
