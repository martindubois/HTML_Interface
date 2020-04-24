
// Author     KMS - Martin Dubois, P.Eng.
// Copyright  (C) 2020 KMS. All rights reserved.
// Product    HTML_Interface
// File       HILib/CSS_Document.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>

// ===== Includes ===========================================================

#include <HI/CSS_Document.h>

namespace HI
{

    // Public
    /////////////////////////////////////////////////////////////////////////

    CSS_Document::CSS_Document() : Document("css")
    {
    }

    void CSS_Document::Property_Set(CSS_Property aProp, BorderStyleName aValue)
    {
        const char * lValue = NULL;

        switch (aValue)
        {
        case BORDER_STYLE_DASHED : lValue = "dashed" ; break;
        case BORDER_STYLE_DOTTED : lValue = "dotted" ; break;
        case BORDER_STYLE_DOUBLE : lValue = "double" ; break;
        case BORDER_STYLE_GROOVE : lValue = "groove" ; break;
        case BORDER_STYLE_HIDDEN : lValue = "hidden" ; break;
        case BORDER_STYLE_INHERIT: lValue = "inherit"; break;
        case BORDER_STYLE_INITIAL: lValue = "initial"; break;
        case BORDER_STYLE_INSET  : lValue = "inset"  ; break;
        case BORDER_STYLE_NONE   : lValue = "none"   ; break;
        case BORDER_STYLE_OUTSET : lValue = "outset" ; break;
        case BORDER_STYLE_RIDGE  : lValue = "ridge"  ; break;
        case BORDER_STYLE_SOLID  : lValue = "solid"  ; break;

        default: assert(false);
        }

        Property_Set(aProp, lValue);
    }

    void CSS_Document::Property_Set(CSS_Property aProp, const char * aValue)
    {
        CSS_PropertyInfo lPI;

        CSS_Properties::FindByIndex(&lPI, aProp);

        int lRet = fprintf(GetFile(), "%s: %s;", lPI.mName, aValue);
        if (0 >= lRet)
        {
            throw std::exception("fprintf( , , ,  ) failed", lRet);
        }
    }

    void CSS_Document::Rule_Begin_Element(const char * aElement)
    {
        int lRet = fprintf(GetFile(), "%s {", aElement);
        if (0 >= lRet)
        {
            throw std::exception("fprintf( , , ) failed", lRet);
        }
    }

    void CSS_Document::Rule_End()
    {
        int lRet = fprintf(GetFile(), "}");
        if (0 >= lRet)
        {
            throw std::exception("fprintf( ,  ) failed", lRet);
        }
    }

    // ===== Document =======================================================

    CSS_Document::~CSS_Document()
    {
    }

    void CSS_Document::Comment(const char * aText)
    {
        assert(NULL != aText);

        // TODO
    }

    void CSS_Document::Comment_Begin()
    {
        // TODO
    }

    void CSS_Document::Comment_End()
    {
        // TODO
    }

}
