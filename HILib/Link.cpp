
// Author    KMS - Martin Dubois, P.Eng.
// Copyright (C) 2020 KMS. All rights reserved.
// Product   HTML_Interface
// File      HILib/Link.cpp

// CODE REVIEW 2020-06-09 KMS - Martin Dubois, P.Eng.

// TEST COVERAGE 2020-06-09 KMS - Martin Dubois, P.Eng.

// TODO Link
//      Add way to change color and width
//      Add arrow
//      Add a minimal length
//      Add a tooltip

// ===== C ==================================================================
#include <assert.h>
#include <math.h>

// ===== Includes ===========================================================
#include <HI/Line.h>
#include <HI/SVG_Document.h>
#include <HI/Shape.h>

#include <HI/Link.h>

// ===== HILib ==============================================================
#include "Math.h"

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
        assert(NULL  != aFrom);
        assert(NULL  != aTo  );
        assert(aFrom != aTo  );

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
        return GetLine().GetLength();
    }

    Line Link::GetLine() const
    {
        assert(NULL != mFrom);
        assert(NULL != mTo  );

        return Line(mFrom->mCenter, mTo->mCenter);
    }

    // aShape [---;---]
    const Shape * Link::GetOtherShape(const Shape * aShape) const
    {
        assert(NULL != aShape);

        assert(NULL  != mFrom);
        assert(NULL  != mTo  );
        assert(mFrom != mTo  );

        if (mFrom == aShape)
        {
            return mTo;
        }

        assert(mTo == aShape);

        return mFrom;
    }

    const Shape * Link::GetTo() const
    {
        assert(NULL != mTo);

        return mTo;
    }

    // aShape [---;---]
    bool Link::IsConnectedTo(const Shape * aShape) const
    {
        assert(NULL != aShape);

        assert(NULL  != mFrom);
        assert(NULL  != mTo  );
        assert(mFrom != mTo  );

        return (mFrom == aShape) || (mTo == aShape);
    }

    void Link::SetAutoDelete()
    {
        mFlags.mAutoDelete = true;
    }

    void Link::Generate_SVG(SVG_Document * aDoc) const
    {
        assert(NULL != aDoc);

        aDoc->Attribute_Set(SVG_Document::ATTR_X1, mFrom->mCenter.GetX());
        aDoc->Attribute_Set(SVG_Document::ATTR_Y1, mFrom->mCenter.GetY());
        aDoc->Attribute_Set(SVG_Document::ATTR_X2, mTo  ->mCenter.GetX());
        aDoc->Attribute_Set(SVG_Document::ATTR_Y2, mTo  ->mCenter.GetY());

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
