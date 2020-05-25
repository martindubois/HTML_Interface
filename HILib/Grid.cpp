
// Author    KMS - Martin Dubois, P.Eng.
// Copyright (C) 2020 KMS. All rights reserved.
// Product   HTML_Interface
// File      HILib/Grid.cpp

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

bool Grid::Iterator_Next(unsigned int aInc)
{
    assert(      0 <  mCountX);
    assert(mCountX >= mIndexX);

    mIndexX += aInc;
    if (mCountX < mIndexX)
    {
        mIndexX = 1;
        mIndexY++;

        if (mCountY < mIndexY)
        {
            return false;
        }
    }

    return true;
}

void Grid::Iterator_Reset()
{
    mIndexX = 1;
    mIndexY = 1;
}
