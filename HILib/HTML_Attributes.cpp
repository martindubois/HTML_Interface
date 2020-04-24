
// Author     KMS - Martin Dubois, P.Eng.
// Copyright  (C) 2020 KMS. All rights reserved.
// Product    HTML_Interface
// File       HILib/HTML_Attributes.cpp

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

    void HTML_Attributes::FindByIndex(HTML_AttributeInfo * aOut, HTML_Attribute aAttr)
    {
        assert(NULL     != aOut );
        assert(ATTR_QTY >  aAttr);

        memset(aOut, 0, sizeof(*aOut));

        const Data * lData = ATTRIBUTES + aAttr;

        aOut->mAttribute = aAttr         ;
        aOut->mIdName    = lData->mIdName;
        aOut->mName      = lData->mName  ;
    }

}
