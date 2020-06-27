
// Author    KMS - Martin Dubois, P.Eng.
// Copyright (C) 2020 KMS. All rights reserved.
// Product   HTML_Interface
// File      HILib/Diagram.cpp

// CODE REVIEW 2020-06-27 KMS - Martin Dubois, P.Eng.

// TEST COVERAGE 2020-06-27 KMS - Martin Dubois, P.Eng.

// ===== C ==================================================================
#include <assert.h>

// ===== Includes ===========================================================
#include <HI/CPP_Document.h>
#include <HI/HTML_Document.h>
#include <HI/SVG_Document.h>
#include <HI/Shape.h>

#include <HI/Diagram.h>

// ===== HILib ==============================================================
#include "Grid.h"

namespace HI
{

    // Public
    /////////////////////////////////////////////////////////////////////////

    Diagram::Diagram()
    {
        mFlags.mDebug = false;
    }

    Diagram::~Diagram()
    {
    }

    void Diagram::SetDebug()
    {
        mFlags.mDebug = true;
    }

    void Diagram::Generate_CPP(FolderId aFolder, const char * aName)
    {
        assert(FOLDER_QTY >  aFolder);
        assert(NULL       != aName  );

        CPP_Document lDoc;

        lDoc.Create(aFolder, aName);

            mShapes.Generate_CPP(&lDoc);
            mLinks .Generate_CPP(&lDoc, mShapes);

        lDoc.Close();
    }

    void Diagram::Generate_CPP(const char * aFolder, const char * aName)
    {
        assert(NULL != aFolder);
        assert(NULL != aName  );

        CPP_Document lDoc;

        lDoc.Create(aFolder, aName);

            mShapes.Generate_CPP(&lDoc);
            mLinks .Generate_CPP(&lDoc, mShapes);

        lDoc.Close();
    }

    void Diagram::Generate_HTML(FolderId aFolder, const char * aName, const char * aTitle)
    {
        assert(FOLDER_QTY >  aFolder);
        assert(NULL       != aName  );
        assert(NULL       != aTitle );

        HTML_Document lDoc;

        lDoc.Create(aFolder, aName, aTitle);

            lDoc.Tag(HI::HTML_Document::TAG_H1, aTitle);

            Generate_SVG(&lDoc);

        lDoc.Close();
    }

    void Diagram::Generate_SVG(HTML_Document * aDoc)
    {
        assert(NULL != aDoc);

        SVG_Document lDoc;

        RetrieveDiagramSize(&lDoc);

        lDoc.Create(aDoc);

            Generate_SVG(&lDoc);

        lDoc.Close();
    }

    void Diagram::Generate_SVG(SVG_Document * aDoc)
    {
        assert(NULL != aDoc);

        mLinks .Generate_SVG(aDoc);
        mShapes.Generate_SVG(aDoc);
    }

    void Diagram::Generate_SVG(HI::FolderId aFolder, const char * aName)
    {
        assert(FOLDER_QTY >  aFolder);
        assert(NULL       != aName  );

        SVG_Document lDoc;

        RetrieveDiagramSize(&lDoc);

        lDoc.Create(aFolder, aName);

            Generate_SVG(&lDoc);

        lDoc.Close();
    }

    // TODO Diagram.Generate
    //      Add a phase 3 to remove empty space on top and on left

    void Diagram::PositionShapes()
    {
        Grid lGrid;

        mShapes.LinkCounts_Reset();

        mLinks.LinkCounts_Update();

        mShapes.LinkCounts_Sort();

        mShapes.PositionShapes(&lGrid, mLinks);

        PositionShapes(&lGrid);
    }

    // Private
    /////////////////////////////////////////////////////////////////////////

    void Diagram::DebugIteration(unsigned int aIteration)
    {
        char lName[64];

        sprintf_s(lName, "Diagram_Debug_Iteration_%03u", aIteration);

        Generate_SVG(FOLDER_TEMP, lName);
    }

    void Diagram::PositionShapes(Grid * aGrid)
    {
        assert(NULL != aGrid);

        unsigned int lIteration = 100;

        do
        {
            mShapes.Iterator_Reset();

            unsigned int lMoveCount = 0;
            Shape      * lShape;

            while (NULL != (lShape = mShapes.Iterator_Get()))
            {
                lMoveCount += PositionShape(aGrid, lShape);

                mShapes.Iterator_Next();
            }

            lIteration--;

            if ((0 >= lMoveCount) && (1 < lIteration))
            {
                // Nothing moved but shape at the begining of the list could find better place now that the one at the end of the liste
                // moved. This is why we do one more iteration.
                lIteration = 1;
            }

            if (mFlags.mDebug)
            {
                char lName[64];

                sprintf_s(lName, "Diagram_Debug_Iteration_%03u", lIteration);

                Generate_SVG(FOLDER_TEMP, lName);
            }
        }
        while (0 < lIteration);
    }

    unsigned int Diagram::PositionShape(Grid * aGrid, Shape * aShape)
    {
        assert(NULL != aGrid );
        assert(NULL != aShape);

        Point lCenter = aShape->mCenter;

        double lWeight = mLinks.GetWeight(aShape);

        aGrid->Iterator_Reset();

        unsigned int lResult = 0;

        do
        {
            HI::Point lPosition = aGrid->Iterator_GetPosition();

            if (NULL == mShapes.FindByCenter(lPosition))
            {
                aShape->mCenter = lPosition;

                double lNewWeight = mLinks.GetWeight(aShape);
                if (lWeight > lNewWeight)
                {
                    lResult++;
                    lWeight  = lNewWeight;
                    lCenter  = lPosition;
                }
            }
        }
        while (aGrid->Iterator_NextPosition());

        aShape->mCenter = lCenter;

        return lResult;
    }

    void Diagram::RetrieveDiagramSize(SVG_Document * aDoc)
    {
        assert(NULL != aDoc);

        unsigned int lSizeX_pixel;
        unsigned int lSizeY_pixel;

        mShapes.GetDiagramSize(&lSizeX_pixel, &lSizeY_pixel);

        aDoc->Attribute_Set(SVG_Document::ATTR_HEIGHT, lSizeY_pixel);
        aDoc->Attribute_Set(SVG_Document::ATTR_WIDTH , lSizeX_pixel);
    }

}
