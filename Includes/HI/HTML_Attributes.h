
// Product  HTML_Interface

/// \author KMS - Martin Dubois, P.Eng.
/// \file   Includes/HI/HTML_Attributes.h

#pragma once

namespace HI
{

    typedef enum
    {
        ATTR_HREF ,
        ATTR_STYLE,

        ATTR_QTY,
        ATTR_EOL
    }
    HTML_Attribute;

    typedef enum
    {
        ATTR_TYPE_QTY,
        ATTR_TYPE_EOL
    }
    HTML_AttributeType;

    /// \brief HTML_AttributeInfo
    class HTML_AttributeInfo
    {

    public:

        const char * mIdName;
        unsigned int mIndex ;
        const char * mName  ;

    };

    /// \brief HTML_Attributes
    class HTML_Attributes
    {

    public:

        static bool FindByIdName(HTML_AttributeInfo * aOut, const char * aIdName);

        static void FindByIndex(HTML_AttributeInfo * aOut, HTML_Attribute aIndex);

        static bool FindByName(HTML_AttributeInfo * aOut, const char * aName);

        static void GetFirst(HTML_AttributeInfo * aOut);

        static void GetLast(HTML_AttributeInfo * aOut);

        static bool GetNext(HTML_AttributeInfo * aInOut);

        static bool GetPrevious(HTML_AttributeInfo * aInOut);

    };

}
