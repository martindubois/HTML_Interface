
// Author    KMS - Martin Dubois, P.Eng.
// Copyright (C) 2020 KMS. All rights reserved.
// Product   HTML_Interface
// File      HILib/Link.cpp

// CODE REVIEW 2020-05-24 KMS - Martin Dubois, P.Eng.

// TEST COVERAGE 2020-05-24 KMS - Martin Dubois, P.Eng.

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

    double Link::GetLength() const
    {
        assert(NULL != mFrom);
        assert(NULL != mTo  );

        unsigned int lX0_pixel;
        unsigned int lX1_pixel;
        unsigned int lY0_pixel;
        unsigned int lY1_pixel;

        mFrom->GetCenter(&lX0_pixel, &lY0_pixel);
        mTo  ->GetCenter(&lX1_pixel, &lY1_pixel);

        double lDX_pixel = lX0_pixel;
        double lDY_pixel = lY0_pixel;

        lDX_pixel -= lX1_pixel;
        lDY_pixel -= lY1_pixel;

        return sqrt(lDX_pixel * lDX_pixel + lDY_pixel * lDY_pixel);
    }

    // aShape [---;---]
    bool Link::IsConnectedTo(const Shape * aShape)
    {
        assert(NULL != aShape);

        assert(NULL != mFrom);
        assert(NULL != mTo  );

        return (mFrom == aShape) || (mTo == aShape);
    }

    void Link::SetAutoDelete()
    {
        mFlags.mAutoDelete = true;
    }

    void Link::Generate_SVG(SVG_Document * aDoc) const
    {
        assert(NULL != aDoc);

        unsigned int lX_pixel;
        unsigned int lY_pixel;

        mFrom->GetCenter(&lX_pixel, &lY_pixel);

        aDoc->Attribute_Set(SVG_Document::ATTR_X1, lX_pixel);
        aDoc->Attribute_Set(SVG_Document::ATTR_Y1, lY_pixel);

        mTo->GetCenter(&lX_pixel, &lY_pixel);

        aDoc->Attribute_Set(SVG_Document::ATTR_X2, lX_pixel);
        aDoc->Attribute_Set(SVG_Document::ATTR_Y2, lY_pixel);

        aDoc->Attribute_Set(SVG_Document::ATTR_STYLE, "stroke:black;");

        aDoc->Tag(SVG_Document::TAG_LINE);
    }

    // Private
    /////////////////////////////////////////////////////////////////////////

    void Link::Init()
    {
        mFlags.mAutoDelete = false;
    }

}
