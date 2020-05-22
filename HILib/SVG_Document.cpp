
// Author     KMS - Martin Dubois, P.Eng.
// Copyright  (C) 2020 KMS. All rights reserved.
// Product    HTML_Interface
// File       HILib/SVG_Document.cpp

// CODE REVIEW 2020-05-22 KMS - Martin Dubois, P.Eng.

// TEST COVERAGE 2020-05-22 KMS - Martin Dubois, P.Eng.

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>

// ===== Includes ===========================================================
#include <HI/SVG_Document.h>

// ===== HILib ==============================================================
#include "Utils.h"

// Constants
/////////////////////////////////////////////////////////////////////////////

static const HI::XML_Document::Data ATTRIBUTES[HI::SVG_Document::ATTR_QTY] =
{
    { "ATTR_CLASS"           , "class"            },
    { "ATTR_CX"              , "cx"               },
    { "ATTR_CY"              , "cy"               },
    { "ATTR_D"               , "d"                },
    { "ATTR_DX"              , "dx"               },
    { "ATTR_DY"              , "dy"               },
    { "ATTR_FILL"            , "fill"             },
    { "ATTR_FILL_RULE"       , "fill-rule"        },
    { "ATTR_FX"              , "fx"               },
    { "ATTR_FY"              , "fy"               },
    { "ATTR_HEIGHT"          , "height"           },
    { "ATTR_HREF"            , "xlink:href"       },
    { "ATTR_ID"              , "id"               },
    { "ATTR_LENGTH_ADJUST"   , "lengthAdjust"     },
    { "ATTR_MARKER_HEIGHT"   , "markerHeight"     },
    { "ATTR_MARKER_WIDTH"    , "markerWidth"      },
    { "ATTR_OPACITY"         , "opacity"          },
    { "ATTR_PATH_LENGTH"     , "pathLength"       },
    { "ATTR_POINTS"          , "points"           },
    { "ATTR_R"               , "r"                },
    { "ATTR_REF_X"           , "refx"             },
    { "ATTR_REF_Y"           , "refy"             },
    { "ATTR_ROTATE"          , "rotate"           },
    { "ATTR_RX"              , "rx"               },
    { "ATTR_RY"              , "ry"               },
    { "ATTR_STROKE"          , "stroke"           },
    { "ATTR_STROKE_DASHARRAY", "stroke-dasharray" },
    { "ATTR_STROKE_LINECAP"  , "stroke-linecap"   },
    { "ATTR_STROKE_WIDTH"    , "stroke-width"     },
    { "ATTR_STYLE"           , "style"            },
    { "ATTR_TARGET"          , "target"           },
    { "ATTR_TEXT_LENGTH"     , "textLength"       },
    { "ATTR_TRANSFORM"       , "transform"        },
    { "ATTR_VIEW_BOX"        , "viewBox"          },
    { "ATTR_WIDTH"           , "width"            },
    { "ATTR_X"               , "x"                },
    { "ATTR_X1"              , "x1"               },
    { "ATTR_X2"              , "x2"               },
    { "ATTR_XMLNS"           , "xmlns"            },
    { "ATTR_Y"               , "y"                },
    { "ATTR_Y1"              , "y1"               },
    { "ATTR_Y2"              , "y2"               },
};

static const HI::XML_Document::Data TAGS[HI::SVG_Document::TAG_QTY] =
{
    { "TAG_A"       , "a"        },
    { "TAG_CIRCLE"  , "circle"   },
    { "TAG_DEFS"    , "defs"     },
    { "TAG_ELLIPSE" , "ellipse"  },
    { "TAG_G"       , "g"        },
    { "TAG_IMAGE"   , "image"    },
    { "TAG_LINE"    , "line"     },
    { "TAG_MARKER"  , "marker"   },
    { "TAG_PATH"    , "path"     },
    { "TAG_POLYGON" , "polygon"  },
    { "TAG_POLYLINE", "polyline" },
    { "TAG_RECT"    , "rect"     },
    { "TAG_STYLE"   , "style"    },
    { "TAG_SVG"     , "svg"     , HI::XML_Document::FLAG_TAG_MANDATORY_ATTR },
    { "TAG_TEXT"    , "text"     },
    { "TAG_TITLE"   , "title"    },
    { "TAG_TSPAN"   , "tspan"    },
    { "TAG_XML"     , "?xml"    , HI::XML_Document::FLAG_TAG_MANDATORY_ATTR | HI::XML_Document::FLAG_TAG_NO_OPT_ATTR },
};

namespace HI
{

    // Public
    /////////////////////////////////////////////////////////////////////////

    // TESTED SVG_Document.Attributes.Enumerates
    //        GenDoc.exe uses Attributes_GetFirst and Attribute_GetNext.

    // aOut [---;-W-]
    void SVG_Document::Attribute_GetFirst(Info * aOut)
    {
        assert(NULL != aOut);

        Info_Init(aOut, ATTRIBUTES[0]);
    }

    bool SVG_Document::Attribute_GetNext(Info * aInOut)
    {
        assert(NULL != aInOut);

        aInOut->mIndex++;

        if (ATTR_QTY <= aInOut->mIndex)
        {
            return false;
        }

        Info_Copy(aInOut, ATTRIBUTES[aInOut->mIndex]);

        return true;
    }

    // TESTED SVG_Document.Tags.Enumerates
    //        GenDoc.exe uses Tag_GetFirst and Tag_GetNext.

    // aOut [---;-W-]
    void SVG_Document::Tag_GetFirst(Info * aOut)
    {
        assert(NULL != aOut);

        Info_Init(aOut, TAGS[0]);
    }

    bool SVG_Document::Tag_GetNext(Info * aInOut)
    {
        assert(NULL != aInOut);

        aInOut->mIndex++;

        if (TAG_QTY <= aInOut->mIndex)
        {
            return false;
        }

        Info_Copy(aInOut, TAGS[aInOut->mIndex]);

        return true;
    }

    SVG_Document::SVG_Document() : XML_Document("svg", ATTR_QTY, ATTRIBUTES, TAG_QTY, TAGS)
    {
        AddTagAttribute(TAG_SVG, " xmlns=\"http://www.w3.org/2000/svg\"");
        AddTagAttribute(TAG_XML, " version=\"1.0\" ?"                   );
    }

    // ===== Document =======================================================

    SVG_Document::~SVG_Document()
    {
    }

    // NOT TESTED SVG_Document.Create
    //            Create a SVG document into a HTML document

    void SVG_Document::Create(HI::Document * aDocument)
    {
        assert(NULL != aDocument);

        Document::Create(aDocument);

        Create();
    }

    void SVG_Document::Create(HI::FolderId aFolder, const char * aName)
    {
        assert(FOLDER_QTY >  aFolder);
        assert(NULL       != aName  );

        Document::Create(aFolder, aName);

        Create();
    }

    // NOT TESTED SVG_Document.Create
    //            Create a SVG document into a named folder

    void SVG_Document::Create(const char * aFolder, const char * aName)
    {
        assert(NULL != aFolder);
        assert(NULL != aName  );

        Document::Create(aFolder, aName);

        Tag(TAG_XML);

        Create();
    }

    // Private
    /////////////////////////////////////////////////////////////////////////

    void SVG_Document::Create()
    {
        NewLine();

        Tag_Begin(TAG_SVG);
    }

}
