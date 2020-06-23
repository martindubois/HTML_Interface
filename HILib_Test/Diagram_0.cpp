
/*
    Generated using the HTML_Interface library
*/

// ===== C =====
#include <assert.h>

// ===== HTML_Interface =====
#include <HI/Diagram.h>
#include <HI/Link.h>

HI::Diagram * Diagram_0()
{
    HI::Diagram * lResult = new HI::Diagram();
    assert(NULL != lResult);

    HI::Shape * lShape00 = lResult->mShapes.AddShape("SubNet", "192.168.10.0", HI::Shape::TYPE_ELLIPSE);
    assert(NULL != lShape00);

    lShape00->SetFillColor("white");
    lShape00->SetTitle    ("255.255.255.0");

    HI::Shape * lShape01 = lResult->mShapes.AddShape("SubNet", "192.168.20.0", HI::Shape::TYPE_ELLIPSE);
    assert(NULL != lShape01);

    lShape01->SetFillColor("white");
    lShape01->SetTitle    ("255.255.255.0");

    HI::Shape * lShape02 = lResult->mShapes.AddShape("SubNet", "192.168.30.0", HI::Shape::TYPE_ELLIPSE);
    assert(NULL != lShape02);

    lShape02->SetFillColor("white");
    lShape02->SetTitle    ("255.255.255.0");

    HI::Shape * lShape03 = lResult->mShapes.AddShape("SubNet", "192.168.40.0", HI::Shape::TYPE_ELLIPSE);
    assert(NULL != lShape03);

    lShape03->SetFillColor("white");
    lShape03->SetTitle    ("255.255.255.0");

    HI::Shape * lShape04 = lResult->mShapes.AddShape("SubNet", "192.168.50.0", HI::Shape::TYPE_ELLIPSE);
    assert(NULL != lShape04);

    lShape04->SetFillColor("white");
    lShape04->SetTitle    ("255.255.255.0");

    HI::Shape * lShape05 = lResult->mShapes.AddShape("SubNet", "192.168.60.0", HI::Shape::TYPE_ELLIPSE);
    assert(NULL != lShape05);

    lShape05->SetFillColor("white");
    lShape05->SetTitle    ("255.255.255.0");

    HI::Shape * lShape06 = lResult->mShapes.AddShape("SubNet", "192.168.70.0", HI::Shape::TYPE_ELLIPSE);
    assert(NULL != lShape06);

    lShape06->SetFillColor("white");
    lShape06->SetTitle    ("255.255.255.0");

    HI::Shape * lShape07 = lResult->mShapes.AddShape("Interface", "Tunnel 0", HI::Shape::TYPE_RECT);
    assert(NULL != lShape07);

    lShape07->SetFillColor("Aquamarine");
    lShape07->SetTitle    ("192.168.200.1");

    HI::Shape * lShape08 = lResult->mShapes.AddShape("Interface", "e0/3/0", HI::Shape::TYPE_RECT);
    assert(NULL != lShape08);

    lShape08->SetFillColor("Aquamarine");
    lShape08->SetTitle    ("8.1.2.3");

    HI::Shape * lShape09 = lResult->mShapes.AddShape("Interface", "f0/0", HI::Shape::TYPE_RECT);
    assert(NULL != lShape09);

    lShape09->SetFillColor("Aquamarine");
    lShape09->SetTitle    ("192.168.10.1\nDHCP Server");

    HI::Shape * lShape10 = lResult->mShapes.AddShape("Interface", "f0/1", HI::Shape::TYPE_RECT);
    assert(NULL != lShape10);

    lShape10->SetFillColor("Aquamarine");
    lShape10->SetTitle    ("192.168.20.1");

    HI::Shape * lShape11 = lResult->mShapes.AddShape("Interface", "f1/0", HI::Shape::TYPE_RECT);
    assert(NULL != lShape11);

    lShape11->SetFillColor("Aquamarine");
    lShape11->SetTitle    ("192.168.100.1");

    HI::Shape * lShape12 = lResult->mShapes.AddShape("Interface", "f0/0", HI::Shape::TYPE_RECT);
    assert(NULL != lShape12);

    lShape12->SetFillColor("BurlyWood");
    lShape12->SetTitle    ("192.168.30.1");

    HI::Shape * lShape13 = lResult->mShapes.AddShape("Interface", "f0/1", HI::Shape::TYPE_RECT);
    assert(NULL != lShape13);

    lShape13->SetFillColor("BurlyWood");
    lShape13->SetTitle    ("192.168.110.1");

    HI::Shape * lShape14 = lResult->mShapes.AddShape("Interface", "f1/0", HI::Shape::TYPE_RECT);
    assert(NULL != lShape14);

    lShape14->SetFillColor("BurlyWood");
    lShape14->SetTitle    ("192.168.100.2");

    HI::Shape * lShape15 = lResult->mShapes.AddShape("Interface", "f0/0", HI::Shape::TYPE_RECT);
    assert(NULL != lShape15);

    lShape15->SetFillColor("Aqua");
    lShape15->SetTitle    ("192.168.110.2");

    HI::Shape * lShape16 = lResult->mShapes.AddShape("Interface", "f0/1", HI::Shape::TYPE_RECT);
    assert(NULL != lShape16);

    lShape16->SetFillColor("Aqua");
    lShape16->SetTitle    ("192.168.40.1");

    HI::Shape * lShape17 = lResult->mShapes.AddShape("Interface", "f1/0", HI::Shape::TYPE_RECT);
    assert(NULL != lShape17);

    lShape17->SetFillColor("Aqua");
    lShape17->SetTitle    ("192.168.120.1");

    HI::Shape * lShape18 = lResult->mShapes.AddShape("Interface", "f0/0", HI::Shape::TYPE_RECT);
    assert(NULL != lShape18);

    lShape18->SetFillColor("LightGray");
    lShape18->SetTitle    ("192.168.50.1");

    HI::Shape * lShape19 = lResult->mShapes.AddShape("Interface", "f0/1", HI::Shape::TYPE_RECT);
    assert(NULL != lShape19);

    lShape19->SetFillColor("LightGray");
    lShape19->SetTitle    ("192.168.130.1");

    HI::Shape * lShape20 = lResult->mShapes.AddShape("Interface", "f1/0", HI::Shape::TYPE_RECT);
    assert(NULL != lShape20);

    lShape20->SetFillColor("LightGray");
    lShape20->SetTitle    ("192.168.120.2");

    HI::Shape * lShape21 = lResult->mShapes.AddShape("Interface", "f0/0", HI::Shape::TYPE_RECT);
    assert(NULL != lShape21);

    lShape21->SetFillColor("DarkSeaGreen");
    lShape21->SetTitle    ("192.168.130.2");

    HI::Shape * lShape22 = lResult->mShapes.AddShape("Interface", "f0/1", HI::Shape::TYPE_RECT);
    assert(NULL != lShape22);

    lShape22->SetFillColor("DarkSeaGreen");
    lShape22->SetTitle    ("192.168.60.1");

    HI::Shape * lShape23 = lResult->mShapes.AddShape("Interface", "f1/0", HI::Shape::TYPE_RECT);
    assert(NULL != lShape23);

    lShape23->SetFillColor("DarkSeaGreen");
    lShape23->SetTitle    ("192.168.140.1");

    HI::Shape * lShape24 = lResult->mShapes.AddShape("Interface", "Tunnel 0", HI::Shape::TYPE_RECT);
    assert(NULL != lShape24);

    lShape24->SetFillColor("LightCoral");
    lShape24->SetTitle    ("192.168.200.2");

    HI::Shape * lShape25 = lResult->mShapes.AddShape("Interface", "f0/0", HI::Shape::TYPE_RECT);
    assert(NULL != lShape25);

    lShape25->SetFillColor("LightCoral");
    lShape25->SetTitle    ("192.168.70.1");

    HI::Shape * lShape26 = lResult->mShapes.AddShape("Interface", "f0/1", HI::Shape::TYPE_RECT);
    assert(NULL != lShape26);

    lShape26->SetFillColor("LightCoral");
    lShape26->SetTitle    ("8.2.3.4");

    HI::Shape * lShape27 = lResult->mShapes.AddShape("Interface", "f1/0", HI::Shape::TYPE_RECT);
    assert(NULL != lShape27);

    lShape27->SetFillColor("LightCoral");
    lShape27->SetTitle    ("192.168.140.2");

    HI::Shape * lShape28 = lResult->mShapes.AddShape("SubNet", "8.0.0.0", HI::Shape::TYPE_ELLIPSE);
    assert(NULL != lShape28);

    lShape28->SetFillColor("white");
    lShape28->SetTitle    ("255.0.0.0");

    HI::Shape * lShape29 = lResult->mShapes.AddShape("SubNet", "192.168.100.0", HI::Shape::TYPE_ELLIPSE);
    assert(NULL != lShape29);

    lShape29->SetFillColor("white");
    lShape29->SetTitle    ("255.255.255.0");

    HI::Shape * lShape30 = lResult->mShapes.AddShape("SubNet", "192.168.200.0", HI::Shape::TYPE_ELLIPSE);
    assert(NULL != lShape30);

    lShape30->SetFillColor("white");
    lShape30->SetTitle    ("255.255.255.0");

    HI::Shape * lShape31 = lResult->mShapes.AddShape("SubNet", "192.168.110.0", HI::Shape::TYPE_ELLIPSE);
    assert(NULL != lShape31);

    lShape31->SetFillColor("white");
    lShape31->SetTitle    ("255.255.255.0");

    HI::Shape * lShape32 = lResult->mShapes.AddShape("SubNet", "192.168.120.0", HI::Shape::TYPE_ELLIPSE);
    assert(NULL != lShape32);

    lShape32->SetFillColor("white");
    lShape32->SetTitle    ("255.255.255.0");

    HI::Shape * lShape33 = lResult->mShapes.AddShape("SubNet", "192.168.130.0", HI::Shape::TYPE_ELLIPSE);
    assert(NULL != lShape33);

    lShape33->SetFillColor("white");
    lShape33->SetTitle    ("255.255.255.0");

    HI::Shape * lShape34 = lResult->mShapes.AddShape("SubNet", "192.168.140.0", HI::Shape::TYPE_ELLIPSE);
    assert(NULL != lShape34);

    lShape34->SetFillColor("white");
    lShape34->SetTitle    ("255.255.255.0");

    HI::Shape * lShape35 = lResult->mShapes.AddShape("Router", "Test_5_Router_1", HI::Shape::TYPE_RECT);
    assert(NULL != lShape35);

    lShape35->SetFillColor("BurlyWood");
    lShape35->SetTitle    ("");

    HI::Shape * lShape36 = lResult->mShapes.AddShape("Router", "Test_5_Router_2", HI::Shape::TYPE_RECT);
    assert(NULL != lShape36);

    lShape36->SetFillColor("Aqua");
    lShape36->SetTitle    ("");

    HI::Shape * lShape37 = lResult->mShapes.AddShape("Router", "Test_5_Router_3", HI::Shape::TYPE_RECT);
    assert(NULL != lShape37);

    lShape37->SetFillColor("LightGray");
    lShape37->SetTitle    ("");

    HI::Shape * lShape38 = lResult->mShapes.AddShape("Router", "Test_5_Router_4", HI::Shape::TYPE_RECT);
    assert(NULL != lShape38);

    lShape38->SetFillColor("DarkSeaGreen");
    lShape38->SetTitle    ("");

    HI::Shape * lShape39 = lResult->mShapes.AddShape("Router", "Test_5_Router_5", HI::Shape::TYPE_RECT);
    assert(NULL != lShape39);

    lShape39->SetFillColor("LightCoral");
    lShape39->SetTitle    ("");

    HI::Shape * lShape40 = lResult->mShapes.AddShape("Router", "Test_5_Router_0", HI::Shape::TYPE_RECT);
    assert(NULL != lShape40);

    lShape40->SetFillColor("Aquamarine");
    lShape40->SetTitle    ("");

    HI::Link * lLink00 = lResult->mLinks.AddLink(lShape07, lShape30);
    assert(NULL != lLink00);

    lLink00->SetColor       ("Blue");
    lLink00->SetDashArray   ("6, 2");
    lLink00->SetWeightFactor(1.000000);
    lLink00->SetWidth       (2);

    HI::Link * lLink01 = lResult->mLinks.AddLink(lShape40, lShape07);
    assert(NULL != lLink01);

    lLink01->SetColor       ("black");
    lLink01->SetDashArray   ("9, 3");
    lLink01->SetWeightFactor(2.000000);
    lLink01->SetWidth       (3);

    HI::Link * lLink02 = lResult->mLinks.AddLink(lShape08, lShape28);
    assert(NULL != lLink02);

    lLink02->SetColor       ("Blue");
    lLink02->SetDashArray   ("");
    lLink02->SetWeightFactor(1.000000);
    lLink02->SetWidth       (2);

    HI::Link * lLink03 = lResult->mLinks.AddLink(lShape40, lShape08);
    assert(NULL != lLink03);

    lLink03->SetColor       ("black");
    lLink03->SetDashArray   ("");
    lLink03->SetWeightFactor(2.000000);
    lLink03->SetWidth       (3);

    HI::Link * lLink04 = lResult->mLinks.AddLink(lShape09, lShape00);
    assert(NULL != lLink04);

    lLink04->SetColor       ("Blue");
    lLink04->SetDashArray   ("");
    lLink04->SetWeightFactor(1.000000);
    lLink04->SetWidth       (2);

    HI::Link * lLink05 = lResult->mLinks.AddLink(lShape40, lShape09);
    assert(NULL != lLink05);

    lLink05->SetColor       ("black");
    lLink05->SetDashArray   ("");
    lLink05->SetWeightFactor(2.000000);
    lLink05->SetWidth       (3);

    HI::Link * lLink06 = lResult->mLinks.AddLink(lShape10, lShape01);
    assert(NULL != lLink06);

    lLink06->SetColor       ("Blue");
    lLink06->SetDashArray   ("");
    lLink06->SetWeightFactor(1.000000);
    lLink06->SetWidth       (2);

    HI::Link * lLink07 = lResult->mLinks.AddLink(lShape40, lShape10);
    assert(NULL != lLink07);

    lLink07->SetColor       ("black");
    lLink07->SetDashArray   ("");
    lLink07->SetWeightFactor(2.000000);
    lLink07->SetWidth       (3);

    HI::Link * lLink08 = lResult->mLinks.AddLink(lShape11, lShape29);
    assert(NULL != lLink08);

    lLink08->SetColor       ("Blue");
    lLink08->SetDashArray   ("");
    lLink08->SetWeightFactor(1.000000);
    lLink08->SetWidth       (2);

    HI::Link * lLink09 = lResult->mLinks.AddLink(lShape40, lShape11);
    assert(NULL != lLink09);

    lLink09->SetColor       ("black");
    lLink09->SetDashArray   ("");
    lLink09->SetWeightFactor(2.000000);
    lLink09->SetWidth       (3);

    HI::Link * lLink10 = lResult->mLinks.AddLink(lShape12, lShape02);
    assert(NULL != lLink10);

    lLink10->SetColor       ("Blue");
    lLink10->SetDashArray   ("");
    lLink10->SetWeightFactor(1.000000);
    lLink10->SetWidth       (2);

    HI::Link * lLink11 = lResult->mLinks.AddLink(lShape35, lShape12);
    assert(NULL != lLink11);

    lLink11->SetColor       ("black");
    lLink11->SetDashArray   ("");
    lLink11->SetWeightFactor(2.000000);
    lLink11->SetWidth       (3);

    HI::Link * lLink12 = lResult->mLinks.AddLink(lShape13, lShape31);
    assert(NULL != lLink12);

    lLink12->SetColor       ("Blue");
    lLink12->SetDashArray   ("");
    lLink12->SetWeightFactor(1.000000);
    lLink12->SetWidth       (2);

    HI::Link * lLink13 = lResult->mLinks.AddLink(lShape35, lShape13);
    assert(NULL != lLink13);

    lLink13->SetColor       ("black");
    lLink13->SetDashArray   ("");
    lLink13->SetWeightFactor(2.000000);
    lLink13->SetWidth       (3);

    HI::Link * lLink14 = lResult->mLinks.AddLink(lShape14, lShape29);
    assert(NULL != lLink14);

    lLink14->SetColor       ("Blue");
    lLink14->SetDashArray   ("");
    lLink14->SetWeightFactor(1.000000);
    lLink14->SetWidth       (2);

    HI::Link * lLink15 = lResult->mLinks.AddLink(lShape35, lShape14);
    assert(NULL != lLink15);

    lLink15->SetColor       ("black");
    lLink15->SetDashArray   ("");
    lLink15->SetWeightFactor(2.000000);
    lLink15->SetWidth       (3);

    HI::Link * lLink16 = lResult->mLinks.AddLink(lShape15, lShape31);
    assert(NULL != lLink16);

    lLink16->SetColor       ("Blue");
    lLink16->SetDashArray   ("");
    lLink16->SetWeightFactor(1.000000);
    lLink16->SetWidth       (2);

    HI::Link * lLink17 = lResult->mLinks.AddLink(lShape36, lShape15);
    assert(NULL != lLink17);

    lLink17->SetColor       ("black");
    lLink17->SetDashArray   ("");
    lLink17->SetWeightFactor(2.000000);
    lLink17->SetWidth       (3);

    HI::Link * lLink18 = lResult->mLinks.AddLink(lShape16, lShape03);
    assert(NULL != lLink18);

    lLink18->SetColor       ("Blue");
    lLink18->SetDashArray   ("");
    lLink18->SetWeightFactor(1.000000);
    lLink18->SetWidth       (2);

    HI::Link * lLink19 = lResult->mLinks.AddLink(lShape36, lShape16);
    assert(NULL != lLink19);

    lLink19->SetColor       ("black");
    lLink19->SetDashArray   ("");
    lLink19->SetWeightFactor(2.000000);
    lLink19->SetWidth       (3);

    HI::Link * lLink20 = lResult->mLinks.AddLink(lShape17, lShape32);
    assert(NULL != lLink20);

    lLink20->SetColor       ("Blue");
    lLink20->SetDashArray   ("");
    lLink20->SetWeightFactor(1.000000);
    lLink20->SetWidth       (2);

    HI::Link * lLink21 = lResult->mLinks.AddLink(lShape36, lShape17);
    assert(NULL != lLink21);

    lLink21->SetColor       ("black");
    lLink21->SetDashArray   ("");
    lLink21->SetWeightFactor(2.000000);
    lLink21->SetWidth       (3);

    HI::Link * lLink22 = lResult->mLinks.AddLink(lShape18, lShape04);
    assert(NULL != lLink22);

    lLink22->SetColor       ("Blue");
    lLink22->SetDashArray   ("");
    lLink22->SetWeightFactor(1.000000);
    lLink22->SetWidth       (2);

    HI::Link * lLink23 = lResult->mLinks.AddLink(lShape37, lShape18);
    assert(NULL != lLink23);

    lLink23->SetColor       ("black");
    lLink23->SetDashArray   ("");
    lLink23->SetWeightFactor(2.000000);
    lLink23->SetWidth       (3);

    HI::Link * lLink24 = lResult->mLinks.AddLink(lShape19, lShape33);
    assert(NULL != lLink24);

    lLink24->SetColor       ("Blue");
    lLink24->SetDashArray   ("");
    lLink24->SetWeightFactor(1.000000);
    lLink24->SetWidth       (2);

    HI::Link * lLink25 = lResult->mLinks.AddLink(lShape37, lShape19);
    assert(NULL != lLink25);

    lLink25->SetColor       ("black");
    lLink25->SetDashArray   ("");
    lLink25->SetWeightFactor(2.000000);
    lLink25->SetWidth       (3);

    HI::Link * lLink26 = lResult->mLinks.AddLink(lShape20, lShape32);
    assert(NULL != lLink26);

    lLink26->SetColor       ("Blue");
    lLink26->SetDashArray   ("");
    lLink26->SetWeightFactor(1.000000);
    lLink26->SetWidth       (2);

    HI::Link * lLink27 = lResult->mLinks.AddLink(lShape37, lShape20);
    assert(NULL != lLink27);

    lLink27->SetColor       ("black");
    lLink27->SetDashArray   ("");
    lLink27->SetWeightFactor(2.000000);
    lLink27->SetWidth       (3);

    HI::Link * lLink28 = lResult->mLinks.AddLink(lShape21, lShape33);
    assert(NULL != lLink28);

    lLink28->SetColor       ("Blue");
    lLink28->SetDashArray   ("");
    lLink28->SetWeightFactor(1.000000);
    lLink28->SetWidth       (2);

    HI::Link * lLink29 = lResult->mLinks.AddLink(lShape38, lShape21);
    assert(NULL != lLink29);

    lLink29->SetColor       ("black");
    lLink29->SetDashArray   ("");
    lLink29->SetWeightFactor(2.000000);
    lLink29->SetWidth       (3);

    HI::Link * lLink30 = lResult->mLinks.AddLink(lShape22, lShape05);
    assert(NULL != lLink30);

    lLink30->SetColor       ("Blue");
    lLink30->SetDashArray   ("");
    lLink30->SetWeightFactor(1.000000);
    lLink30->SetWidth       (2);

    HI::Link * lLink31 = lResult->mLinks.AddLink(lShape38, lShape22);
    assert(NULL != lLink31);

    lLink31->SetColor       ("black");
    lLink31->SetDashArray   ("");
    lLink31->SetWeightFactor(2.000000);
    lLink31->SetWidth       (3);

    HI::Link * lLink32 = lResult->mLinks.AddLink(lShape23, lShape34);
    assert(NULL != lLink32);

    lLink32->SetColor       ("Blue");
    lLink32->SetDashArray   ("");
    lLink32->SetWeightFactor(1.000000);
    lLink32->SetWidth       (2);

    HI::Link * lLink33 = lResult->mLinks.AddLink(lShape38, lShape23);
    assert(NULL != lLink33);

    lLink33->SetColor       ("black");
    lLink33->SetDashArray   ("");
    lLink33->SetWeightFactor(2.000000);
    lLink33->SetWidth       (3);

    HI::Link * lLink34 = lResult->mLinks.AddLink(lShape24, lShape30);
    assert(NULL != lLink34);

    lLink34->SetColor       ("Blue");
    lLink34->SetDashArray   ("6, 2");
    lLink34->SetWeightFactor(1.000000);
    lLink34->SetWidth       (2);

    HI::Link * lLink35 = lResult->mLinks.AddLink(lShape39, lShape24);
    assert(NULL != lLink35);

    lLink35->SetColor       ("black");
    lLink35->SetDashArray   ("9, 3");
    lLink35->SetWeightFactor(2.000000);
    lLink35->SetWidth       (3);

    HI::Link * lLink36 = lResult->mLinks.AddLink(lShape25, lShape06);
    assert(NULL != lLink36);

    lLink36->SetColor       ("Blue");
    lLink36->SetDashArray   ("");
    lLink36->SetWeightFactor(1.000000);
    lLink36->SetWidth       (2);

    HI::Link * lLink37 = lResult->mLinks.AddLink(lShape39, lShape25);
    assert(NULL != lLink37);

    lLink37->SetColor       ("black");
    lLink37->SetDashArray   ("");
    lLink37->SetWeightFactor(2.000000);
    lLink37->SetWidth       (3);

    HI::Link * lLink38 = lResult->mLinks.AddLink(lShape26, lShape28);
    assert(NULL != lLink38);

    lLink38->SetColor       ("Blue");
    lLink38->SetDashArray   ("");
    lLink38->SetWeightFactor(1.000000);
    lLink38->SetWidth       (2);

    HI::Link * lLink39 = lResult->mLinks.AddLink(lShape39, lShape26);
    assert(NULL != lLink39);

    lLink39->SetColor       ("black");
    lLink39->SetDashArray   ("");
    lLink39->SetWeightFactor(2.000000);
    lLink39->SetWidth       (3);

    HI::Link * lLink40 = lResult->mLinks.AddLink(lShape27, lShape34);
    assert(NULL != lLink40);

    lLink40->SetColor       ("Blue");
    lLink40->SetDashArray   ("");
    lLink40->SetWeightFactor(1.000000);
    lLink40->SetWidth       (2);

    HI::Link * lLink41 = lResult->mLinks.AddLink(lShape39, lShape27);
    assert(NULL != lLink41);

    lLink41->SetColor       ("black");
    lLink41->SetDashArray   ("");
    lLink41->SetWeightFactor(2.000000);
    lLink41->SetWidth       (3);

    return lResult;
}
