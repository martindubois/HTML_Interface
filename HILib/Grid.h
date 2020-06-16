
// Author    KMS - Martin Dubois, P.Eng.
// Copyright (C) 2020 KMS. All rights reserved.
// Product   HTML_Interface
// File      HILib/Grid.h

// CODE REVIEW 2020-06-15 KMS - Martin Dubois, P.Eng.

#pragma once

// ===== Includes ===========================================================
#include <HI/Point.h>

class Grid
{

public:

    Grid();

    HI::Point    Iterator_GetPosition();
    bool         Iterator_Next (unsigned int aInc = 1);
    void         Iterator_Reset();

    unsigned int mCountX;
    unsigned int mCountY;

    unsigned int mDelta_pixel;

private:

    unsigned int mIndexX;
    unsigned int mIndexY;

};
