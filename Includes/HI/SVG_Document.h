
// Product  HTML_Interface

/// \author KMS - Martin Dubois, P.Eng.
/// \file   Includes/HI/SVG_Document.h

#pragma once

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== Includes ===========================================================
#include <HI/XML_Document.h>

namespace HI
{

    /// \brief SVG_Document
    class SVG_Document : public XML_Document
    {

    public:

        /// \brief AttributeIndex
        typedef enum
        {
            ATTR_CLASS           ,
            ATTR_CX              ,
            ATTR_CY              ,
            ATTR_D               ,
            ATTR_DX              ,
            ATTR_DY              ,
            ATTR_FILL            ,
            ATTR_FILL_RULE       ,
            ATTR_FX              ,
            ATTR_FY              ,
            ATTR_HEIGHT          ,
            ATTR_HREF            ,
            ATTR_ID              ,
            ATTR_LENGTH_ADJUST   ,
            ATTR_MARKER_HEIGHT   ,
            ATTR_MARKER_WIDTH    ,
            ATTR_OPACITY         ,
            ATTR_PATH_LENGTH     ,
            ATTR_POINTS          ,
            ATTR_R               ,
            ATTR_REF_X           ,
            ATTR_REF_Y           ,
            ATTR_ROTATE          ,
            ATTR_RX              ,
            ATTR_RY              ,
            ATTR_STROKE          ,
            ATTR_STROKE_DASHARRAY,
            ATTR_STROKE_LINECAP  ,
            ATTR_STROKE_WIDTH    ,
            ATTR_STYLE           ,
            ATTR_TARGET          ,
            ATTR_TEXT_LENGTH     ,
            ATTR_TRANSFORM       ,
            ATTR_VIEW_BOX        ,  
            ATTR_WIDTH           ,
            ATTR_X               ,
            ATTR_X1              ,
            ATTR_X2              ,
            ATTR_XMLNS           ,
            ATTR_Y               ,
            ATTR_Y1              ,
            ATTR_Y2              ,

            ATTR_QTY
        }
        AttributeIndex;

        /// \brief TagIndex
        typedef enum
        {
            TAG_A       ,
            TAG_CIRCLE  ,
            TAG_DEFS    ,
            TAG_ELLIPSE ,
            TAG_G       ,
            TAG_IMAGE   ,
            TAG_LINE    ,
            TAG_MARKER  ,
            TAG_PATH    ,
            TAG_POLYGON ,
            TAG_POLYLINE,
            TAG_RECT    ,
            TAG_STYLE   ,
            TAG_SVG     ,
            TAG_TEXT    ,
            TAG_TITLE   ,
            TAG_TSPAN   ,
            TAG_XML     ,

            TAG_QTY
        }
        TagIndex;

        SVG_Document();

        static void Attribute_GetFirst(Info * aOut);

        static bool Attribute_GetNext(Info * aInOut);

        static void Tag_GetFirst(Info * aOut);

        static bool Tag_GetNext(Info * aInOut);

        // ===== Document ===================================================

        virtual ~SVG_Document();

        virtual void Create(Document   * aDocument);
        virtual void Create(FolderId     aFolder, const char * aName);
        virtual void Create(const char * aFolder, const char * aName);

    private:

        void Create();

    };

}
