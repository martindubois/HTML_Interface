
// Product  HTML_Interface

/// \author KMS - Martin Dubois, P.Eng.
/// \file   Includes/HI/HTML_Document.h

#pragma once

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C++ ================================================================
#include <list>
#include <string>

// ===== Includes ===========================================================
#include <HI/Document.h>
#include <HI/HTML_Attributes.h>
#include <HI/HTML_Tags.h>

namespace HI
{

    /// \brief HTML_Document
    class HTML_Document : public Document
    {

    public:

        typedef enum
        {
            AUTO_COMPLETE_OFF,
            AUTO_COMPLETE_ON ,
        }
        AutoCompleteName;

        typedef enum
        {
            BOOLEAN_FALSE,
            BOOLEAN_TRUE ,
        }
        BooleanName;

        typedef enum
        {
            FORM_METHOD_GET ,
            FORM_METHOD_POST,
        }
        FormMethodName;

        typedef enum
        {
            KIND_CAPTIONS    ,
            KIND_CHAPTERS    ,
            KIND_DESCRIPTIONS,
            KIND_METADATA    ,
            KIND_SUBTITLES   ,
        }
        KindName;

        typedef enum
        {
            PRELOAD_AUTO    ,
            PRELOAD_METADATA,
            PRELOAD_NONE    ,
        }
        PreloadName;

        typedef enum
        {
            REL_ALTERNATE   ,
            REL_AUTHOR      ,
            REL_BOOKMARK    ,
            REL_DNS_PREFETCH,
            REL_EXTERNAL    ,
            REL_HELP        ,
            REL_ICON        ,
            REL_LICENSE     ,
            REL_NEXT        ,
            REL_NO_FOLLOW   ,
            REL_NO_REFERRER ,
            REL_NO_OPENER   ,
            REL_PINGBACK    ,
            REL_PRECONNECT  ,
            REL_PREFETCH    ,
            REL_PRELOAD     ,
            REL_PREV        ,
            REL_SEARCH      ,
            REL_STYLESHEET  ,
            REL_TAG         ,
        }
        RelName;

        typedef enum
        {
            SCOPE_COL     ,
            SCOPE_COLGROUP,
            SCOPE_ROW     ,
            SCOPE_ROWGROUP,
        }
        ScopeName;

        typedef enum
        {
            SHAPE_CIRCLE ,
            SHAPE_DEFAULT,
            SHAPE_POLY   ,
            SHAPE_RECT   ,
        }
        ShapeName;

        typedef enum
        {
            TARGET_BLANK ,
            TARGET_PARENT,
            TARGET_SELF  ,
            TARGET_TOP   ,
        }
        TargetName;

        typedef enum
        {
            TYPE_BUTTON        ,
            TYPE_CHECKBOX      ,
            TYPE_COLOR         ,
            TYPE_DATE          ,
            TYPE_DATETIME_LOCAL,
            TYPE_EMAIL         ,
            TYPE_FILE          ,
            TYPE_HIDDEN        ,
            TYPE_IMAGE         ,
            TYPE_MONTH         ,
            TYPE_NUMBER        ,
            TYPE_PASSWORD      ,
            TYPE_RADIO         ,
            TYPE_RESET         ,
            TYPE_SEARCH        ,
            TYPE_SUBMIT        ,
            TYPE_TEL           ,
            TYPE_TEXT          ,
            TYPE_TIME          ,
            TYPE_URL           ,
            TYPE_WEEK          ,
        }
        TypeName;

        typedef enum
        {
            WRAP_HARD,
            WRAP_SOFT,
        }
        WrapName;

        HTML_Document();

        void Create(FolderId aFolder, const char * aName, const char * aTitle);

        void Create(const char * aFolder, const char * aName, const char * aTitle);

        void Attribute_Set(HTML_Attribute aAttribute, AutoCompleteName aValue);

        void Attribute_Set(HTML_Attribute aAttribute, BooleanName aValue);

        void Attribute_Set(HTML_Attribute aAttribute, FormMethodName aValue);

        void Attribute_Set(HTML_Attribute aAttribute, KindName aValue);

        void Attribute_Set(HTML_Attribute aAttribute, PreloadName aValue);

        void Attribute_Set(HTML_Attribute aAttribute, RelName aValue);

        void Attribute_Set(HTML_Attribute aAttribute, ScopeName aValue);

        void Attribute_Set(HTML_Attribute aAttribute, ShapeName aValue);

        void Attribute_Set(HTML_Attribute aAttribute, TargetName aValue);

        void Attribute_Set(HTML_Attribute aAttribute, TypeName aValue);

        void Attribute_Set(HTML_Attribute aAttribute, WrapName aValue);

        void Attribute_Set(HTML_Attribute aAttribute, const char * aValue);

        void Tag(HTML_Tag aTag);

        void Tag(HTML_Tag aTag, const char * aText);

        void Tag_Begin(HTML_Tag aTag);

        void Tag_End();

        // ===== Document ===================================================

        virtual ~HTML_Document();

        virtual void Close();

        virtual void Comment      (const char * aComment);
        virtual void Comment_Begin();
        virtual void Comment_End  ();

        virtual void Create(FolderId     aFolder, const char * aName);
        virtual void Create(const char * aFolder, const char * aName);

    private:

        typedef std::list<std::string> StringList;

        StringList mAttributes;
        bool       mEndBody   ;
        StringList mTags      ;

    };

}
