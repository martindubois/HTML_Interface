
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
#include <HI/XML_Document.h>

namespace HI
{

    /// \brief HTML_Document
    class HTML_Document : public XML_Document
    {

    public:

        typedef enum
        {
            ATTR_HREF ,
            ATTR_STYLE,

            ATTR_QTY
        }
        AttributeIndex;

        typedef enum
        {
            TAG_A      ,
            TAG_BODY   ,
            TAG_CODE   ,
            TAG_DETAILS,
            TAG_DOCTYPE,
            TAG_HEAD   ,
            TAG_H1     ,
            TAG_H2     ,
            TAG_HR     ,
            TAG_HTML   ,
            TAG_I      ,
            TAG_P      ,
            TAG_STYLE  ,
            TAG_SUMMARY,
            TAG_TABLE  ,
            TAG_TD     ,
            TAG_TH     ,
            TAG_TITLE  ,
            TAG_TR     ,

            TAG_QTY,
            TAG_NONE
        }
        TagIndex;

        static void Attribute_GetFirst(Info * aOut);

        static bool Attribute_GetNext(Info * aInOut);

        static bool Tag_FindByIdName(Info * aOut, const char * aIdName);

        static void Tag_FindByIndex(Info * aOut, TagIndex aIndex);

        static bool Tag_FindByName(Info * aOut, const char * aName);

        static void Tag_GetFirst(Info * aOut);

        static void Tag_GetLast(Info * aOut);

        static bool Tag_GetNext(Info * aInOut);

        static bool Tag_GetPrevious(Info * aInOut);

        HTML_Document();

        /// \exception std::exception
        void Create(FolderId aFolder, const char * aName, const char * aTitle);

        /// \exception std::exception
        void Create(const char * aFolder, const char * aName, const char * aTitle);

        // ===== Document ===================================================

        virtual ~HTML_Document();

        virtual void Create(FolderId     aFolder, const char * aName);
        virtual void Create(const char * aFolder, const char * aName);

    private:

        void Create();
        void Create(const char * aTitle);

    };

}
