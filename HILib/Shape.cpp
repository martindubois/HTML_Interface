
// Author    KMS - Martin Dubois, P.Eng.
// Copyright (C) 2020 KMS. All rights reserved.
// Product   HTML_Interface
// File      HILib/Shape.cpp

// CODE REVIEW 2020-05-25 KMS - Martin Dubois, P.Eng.

// TEST COVERAGE 2020-05-25 KMS - Martin Dubois, P.Eng.

// TODO Shape
//      Add a shape type (RECT or ELIPSE)
//      Add a line width
//      Add a line color
//      Add a fill color
//      Add a type text color
//      Add a name text color
//      Add a tooltip
//      Make type smaller than name
//      Add a font size for the name and type
//      Add GetRight and GetTop
//      Add a minimum and a maximum size
//      Add SetSize

// ===== C ==================================================================
#include <assert.h>

// ===== Includes ===========================================================
#include <HI/SVG_Document.h>

#include <HI/Shape.h>

// Constants
/////////////////////////////////////////////////////////////////////////////

#define CHAR_SIZE_X_pixel (8)

#define SIZE_X_DEFAULT_pixel (70)
#define SIZE_Y_DEFAULT_pixel (50)

namespace HI
{

    // Public
    /////////////////////////////////////////////////////////////////////////

    // NOT TESTED Shape
    //            Default contructor

    Shape::Shape()
    {
        Init();
    }

    Shape::Shape(const char * aType, const char * aName) : mType(aType)
    {
        assert(NULL != aType);
        assert(NULL != aName);

        Init();

        SetName(aName);
    }

    Shape::~Shape()
    {
    }

    bool Shape::CanMove() const
    {
        return !mFlags.mDoNotMove;
    }

    bool Shape::GetAutoDelete() const
    {
        return mFlags.mAutoDelete;
    }

    unsigned int Shape::GetBottom() const
    {
        assert(0 < mSizeY_pixel);

        return mCenterY_pixel + mSizeY_pixel / 2;
    }

    // aX_pixel [---;-W-]
    // aY_pixel [---;-W-]
    void Shape::GetCenter(unsigned int * aX_pixel, unsigned int * aY_pixel) const
    {
        assert(NULL != aX_pixel);
        assert(NULL != aY_pixel);

        *aX_pixel = mCenterX_pixel;
        *aY_pixel = mCenterY_pixel;
    }

    const char * Shape::GetName() const
    {
        return mName.c_str();
    }

    unsigned int Shape::GetRight() const
    {
        assert(0 < mSizeX_pixel);

        return mCenterX_pixel + mSizeX_pixel / 2;
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

    bool Shape::IsCenterAt(unsigned int aX_pixel, unsigned int aY_pixel) const
    {
        return (mCenterX_pixel == aX_pixel) && (mCenterY_pixel == aY_pixel);
    }

    void Shape::SetAutoDelete()
    {
        mFlags.mAutoDelete = true;
    }

    void Shape::SetCenter(unsigned int aX_pixel, unsigned int aY_pixel)
    {
        mCenterX_pixel = aX_pixel;
        mCenterY_pixel = aY_pixel;
    }

    // REQUIREMENT Shape.SetName
    //             If needed, SetName increase the shape width to fit the name length.

    void Shape::SetName(const char * aName)
    {
        assert(NULL != aName);

        mName = aName;

        unsigned int lSizeX_pixel = mName.size() * CHAR_SIZE_X_pixel;

        if (mSizeX_pixel < lSizeX_pixel)
        {
            mSizeX_pixel = lSizeX_pixel;
        }
    }

    void Shape::Generate_SVG(SVG_Document * aDoc) const
    {
        assert(NULL != aDoc);
        
        assert(0 < mSizeX_pixel);
        assert(0 < mSizeY_pixel);

        unsigned int lX_pixel = mCenterX_pixel - mSizeX_pixel / 2;
        unsigned int lY_pixel = mCenterY_pixel - mSizeY_pixel / 2;

        aDoc->Attribute_Set(SVG_Document::ATTR_HEIGHT, mSizeY_pixel);
        aDoc->Attribute_Set(SVG_Document::ATTR_WIDTH , mSizeX_pixel);
        aDoc->Attribute_Set(SVG_Document::ATTR_X     , lX_pixel);
        aDoc->Attribute_Set(SVG_Document::ATTR_Y     , lY_pixel);
        aDoc->Attribute_Set(SVG_Document::ATTR_STYLE , "fill:white; stroke:black;");

        aDoc->Tag(SVG_Document::TAG_RECT);

        lX_pixel +=  5;
        lY_pixel += 20;

        aDoc->Attribute_Set(SVG_Document::ATTR_X    , lX_pixel);
        aDoc->Attribute_Set(SVG_Document::ATTR_Y    , lY_pixel);
        aDoc->Attribute_Set(SVG_Document::ATTR_STYLE, "fill:grey;");

        aDoc->Tag(SVG_Document::TAG_TEXT, mType.c_str());

        lY_pixel += 20;

        aDoc->Attribute_Set(SVG_Document::ATTR_X, lX_pixel);
        aDoc->Attribute_Set(SVG_Document::ATTR_Y, lY_pixel);

        aDoc->Tag(SVG_Document::TAG_TEXT, mName.c_str());
    }

    // Private
    /////////////////////////////////////////////////////////////////////////

    void Shape::Init()
    {
        mCenterX_pixel = 0;
        mCenterY_pixel = 0;

        mFlags.mAutoDelete = false;

        mSizeX_pixel = SIZE_X_DEFAULT_pixel;
        mSizeY_pixel = SIZE_Y_DEFAULT_pixel;
    }

}
