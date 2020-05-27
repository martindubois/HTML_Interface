
// Author    KMS - Martin Dubois, P.Eng.
// Copyright (C) 2020 KMS. All rights reserved.
// Product   HTML_Interface
// File      HILib/Link.cpp

// CODE REVIEW 2020-05-27 KMS - Martin Dubois, P.Eng.

// TEST COVERAGE 2020-05-27 KMS - Martin Dubois, P.Eng.

// TODO Link
//      Add way to change color and width
//      Add arrow
//      Add a minimal length
//      Add a tooltip

// ===== C ==================================================================
#include <assert.h>
#include <math.h>

// ===== Includes ===========================================================
#include <HI/SVG_Document.h>
#include <HI/Shape.h>

#include <HI/Link.h>

// Macros
/////////////////////////////////////////////////////////////////////////////

#define INSIDE_X(x) ((lFX_pixel >= (x)) || (lTX_pixel >= (x))) && ((lFX_pixel <= (x)) || (lTX_pixel <= (x)))
#define INSIDE_Y(y) ((lFY_pixel >= (y)) || (lTY_pixel >= (y))) && ((lFY_pixel <= (y)) || (lTY_pixel <= (y)))

#define OUTSIDE_X(x) ((lFX_pixel < (x)) && (lTX_pixel < (x))) || ((lFX_pixel > (x)) && (lTX_pixel > (x)))
#define OUTSIDE_Y(y) ((lFY_pixel < (y)) && (lTY_pixel < (y))) || ((lFY_pixel > (y)) && (lTY_pixel > (y)))

#define RETRIEVE_DELTA                \
    double lDX_pixel;                 \
    double lDY_pixel;                 \
    GetDelta(&lDX_pixel, &lDY_pixel);


#define RETRIEVE_XY                           \
    assert(NULL != mFrom);                    \
    assert(NULL != mTo  );                    \
    unsigned int lFX_pixel;                   \
    unsigned int lFY_pixel;                   \
    unsigned int lTX_pixel;                   \
    unsigned int lTY_pixel;                   \
    mFrom->GetCenter(&lFX_pixel, &lFY_pixel); \
    mTo  ->GetCenter(&lTX_pixel, &lTY_pixel);

namespace HI
{

    // Public
    /////////////////////////////////////////////////////////////////////////

    // NOT TESTED Link
    //            Default contructor

    Link::Link()
    {
        Init();
    }

    // aFrom [-K-;R--]
    // aTo   [-K-;R--]
    Link::Link(const Shape * aFrom, const Shape * aTo) : mFrom(aFrom), mTo(aTo)
    {
        assert(NULL != aFrom);
        assert(NULL != aTo  );

        Init();
    }

    Link::~Link()
    {
    }

    bool Link::GetAutoDelete() const
    {
        return mFlags.mAutoDelete;
    }

    const Shape * Link::GetFrom() const
    {
        assert(NULL != mFrom);

        return mFrom;
    }

    double Link::GetLength() const
    {
        RETRIEVE_DELTA

        assert((0 != lDX_pixel) || (0 != lDY_pixel));

        return sqrt(lDX_pixel * lDX_pixel + lDY_pixel * lDY_pixel);
    }

    // aShape [---;---]
    bool Link::IsConnectedTo(const Shape * aShape) const
    {
        assert(NULL != aShape);

        assert(NULL != mFrom);
        assert(NULL != mTo  );

        return (mFrom == aShape) || (mTo == aShape);
    }

    bool Link::IsCrossing(const Link * aLink) const
    {
        assert(NULL != aLink);

        RETRIEVE_XY

        unsigned int lBFX_pixel;
        unsigned int lBFY_pixel;

        aLink->GetFrom()->GetCenter(&lBFX_pixel, &lBFY_pixel);

        if (IsVertical  ()) { return (!aLink->IsVertical  ()) && aLink->GetY(lFX_pixel); }
        if (IsHorizontal()) { return (!aLink->IsHorizontal()) && aLink->GetX(lFY_pixel); }

        if (aLink->IsVertical  ()) { return INSIDE_X(lBFX_pixel); }
        if (aLink->IsHorizontal()) { return INSIDE_Y(lBFY_pixel); }

        double lAS =        GetSlope();
        double lBS = aLink->GetSlope();

        assert(0 != lAS);
        assert(0 != lBS);

        if (lAS == lBS)
        {
            return false;
        }

        double lAY0_pixel = lFY_pixel ;
        double lBY0_pixel = lBFY_pixel;

        lAY0_pixel -= lAS * lFX_pixel ;
        lBY0_pixel -= lBS * lBFX_pixel;

        double lX_pixel = (lBY0_pixel - lAY0_pixel) / (lAS - lBS);

        return INSIDE_X(lX_pixel);
    }

    bool Link::IsHorizontal() const
    {
        RETRIEVE_XY

        return (lFY_pixel == lTY_pixel);
    }

    bool Link::IsOverlapping(const Link * aLink) const
    {
        assert(NULL != aLink);

        RETRIEVE_XY

        unsigned int lBFX_pixel;
        unsigned int lBFY_pixel;

        aLink->GetFrom()->GetCenter(&lBFX_pixel, &lBFY_pixel);

        if (IsHorizontal()) { return aLink->IsHorizontal() && (lFY_pixel == lBFY_pixel) && (aLink->GetY(lFX_pixel) || aLink->GetY(lTX_pixel)); }
        if (IsVertical  ()) { return aLink->IsVertical  () && (lFX_pixel == lBFX_pixel) && (aLink->GetX(lFY_pixel) || aLink->GetX(lTY_pixel)); }

        if (aLink->IsHorizontal() || aLink->IsVertical())
        {
            return false;
        }

        double lAS =        GetSlope();
        double lBS = aLink->GetSlope();

        if (lAS != lBS)
        {
            return false;
        }

        double lAY0_pixel = lFY_pixel ;
        double lBY0_pixel = lBFY_pixel;

        lAY0_pixel -= lAS * lFX_pixel ;
        lBY0_pixel -= lBS * lBFX_pixel;

        return lAY0_pixel == lBY0_pixel;
    }

    bool Link::IsVertical() const
    {
        RETRIEVE_XY

        return (lFX_pixel == lTX_pixel);
    }

    void Link::SetAutoDelete()
    {
        mFlags.mAutoDelete = true;
    }

    void Link::Generate_SVG(SVG_Document * aDoc) const
    {
        assert(NULL != aDoc);

        RETRIEVE_XY

        aDoc->Attribute_Set(SVG_Document::ATTR_X1, lFX_pixel);
        aDoc->Attribute_Set(SVG_Document::ATTR_Y1, lFY_pixel);
        aDoc->Attribute_Set(SVG_Document::ATTR_X2, lTX_pixel);
        aDoc->Attribute_Set(SVG_Document::ATTR_Y2, lTY_pixel);

        aDoc->Attribute_Set(SVG_Document::ATTR_STYLE, "stroke:black;");

        aDoc->Tag(SVG_Document::TAG_LINE);
    }

    // Private
    /////////////////////////////////////////////////////////////////////////

    void Link::Init()
    {
        mFlags.mAutoDelete = false;
    }

    void Link::GetDelta(double * aDX_pixel, double * aDY_pixel) const
    {
        assert(NULL != aDX_pixel);
        assert(NULL != aDY_pixel);

        RETRIEVE_XY

        *aDX_pixel = lTX_pixel;
        *aDY_pixel = lTY_pixel;

        *aDX_pixel -= lFX_pixel;
        *aDY_pixel -= lFY_pixel;
    }

    double Link::GetSlope() const
    {
        RETRIEVE_DELTA

        assert(0 != lDX_pixel);

        return lDY_pixel / lDX_pixel;
    }

    bool Link::GetX(unsigned int aY_pixel) const
    {
        RETRIEVE_XY

        return INSIDE_Y(aY_pixel);
    }

    bool Link::GetY(unsigned int aX_pixel) const
    {
        RETRIEVE_XY

        return INSIDE_X(aX_pixel);
    }

}
