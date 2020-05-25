
// Author    KMS - Martin Dubois, P.Eng.
// Copyright (C) 2020 KMS. All rights reserved.
// Product   HTML_Interface
// File      HILib/ShapeList.cpp

// CODE REVIEW 2020-05-24 KMS - Martin Dubois, P.Eng.

// TEST COVERAGE 2020-05-24 KMS - Martin Dubois, P.Eng.

// TODO ShapeList
//      Add the Trim method to remove empty space on top and on left

// ===== C ==================================================================
#include <assert.h>

// ===== Includes ===========================================================
#include <HI/Shape.h>

#include <HI/ShapeList.h>

// ===== HILib ==============================================================
#include "Grid.h"

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

    void ShapeList::AddShape(const char * aType, const char * aName)
    {
        assert(NULL != aType);
        assert(NULL != aName);

        Shape * lShape = new Shape(aType, aName);
        assert(NULL != lShape);

        lShape->SetAutoDelete();

        mShapes.push_back(lShape);
    }

    const Shape * ShapeList::FindByCenter(unsigned int aX_pixel, unsigned int aY_pixel) const
    {
        for (InternalList::const_iterator lIt = mShapes.begin(); lIt != mShapes.end(); lIt++)
        {
            const Shape * lShape = *lIt;
            assert(NULL != lShape);

            if (lShape->IsCenterAt(aX_pixel, aY_pixel))
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
        ComputeGrid(aGrid);

        aGrid->Iterator_Reset();

        for (InternalList::iterator lIt = mShapes.begin(); lIt != mShapes.end(); lIt++)
        {
            Shape * lShape = *lIt;
            assert(NULL != lShape);

            if (lShape->CanMove())
            {
                lShape->SetCenter(aGrid->Iterator_GetX(), aGrid->Iterator_GetY());
                aGrid->Iterator_Next();
            }
        }
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
            aGrid->mDelta_pixel = lSizeY_pixel / 2 * 3;
        }
        else
        {
            aGrid->mDelta_pixel = lSizeX_pixel / 2 * 3;
        }

        aGrid->mCountX = 1280 / aGrid->mDelta_pixel;
        aGrid->mCountY = static_cast<unsigned int>(mShapes.size() * 2 / aGrid->mCountX);

        if (aGrid->mCountX > aGrid->mCountY)
        {
            aGrid->mCountY = aGrid->mCountX;
        };
    }

}
