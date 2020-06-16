
// Author     KMS - Martin Dubois, P.Eng.
// Copyright  (C) 2020 KMS. All rights reserved.
// Product    HTML_Interface
// File       HILib_Test/Diagram.cpp

// ===== Import/Includes ====================================================
#include <KmsTest.h>

// ===== Includes ===========================================================
#include <HI/Diagram.h>
#include <HI/Link.h>
#include <HI/Shape.h>

// Tests
/////////////////////////////////////////////////////////////////////////////

KMS_TEST_BEGIN(Diagram_Base)

    HI::Diagram lD0;

    KMS_TEST_ASSERT(NULL == lD0.mLinks .GetLink (0));
    KMS_TEST_ASSERT(NULL == lD0.mShapes.GetShape(0));

    lD0.mShapes.AddShape("Box", "Alpha - B - C - D");
    lD0.mShapes.AddShape("Box", "Bravo - A - C");
    lD0.mShapes.AddShape("Box", "Charlie - A - B");
    lD0.mShapes.AddShape("Box", "Delta - A - E - F");
    lD0.mShapes.AddShape("Box", "Echo - D - F");
    lD0.mShapes.AddShape("Box", "Foxtrot - D - E - G");
    lD0.mShapes.AddShape("Box", "Golf - F", HI::Shape::TYPE_ELLIPSE);

    lD0.mShapes.GetShape(0)->SetFillColor(HI::COLOR_ALICE_BLUE);
    lD0.mShapes.GetShape(1)->SetFillColor("LightGray");
    lD0.mShapes.GetShape(1)->SetTitle("LightGray");

    lD0.mLinks.AddLink(lD0.mShapes.GetShape(0), lD0.mShapes.GetShape(1));
    lD0.mLinks.AddLink(lD0.mShapes.GetShape(1), lD0.mShapes.GetShape(2));
    lD0.mLinks.AddLink(lD0.mShapes.GetShape(2), lD0.mShapes.GetShape(0));

    lD0.mLinks.AddLink(lD0.mShapes.GetShape(0), lD0.mShapes.GetShape(3));

    lD0.mLinks.GetLink(3)->SetColor(HI::COLOR_BLUE);

    lD0.mLinks.AddLink(lD0.mShapes.GetShape(3), lD0.mShapes.GetShape(4));
    lD0.mLinks.AddLink(lD0.mShapes.GetShape(4), lD0.mShapes.GetShape(5));
    lD0.mLinks.AddLink(lD0.mShapes.GetShape(5), lD0.mShapes.GetShape(3));

    lD0.mLinks.AddLink(lD0.mShapes.GetShape(5), lD0.mShapes.GetShape(6));

    lD0.mLinks.GetLink(7)->SetColor("Red");
    lD0.mLinks.GetLink(7)->SetWeightFactor(2);
    lD0.mLinks.GetLink(7)->SetWidth(3);

    KMS_TEST_COMPARE(0, strcmp("Alpha - B - C - D", lD0.mShapes.GetShape(0)->GetName()));

    KMS_TEST_ASSERT(NULL == lD0.mShapes.GetShape(7));

    lD0.PositionShapes();

    KMS_TEST_ASSERT(0 < lD0.mLinks.GetLength(lD0.mShapes.GetShape(0)));

    lD0.Generate_HTML(HI::FOLDER_CURRENT, "Diagram_Base_0", "Diagram - Base - 0");

    HI::Diagram lD1;

    lD1.mShapes.AddShape("Box", "Alpha - B - C");
    lD1.mShapes.AddShape("Box", "Bravo - A - E - F");
    lD1.mShapes.AddShape("Box", "Charlie - A - D");
    lD1.mShapes.AddShape("Box", "Delta - C");
    lD1.mShapes.AddShape("Box", "Echo - B - G");
    lD1.mShapes.AddShape("Box", "Foxtrot - B - H", HI::Shape::TYPE_ELLIPSE);
    lD1.mShapes.AddShape("Box", "Golf - E - I");
    lD1.mShapes.AddShape("Box", "Hotel - F");
    lD1.mShapes.AddShape("Box", "India - G");

    lD1.mLinks.AddLink(lD1.mShapes.GetShape(0), lD1.mShapes.GetShape(1));
    lD1.mLinks.AddLink(lD1.mShapes.GetShape(0), lD1.mShapes.GetShape(2));
    lD1.mLinks.AddLink(lD1.mShapes.GetShape(1), lD1.mShapes.GetShape(4));
    lD1.mLinks.AddLink(lD1.mShapes.GetShape(1), lD1.mShapes.GetShape(5));
    lD1.mLinks.AddLink(lD1.mShapes.GetShape(2), lD1.mShapes.GetShape(3));
    lD1.mLinks.AddLink(lD1.mShapes.GetShape(4), lD1.mShapes.GetShape(6));
    lD1.mLinks.AddLink(lD1.mShapes.GetShape(5), lD1.mShapes.GetShape(7));
    lD1.mLinks.AddLink(lD1.mShapes.GetShape(6), lD1.mShapes.GetShape(8));

    lD1.SetDebug();

    lD1.PositionShapes();

    lD1.Generate_HTML(HI::FOLDER_CURRENT, "Diagram_Base_1", "Diagram - Base - 1");

KMS_TEST_END
