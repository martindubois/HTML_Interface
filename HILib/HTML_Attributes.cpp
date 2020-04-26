
// Author     KMS - Martin Dubois, P.Eng.
// Copyright  (C) 2020 KMS. All rights reserved.
// Product    HTML_Interface
// File       HILib/HTML_Attributes.cpp

// CODE REVIEW 2020-04-26 KMS - Martin Dubois, P.Eng

// TEST COVERAGE 2020-04-26 KMS - Martin Dubois, P.Eng

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>
#include <memory.h>

// ===== Includes ===========================================================

#include <HI/HTML_Attributes.h>

// Data type
/////////////////////////////////////////////////////////////////////////////

class Data
{

public:

    const char * mIdName;
    const char * mName  ;

};

// Static function declarations
/////////////////////////////////////////////////////////////////////////////

static void CopyInfo(HI::HTML_AttributeInfo * aOut, const Data * aIn);
static void InitInfo(HI::HTML_AttributeInfo * aOut, const Data * aIn);

// Constants
/////////////////////////////////////////////////////////////////////////////

static const Data ATTRIBUTES[HI::ATTR_QTY] =
{
    { "ATTR_HREF" , "href"  },
    { "ATTR_STYLE", "style" },
};

namespace HI
{

    // Public
    /////////////////////////////////////////////////////////////////////////

    // aOut [---;-W-]
    void HTML_Attributes::FindByIndex(HTML_AttributeInfo * aOut, HTML_Attribute aIndex)
    {
        assert(NULL     != aOut  );
        assert(ATTR_QTY >  aIndex);

        InitInfo(aOut, ATTRIBUTES + aIndex);

        aOut->mIndex = aIndex;
    }

    // aOut [---;-W-]
    void HTML_Attributes::GetFirst(HTML_AttributeInfo * aOut)
    {
        assert(NULL != aOut);

        InitInfo(aOut, ATTRIBUTES);
    }

    // aOut [---;RW-]
    bool HTML_Attributes::GetNext(HTML_AttributeInfo * aInOut)
    {
        assert(NULL != aInOut);

        aInOut->mIndex++;
        if (ATTR_QTY <= aInOut->mIndex)
        {
            return false;
        }

        CopyInfo(aInOut, ATTRIBUTES + aInOut->mIndex);

        return true;
    }

}

// Static functions
/////////////////////////////////////////////////////////////////////////////

// aOut [---;-W-]
// aIn  [---;R--]
void CopyInfo(HI::HTML_AttributeInfo * aOut, const Data * aIn)
{
    assert(NULL != aOut);
    assert(NULL != aIn );

    aOut->mIdName = aIn->mIdName;
    aOut->mName   = aIn->mName  ;
}

// aOut [---;-W-]
// aIn  [---;R--]
void InitInfo(HI::HTML_AttributeInfo * aOut, const Data * aIn)
{
    assert(NULL != aOut);
    assert(NULL != aIn );

    memset(aOut, 0, sizeof(*aOut));

    CopyInfo(aOut, aIn);
}
