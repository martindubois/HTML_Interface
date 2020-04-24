
// Author     KMS - Martin Dubois, P.Eng.
// Copyright  (C) 2020 KMS. All rights reserved.
// Product    HTML_Interface
// File       HILib/HTML_Tags.cpp

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

// Constants
/////////////////////////////////////////////////////////////////////////////

static const Data TAGS[HI::TAG_QTY] =
{
    { "TAG_A"      , "a"             },
    { "TAG_BODY"   , "body"          },
    { "TAG_DOCTYPE", "!DOCTYPE html" },
    { "TAG_HEAD"   , "head"          },
    { "TAG_H1"     , "h1"            },
    { "TAG_H2"     , "h2"            },
    { "TAG_HTML"   , "html"          },
    { "TAG_P"      , "p"             },
    { "TAG_STYLE"  , "style"         },
    { "TAG_TABLE"  , "table"         },
    { "TAG_RD"     , "td"            },
    { "TAG_TITLE"  , "title"         },
    { "TAG_TR"     , "tr"            },
};

namespace HI
{

    // Public
    /////////////////////////////////////////////////////////////////////////

    void HTML_Tags::FindByIndex(HTML_TagInfo * aOut, HTML_Tag aIndex)
    {
        assert(NULL    != aOut  );
        assert(TAG_QTY >  aIndex);

        memset(aOut, 0, sizeof(*aOut));

        const Data * lData = TAGS + aIndex;

        aOut->mIdName = lData->mIdName;
        aOut->mName   = lData->mName  ;
        aOut->mTag    = aIndex        ;
    }

}
