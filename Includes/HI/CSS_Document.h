
// Product  HTML_Interface

/// \author KMS - Martin Dubois, P.Eng.
/// \file   Includes/HI/CSS_Document.h

#pragma once

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== Includes ===========================================================
#include <HI/Document.h>

namespace HI
{

    /// \brief CSS_Document
    class CSS_Document : public Document
    {

    public:

        typedef enum
        {
            ALIGN_INHERIT,
            ALIGN_INITIAL,

            ALIGN_AUTO         ,
            ALIGN_BASELINE     ,
            ALIGN_CENTER       ,
            ALIGN_FLEX_END     ,
            ALIGN_FLEX_START   ,
            ALIGN_SPACE_AROUND ,
            ALIGN_SPACE_BETWEEN,
            ALIGN_STRETCH      ,
        }
        AlignName;

        typedef enum
        {
            BACKGROUND_ATTACHMENT_INHERIT,
            BACKGROUND_ATTACHMENT_INITIAL,

            BACKGROUND_ATTACHMENT_FIXED ,
            BACKGROUND_ATTACHMENT_LOCAL ,
            BACKGROUND_ATTACHMENT_SCROLL,
        }
        BackgrounAttachmentName;

        typedef enum
        {
            BACKGROUND_BLEND_MODE_COLOR      ,
            BACKGROUND_BLEND_MODE_COLOR_DODGE,
            BACKGROUND_BLEND_MODE_DARKEN     ,
            BACKGROUND_BLEND_MODE_LIGHTEN    ,
            BACKGROUND_BLEND_MODE_LUMINOSITY ,
            BACKGROUND_BLEND_MODE_MULTIPLY   ,
            BACKGROUND_BLEND_MODE_NORMAL     ,
            BACKGROUND_BLEND_MODE_OVERLAY    ,
            BACKGROUND_BLEND_MODE_SATURATION ,
            BACKGROUND_BLEND_MODE_SCREEN     ,
        }
        BackgroundBlendModeName;

        typedef enum
        {
            BACKGROUND_INHERIT,
            BACKGROUND_INITIAL,

            BACKGROUND_CLIP_BORDER_BOX ,
            BACKGROUND_CLIP_CONTENT_BOX,
            BACKGROUND_CLIP_PADDING_BOX,
        }
        BackgroundClipName;

        typedef enum
        {
            BASE_INITIAL,
            BASE_INHERIT,
            BASE_NONE   ,
            BASE_UNSET  ,
        }
        BaseName;

        typedef enum
        {
            BORDER_STYLE_INITIAL,
            BORDER_STYLE_INHERIT,
            BORDER_STYLE_NONE   ,

            BORDER_STYLE_DASHED,
            BORDER_STYLE_DOTTED,
            BORDER_STYLE_DOUBLE,
            BORDER_STYLE_GROOVE,
            BORDER_STYLE_HIDDEN,
            BORDER_STYLE_INSET ,
            BORDER_STYLE_OUTSET,
            BORDER_STYLE_RIDGE ,
            BORDER_STYLE_SOLID ,
        }
        BorderStyleName;

        typedef enum
        {
            DIRECTION_INHERIT,
            DIRECTION_INITIAL,

            DIRECTION_ALTERNATE        ,
            DIRECTION_ALTERNATE_REVERSE,
            DIRECTION_NORMAL           ,
            DIRECTION_REVERSE          ,
        }
        DirectionName;

        typedef enum
        {
            FILL_MODE_INHERIT,
            FILL_MODE_INITIAL,
            FILL_MODE_NONE   ,

            FILL_MODE_BACKWARDS,
            FILL_MODE_BOTH     ,
            FILL_MODE_FORWARDS ,
        }
        FillModeName;

        class Info
        {

        public:

            const char * mIdName;
            unsigned int mIndex ;
            const char * mName  ;

        };

        typedef enum
        {
            PLAY_STATE_INHERITED,
            PLAY_STATE_INITIAL  ,

            PLAY_STATE_PAUSED ,
            PLAY_STATE_RUNNING,
        }
        PlayStateName;

        typedef enum
        {
            PROP_BORDER_STYLE,
            PROP_PADDING     ,

            PROP_QTY
        }
        PropertyIndex;

        typedef enum
        {
            TIMMING_FUNCTION_INHERIT,
            TIMMING_FUNCTION_INITIAL,

            TIMMING_FUNCTION_CUBIC_BEZIER,
            TIMMING_FUNCTION_EASE        ,
            TIMMING_FUNCTION_EASE_IN     ,
            TIMMING_FUNCTION_EASE_OUT    ,
            TIMMING_FUNCTION_LINEAR      ,
            TIMMING_FUNCTION_STEP        ,
            TIMMING_FUNCTION_STEP_END    ,
            TIMMING_FUNCTION_STEP_START  ,
        }
        TimmingFunctionName;

        typedef enum
        {
            UNIT_MS,
            UNIT_PX,
            UNIT_S ,
        }
        UnitName;

        typedef enum
        {
            VISIBILITY_INHERIT,
            VISIBILITY_INITIAL,

            VISIBILITY_HIDEN  ,
            VISIBILITY_VISIBLE,
        }
        VisibilityName;

        static void Property_GetFirst(Info * aOut);

        static bool Property_GetNext(Info * aInOut);

        CSS_Document();

        /// \exception std::exception
        void Property_Set(PropertyIndex aProp, AlignName aValue);

        /// \exception std::exception
        void Property_Set(PropertyIndex aProp, BackgrounAttachmentName aValue);

        /// \exception std::exception
        void Property_Set(PropertyIndex aProp, BackgroundBlendModeName aValue);

        /// \exception std::exception
        void Property_Set(PropertyIndex aProp, BackgroundClipName aValue);

        /// \exception std::exception
        void Property_Set(PropertyIndex aProp, BaseName aValue);

        /// \exception std::exception
        void Property_Set(PropertyIndex aProp, BorderStyleName aValue);

        /// \exception std::exception
        void Property_Set(PropertyIndex aProp, DirectionName aValue);

        /// \exception std::exception
        void Property_Set(PropertyIndex aProp, FillModeName aValue);

        /// \exception std::exception
        void Property_Set(PropertyIndex aProp, PlayStateName aValue);

        /// \exception std::exception
        void Property_Set(PropertyIndex aProp, TimmingFunctionName aValue);

        /// \exception std::exception
        void Property_Set(PropertyIndex aProp, VisibilityName aValue);

        /// \exception std::exception
        void Property_Set(PropertyIndex aProp, unsigned int aValue, UnitName aUnit);

        /// \exception std::exception
        void Property_Set(PropertyIndex aProp, const char * aValue);

        /// \exception std::exception
        void Rule_Begin_Class(const char * aClass);

        /// \exception std::exception
        void Rule_Begin_Element(const char * aElement);

        /// \exception std::exception
        void Rule_Begin_Elements(const char * aFirst, ...);

        /// \exception std::exception
        void Rule_Begin_Elements(unsigned int aCount, const char * * aVector);

        /// \exception std::exception
        void Rule_Begin_Element_Class(const char * aElement, const char * aClass);

        /// \exception std::exception
        void Rule_Begin_Id(const char * aId);

        /// \exception std::exception
        void Rule_Begin_Universal();

        /// \exception std::exception
        void Rule_End();

        // ===== Document ===================================================

        virtual ~CSS_Document();

        virtual void Comment_Begin();
        virtual void Comment_End  ();

        virtual void Create(Document   * aDocument);
        virtual void Create(FolderId     aFolder, const char * aName);
        virtual void Create(const char * aFolder, const char * aName);

        virtual void NewLine();

    private:

        void Create();

        bool mInRule;

    };

}
