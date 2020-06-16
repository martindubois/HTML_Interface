
// Author    KMS - Martin Dubois, P.Eng.
// Copyright (C) 2020 KMS. All rights reserved.
// Product   HTML_Interface
// File      HILib/Grid.cpp

// CODE REVIEW 2020-06-15 KMS - Martin Dubois, P.Eng.

// TEST COVERAGE 2020-06-15 KMS - Martin Dubois, P.Eng.

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
