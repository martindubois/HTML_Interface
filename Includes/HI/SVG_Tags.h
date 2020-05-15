
// Product  HTML_Interface

/// \author KMS - Martin Dubois, P.Eng.
/// \file   Includes/HI/SVG_Tags.h

#pragma once

namespace HI
{

    /// \brief HTML_Tags
    class HTML_Tags
    {

    public:

        static bool FindByIdName(SVG_TagInfo * aOut, const char * aIdName);

        static void FindByIndex(SVG_TagInfo * aOut, HTML_Tag aIndex);

        static bool FindByName(SVG_TagInfo * aOut, const char * aName);

        static bool GetElement(SVG_TagInfo * aInOut);

        static void GetFirst(SVG_TagInfo * aOut);

        static void GetLast(SVG_TagInfo * aOut);

        static bool GetNext(SVG_TagInfo * aInOut);

        static bool GetPrevious(SVG_TagInfo * aInOut);

    };

}
