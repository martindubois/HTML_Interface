
// Author    KMS - Martin Dubois, P.Eng.
// Copyright (C) 2020 KMS. All rights reserved.
// Product   HTML_Interface
// File      HILib/Point.cpp

// CODE REVIEW 2020-06-22 KMS - Martin Dubois, P.Eng.

// TEST COVERAGE 2020-06-22 KMS - Martin Dubois, P.Eng.

// ===== C ==================================================================
#include <assert.h>

// ===== Includes ===========================================================
#include <HI/Point.h>

namespace HI
{

    // Public
    /////////////////////////////////////////////////////////////////////////////

    Point::Point(const Point & aIn) : mX_pixel(aIn.GetX()), mY_pixel(aIn.GetY())
    {
        assert(NULL != &aIn);
    }

    const Point & Point::operator = (const Point & aValue)
    {
        assert(NULL != &aValue);

        mX_pixel = aValue.GetX();
        mY_pixel = aValue.GetY();

        return (*this);
    }

    bool Point::operator == (const Point & aB) const
    {
        assert(NULL != &aB);

        return (mX_pixel == aB.GetX()) && (mY_pixel == aB.GetY());
    }

    void Point::Set(unsigned int aX_pixel, unsigned int aY_pixel)
    {
        mX_pixel = aX_pixel;
        mY_pixel = aY_pixel;
    }

}
