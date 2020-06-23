
// Author    KMS - Martin Dubois, P.Eng.
// Copyright (C) 2020 KMS. All rights reserved.
// Product   HTML_Interface
// File      HILib/Grid.cpp

// CODE REVIEW 2020-06-22 KMS - Martin Dubois, P.Eng.

// TEST COVERAGE 2020-06-22 KMS - Martin Dubois, P.Eng.

// ===== C ==================================================================
#include <assert.h>

// ===== HILib ==============================================================
#include "Grid.h"

// Public
/////////////////////////////////////////////////////////////////////////////

Grid::Grid() : mCountX(0), mCountY(0), mDelta_pixel(0)
{
    Iterator_Reset();
}

HI::Point Grid::Iterator_GetCorner(unsigned int aIndex)
{
    unsigned int lFirst_pixel = mDelta_pixel / 2;
    HI::Point    lResult;

    if (0 == aIndex)
    {
        mIndexY += (0 == mIndexX) ? 1 : 2;
        mIndexX = mCountX - 1;
    }

    unsigned int lBottom_pixel = lFirst_pixel + (mCountY - 2) * mDelta_pixel;
    unsigned int lLeft_pixel   = lFirst_pixel +                 mDelta_pixel;
    unsigned int lRight_pixel  = lFirst_pixel + (mCountX - 2) * mDelta_pixel;
    unsigned int lTop_pixel    = lFirst_pixel +  mIndexY      * mDelta_pixel;

    switch (aIndex)
    {
    case 0: lResult.Set(lLeft_pixel , lTop_pixel   ); break;
    case 1: lResult.Set(lRight_pixel, lTop_pixel   ); break;
    case 2: lResult.Set(lLeft_pixel , lBottom_pixel); break;
    case 3: lResult.Set(lRight_pixel, lBottom_pixel); break;

    default: assert(false);
    }

    return lResult;
}

HI::Point Grid::Iterator_GetPosition()
{
    assert(2 < mDelta_pixel);

    unsigned int lFirst_pixel = mDelta_pixel / 2;

    return HI::Point(lFirst_pixel + mIndexX * mDelta_pixel, lFirst_pixel + mIndexY * mDelta_pixel);
}

bool Grid::Iterator_Next(unsigned int aInc)
{
    assert(      0 <  mCountX);
    assert(      0 <  mCountY);
    assert(mCountX >  mIndexX);
    assert(mCountY >= mIndexY);

    mIndexX += aInc;
    if (mCountX <= mIndexX)
    {
        mIndexX = 0;
        mIndexY++;

        if (mCountY <= mIndexY)
        {
            return false;
        }
    }

    return true;
}

void Grid::Iterator_Reset()
{
    mIndexX = 0;
    mIndexY = 0;
}
