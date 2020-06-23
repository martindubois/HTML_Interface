
// Author    KMS - Martin Dubois, P.Eng.
// Copyright (C) 2020 KMS. All rights reserved.
// Product   HTML_Interface
// File      HILib/Shape.cpp

// CODE REVIEW 2020-06-22 KMS - Martin Dubois, P.Eng.

// TEST COVERAGE 2020-06-22 KMS - Martin Dubois, P.Eng.

// TODO Shape
//      Add a line width
//      Add a line color
//      Add a type text color
//      Add a name text color
//      Make type smaller than name
//      Add a font size for the name and type
//      Add GetRight and GetTop
//      Add a minimum and a maximum size
//      Add SetSize

// ===== C ==================================================================
#include <assert.h>

// ===== Includes ===========================================================
#include <HI/CPP_Document.h>
#include <HI/Line.h>
#include <HI/SVG_Document.h>

#include <HI/Shape.h>

// ===== HILib ==============================================================
#include "Utils.h"

// Constants
/////////////////////////////////////////////////////////////////////////////

#define CHAR_SIZE_X_pixel (8)

#define SIZE_X_DEFAULT_pixel (70)
#define SIZE_Y_DEFAULT_pixel (50)

static const char * TYPE_NAMES[HI::Shape::TYPE_QTY] =
{
    "TYPE_ELLIPSE",
    "TYPE_RECT"   ,
};

// Static function declaration
/////////////////////////////////////////////////////////////////////////////

static void Generate_Text(HI::SVG_Document * aDoc, unsigned int aX_pixel, unsigned int aY_pixel, const char * aStyle, const char * aText);

namespace HI
{

    // Public
    /////////////////////////////////////////////////////////////////////////

    // NOT TESTED Shape
    //            Default contructor

    Shape::Shape()
    {
        Init(TYPE_RECT);
    }

    Shape::Shape(const char * aTypeName, const char * aName, Type aType) : mTypeName(aTypeName)
    {
        assert(NULL            != aTypeName);
        assert(NULL            != aName    );
        assert(Shape::TYPE_QTY >  aType    );

        Init(aType);

        SetName(aName);
    }

    Shape::~Shape()
    {
    }

    bool Shape::GetAutoDelete() const
    {
        return mFlags.mAutoDelete;
    }

    unsigned int Shape::GetBottom() const
    {
        assert(0 < mSizeY_pixel);

        return mCenter.GetY() + mSizeY_pixel / 2;
    }

    const char * Shape::GetName() const
    {
        return mName.c_str();
    }

    unsigned int Shape::GetRight() const
    {
        assert(0 < mSizeX_pixel);

        return mCenter.GetX() + mSizeX_pixel / 2;
    }

    // aSizeX_pixel [---;-W-]
    // aSizeY_pixel [---;-W-]
    void Shape::GetSize(unsigned int * aSizeX_pixel, unsigned int * aSizeY_pixel) const
    {
        assert(NULL != aSizeX_pixel);
        assert(NULL != aSizeY_pixel);

        *aSizeX_pixel = mSizeX_pixel;
        *aSizeY_pixel = mSizeY_pixel;
    }

    bool Shape::IsCrossing(const Line & aLine) const
    {
        assert(NULL != &aLine);

        unsigned int lRX_pixel = mSizeX_pixel / 2;
        unsigned int lRY_pixel = mSizeY_pixel / 2;

        Line lH(mCenter.GetX() - lRX_pixel, mCenter.GetY(), mCenter.GetX() + lRX_pixel, mCenter.GetY());
        Line lV(mCenter.GetX(), mCenter.GetY() - lRY_pixel, mCenter.GetX(), mCenter.GetY() + lRY_pixel);

        return lH.IsCrossing(aLine) || lV.IsCrossing(aLine);
    }

    void Shape::SetAutoDelete()
    {
        mFlags.mAutoDelete = true;
    }

    void Shape::SetFillColor(CSS_Color aColor)
    {
        assert(COLOR_INVALID != aColor);

        char lColor[64];;

        CSS_Colors::RetrieveName(lColor, sizeof(lColor), aColor);

        mFillColor = lColor;
    }

    void Shape::SetFillColor(const char * aColor)
    {
        assert(NULL != aColor);

        mFillColor = aColor;
    }

    void Shape::SetName(const char * aName)
    {
        assert(NULL != aName);

        mName = aName;

        unsigned int lSizeX_pixel = static_cast<unsigned int>(mName.size() * CHAR_SIZE_X_pixel);
        if (mSizeX_pixel < lSizeX_pixel)
        {
            mSizeX_pixel = lSizeX_pixel;
        }
    }

    void Shape::SetTitle(const char * aTitle)
    {
        assert(NULL != aTitle);

        mTitle = aTitle;
    }

    // TODO HI.Shape.Generate_CPP
    //      Replace new line with "\n" whant setting the title.

    void Shape::Generate_CPP(CPP_Document * aDoc, unsigned int aIndex) const
    {
        assert(NULL != aDoc);

        FILE * lFile = aDoc->GetFile();
        assert(NULL != lFile);

        fprintf(lFile, EOL);
        fprintf(lFile, "    HI::Shape * lShape%02u = lResult->mShapes.AddShape(\"%s\", \"%s\", HI::Shape::%s);" EOL, aIndex, mTypeName.c_str(), mName.c_str(), TYPE_NAMES[mType]);
        fprintf(lFile, "    assert(NULL != lShape%02u);" EOL, aIndex);
        fprintf(lFile, EOL);
        fprintf(lFile, "    lShape%02u->SetFillColor (\"%s\");" EOL, aIndex, mFillColor.c_str());

        if (!mTitle.empty()) { fprintf(lFile, "    lShape%02u->SetTitle     (\"%s\");" EOL, aIndex, mTitle.c_str()); }
    }

    void Shape::Generate_SVG(SVG_Document * aDoc) const
    {
        assert(NULL != aDoc);
        
        assert(0 < mSizeX_pixel);
        assert(0 < mSizeY_pixel);

        aDoc->Tag_Begin(SVG_Document::TAG_G);

            char lStyle[64];

            sprintf_s(lStyle, "fill:%s; stroke:black;", mFillColor.c_str());

            aDoc->Attribute_Set(SVG_Document::ATTR_STYLE, lStyle);

            switch (mType)
            {
            case TYPE_ELLIPSE: Generate_SVG_Ellipse(aDoc); break;
            case TYPE_RECT   : Generate_SVG_Rect   (aDoc); break;

            default: assert(false);
            }

            unsigned int lX_pixel = mCenter.GetX() - mSizeX_pixel / 2 +  5;
            unsigned int lY_pixel = mCenter.GetY() - mSizeY_pixel / 2 + 20;

            Generate_Text(aDoc, lX_pixel, lY_pixel, "fill:grey;", mTypeName.c_str());

            lY_pixel += 20;

            Generate_Text(aDoc, lX_pixel, lY_pixel, NULL, mName.c_str());

            if (!mTitle.empty())
            {
                aDoc->Tag(SVG_Document::TAG_TITLE, mTitle.c_str());
            }

        aDoc->Tag_End();
    }

    // Internal
    /////////////////////////////////////////////////////////////////////////

    unsigned int Shape::LinkCount_Get  () const { return mLinkCount; }
    void         Shape::LinkCount_Inc  () const { mLinkCount++; }
    void         Shape::LinkCount_Reset()       { mLinkCount = 0; }

    // Private
    /////////////////////////////////////////////////////////////////////////

    void Shape::Init(Type aType)
    {
        assert(TYPE_QTY > aType);

        mFillColor = "white";

        mFlags.mAutoDelete = false;

        mSizeX_pixel = SIZE_X_DEFAULT_pixel;
        mSizeY_pixel = SIZE_Y_DEFAULT_pixel;

        mType = aType;
    }

    void Shape::Generate_SVG_Ellipse(SVG_Document * aDoc) const
    {
        assert(NULL != aDoc);

        aDoc->Attribute_Set(SVG_Document::ATTR_CX, mCenter.GetX());
        aDoc->Attribute_Set(SVG_Document::ATTR_CY, mCenter.GetY());
        aDoc->Attribute_Set(SVG_Document::ATTR_RX, mSizeX_pixel / 2);
        aDoc->Attribute_Set(SVG_Document::ATTR_RY, mSizeY_pixel / 2);

        aDoc->Tag(SVG_Document::TAG_ELLIPSE);
    }

    void Shape::Generate_SVG_Rect(SVG_Document * aDoc) const
    {
        assert(NULL != aDoc);

        aDoc->Attribute_Set(SVG_Document::ATTR_HEIGHT, mSizeY_pixel);
        aDoc->Attribute_Set(SVG_Document::ATTR_WIDTH , mSizeX_pixel);
        aDoc->Attribute_Set(SVG_Document::ATTR_X     , mCenter.GetX() - mSizeX_pixel / 2);
        aDoc->Attribute_Set(SVG_Document::ATTR_Y     , mCenter.GetY() - mSizeY_pixel / 2);

        aDoc->Tag(SVG_Document::TAG_RECT);
    }

}

// Static function declaration
/////////////////////////////////////////////////////////////////////////////

void Generate_Text(HI::SVG_Document * aDoc, unsigned int aX_pixel, unsigned int aY_pixel, const char * aStyle, const char * aText)
{
    assert(NULL != aDoc );
    assert(NULL != aText);

    aDoc->Attribute_Set(HI::SVG_Document::ATTR_X, aX_pixel);
    aDoc->Attribute_Set(HI::SVG_Document::ATTR_Y, aY_pixel);

    if (NULL != aStyle)
    {
        aDoc->Attribute_Set(HI::SVG_Document::ATTR_STYLE, aStyle);
    }

    aDoc->Tag(HI::SVG_Document::TAG_TEXT, aText);
}
