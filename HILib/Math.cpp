
// Author    KMS - Martin Dubois, P.Eng.
// Copyright (C) 2020 KMS. All rights reserved.
// Product   HTML_Interface
// File      HILib/Math.cpp

// CODE REVIEW 2020-06-09 KMS - Martin Dubois, P.Eng.

// TEST COVERAGE 2020-06-09 KMS - Martin Dubois, P.Eng.

// ===== C ==================================================================
#include <assert.h>

// ===== HILib ==============================================================
#include "Math.h"

// Function
/////////////////////////////////////////////////////////////////////////////

bool Math_Range_Include_Excl(unsigned int aFrom, unsigned int aTo, double aValue)
{
    assert(aFrom != aTo);

    if ((aFrom <= aValue) && (aTo <= aValue))
    {
        return false;
    };

    if ((aFrom >= aValue) && (aTo >= aValue))
    {
        return false;
    }

    return true;
}

bool Math_Range_Include_Incl(unsigned int aFrom, unsigned int aTo, double aValue)
{
    assert(aFrom != aTo);

    if ((aFrom < aValue) && (aTo < aValue))
    {
        return false;
    };

    if ((aFrom > aValue) && (aTo > aValue))
    {
        return false;
    }

    return true;
}

bool Math_Ranges_Overlap_Excl(unsigned int aAF, unsigned int aAT, unsigned int aBF, unsigned int aBT)
{
    assert(aAF != aAT);

    if ((aBF <= aAF) && (aBT <= aAF) && (aBF <= aAT) && (aBT <= aAT))
    {
        return false;
    }

    if ((aBF >= aAF) && (aBT >= aAF) && (aBF >= aAT) && (aBT >= aAT))
    {
        return false;
    }

    return true;
}
