
// Product  HTML_Interface

/// \author KMS - Martin Dubois, P.Eng.
/// \file   Includes/HTML_Tags.h

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
        TAG_DOCTYPE,
        TAG_HEAD   ,
        TAG_H1     ,
        TAG_H2     ,
        TAG_HTML   ,
        TAG_P      ,
        TAG_STYLE  ,
        TAG_TABLE  ,
        TAG_TD     ,
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

        const char  * mIdName;
        const char  * mName  ;
        HTML_Tag      mTag   ;

    };

    /// \brief HTML_Tags
    class HTML_Tags
    {

    public:

        typedef enum
        {
            ORDER_NAME    ,
            ORDER_SEQUENCE,
        }
        Order;

        static bool FindByIdName(HTML_TagInfo * aOut, const char * aIdName);

        static void FindByIndex(HTML_TagInfo * aOut, HTML_Tag aIndex);

        static bool FindByName(HTML_TagInfo * aOut, const char * aName);

        static bool GetElement(HTML_TagInfo * aInOut);

        static void GetFirst(HTML_TagInfo * aOut);

        static void GetLast(HTML_TagInfo * aOut);

        static void GetNext(HTML_TagInfo * aInOut, Order aOrder = ORDER_NAME);

        static void GetPrevious(HTML_TagInfo * aInOut, Order aOrder = ORDER_NAME);

    };

}
