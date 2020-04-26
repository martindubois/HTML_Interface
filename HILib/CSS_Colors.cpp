
// Author     KMS - Martin Dubois, P.Eng.
// Copyright  (C) 2020 KMS. All rights reserved.
// Product    HTML_Interface
// File       HILib/CSS_Colors.cpp

// CODE REVIEW 2020-04-26 KMS - Martin Dubois, P.Eng.

// TEST COVERAGE 2020-04-26 KMS - Martin Dubois, P.Eng.

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>

// ===== Includes ===========================================================

#include <HI/CSS_Colors.h>

// Data type
/////////////////////////////////////////////////////////////////////////////

typedef int(*CompareFunction)(uint32_t, uint32_t);

class Data
{

public:

    const char * mIdName;
    const char * mName  ;

    HI::CSS_Color mValue;

};

// Static function declarations
/////////////////////////////////////////////////////////////////////////////

static int CompareBlue (uint32_t aA, uint32_t aB);
static int CompareGreen(uint32_t aA, uint32_t aB);
static int CompareRed  (uint32_t aA, uint32_t aB);
static int CompareWhite(uint32_t aA, uint32_t aB);

static void InitializeOrders();

// Constants
/////////////////////////////////////////////////////////////////////////////

static const Data COLORS[] =
{
    { "COLOR_ALICE_BLUE"             , "AliceBlue"           , HI::COLOR_ALICE_BLUE              }, // f0 f8 ff  307    0
    { "COLOR_ANTIQUE_WHITE"          , "AntiqueWhite"        , HI::COLOR_ANTIQUE_WHITE           }, // fa eb d7  2bc    1
    { "COLOR_AQUA"                   , "Aqua"                , HI::COLOR_AQUA                    }, // 00 ff ff  1fe    2
    { "COLOR_AQUAMARINE"             , "Aquamarine"          , HI::COLOR_AQUAMARINE              }, // 7f ff d4  252    3
    { "COLOR_AZURE"                  , "Azure"               , HI::COLOR_AZURE                   }, // f0 ff ff  2ee    4
    { "COLOR_BEIGE"                  , "Beige"               , HI::COLOR_BEIGE                   }, // f5 f5 dc  2c6    5
    { "COLOR_BISQUE"                 , "Bisque"              , HI::COLOR_BISQUE                  }, // ff e4 c4  2a7    6
    { "COLOR_BLACK"                  , "Black"               , HI::COLOR_BLACK                   }, // 00 00 00    0    7
    { "COLOR_BLANCHED_ALMOND"        , "BlanchedAlmond"      , HI::COLOR_BLANCHED_ALMOND         }, // ff eb cd  2b7    8
    { "COLOR_BLUE"                   , "Blue"                , HI::COLOR_BLUE                    }, // 00 00 ff   ff    9
    { "COLOR_BLUE_VIOLET"            , "BlueViolet"          , HI::COLOR_BLUE_VIOLET             }, // 8a 2b e2  197   10
    { "COLOR_BROWN"                  , "Brown"               , HI::COLOR_BROWN                   }, // a5 2a 2a   f9   11
    { "COLOR_BURLY_WOOD"             , "BurlyWood"           , HI::COLOR_BURLY_WOOD              }, // de b8 87  21d   12
    { "COLOR_CADET_BLUE"             , "CadetBlue"           , HI::COLOR_CADET_BLUE              }, // 5f 9e a0  19d   13
    { "COLOR_CHARTREUSE"             , "Chartreuse"          , HI::COLOR_CHARTREUSE              }, // 7f 77 00   f6   14
    { "COLOR_CHOCOLATE"              , "Chocolate"           , HI::COLOR_CHOCOLATE               }, // d2 69 1e  159   15
    { "COLOR_CORAL"                  , "Coral"               , HI::COLOR_CORAL                   }, // ff 7f 50  1ce   16
    { "COLOR_CORNFLOWER_BLUE"        , "CornflowerBlue"      , HI::COLOR_CORNFLOWER_BLUE         }, // 64 95 ed  1e6   17
    { "COLOR_CORNSILK"               , "Cornsilk"            , HI::COLOR_CORNSILK                }, // ff f8 dc  2d3   18
    { "COLOR_CRIMSON"                , "Crimson"             , HI::COLOR_CRIMSON                 }, // dc 14 3c  12c   19
    { "COLOR_CYAN"                   , "Cyan"                , HI::COLOR_CYAN                    }, // 00 ff ff  1fe   20
    { "COLOR_DARK_BLUE"              , "DarkBlue"            , HI::COLOR_DARK_BLUE               }, // 00 00 8b   8b   21
    { "COLOR_DARK_CYAN"              , "DarkCyan"            , HI::COLOR_DARK_CYAN               }, // 00 0b 0b   16   22
    { "COLOR_DARK_GOLDER_ROD"        , "DarkGoldenRod"       , HI::COLOR_DARK_COLDEN_ROD         }, // b8 86 0b  149   23
    { "COLOR_DARK_GRAY"              , "DarkGray"            , HI::COLOR_DARK_GRAY               }, // a9 a9 a9  1f6   24
    { "COLOR_DARK_GREEN"             , "DarkGreen"           , HI::COLOR_DARK_GREEN              }, // 00 64 00   64   25
    { "COLOR_DARK_KHAKI"             , "DarkKhaki"           , HI::COLOR_DARK_KHAKI              }, // bd b7 6b  1df   26
    { "COLOR_DARK_MAGENTA"           , "DarkMagenta"         , HI::COLOR_DARK_MAGENTA            }, // 8b 00 8b  116   27
    { "COLOR_DARK_OLIVE_GREEN"       , "DarkOliveGreen"      , HI::COLOR_DARK_OLIVE_GREEN        }, // 55 6b 2f   ef   28
    { "COLOR_DARK_ORANGE"            , "DarkOrange"          , HI::COLOR_DARK_ORANGE             }, // ff 8c 00  18b   29
    { "COLOR_DARK_ORCHID"            , "DarkOrchid"          , HI::COLOR_DARK_ORCHID             }, // 99 32 cc  197   30
    { "COLOR_DARK_RED"               , "DarkRed"             , HI::COLOR_DARK_RED                }, // 8b 00 00   8b   31
    { "COLOR_DARK_SALMON"            , "DarkSalmon"          , HI::COLOR_DARK_SALMON             }, // e9 96 7a  1f9   32
    { "COLOR_DARK_SEA_GREEN"         , "DarkSeaGreen"        , HI::COLOR_DARK_SEA_GREEN          }, // 8f bc 8f  1da   33
    { "COLOR_DARK_SLATE_BLUE"        , "DarkSlateBlue"       , HI::COLOR_DARK_SLATE_BLUE         }, // 48 3d 8b  110   34
    { "COLOR_DARK_SLATE_GRAY"        , "DarkSlateGray"       , HI::COLOR_DARK_SLATE_GRAY         }, // 2f 4f 4f   cd   35
    { "COLOR_DARK_TURQUOISE"         , "DarkTurquoise"       , HI::COLOR_DARK_TURQUOISE          }, // 00 ce d1  19f   36
    { "COLOR_DARK_VIOLET"            , "DarkViolet"          , HI::COLOR_DARK_VIOLET             }, // 94 00 d3  167   37
    { "COLOR_DEEP_PINK"              , "DeepPink"            , HI::COLOR_DEEP_PINK               }, // ff 14 93  1a6   38
    { "COLOR_DEEP_SKY_BLUE"          , "DeepSkyBlue"         , HI::COLOR_DEEP_SKY_BLUE           }, // 00 bf ff  1be   39
    { "COLOR_DIM_GRAY"               , "DimGray"             , HI::COLOR_DIM_GRAY                }, // 69 69 69  13b   40
    { "COLOR_DODGER_BLUE"            , "DodgerBlue"          , HI::COLOR_DODGER_BLUE             }, // 1e 90 ff  1ad   41
    { "COLOR_FIRE_BRICK"             , "FireBrick"           , HI::COLOR_FIRE_BRICK              }, // b2 22 22   f6   42
    { "COLOR_FLORAL_WHITE"           , "FloralWhite"         , HI::COLOR_FLORAL_WHITE            }, // ff fa f0  2e9   43
    { "COLOR_FOREST_GREEN"           , "ForestGreen"         , HI::COLOR_FOREST_GREEN            }, // 22 8b 22   cf   44
    { "COLOR_FUCHSIA"                , "Fuchsia"             , HI::COLOR_FUCHSIA                 }, // ff 00 ff  1fe   45
    { "COLOR_GAINSBORO"              , "Gainsboro"           , HI::COLOR_GAINSBORO               }, // dc dc dc  294   46
    { "COLOR_GHOST_WHITE"            , "GhostWhite"          , HI::COLOR_GHOST_WHITE             }, // f8 f8 ff  2ef   47
    { "COLOR_GOLD"                   , "Gold"                , HI::COLOR_GOLD                    }, // ff d7 00  1d6   48
    { "COLOR_GOLDEN_ROD"             , "GoldenRod"           , HI::COLOR_GOLDEN_ROD              }, // da a5 20  19f   49
    { "COLOR_GRAY"                   , "Gray"                , HI::COLOR_GRAY                    }, // 80 80 80  180   50
    { "COLOR_GREEN"                  , "Green"               , HI::COLOR_GREEN                   }, // 00 80 00   80   51
    { "COLOR_GREEN_YELLOW"           , "GreenYellow"         , HI::COLOR_GREEN_YELLOW            }, // ad ff 2f  1db   52
    { "COLOR_HONEY_DEW"              , "HoneyDew"            , HI::COLOR_HONEY_DEW               }, // f0 ff f0  2df   53
    { "COLOR_HOT_PINK"               , "HotPink"             , HI::COLOR_HOT_PINK                }, // ff 69 b4  21c   54
    { "COLOR_INDIAN_RED"             , "IndianRed"           , HI::COLOR_INDIAN_RED              }, // cd 5c 5c  185   55
    { "COLOR_INDIGO"                 , "Indigo"              , HI::COLOR_INDIGO                  }, // 4b 00 82   cd   56
    { "COLOR_IVORY"                  , "Ivory"               , HI::COLOR_IVORY                   }, // ff ff f0  2ee   57
    { "COLOR_KHAKI"                  , "Khaki"               , HI::COLOR_KHAKI                   }, // f0 e6 8c  262   58
    { "COLOR_KMS_BLUE"               , "#005c87"             , HI::COLOR_KMS_BLUE                }, // 00 5c 87   e3   59
    { "COLOR_KMS_GREEN"              , "#83c54b"             , HI::COLOR_KMS_GREEN               }, // 83 c5 4b  195   60
    { "COLOR_LAVANDER"               , "Lavender"            , HI::COLOR_LAVENDER                }, // e6 e6 fa  2c6   61
    { "COLOR_LAVENDER_BLUSH"         , "LavenderBlush"       , HI::COLOR_LAVENDER_BLUSH          }, // ff f0 f5  2e4   62
    { "COLOR_LAWN_GREEN"             , "LawnGreen"           , HI::COLOR_LAWN_GREEN              }, // 7c fc 00  178   63
    { "COLOR_LEMON_CHIFFON"          , "LemonChiffon"        , HI::COLOR_LEMON_CHIFFON           }, // ff fa cd  2c6   64
    { "COLOR_LIGHT_BLUE"             , "LightBlue"           , HI::COLOR_LIGHT_BLUE              }, // ad d8 e6  26b   65
    { "COLOR_LIGHT_CORAL"            , "LightCoral"          , HI::COLOR_LIGHT_CORAL             }, // f0 80 80  1f0   66
    { "COLOR_LIGHT_CYAN"             , "LightGray"           , HI::COLOR_LIGHT_CYAN              }, // e0 ff ff  2de   67
    { "COLOR_LIGHT_GOLDEN_ROD_YELLOW", "LightGoldenRodYellow", HI::COLOR_LIGHT_GOLDEN_ROD_YELLOW }, // fa fa d2  2c6   68
    { "COLOR_LIGHT_GRAY"             , "LightGray"           , HI::COLOR_LIGHT_GRAY              }, // d3 d3 d3  279   69
    { "COLOR_LIGHT_GREEN"            , "LightGreen"          , HI::COLOR_LIGHT_GREEN             }, // 90 ee 90  20e   70
    { "COLOR_LIGHT_PINK"             , "LightPink"           , HI::COLOR_LIGHT_PINK              }, // ff b6 c1  276   71
    { "COLOR_LIGHT_SALMON"           , "LightSalmon"         , HI::COLOR_LIGHT_SALMON            }, // ff a0 7a  219   72
    { "COLOR_LIGHT_SEA_GREEN"        , "LightSeaGreen"       , HI::COLOR_LIGHT_SEA_GREEN         }, // 20 b2 aa  17c   73
    { "COLOR_LIGHT_SKY_BLUE"         , "LightSkyBlue"        , HI::COLOR_LIGHT_SKY_BLUE          }, // 87 ce fa  24f   74
    { "COLOR_LIGHT_SLATE_GRAY"       , "LightSLateGray"      , HI::COLOR_LIGHT_SLATE_GRAY        }, // 77 88 99  198   75
    { "COLOR_LIGHT_STEEL_BLUE"       , "LightSteelBlue"      , HI::COLOR_LIGHT_STEEL_BLUE        }, // b0 c4 de  252   76
    { "COLOR_LIGHT_YELLOW"           , "LightYellow"         , HI::COLOR_LIGHT_YELLOW            }, // ff ff e0  2de   77
    { "COLOR_LIME"                   , "Lime"                , HI::COLOR_LIME                    }, // 00 ff 00   ff   78
    { "COLOR_LIME_GREEN"             , "LimeGreen"           , HI::COLOR_LIME_GREEN              }, // 32 cd 32  131   79
    { "COLOR_LINEN"                  , "Linen"               , HI::COLOR_LINEN                   }, // fa f0 e6  2d0   80
    { "COLOR_MAGENTA"                , "Magenta"             , HI::COLOR_MAGENTA                 }, // ff 00 ff  1fe   81
    { "COLOR_MARROON"                , "Maroon"              , HI::COLOR_MAROON                  }, // 80 00 00   80   82
    { "COLOR_MEDIUM_AQUA_MARINE"     , "MediumAquaMarine"    , HI::COLOR_MEDIUM_AQUA_MARINE      }, // 66 cd aa  1dd   83
    { "COLOR_MEDIUM_BLUE"            , "MediumBlue"          , HI::COLOR_MEDIUM_BLUE             }, // 00 00 cd   cd   84
    { "COLOR_MEDIUM_ORCHID"          , "MediumOrchid"        , HI::COLOR_MEDIUM_ORCHID           }, // ba 55 d3  1e2   85
    { "COLOR_MEDIUM_PURPLE"          , "MediumPurple"        , HI::COLOR_MEDIUM_PURPLE           }, // 93 70 db  1de   86
    { "COLOR_MEDIUM_SEA_GREEN"       , "MediumSeaGreen"      , HI::COLOR_MEDIUM_SEA_GREEN        }, // 3c b3 71  160   87
    { "COLOR_MEDIUM_SLATE_BLUE"      , "MediumSlateBlue"     , HI::COLOR_MEDIUM_SLATE_BLUE       }, // 7b 68 ee  1d3   88
    { "COLOR_MEDIUM_SPRING_GREEN"    , "MediumSpringGreen"   , HI::COLOR_MEDIUM_SPRING_GREEN     }, // 00 fa 9a  194   89
    { "COLOR_MEDIUM_TURQUOISE"       , "MediumTurquoise"     , HI::COLOR_MEDIUM_TURQUOISE        }, // 48 d1 cc  1e5   90
    { "COLOR_MEDIUM_VIOLET_RED"      , "MediumVioletRed"     , HI::COLOR_MEDIUM_VIOLET_RED       }, // c7 15 85  161   91
    { "COLOR_MIDNIGHT_BLUE"          , "MidnightBlue"        , HI::COLOR_MIDNIGHT_BLUE           }, // 19 19 70   a2   92
    { "COLOR_MINT_CREAM"             , "MintCream"           , HI::COLOR_MINT_CREAM              }, // f5 ff fa  2ee   93
    { "COLOR_MISTY_ROSE"             , "MistyRose"           , HI::COLOR_MISTY_ROSE              }, // ff e4 e1  2c4   94
    { "COLOR_MOCCASIN"               , "Moccasin"            , HI::COLOR_MOCCASIN                }, // ff e4 b5  298   95
    { "COLOR_NAVAJO_WHITE"           , "NavajoWhite"         , HI::COLOR_NAVAJO_WHITE            }, // ff de ad  28a   96
    { "COLOR_NAVY"                   , "Navy"                , HI::COLOR_NAVY                    }, // 00 00 80   80   97
    { "COLOR_OLD_LACE"               , "OldLace"             , HI::COLOR_OLD_LACE                }, // fd f5 e6  2d8   98
    { "COLOR_OLIVE"                  , "Olive"               , HI::COLOR_OLIVE                   }, // 80 80 00  100   99
    { "COLOR_OLIVE_DRAB"             , "OliveDrab"           , HI::COLOR_OLIVE_DRAB              }, // 6b 8e 23  11c  100
    { "COLOR_ORANGE"                 , "Orange"              , HI::COLOR_ORANGE                  }, // ff a5 00  1a4  101
    { "COLOR_ORANGE_RED"             , "OrangeRed"           , HI::COLOR_ORAGE_RED               }, // ff 45 00  144  102
    { "COLOR_ORCHID"                 , "Orchid"              , HI::COLOR_ORCHID                  }, // da 70 d6  220  103
    { "COLOR_PALE_GOLDEN_ROD"        , "PaleGoldenRod"       , HI::COLOR_PALE_GOLDEN_ROD         }, // ee e8 aa  280  104
    { "COLOR_PALE_GREEN"             , "PaleGreen"           , HI::COLOR_PALE_GREEN              }, // 98 fb 98  22b  105
    { "COLOR_PALE_TRUQUOISE"         , "PaleTurquoise"       , HI::COLOR_PALE_TURQUOISE          }, // af ee ee  28b  106
    { "COLOR_PALE_VIOLET_RED"        , "PaleVioletRed"       , HI::COLOR_PALE_VIOLET_RED         }, // db 70 93  1de  107
    { "COLOR_PAPAYA_WHIP"            , "PapayaWhip"          , HI::COLOR_PAPAYA_WHIP             }, // ff ef d5  2c3  108
    { "COLOR_PEACH_PUFF"             , "PeachPuff"           , HI::COLOR_PEACH_PUFF              }, // ff da b9  292  109
    { "COLOR_PERU"                   , "Peru"                , HI::COLOR_PERU                    }, // cd 85 3f  191  110
    { "COLOR_PINK"                   , "Pink"                , HI::COLOR_PINK                    }, // ff c0 cb  28a  111
    { "COLOR_PLUM"                   , "Plum"                , HI::COLOR_PLUM                    }, // dd a0 dd  25a  112
    { "COLOR_POWDER_BLUE"            , "PowderBlue"          , HI::COLOR_POWDER_BLUE             }, // b0 e0 e6  276  113
    { "COLOR_PURPLE"                 , "Purple"              , HI::COLOR_PURPLE                  }, // 80 00 80  100  114
    { "COLOR_REBECCA_PURPLE"         , "RebeccaPurple"       , HI::COLOR_REBECCA_PURPLE          }, // 66 33 99  132  115
    { "COLOR_RED"                    , "Red"                 , HI::COLOR_RED                     }, // ff 00 00   ff  116
    { "COLOR_ROSY_BROWN"             , "RosyBrown"           , HI::COLOR_ROSY_BROWN              }, // bc 8f 8f  1da  117
    { "COLOR_ROYAL_BLUE"             , "RoyalBlue"           , HI::COLOR_ROYAL_BLUE              }, // 41 69 e1  18b  118
    { "COLOR_SADDLE_BROWN"           , "SaddleBrown"         , HI::COLOR_SADDLE_BROWN            }, // 8b 45 13   e3  119
    { "COLOR_SALMON"                 , "Salmon"              , HI::COLOR_SALMON                  }, // fa 80 72  1ec  120
    { "COLOR_SANDY_BROWN"            , "SandyBrown"          , HI::COLOR_SANDY_BROWN             }, // f4 a4 60  1f8  121
    { "COLOR_SEA_GREEN"              , "SeaGreen"            , HI::COLOR_SEA_GREEN               }, // 2e 8b 57  110  122
    { "COLOR_SEA_SHELL"              , "SeaShell"            , HI::COLOR_SEA_SHELL               }, // ff f5 ee  2e2  123
    { "COLOR_SIENNA"                 , "Sienna"              , HI::COLOR_SIENNA                  }, // a0 52 2d  11f  124
    { "COLOR_SILVER"                 , "Silver"              , HI::COLOR_SILVER                  }, // c0 c0 c0  240  125
    { "COLOR_SKY_BLUE"               , "SkyBlue"             , HI::COLOR_SKY_BLUE                }, // 87 ce eb  240  126
    { "COLOR_SLATE_BLUE"             , "SlateBlue"           , HI::COLOR_SLATE_BLUE              }, // 6a 5a cd  191  127
    { "COLOR_SLATE_GRAY"             , "SlateGray"           , HI::COLOR_SLATE_GRAY              }, // 70 80 90  180  128
    { "COLOR_SNOW"                   , "Snow"                , HI::COLOR_SNOW                    }, // ff fa fa  2f3  129
    { "COLOR_SPRING_GREEN"           , "SpringGreen"         , HI::COLOR_SPRING_GREEN            }, // 00 ff 7f  17e  130
    { "COLOR_STEEL_BLUE"             , "SteelBlue"           , HI::COLOR_STEEL_BLUE              }, // 46 82 b4   fc  131
    { "COLOR_TAN"                    , "Tan"                 , HI::COLOR_TAN                     }, // d2 b4 8c  212  132
    { "COLOR_TEAL"                   , "Teal"                , HI::COLOR_TEAL                    }, // 00 80 80  100  133
    { "COLOR_THISTLE"                , "Thistle"             , HI::COLOR_THISTLE                 }, // d8 bf d8  26f  134
    { "COLOR_TOMATO"                 , "Tomato"              , HI::COLOR_TOMATO                  }, // ff 63 47  1a9  135
    { "COLOR_TURQUOISE"              , "Turquoise"           , HI::COLOR_TURQUOISE               }, // 40 e0 d0  1f0  136
    { "COLOR_VIOLET"                 , "Violet"              , HI::COLOR_VIOLET                  }, // ee 82 ee  25e  137
    { "COLOR_WHEAT"                  , "Wheat"               , HI::COLOR_WHEAT                   }, // f5 de b3  286  138
    { "COLOR_WHITE"                  , "White"               , HI::COLOR_WHITE                   }, // ff ff ff  2fd  139
    { "COLOR_WHITE_SMOKE"            , "WhiteSmoke"          , HI::COLOR_WHITE_SMOKE             }, // f5 f5 f5  2df  140
    { "COLOR_YELLOW"                 , "Yellow"              , HI::COLOR_YELLOW                  }, // ff ff 00  1fe  141
    { "COLOR_YELLOW_GREEN"           , "YellowGreen"         , HI::COLOR_YELLOW_GREEN            }, // 9a cd 32  199  142
};

static CompareFunction COMPARES[HI::CSS_Colors::ORDER_QTY - 1] =
{
    CompareBlue ,
    CompareGreen,
    CompareRed  ,
    CompareWhite,
};

// Static variables
/////////////////////////////////////////////////////////////////////////////

static bool     sOrderInit;
static uint16_t sOrders[HI::CSS_Colors::ORDER_QTY][HI::COLOR_QTY];

// Macros
/////////////////////////////////////////////////////////////////////////////

#define BLUE(C)  ( (C)        & 0xff)
#define GREEN(C) (((C) >>  8) & 0xff)
#define RED(C)   (((C) >> 16) & 0xff)
#define WHITE(C) BLUE(C) + GREEN(C) + RED(C)

namespace HI
{

    // Public
    /////////////////////////////////////////////////////////////////////////

    uint8_t CSS_ColorInfo::GetBlue () const { return BLUE (mValue); }
    uint8_t CSS_ColorInfo::GetGreen() const { return GREEN(mValue); }
    uint8_t CSS_ColorInfo::GetRed  () const { return RED  (mValue); }

    // aOut [---;-W-]
    void CSS_Colors::GetFirst(CSS_ColorInfo * aOut, Order aOrder)
    {
        assert(NULL != aOut);

        memset(aOut, 0, sizeof(*aOut));

        if (!sOrderInit)
        {
            InitializeOrders();
        }

        switch (aOrder)
        {
        case ORDER_BLUE :
        case ORDER_GREEN:
        case ORDER_RED  :
        case ORDER_WHITE:
            aOut->mIndex = sOrders[aOrder][0];
            break;

        case ORDER_NAME:
            break;

        default:assert(false);
        }

        const Data * lData = COLORS + aOut->mIndex;

        aOut->mIdName  = lData->mIdName;
        aOut->mName    = lData->mName  ;
        aOut->mOrder   = aOrder        ;
        aOut->mValue   = lData->mValue ;
    }

    // aInOut [---;RW-]
    bool CSS_Colors::GetNext(CSS_ColorInfo * aInOut)
    {
        assert(NULL != aInOut);

        aInOut->mIndexBy++;
        if (COLOR_QTY <= aInOut->mIndexBy)
        {
            return false;
        }

        switch (aInOut->mOrder)
        {
        case ORDER_BLUE :
        case ORDER_GREEN:
        case ORDER_RED  :
        case ORDER_WHITE:
            aInOut->mIndex = sOrders[aInOut->mOrder][aInOut->mIndexBy];
            break;

        case ORDER_NAME:
            aInOut->mIndex = aInOut->mIndexBy;
            break;

        default: assert(false);
        }
        
        const Data * lData = COLORS + aInOut->mIndex;

        aInOut->mIdName = lData->mIdName;
        aInOut->mName   = lData->mName  ;
        aInOut->mValue  = lData->mValue ;

        return true;
    }

}

int CompareBlue(uint32_t aA, uint32_t aB)
{
    uint8_t lBA = BLUE(aA);
    uint8_t lBB = BLUE(aB);

    if (lBA < lBB) { return -1; }
    if (lBA > lBB) { return  1; }

    uint16_t lWA = WHITE(aA);
    uint16_t lWB = WHITE(aB);

    if (lWA < lWB) { return -1; }
    if (lWA > lWB) { return  1; }

    uint8_t lGA = GREEN(aA);
    uint8_t lGB = GREEN(aB);

    if (lGA < lGB) { return -1; }
    if (lGA > lGB) { return  1; }

    return 0;
}

int CompareGreen(uint32_t aA, uint32_t aB)
{
    uint8_t lBA = GREEN(aA);
    uint8_t lBB = GREEN(aB);

    if (lBA < lBB) { return -1; }
    if (lBA > lBB) { return  1; }

    uint16_t lWA = WHITE(aA);
    uint16_t lWB = WHITE(aB);

    if (lWA < lWB) { return -1; }
    if (lWA > lWB) { return  1; }

    return 0;
}

int CompareRed(uint32_t aA, uint32_t aB)
{
    uint8_t lBA = RED(aA);
    uint8_t lBB = RED(aB);

    if (lBA < lBB) { return -1; }
    if (lBA > lBB) { return  1; }

    uint16_t lWA = WHITE(aA);
    uint16_t lWB = WHITE(aB);

    if (lWA < lWB) { return -1; }
    if (lWA > lWB) { return  1; }

    uint8_t lGA = GREEN(aA);
    uint8_t lGB = GREEN(aB);

    if (lGA < lGB) { return -1; }
    if (lGA > lGB) { return  1; }

    return 0;
}

int CompareWhite(uint32_t aA, uint32_t aB)
{
    uint16_t lWA = WHITE(aA);
    uint16_t lWB = WHITE(aB);

    if (lWA < lWB) { return -1; }
    if (lWA > lWB) { return  1; }

    uint8_t lGA = GREEN(aA);
    uint8_t lGB = GREEN(aB);

    if (lGA < lGB) { return -1; }
    if (lGA > lGB) { return  1; }

    return 0;
}

void InitializeOrders()
{
    assert(!sOrderInit);

    for (unsigned int lOrder = HI::CSS_Colors::ORDER_BLUE; lOrder < HI::CSS_Colors::ORDER_QTY - 1; lOrder++)
    {
        for (unsigned int i = 0; i < HI::COLOR_QTY; i++)
        {
            unsigned int j;

            for (j = 0; j < i; j++)
            {
                if (0 > COMPARES[lOrder](COLORS[sOrders[lOrder][j]].mValue, COLORS[i].mValue))
                {
                    memmove(sOrders[lOrder] + j + 1, sOrders[lOrder] + j, (i - j) * sizeof(uint16_t));
                    sOrders[lOrder][j] = i;
                    break;
                }
            }

            if (j == i)
            {
                sOrders[lOrder][i] = i;
            }
        }
    }

    sOrderInit = true;
}
