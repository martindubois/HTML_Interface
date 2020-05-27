
// Author    KMS - Martin Dubois, P.Eng.
// Copyright (C) 2020 KMS. All rights reserved.
// Product   HTML_Interface
// File      HILib/Diagram.cpp

// CODE REVIEW 2020-05-27 KMS - Martin Dubois, P.Eng.

// TEST COVERAGE 2020-05-27 KMS - Martin Dubois, P.Eng.

// ===== C ==================================================================
#include <assert.h>

// ===== Includes ===========================================================
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
    }

    Diagram::~Diagram()
    {
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

        PositionShapes();

        unsigned int lSizeX_pixel;
        unsigned int lSizeY_pixel;

        mShapes.GetDiagramSize(&lSizeX_pixel, &lSizeY_pixel);

        SVG_Document lDoc;

        lDoc.Attribute_Set(SVG_Document::ATTR_HEIGHT, lSizeY_pixel);
        lDoc.Attribute_Set(SVG_Document::ATTR_WIDTH , lSizeX_pixel);

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

    // TODO Diagram.Generate
    //      Add a phase 3 to remove empty space on top and on left

    void Diagram::PositionShapes()
    {
        Grid lGrid;

        mShapes.PositionShapes(&lGrid);

        PositionShapes(&lGrid);
    }

    // Private
    /////////////////////////////////////////////////////////////////////////

    void Diagram::PositionShapes(Grid * aGrid)
    {
        unsigned int lMoveCount;

        do
        {
            lMoveCount = 0;

            mShapes.Iterator_Reset();

            Shape * lShape;

            while (NULL != (lShape = mShapes.Iterator_Get()))
            {
                lMoveCount += PositionShape(aGrid, lShape);

                mShapes.Iterator_Next();
            }
        }
        while (0 < lMoveCount);
    }

    unsigned int Diagram::PositionShape(Grid * aGrid, Shape * aShape)
    {
        assert(NULL != aGrid );
        assert(NULL != aShape);

        unsigned int lX_pixel;
        unsigned int lY_pixel;

        aShape->GetCenter(&lX_pixel, &lY_pixel);

        double lWeight = mLinks.GetWeight(aShape);

        aGrid->Iterator_Reset();

        unsigned int lResult = 0;

        do
        {
            if (NULL == mShapes.FindByCenter(aGrid->Iterator_GetX(), aGrid->Iterator_GetY()))
            {
                aShape->SetCenter(aGrid->Iterator_GetX(), aGrid->Iterator_GetY());

                double lNewWeight = mLinks.GetWeight(aShape);
                if (lWeight > lNewWeight)
                {
                    lResult++;
                    lWeight  = lNewWeight;
                    lX_pixel = aGrid->Iterator_GetX();
                    lY_pixel = aGrid->Iterator_GetY();
                }
            }
        }
        while (aGrid->Iterator_Next());

        aShape->SetCenter(lX_pixel, lY_pixel);

        return lResult;
    }

}
