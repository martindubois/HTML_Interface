
// Author    KMS - Martin Dubois, P.Eng.
// Copyright (C) 2020 KMS. All rights reserved.
// Product   HTML_Interface
// File      HILib/Shape.cpp

// CODE REVIEW 2020-07-11 KMS - Martin Dubois, P.Eng.

// TEST COVERAGE 2020-07-11 KMS - Martin Dubois, P.Eng.

// TODO Shape
//      Add a line color
//      Add a type text color
//      Add a name text color
//      Make type smaller than name
//      Add a font size for the name and type
//      Add a minimum and a maximum size

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

#define FILL_COLOR_DEFAULT "white"

#define SIZE_X_DEFAULT_pixel (70)
#define SIZE_Y_DEFAULT_pixel (50)

#define STROKE_WIDTH_DEFAULT_pixel (1)

static const char * TYPE_NAMES[HI::Shape::TYPE_QTY] =
{
    "TYPE_ELLIPSE",
    "TYPE_IMAGE"  ,
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
        assert(NULL != aTypeName);

        Init(aType);

        SetName(aName);
    }

    Shape::~Shape()
    {
    }

    void Shape::AppendToTitle(const char * aText)
    {
        assert(NULL != aText);

        mTitle += aText;
    }

    bool Shape::GetAutoDelete() const
    {
        return mFlags.mAutoDelete;
    }

    unsigned int Shape::GetBottom() const
    {
        return mCenter.GetY() + mSizeY_pixel / 2;
    }

    unsigned int Shape::GetLeft() const
    {
        return mCenter.GetX() - mSizeX_pixel / 2;
    }

    const char * Shape::GetName() const
    {
        return mName.c_str();
    }

    unsigned int Shape::GetRight() const
    {
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

    unsigned int Shape::GetTop() const
    {
        return mCenter.GetY() - mSizeY_pixel / 2;
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
        char lColor[64];;

        CSS_Colors::RetrieveName(lColor, sizeof(lColor), aColor);

        mFillColor = lColor;
    }

    void Shape::SetFillColor(const char * aColor)
    {
        assert(NULL != aColor);

        mFillColor = aColor;
    }

    void Shape::SetImage(FolderId aFolder, const char * aName)
    {
        assert(NULL != aName);

        char lFileName[1024];

        Utl_MakeFileName(lFileName, sizeof(lFileName), aFolder, aName, NULL);

        char lURL[1024];

        int lRet = sprintf_s(lURL, "file://%s", lFileName);
        assert(           0 < lRet);
        assert(sizeof(lURL) > lRet);

        SetImageURL(lURL);
    }

    // NOT TESTED HI.Shape.SetImage
    //            User defined folder

    void Shape::SetImage(const char * aFolder, const char * aName)
    {
        assert(NULL != aName);

        char lURL[1024];

        int lRet;

        if (NULL == aFolder)
        {
            lRet = sprintf_s(lURL, "file:://%s", aName);
        }
        else
        {
            lRet = sprintf_s(lURL, "file:://%s/%s", aFolder, aName);
        }
        assert(           0 < lRet);
        assert(sizeof(lURL) > lRet);

        SetImageURL(lURL);
    }

    void Shape::SetImageURL(const char * aURL)
    {
        assert(NULL != aURL);

        mImageURL = aURL      ;
        mType     = TYPE_IMAGE;
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

    void Shape::SetSize(unsigned int aSizeX_pixel, unsigned int aSizeY_pixel)
    {
        assert(0 < aSizeX_pixel);
        assert(0 < aSizeY_pixel);

        assert(0 < mSizeX_pixel);
        assert(0 < mSizeY_pixel);

        mSizeX_pixel = aSizeX_pixel;
        mSizeY_pixel = aSizeY_pixel;
    }

    void Shape::SetStrokeWidth(unsigned int aStrokeWidth_pixel)
    {
        assert(0 < aStrokeWidth_pixel);

        assert(0 < mStrokeWidth_pixel);

        mStrokeWidth_pixel = aStrokeWidth_pixel;
    }

    void Shape::SetTextOnImage()
    {
        mFlags.mTextOnImage = true;
    }

    void Shape::SetTitle(const char * aTitle)
    {
        assert(NULL != aTitle);

        mTitle = aTitle;
    }

    void Shape::Generate_CPP(CPP_Document * aDoc, unsigned int aIndex) const
    {
        assert(NULL != aDoc);

        FILE * lFile = aDoc->GetFile();
        assert(NULL != lFile);

        fprintf(lFile, EOL);
        fprintf(lFile, "    HI::Shape * lShape%02u = lResult->mShapes.AddShape(\"%s\", \"%s\", HI::Shape::%s);" EOL, aIndex, mTypeName.c_str(), mName.c_str(), TYPE_NAMES[mType]);
        fprintf(lFile, "    assert(NULL != lShape%02u);" EOL, aIndex);
        fprintf(lFile, EOL);

        if (FILL_COLOR_DEFAULT != mFillColor)
        {   fprintf(lFile, "    lShape%02u->SetFillColor  (\"%s\");" EOL, aIndex, mFillColor.c_str()); }
        if (!mImageURL.empty())
        {
            fprintf(lFile, "    lShape%02u->SetImageURL   (\""          , aIndex);
            Utl_WriteCString(lFile, mImageURL.c_str());
            fprintf(lFile, "\");" EOL);
        }
        if ((SIZE_X_DEFAULT_pixel != mSizeX_pixel) || (SIZE_Y_DEFAULT_pixel != mSizeY_pixel))
        {   fprintf(lFile, "    lShape%02u->SetSize       (%u, %u);" EOL, aIndex, mSizeX_pixel, mSizeY_pixel); }
        if (STROKE_WIDTH_DEFAULT_pixel != mStrokeWidth_pixel)
        {   fprintf(lFile, "    lShape%02u->SetStrokeWidth(%u);"     EOL, aIndex, mStrokeWidth_pixel); }
        if (mFlags.mTextOnImage)
        {   fprintf(lFile, "    lShape%02u->SetTextOnImage();"       EOL, aIndex); }
        if (!mTitle.empty())
        {
            fprintf(lFile, "    lShape%02u->SetTitle      (\""          , aIndex);
            Utl_WriteCString(lFile, mTitle.c_str());
            fprintf(lFile, "\");" EOL);
        }
    }

    void Shape::Generate_SVG(SVG_Document * aDoc) const
    {
        assert(NULL != aDoc);
        
        aDoc->Tag_Begin(SVG_Document::TAG_G);
        {
            switch (mType)
            {
            case TYPE_ELLIPSE:
            case TYPE_RECT   :
                Generate_SVG_Shape(aDoc);
                break;

            case TYPE_IMAGE:
                Generate_SVG_Image(aDoc);
                break;

            default: assert(false);
            }

            if (!mTitle.empty())
            {
                aDoc->Tag(SVG_Document::TAG_TITLE, mTitle.c_str());
            }
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

        mFillColor = FILL_COLOR_DEFAULT;

        mFlags.mAutoDelete = false;

        mSizeX_pixel = SIZE_X_DEFAULT_pixel;
        mSizeY_pixel = SIZE_Y_DEFAULT_pixel;

        mStrokeWidth_pixel = STROKE_WIDTH_DEFAULT_pixel;

        mType = aType;
    }

    void Shape::Generate_SVG_Ellipse(SVG_Document * aDoc) const
    {
        assert(NULL != aDoc);

        assert(0 < mSizeX_pixel);
        assert(0 < mSizeY_pixel);

        aDoc->Attribute_Set(SVG_Document::ATTR_CX, mCenter.GetX());
        aDoc->Attribute_Set(SVG_Document::ATTR_CY, mCenter.GetY());
        aDoc->Attribute_Set(SVG_Document::ATTR_RX, mSizeX_pixel / 2);
        aDoc->Attribute_Set(SVG_Document::ATTR_RY, mSizeY_pixel / 2);

        aDoc->Tag(SVG_Document::TAG_ELLIPSE);
    }

    void Shape::Generate_SVG_HWXY(SVG_Document * aDoc) const
    {
        assert(NULL != aDoc);

        assert(0 < mSizeX_pixel);
        assert(0 < mSizeY_pixel);

        aDoc->Attribute_Set(SVG_Document::ATTR_HEIGHT, mSizeY_pixel);
        aDoc->Attribute_Set(SVG_Document::ATTR_WIDTH , mSizeX_pixel);

        aDoc->Attribute_Set(SVG_Document::ATTR_X, mCenter.GetX() - mSizeX_pixel / 2);
        aDoc->Attribute_Set(SVG_Document::ATTR_Y, mCenter.GetY() - mSizeY_pixel / 2);
    }

    void Shape::Generate_SVG_Image(SVG_Document * aDoc) const
    {
        assert(NULL != aDoc);

        Generate_SVG_HWXY(aDoc);

        aDoc->Attribute_Set(SVG_Document::ATTR_HREF, mImageURL.c_str());

        aDoc->Tag(SVG_Document::TAG_IMAGE);

        if (mFlags.mTextOnImage)
        {
            Generate_SVG_Texts(aDoc);
        }
    }

    void Shape::Generate_SVG_Rect(SVG_Document * aDoc) const
    {
        assert(NULL != aDoc);

        Generate_SVG_HWXY(aDoc);

        aDoc->Tag(SVG_Document::TAG_RECT);
    }

    void Shape::Generate_SVG_Shape(SVG_Document * aDoc) const
    {
        assert(NULL != aDoc);

        assert(0 < mStrokeWidth_pixel);

        aDoc->Attribute_Set(SVG_Document::ATTR_FILL  , mFillColor.c_str());
        aDoc->Attribute_Set(SVG_Document::ATTR_STROKE, "black");

        if (STROKE_WIDTH_DEFAULT_pixel != mStrokeWidth_pixel)
        {
            aDoc->Attribute_Set(SVG_Document::ATTR_STROKE_WIDTH, mStrokeWidth_pixel);
        }

        switch (mType)
        {
        case TYPE_ELLIPSE: Generate_SVG_Ellipse(aDoc); break;
        case TYPE_RECT   : Generate_SVG_Rect   (aDoc); break;

        default: assert(false);
        }

        Generate_SVG_Texts(aDoc);
    }

    void Shape::Generate_SVG_Texts(SVG_Document * aDoc) const
    {
        assert(NULL != aDoc);

        unsigned int lX_pixel = mCenter.GetX() - mSizeX_pixel / 2 + 5;
        unsigned int lY_pixel = mCenter.GetY() - mSizeY_pixel / 2 + 20;

        Generate_Text(aDoc, lX_pixel, lY_pixel, "fill:grey;", mTypeName.c_str());

        lY_pixel += 20;

        Generate_Text(aDoc, lX_pixel, lY_pixel, NULL, mName.c_str());
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
