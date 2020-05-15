
// Author     KMS - Martin Dubois, P.Eng.
// Copyright  (C) 2020 KMS. All rights reserved.
// Product    HTML_Interface
// File       HILib/CSS_Document.cpp

// CODE REVIEW 2020-05-15 KMS - Martin Dubois, P.Eng.

// TEST COVERAGE 2020-05-15 KMS - Martin Dubois, P.Eng.

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>

// ===== Includes ===========================================================
#include <HI/CSS_Document.h>

// ===== HILib ==============================================================
#include "Utils.h"

// Data type
/////////////////////////////////////////////////////////////////////////////

class Data
{

public:

    const char * mIdName;
    const char * mName  ;

};

// Static fonction declarations
/////////////////////////////////////////////////////////////////////////////

static void Info_Copy(HI::CSS_Document::Info * aOut, const Data & aIn);
static void Info_Init(HI::CSS_Document::Info * aOut, const Data & aIn);

// Constants
/////////////////////////////////////////////////////////////////////////////

static const Data PROPERTIES[HI::CSS_Document::PROP_QTY]
{
    { "PROP_BORDER_STYLE", "border-style" },
    { "PROP_PADDING"     , "padding"      },
};

namespace HI
{

    // Public
    /////////////////////////////////////////////////////////////////////////

    // TESTED  CSS_Document.Properties.Enumerate
    //         GenDoc.exe uses Property_GetFirst and Property_GetNext.

    void CSS_Document::Property_GetFirst(Info * aOut)
    {
        assert(NULL != aOut);

        Info_Init(aOut, PROPERTIES[0]);
    }

    bool CSS_Document::Property_GetNext(Info * aInOut)
    {
        assert(NULL != aInOut);

        aInOut->mIndex++;
        if (PROP_QTY <= aInOut->mIndex)
        {
            return false;
        }

        Info_Copy(aInOut, PROPERTIES[aInOut->mIndex]);

        return true;
    }

    CSS_Document::CSS_Document() : Document("css"), mInRule(false)
    {
    }

    // NOT TESTED  CSS_Document.Property.Set
    //             Some BORDER_STYLE_ values

    // TESTED  CSS_Document.Property.Set
    //         Set a property using BorderStyleName enum (GenDoc.exe uses BORDER_STYLE_SOLID)

    void CSS_Document::Property_Set(PropertyIndex aProp, BorderStyleName aValue)
    {
        assert(PROP_QTY > aProp);

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

    // NOT TESTED CSS_Document.Property.Set
    //            Some UNIT_ values

    void CSS_Document::Property_Set(PropertyIndex aProp, unsigned int aValue, UnitName aUnit)
    {
        assert(PROP_QTY > aProp);

        const char * lUnit = NULL;

        switch (aUnit)
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

    void CSS_Document::Property_Set(PropertyIndex aProp, const char * aValue)
    {
        assert(PROP_QTY >  aProp );
        assert(NULL     != aValue);

        int lRet = fprintf(GetFile(), "%s: %s;", PROPERTIES[aProp].mName, aValue);
        Utl_VerifyReturn(lRet);
    }

    void CSS_Document::Rule_Begin_Element(const char * aElement)
    {
        assert(NULL != aElement);

        assert(!mInRule);

        int lRet = fprintf(GetFile(), "%s {", aElement);
        Utl_VerifyReturn(lRet);

        mInRule = true;
    }

    void CSS_Document::Rule_End()
    {
        assert(mInRule);

        mInRule = false;

        int lRet = fprintf(GetFile(), "}");
        Utl_VerifyReturn(lRet);
    }

    // ===== Document =======================================================

    CSS_Document::~CSS_Document()
    {
    }

    void CSS_Document::Comment_Begin()
    {
        NewLine();

        int lRet = fprintf(GetFile(), "/*");
        Utl_VerifyReturn(lRet);

        Document::Comment_Begin();

        NewLine();
    }

    void CSS_Document::Comment_End()
    {
        Document::Comment_End();

        NewLine();

        int lRet = fprintf(GetFile(), "*/");
        Utl_VerifyReturn(lRet);

        NewLine();
    }

    // TESTED  CSS_Document.Create
    //         Create a CSS document inside an HTML document (GenDoc.exe)

    void CSS_Document::Create(Document * aDocument)
    {
        assert(NULL != aDocument);

        Document::Create(aDocument);
    }

    void CSS_Document::Create(FolderId aFolder, const char * aName)
    {
        assert(FOLDER_QTY > aFolder);
        assert(NULL       != aName );

        Document::Create(aFolder, aName);

        Create();
    }

    void CSS_Document::Create(const char * aFolder, const char * aName)
    {
        assert(NULL != aName);

        Document::Create(aFolder, aName);

        Create();
    }

    void CSS_Document::NewLine()
    {
        Document::NewLine();

        Indent((mInRule ? 1 : 0) + (InComment() ? 1 : 0));
    }

    // Private
    /////////////////////////////////////////////////////////////////////////

    // TODO CSS_Document.Create
    //      Add the generation date and time to the comment

    void CSS_Document::Create()
    {
        Comment("Generated using the HTML_Interface library");
    }

}

// Static functions
/////////////////////////////////////////////////////////////////////////////

// aOut [---;-W-]
void Info_Copy(HI::CSS_Document::Info * aOut, const Data & aIn)
{
    assert(NULL !=   aOut);
    assert(NULL != (&aIn));

    aOut->mIdName = aIn.mIdName;
    aOut->mName   = aIn.mName  ;
}

// aOut [---;-W-]
void Info_Init(HI::CSS_Document::Info * aOut, const Data & aIn)
{
    assert(NULL !=   aOut);
    assert(NULL != (&aIn));

    memset(aOut, 0, sizeof(*aOut));

    Info_Copy(aOut, aIn);
}
