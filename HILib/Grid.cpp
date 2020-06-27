
// Author    KMS - Martin Dubois, P.Eng.
// Copyright (C) 2020 KMS. All rights reserved.
// Product   HTML_Interface
// File      HILib/Grid.cpp

// CODE REVIEW 2020-06-27 KMS - Martin Dubois, P.Eng.

// TEST COVERAGE 2020-06-27 KMS - Martin Dubois, P.Eng.

// ===== C ==================================================================
#include <assert.h>
#include <memory.h>

// ===== HILib ==============================================================
#include "Grid.h"

// Constants
/////////////////////////////////////////////////////////////////////////////

static int GROUP_OFFSETS[Grid::GROUP_QTY][Grid::GROUP_ELEMENT_QTY][2] =
{
    { {  1, 0 }, {  1, -1 }, { 0, -1 }, { -1, -1 }, { -1, 0 } },
    { { -1, 0 }, { -1, -1 }, { 0, -1 }, {  1, -1 }, {  1, 0 } },
    { { -1, 0 }, { -1,  1 }, { 0,  1 }, {  1,  1 }, {  1, 0 } },
    { {  1, 0 }, {  1,  1 }, { 0,  1 }, { -1,  1 }, { -1, 1 } },
};

#define X 0
#define Y 1

// Public
/////////////////////////////////////////////////////////////////////////////

Grid::Grid() : mCountX(0), mCountY(0), mDelta_pixel(0), mGroupCount(0)
{
    memset(&mIndexE, 0, sizeof(mIndexE));

    mGroups[0][X] = 1;
    mGroups[3][X] = 1;

    Iterator_Reset();
}

// NOT TESTED Grid.Compute
//            aSizeMaxX_pixel < aSizeMaxT_pixel

void Grid::Compute(unsigned int aSizeMaxX_pixel, unsigned int aSizeMaxY_pixel, unsigned int aShapeCount)
{
    assert(2 <= aSizeMaxX_pixel);
    assert(2 <= aSizeMaxY_pixel);
    assert(0 <  aShapeCount    );

    mFirstX_pixel = aSizeMaxX_pixel / 2 + 1;
    mFirstY_pixel = aSizeMaxY_pixel / 2 + 1;

    assert(2 <= mFirstX_pixel);
    assert(2 <= mFirstY_pixel);

    if (aSizeMaxX_pixel < aSizeMaxY_pixel)
    {
        mDelta_pixel = aSizeMaxY_pixel / 3 * 4;
    }
    else
    {
        mDelta_pixel = aSizeMaxX_pixel / 3 * 4;
    }

    assert(2 <= mDelta_pixel);

    mCountX = ((1280 - 2 * mFirstX_pixel) / mDelta_pixel) + 1;
    mCountY = static_cast<unsigned int>(aShapeCount / mCountX + 5);

    assert(2 < mCountX);
    assert(2 < mCountY);

    if (mCountX > mCountY)
    {
        mCountY = mCountX;
    };

    mGroups[1][X] = mCountX - 2;
    mGroups[2][X] = mCountX - 2;
    mGroups[2][Y] = mCountY - 2;
    mGroups[3][Y] = mCountY - 2;
}

HI::Point Grid::Iterator_GetGroupCenter()
{
    assert(GROUP_QTY > mGroupCount);

    if (0 == mGroupCount)
    {
        mIndexY += (0 == mIndexX) ? 1 : 2;

        mGroups[0][Y] = mIndexY;
        mGroups[1][Y] = mIndexY;

        mIndexX = 0;
        mIndexY++;
    }

    unsigned int lX = mGroups[mGroupCount][X];
    unsigned int lY = mGroups[mGroupCount][Y];

    mGroupCount++;

    return PosToPixel(lX, lY);
}

HI::Point Grid::Iterator_GetGroupPosition(unsigned int aGroup)
{
    assert(GROUP_QTY > aGroup);

    unsigned int lIndexE = mIndexE[aGroup];
    assert(GROUP_ELEMENT_QTY > lIndexE);

    unsigned int lX = mGroups[aGroup][X] + GROUP_OFFSETS[aGroup][lIndexE][X];
    unsigned int lY = mGroups[aGroup][Y] + GROUP_OFFSETS[aGroup][lIndexE][Y];

    mIndexE[aGroup]++;

    return PosToPixel(lX, lY);
}

unsigned int Grid::Iterator_GetGroupCount()
{
    assert(GROUP_QTY >= mGroupCount);

    return mGroupCount;
}

HI::Point Grid::Iterator_GetPosition()
{
    return PosToPixel(mIndexX, mIndexY);
}

bool Grid::Iterator_IsGroupFull(unsigned int aGroup)
{
    assert(GROUP_QTY > aGroup);

    assert(GROUP_ELEMENT_QTY >= mIndexE[aGroup]);

    return (GROUP_ELEMENT_QTY <= mIndexE[aGroup]);
}

bool Grid::Iterator_NextPosition()
{
    assert(      0 <  mCountX);
    assert(      0 <  mCountY);
    assert(mCountX >  mIndexX);
    assert(mCountY >= mIndexY);

    mIndexX += 1;
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

// Private
/////////////////////////////////////////////////////////////////////////////

HI::Point Grid::PosToPixel(unsigned int aX, unsigned int aY) const
{
    assert(2 <= mDelta_pixel );
    assert(2 <= mFirstX_pixel);
    assert(2 <= mFirstY_pixel);

    return HI::Point(mFirstX_pixel + aX * mDelta_pixel, mFirstY_pixel + aY * mDelta_pixel);
}
