
// Author    KMS - Martin Dubois, P.Eng.
// Copyright (C) 2020 KMS. All rights reserved.
// Product   HTML_Interface
// File      HILib/ShapeList.cpp

// CODE REVIEW 2020-06-21 KMS - Martin Dubois, P.Eng.

// TEST COVERAGE 2020-06-21 KMS - Martin Dubois, P.Eng.

// TODO ShapeList
//      Add the Trim method to remove empty space on top and on left

// ===== C ==================================================================
#include <assert.h>

// ===== Includes ===========================================================
#include <HI/Shape.h>

#include <HI/ShapeList.h>

// ===== HILib ==============================================================
#include "Grid.h"
#include "Utils.h"

// Static function declarations
/////////////////////////////////////////////////////////////////////////////

static bool CompareShape(const HI::Shape * aA, const HI::Shape * aB);

namespace HI
{

    // Public
    /////////////////////////////////////////////////////////////////////////

    ShapeList::ShapeList() : mIterator(mShapes.end())
    {
    }

    ShapeList::~ShapeList()
    {
        for (InternalList::iterator lIt = mShapes.begin(); lIt != mShapes.end(); lIt++)
        {
            Shape * lShape = (*lIt);
            assert(NULL != lShape);

            if (lShape->GetAutoDelete())
            {
                delete lShape;
            }
        }
    }

    void ShapeList::AddShape(HI::Shape * aShape)
    {
        assert(NULL != aShape);

        mShapes.push_back(aShape);
    }

    Shape * ShapeList::AddShape(const char * aTypeName, const char * aName, Shape::Type aType)
    {
        assert(NULL            != aTypeName);
        assert(NULL            != aName    );
        assert(Shape::TYPE_QTY >  aType    );

        Shape * lResult = new Shape(aTypeName, aName, aType);
        assert(NULL != lResult);

        lResult->SetAutoDelete();

        AddShape(lResult);

        return lResult;
    }

    const Shape * ShapeList::FindByCenter(const Point & aCenter) const
    {
        assert(NULL != &aCenter);

        for (InternalList::const_iterator lIt = mShapes.begin(); lIt != mShapes.end(); lIt++)
        {
            const Shape * lShape = *lIt;
            assert(NULL != lShape);

            if (lShape->mCenter == aCenter)
            {
                return lShape;
            }
        }

        return NULL;
    }

    void ShapeList::GetDiagramSize(unsigned int * aSizeX_pixel, unsigned int * aSizeY_pixel) const
    {
        assert(NULL != aSizeX_pixel);
        assert(NULL != aSizeY_pixel);

        *aSizeX_pixel = 0;
        *aSizeY_pixel = 0;

        for (InternalList::const_iterator lIt = mShapes.begin(); lIt != mShapes.end(); lIt++)
        {
            Shape * lShape = (*lIt);
            assert(NULL != lShape);

            unsigned int lX_pixel = lShape->GetRight ();
            unsigned int lY_pixel = lShape->GetBottom();

            assert(0 < lX_pixel);
            assert(0 < lY_pixel);

            if (*aSizeX_pixel < lX_pixel) { *aSizeX_pixel = lX_pixel; }
            if (*aSizeY_pixel < lY_pixel) { *aSizeY_pixel = lY_pixel; }
        }
    }

    // NOT TESTED HI.ShapeList.GetIndex.Error
    //            The shape is not in the list.

    // aShape [---;---]
    unsigned int ShapeList::GetIndex(const Shape * aShape) const
    {
        assert(NULL != aShape);

        unsigned int lIndex = 0;

        for (InternalList::const_iterator lShape = mShapes.begin(); lShape != mShapes.end(); lShape++)
        {
            assert(NULL != *lShape);

            if (*lShape == aShape)
            {
                return lIndex;
            }

            lIndex++;
        }

        Utl_ThrowError("ERROR", __LINE__, "Shape is not in the ShapeList");

        return 0xffffffff;
    }

    void ShapeList::GetMaximumSize(unsigned int * aSizeX_pixel, unsigned int * aSizeY_pixel) const
    {
        assert(NULL != aSizeX_pixel);
        assert(NULL != aSizeY_pixel);

        *aSizeX_pixel = 0;
        *aSizeY_pixel = 0;

        for (InternalList::const_iterator lIt = mShapes.begin(); lIt != mShapes.end(); lIt++)
        {
            unsigned int lSizeX_pixel;
            unsigned int lSizeY_pixel;

            (*lIt)->GetSize(&lSizeX_pixel, &lSizeY_pixel);

            assert(0 < lSizeX_pixel);
            assert(0 < lSizeY_pixel);

            if (*aSizeX_pixel < lSizeX_pixel) { *aSizeX_pixel = lSizeX_pixel; }
            if (*aSizeY_pixel < lSizeY_pixel) { *aSizeY_pixel = lSizeY_pixel; }
        }
    }

    Shape * ShapeList::GetShape(unsigned int aIndex)
    {
        InternalList::iterator lIt = mShapes.begin();

        for (unsigned int i = 0; i < aIndex; i++)
        {
            lIt++;
        }

        if (mShapes.end() == lIt)
        {
            return NULL;
        }

        assert(NULL != *lIt);

        return *lIt;
    }

    void ShapeList::Generate_CPP(CPP_Document * aDoc) const
    {
        assert(NULL != aDoc);

        unsigned int lIndex = 0;

        for (InternalList::const_iterator lShape = mShapes.begin(); lShape != mShapes.end(); lShape++)
        {
            assert(NULL != (*lShape));

            (*lShape)->Generate_CPP(aDoc, lIndex);

            lIndex++;
        }
    }

    void ShapeList::Generate_SVG(SVG_Document * aDoc) const
    {
        assert(NULL != aDoc);

        for (InternalList::const_iterator lIt = mShapes.begin(); lIt != mShapes.end(); lIt++)
        {
            assert(NULL != (*lIt));

            (*lIt)->Generate_SVG(aDoc);
        }
    }

    // Internal
    /////////////////////////////////////////////////////////////////////////

    Shape * ShapeList::Iterator_Get()
    {
        if (mShapes.end() == mIterator)
        {
            return NULL;
        }

        assert(NULL != *mIterator);

        return *mIterator;
    }

    void ShapeList::Iterator_Next()
    {
        mIterator++;
    }

    void ShapeList::Iterator_Reset()
    {
        mIterator = mShapes.begin();
    }

    void ShapeList::PositionShapes(Grid * aGrid)
    {
        assert(NULL != aGrid);

        ComputeGrid(aGrid);

        aGrid->Iterator_Reset();

        InternalList::iterator lF;
        Shape                * lShape;

        for (lF = mShapes.begin(); lF != mShapes.end(); lF++)
        {
            lShape = *lF;
            assert(NULL != lShape);

            if (0 < lShape->LinkCount_Get()) { break; }

            lShape->mCenter = aGrid->Iterator_GetPosition();
            aGrid->Iterator_Next();
        }

        if (mShapes.end() != lF)
        {
            unsigned int                   lIndex = 0;
            InternalList::reverse_iterator lR;

            for (lR = mShapes.rbegin(); lR != mShapes.rend(); lR++)
            {
                lShape = *lR;

                lShape->mCenter = aGrid->Iterator_GetCorner(lIndex);

                lIndex++;

                if (*lF == lShape) { return; }

                if (4 == lIndex) { break; }
            }

            for (; *lF != *lR; lF++)
            {
                lShape = *lF;
                assert(NULL != lShape);

                lShape->mCenter = aGrid->Iterator_GetPosition();
                aGrid->Iterator_Next();
            }
        }
    }

    void ShapeList::LinkCounts_Reset()
    {
        for (InternalList::iterator lIt = mShapes.begin(); lIt != mShapes.end(); lIt++)
        {
            assert(NULL != (*lIt));

            (*lIt)->LinkCount_Reset();
        }
    }

    void ShapeList::LinkCounts_Sort()
    {
        mShapes.sort(CompareShape);
    }

    // Private
    /////////////////////////////////////////////////////////////////////////

    // NOT TESTED ShapeList
    //            Maximum shape is larger on Y than on X

    void ShapeList::ComputeGrid(Grid * aGrid) const
    {
        assert(NULL != aGrid);

        unsigned int lSizeX_pixel;
        unsigned int lSizeY_pixel;

        GetMaximumSize(&lSizeX_pixel, &lSizeY_pixel);

        assert(0 < lSizeX_pixel);
        assert(0 < lSizeY_pixel);

        if (lSizeX_pixel < lSizeY_pixel)
        {
            aGrid->mDelta_pixel = lSizeY_pixel / 3 * 4;
        }
        else
        {
            aGrid->mDelta_pixel = lSizeX_pixel / 3 * 4;
        }

        aGrid->mCountX = 1280 / aGrid->mDelta_pixel;
        aGrid->mCountY = static_cast<unsigned int>(mShapes.size() / aGrid->mCountX + 5);

        if (aGrid->mCountX > aGrid->mCountY)
        {
            aGrid->mCountY = aGrid->mCountX;
        };
    }

}

// Static functions
/////////////////////////////////////////////////////////////////////////////

bool CompareShape(const HI::Shape * aA, const HI::Shape * aB)
{
    assert(NULL != aA);
    assert(NULL != aB);

    return aA->LinkCount_Get() < aB->LinkCount_Get();
}
