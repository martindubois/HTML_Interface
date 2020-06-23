
// Author    KMS - Martin Dubois, P.Eng.
// Copyright (C) 2020 KMS. All rights reserved.
// Product   HTML_Interface
// File      HILib/Link.cpp

// CODE REVIEW 2020-06-22 KMS - Martin Dubois, P.Eng.

// TEST COVERAGE 2020-06-22 KMS - Martin Dubois, P.Eng.

// TODO Link
//      Add arrow
//      Add a minimal length
//      Add a tooltip

// ===== C ==================================================================
#include <assert.h>
#include <math.h>

// ===== Includes ===========================================================
#include <HI/CPP_Document.h>
#include <HI/CSS_Colors.h>
#include <HI/Line.h>
#include <HI/SVG_Document.h>
#include <HI/Shape.h>
#include <HI/ShapeList.h>

#include <HI/Link.h>

// ===== HILib ==============================================================
#include "Math.h"
#include "Utils.h"

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
    Link::Link(const Shape * aFrom, const Shape * aTo)
    {
        assert(NULL  != aFrom);
        assert(NULL  != aTo  );
        assert(aFrom != aTo  );

        Init();

        mFrom = aFrom;
        mTo   = aTo  ;
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

    double Link::GetWeight() const
    {
        assert(0 < mWeightFactor);

        return mWeightFactor * GetLength();
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

    void Link::SetColor(CSS_Color aColor)
    {
        assert(COLOR_INVALID != aColor);

        char lColor[64];;

        CSS_Colors::RetrieveName(lColor, sizeof(lColor), aColor);

        mColor = lColor;
    }

    void Link::SetColor(const char * aColor)
    {
        assert(NULL != aColor);

        mColor = aColor;
    }

    void Link::SetDashArray(const char * aDashArray)
    {
        assert(NULL != aDashArray);

        mDashArray = aDashArray;
    }

    void Link::SetWeightFactor(double aWeightFactor)
    {
        assert(0 < aWeightFactor);

        mWeightFactor = aWeightFactor;
    }

    void Link::SetWidth(unsigned int aWidth_pixel)
    {
        assert(0 < aWidth_pixel);

        mWidth_pixel = aWidth_pixel;
    }

    void Link::Generate_CPP(CPP_Document * aDoc, unsigned int aIndex, const ShapeList & aShapes) const
    {
        assert(NULL !=  aDoc   );
        assert(NULL != &aShapes);

        unsigned int lFrom = aShapes.GetIndex(mFrom);
        unsigned int lTo   = aShapes.GetIndex(mTo  );

        FILE * lFile = aDoc->GetFile();
        assert(NULL != lFile);

        fprintf(lFile, EOL);
        fprintf(lFile, "    HI::Link * lLink%02u = lResult->mLinks.AddLink(lShape%02u, lShape%02u);" EOL, aIndex, lFrom, lTo);
        fprintf(lFile, "    assert(NULL != lLink%02u);" EOL, aIndex);
        fprintf(lFile, EOL);
        fprintf(lFile, "    lLink%02u->SetColor       (\"%s\");" EOL, aIndex, mColor    .c_str());

        if (!mDashArray.empty() ) { fprintf(lFile, "    lLink%02u->SetDashArray   (\"%s\");" EOL, aIndex, mDashArray.c_str()); }
        if (1.0 != mWeightFactor) { fprintf(lFile, "    lLink%02u->SetWeightFactor(%f);"     EOL, aIndex, mWeightFactor     ); }
        if (1   != mWidth_pixel ) { fprintf(lFile, "    lLink%02u->SetWidth       (%u);"     EOL, aIndex, mWidth_pixel      ); }
    }

    void Link::Generate_SVG(SVG_Document * aDoc) const
    {
        assert(NULL != aDoc);

        assert(!mColor.empty());
        assert(0 < mWidth_pixel);

        aDoc->Attribute_Set(SVG_Document::ATTR_X1, mFrom->mCenter.GetX());
        aDoc->Attribute_Set(SVG_Document::ATTR_Y1, mFrom->mCenter.GetY());
        aDoc->Attribute_Set(SVG_Document::ATTR_X2, mTo  ->mCenter.GetX());
        aDoc->Attribute_Set(SVG_Document::ATTR_Y2, mTo  ->mCenter.GetY());

        aDoc->Attribute_Set(SVG_Document::ATTR_STROKE      , mColor.c_str());
        aDoc->Attribute_Set(SVG_Document::ATTR_STROKE_WIDTH, mWidth_pixel);

        if (!mDashArray.empty())
        {
            aDoc->Attribute_Set(SVG_Document::ATTR_STROKE_DASHARRAY, mDashArray.c_str());
        }

        aDoc->Tag(SVG_Document::TAG_LINE);
    }

    // Private
    /////////////////////////////////////////////////////////////////////////

    void Link::Init()
    {
        mColor = "black";

        mFlags.mAutoDelete = false;

        mFrom = NULL;
        mTo   = NULL;

        mWeightFactor = 1.0;
        mWidth_pixel  = 1  ;
    }

}
