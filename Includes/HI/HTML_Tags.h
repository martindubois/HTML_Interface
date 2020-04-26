
// Product  HTML_Interface

/// \author KMS - Martin Dubois, P.Eng.
/// \file   Includes/HI/HTML_Tags.h

#pragma once

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== Includes ===========================================================
#include <HI/HTML_Attributes.h>

namespace HI
{

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
    HTML_Tag;

    /// \brief HTML_TagInfo
    class HTML_TagInfo
    {

    public:

        const char * mIdName;
        unsigned int mIndex ;
        const char * mName  ;

    };

    /// \brief HTML_Tags
    class HTML_Tags
    {

    public:

        static bool FindByIdName(HTML_TagInfo * aOut, const char * aIdName);

        static void FindByIndex(HTML_TagInfo * aOut, HTML_Tag aIndex);

        static bool FindByName(HTML_TagInfo * aOut, const char * aName);

        static bool GetElement(HTML_TagInfo * aInOut);

        static void GetFirst(HTML_TagInfo * aOut);

        static void GetLast(HTML_TagInfo * aOut);

        static bool GetNext(HTML_TagInfo * aInOut);

        static bool GetPrevious(HTML_TagInfo * aInOut);

    };

}
