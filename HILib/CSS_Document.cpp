
// Author     KMS - Martin Dubois, P.Eng.
// Copyright  (C) 2020 KMS. All rights reserved.
// Product    HTML_Interface
// File       HILib/CSS_Document.cpp

// CODE REVIEW 2020-04-26 KMS - Martin Dubois. P.Eng.

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>

// ===== Includes ===========================================================
#include <HI/CSS_Document.h>

// ===== HILib ==============================================================
#include "Utils.h"

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

    // NOT TESTED CSS_Document.Property.UnsignedInt
    void CSS_Document::Property_Set(CSS_Property aProp, unsigned int aValue, UnitName aUnit)
    {
        assert(PROP_QTY > aProp);

        const char * lUnit = NULL;

        switch (aValue)
        {
        case UNIT_MS: lUnit = "ms"; break;
        case UNIT_PX: lUnit = "px"; break;
        case UNIT_S : lUnit = "s" ; break;

        default: assert(false);
        }

        char lStr[64];

        int lRet = sprintf_s(lStr, "%u %s", aValue, lUnit);
        Utl_VerifyReturn(lRet, sizeof(lStr));

        Property_Set(aProp, lStr);
    }

    // aValue [---;R--]
    void CSS_Document::Property_Set(CSS_Property aProp, const char * aValue)
    {
        CSS_PropertyInfo lPI;

        CSS_Properties::FindByIndex(&lPI, aProp);

        int lRet = fprintf(GetFile(), "%s: %s;", lPI.mName, aValue);
        Utl_VerifyReturn(lRet);
    }

    // aElement [---;R--]
    void CSS_Document::Rule_Begin_Element(const char * aElement)
    {
        int lRet = fprintf(GetFile(), "%s {", aElement);
        Utl_VerifyReturn(lRet);
    }

    void CSS_Document::Rule_End()
    {
        int lRet = fprintf(GetFile(), "}");
        Utl_VerifyReturn(lRet);
    }

    // ===== Document =======================================================

    CSS_Document::~CSS_Document()
    {
    }

    // TODO CSS_Document.Comment

    // aText [---;R--]
    void CSS_Document::Comment(const char * aText)
    {
        assert(NULL != aText);
    }

    void CSS_Document::Comment_Begin()
    {
    }

    void CSS_Document::Comment_End()
    {
    }

}
