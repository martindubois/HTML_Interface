
// Author    KMS - Martin Dubois, P.Eng.
// Copyright (C) 2020 KMS. All rights reserved.
// Product   HTML_Interface
// File      HILib/Grid.h

// CODE REVIEW 2020-06-22 KMS - Martin Dubois, P.Eng.

#pragma once

// ===== Includes ===========================================================
#include <HI/Point.h>

class Grid
{

public:

    enum
    {
        GROUP_ELEMENT_QTY = 5,
        GROUP_QTY         = 4,
    };

    Grid();

    void Compute(unsigned int aSizeMaxX_pixel, unsigned int aSizeMaxY_pixel, unsigned int aShapeCount);

    HI::Point    Iterator_GetGroupCenter  ();
    HI::Point    Iterator_GetGroupPosition(unsigned int aGroup);
    unsigned int Iterator_GetGroupCount   ();
    HI::Point    Iterator_GetPosition     ();
    bool         Iterator_IsGroupFull     (unsigned int aGroup);
    bool         Iterator_NextPosition    ();
    void         Iterator_Reset           ();

private:

    HI::Point PosToPixel(unsigned int aX, unsigned int aY) const;

    unsigned int mCountX;
    unsigned int mCountY;
    unsigned int mDelta_pixel;
    unsigned int mFirstX_pixel;
    unsigned int mFirstY_pixel;
    unsigned int mGroupCount;
    unsigned int mGroups[GROUP_QTY][2];
    unsigned int mIndexE[GROUP_QTY];
    unsigned int mIndexX;
    unsigned int mIndexY;

};
