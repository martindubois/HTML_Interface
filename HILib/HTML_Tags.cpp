
// Author     KMS - Martin Dubois, P.Eng.
// Copyright  (C) 2020 KMS. All rights reserved.
// Product    HTML_Interface
// File       HILib/HTML_Tags.cpp

// CODE REVIEW 2020-04-26 KMS - Martin Dubois, P.Eng.

// TEST COVERAGE 2020-04-26 KMS - Martin Dubois, P.Eng.

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>
#include <memory.h>

// ===== Includes ===========================================================

#include <HI/HTML_Tags.h>

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

static void CopyInfo(HI::HTML_TagInfo * aOut, const Data * aIn);
static void InitInfo(HI::HTML_TagInfo * aOut, const Data * aIn);

// Constants
/////////////////////////////////////////////////////////////////////////////

static const Data TAGS[HI::TAG_QTY] =
{
    { "TAG_A"      , "a"             },
    { "TAG_BODY"   , "body"          },
    { "TAG_CODE"   , "code"          },
    { "TAG_DETAILS", "details"       },
    { "TAG_DOCTYPE", "!DOCTYPE html" },
    { "TAG_HEAD"   , "head"          },
    { "TAG_H1"     , "h1"            },
    { "TAG_H2"     , "h2"            },
    { "TAG_HR"     , "hr"            },
    { "TAG_HTML"   , "html"          },
    { "TAG_I"      , "i"             },
    { "TAG_P"      , "p"             },
    { "TAG_STYLE"  , "style"         },
    { "TAG_SUMMARY", "summary"       },
    { "TAG_TABLE"  , "table"         },
    { "TAG_TD"     , "td"            },
    { "TAG_TH"     , "th"            },
    { "TAG_TITLE"  , "title"         },
    { "TAG_TR"     , "tr"            },
};

namespace HI
{

    // Public
    /////////////////////////////////////////////////////////////////////////

    // aOut [---;-W-]
    void HTML_Tags::FindByIndex(HTML_TagInfo * aOut, HTML_Tag aIndex)
    {
        assert(NULL    != aOut  );
        assert(TAG_QTY >  aIndex);

        InitInfo(aOut, TAGS + aIndex);

        aOut->mIndex = aIndex;
    }

    // aOut [---;-W-]
    void HTML_Tags::GetFirst(HTML_TagInfo * aOut)
    {
        assert(NULL != aOut);

        InitInfo(aOut, TAGS);
    }

    // aInOut [---;RW-]
    bool HTML_Tags::GetNext(HTML_TagInfo * aInOut)
    {
        assert(NULL != aInOut);

        aInOut->mIndex++;
        if (TAG_QTY <= aInOut->mIndex)
        {
            return false;
        }

        CopyInfo(aInOut, TAGS + aInOut->mIndex);

        return true;
    }

}

// Static functions
/////////////////////////////////////////////////////////////////////////////

// aOut [---;-W-]
// aIn  [---;R--]
void CopyInfo(HI::HTML_TagInfo * aOut, const Data * aIn)
{
    assert(NULL != aOut);
    assert(NULL != aIn );

    aOut->mIdName = aIn->mIdName;
    aOut->mName   = aIn->mName  ;
}

// aOut [---;-W-]
// aIn  [---;R--]
void InitInfo(HI::HTML_TagInfo * aOut, const Data * aIn)
{
    assert(NULL != aOut);
    assert(NULL != aIn );

    memset(aOut, 0, sizeof(*aOut));

    CopyInfo(aOut, aIn);
}
