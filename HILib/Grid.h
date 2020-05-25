
// Author    KMS - Martin Dubois, P.Eng.
// Copyright (C) 2020 KMS. All rights reserved.
// Product   HTML_Interface
// File      HILib/Grid.h

#pragma once

class Grid
{

public:

    Grid();

    unsigned int Iterator_GetX ();
    unsigned int Iterator_GetY ();
    bool         Iterator_Next (unsigned int aInc = 1);
    void         Iterator_Reset();

    unsigned int mCountX;
    unsigned int mCountY;

    unsigned int mDelta_pixel;

private:

    unsigned int mIndexX;
    unsigned int mIndexY;

};

// Public
/////////////////////////////////////////////////////////////////////////////

inline unsigned int Grid::Iterator_GetX()
{
    return mIndexX * mDelta_pixel;
}

inline unsigned int Grid::Iterator_GetY()
{
    return mIndexY * mDelta_pixel;
}
