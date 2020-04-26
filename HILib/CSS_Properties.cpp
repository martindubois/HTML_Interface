
// Author     KMS - Martin Dubois, P.Eng.
// Copyright  (C) 2020 KMS. All rights reserved.
// Product    HTML_Interface
// File       HILib/CSS_Properties.cpp

// CODE REVIEW 2020-04-26 KMS - Martin Dubois. P.Eng.

// TEST COVERAGE 2020-04-26 KMS - Martin Dubois, P.Eng.

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>
#include <memory.h>

// ===== Includes ===========================================================

#include <HI/CSS_Properties.h>

// Data type
/////////////////////////////////////////////////////////////////////////////

class Data
{

public:

    const char * mIdName;
    const char * mName;

};

// Static fonction declarations
/////////////////////////////////////////////////////////////////////////////

static void CopyInfo(HI::CSS_PropertyInfo * aOut, const Data * aIn);
static void InitInfo(HI::CSS_PropertyInfo * aOut, const Data * aIn);

// Constants
/////////////////////////////////////////////////////////////////////////////

static const Data PROPERTIES[HI::PROP_QTY]
{
    { "PROP_BORDER_STYLE", "border-style" },
    { "PROP_PADDING"     , "padding"      },
};

namespace HI
{

    // Public
    /////////////////////////////////////////////////////////////////////////

    // aOut [---;-W-]
    void CSS_Properties::FindByIndex(CSS_PropertyInfo * aOut, CSS_Property aIndex)
    {
        assert(NULL     != aOut  );
        assert(PROP_QTY >  aIndex);

        InitInfo(aOut, PROPERTIES + aIndex);

        aOut->mIndex = aIndex;
    }

    // aOut [---;-W-]
    void CSS_Properties::GetFirst(CSS_PropertyInfo * aOut)
    {
        assert(NULL != aOut);

        InitInfo(aOut, PROPERTIES);
    }

    // aInOut [---;RW-]
    bool CSS_Properties::GetNext(CSS_PropertyInfo * aInOut)
    {
        assert(NULL != aInOut);

        aInOut->mIndex++;
        if (PROP_QTY <= aInOut->mIndex)
        {
            return false;
        }

        CopyInfo(aInOut, PROPERTIES + aInOut->mIndex);

        return true;
    }

}

// Static functions
/////////////////////////////////////////////////////////////////////////////

// aOut [---;-W-]
// aIn  [---;R--]
void CopyInfo(HI::CSS_PropertyInfo * aOut, const Data * aIn)
{
    assert(NULL != aOut);
    assert(NULL != aIn );

    aOut->mIdName = aIn->mIdName;
    aOut->mName   = aIn->mName  ;
}

// aOut [---;-W-]
// aIn  [---;R--]
void InitInfo(HI::CSS_PropertyInfo * aOut, const Data * aIn)
{
    assert(NULL != aOut);
    assert(NULL != aIn );

    memset(aOut, 0, sizeof(*aOut));

    CopyInfo(aOut, aIn);
}
