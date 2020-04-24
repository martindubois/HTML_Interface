
// Author     KMS - Martin Dubois, P.Eng.
// Copyright  (C) 2020 KMS. All rights reserved.
// Product    HTML_Interface
// File       HILib/CSS_Properties.cpp

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

// Constants
/////////////////////////////////////////////////////////////////////////////

static const Data PROPERTIES[HI::PROP_QTY]
{
    { "PROP_BORDER_STYLE", "border-style" },
};

namespace HI
{

    // Public
    /////////////////////////////////////////////////////////////////////////

    void CSS_Properties::FindByIndex(CSS_PropertyInfo * aOut, CSS_Property aIndex)
    {
        assert(NULL     != aOut  );
        assert(PROP_QTY >  aIndex);

        memset(aOut, 0, sizeof(*aOut));

        const Data * lData = PROPERTIES + aIndex;

        aOut->mIdName   = lData->mIdName;
        aOut->mName     = lData->mName  ;
        aOut->mProperty = aIndex        ;
    }

}
