
// Author     KMS - Martin Dubois, P.Eng.
// Copyright  (C) 2020 KMS. All rights reserved.
// Product    HTML_Interface
// File       HILib_Test/Diagram.cpp

// ===== Import/Includes ====================================================
#include <KmsTest.h>

// ===== Includes ===========================================================
#include <HI/CSS_Colors.h>
#include <HI/Diagram.h>
#include <HI/Link.h>
#include <HI/Shape.h>

// ===== HILib_Test =========================================================
extern HI::Diagram * Diagram_0();
extern HI::Diagram * Diagram_1();

// Tests
/////////////////////////////////////////////////////////////////////////////

KMS_TEST_BEGIN(Diagram_Base)

    HI::Diagram lD0;
    HI::Link  * lL ;
    HI::Shape * lS ;

    KMS_TEST_ASSERT(NULL == lD0.mLinks .GetLink (0));
    KMS_TEST_ASSERT(NULL == lD0.mShapes.GetShape(0));

    lD0.SetBackgroundColor(HI::COLOR_ALICE_BLUE);

    lS = lD0.mShapes.AddShape("Box", "Alpha - B - C - D");
    lS->SetFillColor(HI::COLOR_ALICE_BLUE);

    KMS_TEST_COMPARE(0, strcmp("Alpha - B - C - D", lS->GetName()));

    lS = lD0.mShapes.AddShape("Box", "Bravo - A - C");
    lS->SetFillColor  ("LightGray");
    lS->SetStrokeWidth(4);
    lS->SetTitle      ("Light Gray");
    lS->AppendToTitle ("!");

    lS = lD0.mShapes.AddShape("Box", "Charlie - A - B");
    lS = lD0.mShapes.AddShape("Box", "Delta - A - E - F");
    lS = lD0.mShapes.AddShape("Box", "Echo - D - F");
    lS = lD0.mShapes.AddShape("Box", "Foxtrot - D - E - G");
    lS = lD0.mShapes.AddShape("Box", "Golf - F", HI::Shape::TYPE_ELLIPSE);
    lS = lD0.mShapes.AddShape("Box", "Hotel - G", HI::Shape::TYPE_IMAGE);

    lS->SetImage(HI::FOLDER_STATIC, "KMS.png");
    lS->SetSize(80, 60);
    lS->SetNameOnImage();
    lS->SetTypeOnImage();

    lL = lD0.mLinks.AddLink(lD0.mShapes.GetShape(0), lD0.mShapes.GetShape(1));
    lL = lD0.mLinks.AddLink(lD0.mShapes.GetShape(1), lD0.mShapes.GetShape(2));
    lL = lD0.mLinks.AddLink(lD0.mShapes.GetShape(2), lD0.mShapes.GetShape(0));

    lL = lD0.mLinks.AddLink(lD0.mShapes.GetShape(0), lD0.mShapes.GetShape(3));
    lL->SetColor(HI::COLOR_BLUE);

    lL = lD0.mLinks.AddLink(lD0.mShapes.GetShape(3), lD0.mShapes.GetShape(4));
    lL = lD0.mLinks.AddLink(lD0.mShapes.GetShape(4), lD0.mShapes.GetShape(5));
    lL = lD0.mLinks.AddLink(lD0.mShapes.GetShape(5), lD0.mShapes.GetShape(3));
    lL->SetDashArray("2,2");

    lL = lD0.mLinks.AddLink(lD0.mShapes.GetShape(5), lD0.mShapes.GetShape(6));
    lL->SetColor       ("Red");
    lL->SetWeightFactor(2);
    lL->SetWidth       (3);

    lL = lD0.mLinks.AddLink(lD0.mShapes.GetShape(6), lD0.mShapes.GetShape(7));

    KMS_TEST_ASSERT(NULL != lD0.mLinks.GetLink(0));
    KMS_TEST_ASSERT(NULL == lD0.mLinks.GetLink(9));

    KMS_TEST_ASSERT(NULL != lD0.mShapes.GetShape(0));
    KMS_TEST_ASSERT(NULL == lD0.mShapes.GetShape(8));

    lD0.PositionShapes();

    KMS_TEST_ASSERT(0 < lS->GetLeft());
    KMS_TEST_ASSERT(0 < lS->GetTop ());

    KMS_TEST_ASSERT(0 < lD0.mLinks.GetLength(lD0.mShapes.GetShape(0)));

    lD0.Generate_CPP("HILib_Test\\Tests", "Diagram_Base_0");

    lD0.Generate_CPP(HI::FOLDER_TEMP, "Diagram_Base_0");

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

    HI::Diagram * lD2 = Diagram_0();
    KMS_TEST_ASSERT(NULL != lD2);

    lD2->PositionShapes();
    lD2->Generate_HTML(HI::FOLDER_CURRENT, "Diagram_0", "Diagram 0");

    HI::Diagram * lD3 = Diagram_1();
    KMS_TEST_ASSERT(NULL != lD3);

    lD3->PositionShapes();
    lD3->Generate_HTML(HI::FOLDER_CURRENT, "Diagram_1", "Diagram 1");

    KMS_TEST_END
