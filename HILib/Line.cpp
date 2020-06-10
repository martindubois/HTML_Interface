
// Author    KMS - Martin Dubois, P.Eng.
// Copyright (C) 2020 KMS. All rights reserved.
// Product   HTML_Interface
// File      HILib/Line.cpp

// CODE REVIEW 2020-06-09 KMS - Martin Dubois, P.Eng.

// TEST COVERAGE 2020-06-09 KMS - Martin Dubois, P.Eng.

// ===== C ==================================================================
#include <assert.h>
#include <math.h>

// ===== Includes ===========================================================
#include <HI/Line.h>

// ===== HILib ==============================================================
#include "Math.h"
#include "Straight.h"

namespace HI
{

    // Public
    /////////////////////////////////////////////////////////////////////////////

    Line::Line(const Point & aFrom, const Point & aTo) : mFrom(aFrom), mTo(aTo)
    {
        assert((aFrom.GetX() != aTo.GetX()) || (aFrom.GetY() != aTo.GetY()));
    }

    Line::Line(unsigned int aFX_pixel, unsigned int aFY_pixel, unsigned int aTX_pixel, unsigned int aTY_pixel) : mFrom(aFX_pixel, aFY_pixel), mTo(aTX_pixel, aTY_pixel)
    {
        assert((aFX_pixel != aTX_pixel) || (aFY_pixel != aTY_pixel));
    }

    double Line::GetLength() const
    {
        double lDX_pixel;
        double lDY_pixel;

        GetDelta(&lDX_pixel, &lDY_pixel);

        assert((0 != lDX_pixel) || (0 != lDY_pixel));

        return sqrt(lDX_pixel * lDX_pixel + lDY_pixel * lDY_pixel);
    }

    bool Line::IsCrossing(const Line & aLine) const
    {
        assert(NULL != &aLine);

        if (IsVertical())
        {
            return IsCrossing_Vertical(aLine);
        }

        Straight lA;

        GetStraight(&lA);

        double lX_pixel;

        if (aLine.IsVertical())
        {
            lX_pixel = aLine.mFrom.GetX();

            if (!Math_Range_Include_Incl(mFrom.GetX(), mTo.GetX(), lX_pixel))
            {
                return false;
            }

            double lY_pixel = lA.Evaluate(lX_pixel);

            if (!Math_Range_Include_Incl(aLine.mFrom.GetY(), aLine.mTo.GetY(), lY_pixel))
            {
                return false;
            }
        }
        else
        {
            Straight lB;

            aLine.GetStraight(&lB);

            if (lA.GetM() == lB.GetM())
            {
                return false;
            }

            lX_pixel = (lB.GetB() - lA.GetB()) / (lA.GetM() - lB.GetM());

            if (!Math_Range_Include_Incl(mFrom.GetX(), mTo.GetX(), lX_pixel))
            {
                return false;
            }

            if (!Math_Range_Include_Incl(aLine.mFrom.GetX(), aLine.mTo.GetX(), lX_pixel))
            {
                return false;
            }
        }

        return true;
    }

    bool Line::IsHorizontal() const
    {
        return mFrom.GetY() == mTo.GetY();
    }

    bool Line::IsOverlapping(const Line & aLine) const
    {
        assert(NULL != &aLine);

        if (IsVertical())
        {
            return IsOverlapping_Vertical(aLine);
        }

        if (aLine.IsVertical())
        {
            return false;
        }

        if (!Math_Ranges_Overlap_Excl(mFrom.GetX(), mTo.GetX(), aLine.mFrom.GetX(), aLine.mTo.GetX()))
        {
            return false;
        }

        if (IsHorizontal())
        {
            return IsOverlapping_Horizontal(aLine);
        }

        if (!Math_Ranges_Overlap_Excl(mFrom.GetY(), mTo.GetY(), aLine.mFrom.GetY(), aLine.mTo.GetY()))
        {
            return false;
        }

        Straight lA;
        Straight lB;

        GetStraight(&lA);
        aLine.GetStraight(&lB);

        if (lA.GetM() != lB.GetM())
        {
            return false;
        }

        return lA.GetB() == lB.GetB();
    }

    bool Line::IsVertical() const
    {
        return mFrom.GetX() == mTo.GetX();
    }

    // Private
    /////////////////////////////////////////////////////////////////////////

    void Line::GetStraight(Straight * aOut) const
    {
        assert(NULL != aOut);

        double lDX_pixel;
        double lDY_pixel;

        GetDelta(&lDX_pixel, &lDY_pixel);

        assert(0 != lDX_pixel);

        double lM = lDY_pixel / lDX_pixel;

        double lB = mFrom.GetY();

        lB -= lM * mFrom.GetX();

        aOut->Set(lB, lM);
    }

    void Line::GetDelta(double * aDX_pixel, double * aDY_pixel) const
    {
        assert(NULL != aDX_pixel);
        assert(NULL != aDY_pixel);

        *aDX_pixel = mTo.GetX();
        *aDY_pixel = mTo.GetY();

        *aDX_pixel -= mFrom.GetX();
        *aDY_pixel -= mFrom.GetY();
    }

    bool Line::IsCrossing_Vertical(const Line & aLine) const
    {
        assert(NULL != &aLine);

        if (aLine.IsVertical())
        {
            return false;
        }

        if (!Math_Range_Include_Incl(aLine.mFrom.GetX(), aLine.mTo.GetX(), mFrom.GetX()))
        {
            return false;
        }

        Straight lB;

        aLine.GetStraight(&lB);

        double lY_pixel = lB.Evaluate(mFrom.GetX());;

        return Math_Range_Include_Incl(mFrom.GetY(), mTo.GetY(), lY_pixel);
    }

    bool Line::IsOverlapping_Horizontal(const Line & aLine) const
    {
        assert(NULL != &aLine);

        if (!aLine.IsHorizontal())
        {
            return false;
        }

        return mFrom.GetY() == aLine.mFrom.GetY();
    }

    bool Line::IsOverlapping_Vertical(const Line & aLine) const
    {
        assert(NULL != &aLine);

        if (!aLine.IsVertical())
        {
            return false;
        }

        if (!Math_Ranges_Overlap_Excl(mFrom.GetY(), mTo.GetY(), aLine.mFrom.GetY(), aLine.mTo.GetY()))
        {
            return false;
        }

        return mFrom.GetX() == aLine.mFrom.GetX();
    }
}
