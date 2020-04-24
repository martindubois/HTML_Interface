
// Product  HTML_Interface

/// \author KMS - Martin Dubois, P.Eng.
/// \file   Includes/CSS_Properties.h

#pragma once

namespace HI
{

    typedef enum
    {
        PROP_BORDER_STYLE,

        PROP_QTY
    }
    CSS_Property;

    typedef enum
    {
        PROP_TYPE_BORDER_STYLE,

        PROP_TYPE_QTY,
        PROP_TYPE_EOL
    }
    CSS_PropertyType;

    /// \brief CSS_PropertyInfo
    class CSS_PropertyInfo
    {

    public:

        const char * mIdName  ;
        const char * mName    ;
        CSS_Property mProperty;

    };

    /// \brief HTML_Properties
    class CSS_Properties
    {

    public:

        static bool FindByIdName(CSS_PropertyInfo * aOut, const char * aIdName);

        static void FindByIndex(CSS_PropertyInfo * aOut, CSS_Property aIndex);

        static bool FindByName(CSS_PropertyInfo * aOut, const char * aName);

        static void GetFirst(CSS_PropertyInfo * aOut);

        static void GetLast(CSS_PropertyInfo * aOut);

        static void GetNext(CSS_PropertyInfo * aInOut);

        static void GetPrevious(CSS_PropertyInfo * aInOut);

    };

}
