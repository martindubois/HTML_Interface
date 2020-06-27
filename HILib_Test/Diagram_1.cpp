
/*
    Generated using the HTML_Interface library
*/

// ===== C =====
#include <assert.h>

// ===== HTML_Interface =====
#include <HI/Diagram.h>
#include <HI/Link.h>

HI::Diagram * Diagram_1()
{
    HI::Diagram * lResult = new HI::Diagram();
    assert(NULL != lResult);

    HI::Shape * lShape00 = lResult->mShapes.AddShape("SubNet", "192.168.40.0", HI::Shape::TYPE_ELLIPSE);
    assert(NULL != lShape00);

    lShape00->SetFillColor ("white");
    lShape00->SetTitle     ("255.255.255.0");

    HI::Shape * lShape01 = lResult->mShapes.AddShape("SubNet", "192.168.10.0", HI::Shape::TYPE_ELLIPSE);
    assert(NULL != lShape01);

    lShape01->SetFillColor ("white");
    lShape01->SetTitle     ("255.255.255.0");

    HI::Shape * lShape02 = lResult->mShapes.AddShape("SubNet", "192.168.60.0", HI::Shape::TYPE_ELLIPSE);
    assert(NULL != lShape02);

    lShape02->SetFillColor ("white");
    lShape02->SetTitle     ("255.255.255.0");

    HI::Shape * lShape03 = lResult->mShapes.AddShape("SubNet", "192.168.80.0", HI::Shape::TYPE_ELLIPSE);
    assert(NULL != lShape03);

    lShape03->SetFillColor ("white");
    lShape03->SetTitle     ("255.255.255.0");

    HI::Shape * lShape04 = lResult->mShapes.AddShape("SubNet", "192.168.20.0", HI::Shape::TYPE_ELLIPSE);
    assert(NULL != lShape04);

    lShape04->SetFillColor ("white");
    lShape04->SetTitle     ("255.255.255.0");

    HI::Shape * lShape05 = lResult->mShapes.AddShape("Interface", "Tunnel 0", HI::Shape::TYPE_RECT);
    assert(NULL != lShape05);

    lShape05->SetFillColor ("Aquamarine");
    lShape05->SetTitle     ("192.168.50.1");

    HI::Shape * lShape06 = lResult->mShapes.AddShape("Interface", "f0/0", HI::Shape::TYPE_RECT);
    assert(NULL != lShape06);

    lShape06->SetFillColor ("Aquamarine");
    lShape06->SetTitle     ("8.2.3.4");

    HI::Shape * lShape07 = lResult->mShapes.AddShape("Interface", "f0/1", HI::Shape::TYPE_RECT);
    assert(NULL != lShape07);

    lShape07->SetFillColor ("Aquamarine");
    lShape07->SetTitle     ("192.168.40.1\nDHCP Server");

    HI::Shape * lShape08 = lResult->mShapes.AddShape("Interface", "Tunnel 0", HI::Shape::TYPE_RECT);
    assert(NULL != lShape08);

    lShape08->SetFillColor ("BurlyWood");
    lShape08->SetTitle     ("192.168.70.1");

    HI::Shape * lShape09 = lResult->mShapes.AddShape("Interface", "f0/0", HI::Shape::TYPE_RECT);
    assert(NULL != lShape09);

    lShape09->SetFillColor ("BurlyWood");
    lShape09->SetTitle     ("8.3.4.5");

    HI::Shape * lShape10 = lResult->mShapes.AddShape("Interface", "f0/1", HI::Shape::TYPE_RECT);
    assert(NULL != lShape10);

    lShape10->SetFillColor ("BurlyWood");
    lShape10->SetTitle     ("192.168.60.1\nDHCP Server");

    HI::Shape * lShape11 = lResult->mShapes.AddShape("Interface", "Tunnel 0", HI::Shape::TYPE_RECT);
    assert(NULL != lShape11);

    lShape11->SetFillColor ("Aqua");
    lShape11->SetTitle     ("192.168.90.1");

    HI::Shape * lShape12 = lResult->mShapes.AddShape("Interface", "e0/0/0", HI::Shape::TYPE_RECT);
    assert(NULL != lShape12);

    lShape12->SetFillColor ("Aqua");
    lShape12->SetTitle     ("192.168.30.2");

    HI::Shape * lShape13 = lResult->mShapes.AddShape("Interface", "f0/0", HI::Shape::TYPE_RECT);
    assert(NULL != lShape13);

    lShape13->SetFillColor ("Aqua");
    lShape13->SetTitle     ("192.168.80.1\nDHCP Server");

    HI::Shape * lShape14 = lResult->mShapes.AddShape("Interface", "f0/1", HI::Shape::TYPE_RECT);
    assert(NULL != lShape14);

    lShape14->SetFillColor ("Aqua");
    lShape14->SetTitle     ("8.4.5.6");

    HI::Shape * lShape15 = lResult->mShapes.AddShape("Interface", "Tunnel 0", HI::Shape::TYPE_RECT);
    assert(NULL != lShape15);

    lShape15->SetFillColor ("LightGray");
    lShape15->SetTitle     ("192.168.50.2");

    HI::Shape * lShape16 = lResult->mShapes.AddShape("Interface", "Tunnel 1", HI::Shape::TYPE_RECT);
    assert(NULL != lShape16);

    lShape16->SetFillColor ("LightGray");
    lShape16->SetTitle     ("192.168.70.2");

    HI::Shape * lShape17 = lResult->mShapes.AddShape("Interface", "Tunnel 2", HI::Shape::TYPE_RECT);
    assert(NULL != lShape17);

    lShape17->SetFillColor ("LightGray");
    lShape17->SetTitle     ("192.168.90.2");

    HI::Shape * lShape18 = lResult->mShapes.AddShape("Interface", "e0/0/0", HI::Shape::TYPE_RECT);
    assert(NULL != lShape18);

    lShape18->SetFillColor ("LightGray");
    lShape18->SetTitle     ("192.168.30.1");

    HI::Shape * lShape19 = lResult->mShapes.AddShape("Interface", "f0/0.1", HI::Shape::TYPE_RECT);
    assert(NULL != lShape19);

    lShape19->SetFillColor ("LightGray");
    lShape19->SetTitle     ("192.168.10.1\nVLAN 10");

    HI::Shape * lShape20 = lResult->mShapes.AddShape("Interface", "f0/0.2", HI::Shape::TYPE_RECT);
    assert(NULL != lShape20);

    lShape20->SetFillColor ("LightGray");
    lShape20->SetTitle     ("192.168.20.1\nVLAN 20\nDHCP Server");

    HI::Shape * lShape21 = lResult->mShapes.AddShape("Interface", "f0/1", HI::Shape::TYPE_RECT);
    assert(NULL != lShape21);

    lShape21->SetFillColor ("LightGray");
    lShape21->SetTitle     ("8.1.2.3");

    HI::Shape * lShape22 = lResult->mShapes.AddShape("SubNet", "192.168.50.0", HI::Shape::TYPE_ELLIPSE);
    assert(NULL != lShape22);

    lShape22->SetFillColor ("white");
    lShape22->SetTitle     ("255.255.255.0");

    HI::Shape * lShape23 = lResult->mShapes.AddShape("SubNet", "192.168.70.0", HI::Shape::TYPE_ELLIPSE);
    assert(NULL != lShape23);

    lShape23->SetFillColor ("white");
    lShape23->SetTitle     ("255.255.255.0");

    HI::Shape * lShape24 = lResult->mShapes.AddShape("SubNet", "192.168.30.0", HI::Shape::TYPE_ELLIPSE);
    assert(NULL != lShape24);

    lShape24->SetFillColor ("white");
    lShape24->SetTitle     ("255.255.255.0");

    HI::Shape * lShape25 = lResult->mShapes.AddShape("SubNet", "192.168.90.0", HI::Shape::TYPE_ELLIPSE);
    assert(NULL != lShape25);

    lShape25->SetFillColor ("white");
    lShape25->SetTitle     ("255.255.255.0");

    HI::Shape * lShape26 = lResult->mShapes.AddShape("Router", "Test_4_Router_0", HI::Shape::TYPE_RECT);
    assert(NULL != lShape26);

    lShape26->SetFillColor ("Aquamarine");

    HI::Shape * lShape27 = lResult->mShapes.AddShape("Router", "Test_4_Router_1", HI::Shape::TYPE_RECT);
    assert(NULL != lShape27);

    lShape27->SetFillColor ("BurlyWood");

    HI::Shape * lShape28 = lResult->mShapes.AddShape("Interface", "f0/0", HI::Shape::TYPE_RECT);
    assert(NULL != lShape28);

    lShape28->SetFillColor ("LightGray");

    HI::Shape * lShape29 = lResult->mShapes.AddShape("Router", "Test_4_Router_2", HI::Shape::TYPE_RECT);
    assert(NULL != lShape29);

    lShape29->SetFillColor ("Aqua");

    HI::Shape * lShape30 = lResult->mShapes.AddShape("SubNet", "8.0.0.0", HI::Shape::TYPE_ELLIPSE);
    assert(NULL != lShape30);

    lShape30->SetFillColor ("white");
    lShape30->SetTitle     ("255.0.0.0");

    HI::Shape * lShape31 = lResult->mShapes.AddShape("Router", "Test_4_Router_3", HI::Shape::TYPE_RECT);
    assert(NULL != lShape31);

    lShape31->SetFillColor ("LightGray");

    HI::Link * lLink00 = lResult->mLinks.AddLink(lShape05, lShape22);
    assert(NULL != lLink00);

    lLink00->SetColor       ("Blue");
    lLink00->SetDashArray   ("6, 2");
    lLink00->SetWidth       (2);

    HI::Link * lLink01 = lResult->mLinks.AddLink(lShape06, lShape30);
    assert(NULL != lLink01);

    lLink01->SetColor       ("Blue");
    lLink01->SetWidth       (2);

    HI::Link * lLink02 = lResult->mLinks.AddLink(lShape07, lShape00);
    assert(NULL != lLink02);

    lLink02->SetColor       ("Blue");
    lLink02->SetWidth       (2);

    HI::Link * lLink03 = lResult->mLinks.AddLink(lShape26, lShape05);
    assert(NULL != lLink03);

    lLink03->SetColor       ("black");
    lLink03->SetDashArray   ("9, 3");
    lLink03->SetWeightFactor(2.000000);
    lLink03->SetWidth       (3);

    HI::Link * lLink04 = lResult->mLinks.AddLink(lShape26, lShape06);
    assert(NULL != lLink04);

    lLink04->SetColor       ("black");
    lLink04->SetWeightFactor(2.000000);
    lLink04->SetWidth       (3);

    HI::Link * lLink05 = lResult->mLinks.AddLink(lShape26, lShape07);
    assert(NULL != lLink05);

    lLink05->SetColor       ("black");
    lLink05->SetWeightFactor(2.000000);
    lLink05->SetWidth       (3);

    HI::Link * lLink06 = lResult->mLinks.AddLink(lShape08, lShape23);
    assert(NULL != lLink06);

    lLink06->SetColor       ("Blue");
    lLink06->SetDashArray   ("6, 2");
    lLink06->SetWidth       (2);

    HI::Link * lLink07 = lResult->mLinks.AddLink(lShape09, lShape30);
    assert(NULL != lLink07);

    lLink07->SetColor       ("Blue");
    lLink07->SetWidth       (2);

    HI::Link * lLink08 = lResult->mLinks.AddLink(lShape10, lShape02);
    assert(NULL != lLink08);

    lLink08->SetColor       ("Blue");
    lLink08->SetWidth       (2);

    HI::Link * lLink09 = lResult->mLinks.AddLink(lShape27, lShape08);
    assert(NULL != lLink09);

    lLink09->SetColor       ("black");
    lLink09->SetDashArray   ("9, 3");
    lLink09->SetWeightFactor(2.000000);
    lLink09->SetWidth       (3);

    HI::Link * lLink10 = lResult->mLinks.AddLink(lShape27, lShape09);
    assert(NULL != lLink10);

    lLink10->SetColor       ("black");
    lLink10->SetWeightFactor(2.000000);
    lLink10->SetWidth       (3);

    HI::Link * lLink11 = lResult->mLinks.AddLink(lShape27, lShape10);
    assert(NULL != lLink11);

    lLink11->SetColor       ("black");
    lLink11->SetWeightFactor(2.000000);
    lLink11->SetWidth       (3);

    HI::Link * lLink12 = lResult->mLinks.AddLink(lShape11, lShape25);
    assert(NULL != lLink12);

    lLink12->SetColor       ("Blue");
    lLink12->SetDashArray   ("6, 2");
    lLink12->SetWidth       (2);

    HI::Link * lLink13 = lResult->mLinks.AddLink(lShape12, lShape24);
    assert(NULL != lLink13);

    lLink13->SetColor       ("Blue");
    lLink13->SetWidth       (2);

    HI::Link * lLink14 = lResult->mLinks.AddLink(lShape13, lShape03);
    assert(NULL != lLink14);

    lLink14->SetColor       ("Blue");
    lLink14->SetWidth       (2);

    HI::Link * lLink15 = lResult->mLinks.AddLink(lShape14, lShape30);
    assert(NULL != lLink15);

    lLink15->SetColor       ("Blue");
    lLink15->SetWidth       (2);

    HI::Link * lLink16 = lResult->mLinks.AddLink(lShape29, lShape11);
    assert(NULL != lLink16);

    lLink16->SetColor       ("black");
    lLink16->SetDashArray   ("9, 3");
    lLink16->SetWeightFactor(2.000000);
    lLink16->SetWidth       (3);

    HI::Link * lLink17 = lResult->mLinks.AddLink(lShape29, lShape12);
    assert(NULL != lLink17);

    lLink17->SetColor       ("black");
    lLink17->SetWeightFactor(2.000000);
    lLink17->SetWidth       (3);

    HI::Link * lLink18 = lResult->mLinks.AddLink(lShape29, lShape13);
    assert(NULL != lLink18);

    lLink18->SetColor       ("black");
    lLink18->SetWeightFactor(2.000000);
    lLink18->SetWidth       (3);

    HI::Link * lLink19 = lResult->mLinks.AddLink(lShape29, lShape14);
    assert(NULL != lLink19);

    lLink19->SetColor       ("black");
    lLink19->SetWeightFactor(2.000000);
    lLink19->SetWidth       (3);

    HI::Link * lLink20 = lResult->mLinks.AddLink(lShape15, lShape22);
    assert(NULL != lLink20);

    lLink20->SetColor       ("Blue");
    lLink20->SetDashArray   ("6, 2");
    lLink20->SetWidth       (2);

    HI::Link * lLink21 = lResult->mLinks.AddLink(lShape16, lShape23);
    assert(NULL != lLink21);

    lLink21->SetColor       ("Blue");
    lLink21->SetDashArray   ("6, 2");
    lLink21->SetWidth       (2);

    HI::Link * lLink22 = lResult->mLinks.AddLink(lShape17, lShape25);
    assert(NULL != lLink22);

    lLink22->SetColor       ("Blue");
    lLink22->SetDashArray   ("6, 2");
    lLink22->SetWidth       (2);

    HI::Link * lLink23 = lResult->mLinks.AddLink(lShape18, lShape24);
    assert(NULL != lLink23);

    lLink23->SetColor       ("Blue");
    lLink23->SetWidth       (2);

    HI::Link * lLink24 = lResult->mLinks.AddLink(lShape19, lShape01);
    assert(NULL != lLink24);

    lLink24->SetColor       ("Blue");
    lLink24->SetWidth       (2);

    HI::Link * lLink25 = lResult->mLinks.AddLink(lShape20, lShape04);
    assert(NULL != lLink25);

    lLink25->SetColor       ("Blue");
    lLink25->SetWidth       (2);

    HI::Link * lLink26 = lResult->mLinks.AddLink(lShape21, lShape30);
    assert(NULL != lLink26);

    lLink26->SetColor       ("Blue");
    lLink26->SetWidth       (2);

    HI::Link * lLink27 = lResult->mLinks.AddLink(lShape31, lShape15);
    assert(NULL != lLink27);

    lLink27->SetColor       ("black");
    lLink27->SetDashArray   ("9, 3");
    lLink27->SetWeightFactor(2.000000);
    lLink27->SetWidth       (3);

    HI::Link * lLink28 = lResult->mLinks.AddLink(lShape31, lShape16);
    assert(NULL != lLink28);

    lLink28->SetColor       ("black");
    lLink28->SetDashArray   ("9, 3");
    lLink28->SetWeightFactor(2.000000);
    lLink28->SetWidth       (3);

    HI::Link * lLink29 = lResult->mLinks.AddLink(lShape31, lShape17);
    assert(NULL != lLink29);

    lLink29->SetColor       ("black");
    lLink29->SetDashArray   ("9, 3");
    lLink29->SetWeightFactor(2.000000);
    lLink29->SetWidth       (3);

    HI::Link * lLink30 = lResult->mLinks.AddLink(lShape31, lShape18);
    assert(NULL != lLink30);

    lLink30->SetColor       ("black");
    lLink30->SetWeightFactor(2.000000);
    lLink30->SetWidth       (3);

    HI::Link * lLink31 = lResult->mLinks.AddLink(lShape31, lShape28);
    assert(NULL != lLink31);

    lLink31->SetColor       ("black");
    lLink31->SetWeightFactor(2.000000);
    lLink31->SetWidth       (3);

    HI::Link * lLink32 = lResult->mLinks.AddLink(lShape28, lShape19);
    assert(NULL != lLink32);

    lLink32->SetColor       ("black");
    lLink32->SetWeightFactor(2.000000);
    lLink32->SetWidth       (3);

    HI::Link * lLink33 = lResult->mLinks.AddLink(lShape28, lShape20);
    assert(NULL != lLink33);

    lLink33->SetColor       ("black");
    lLink33->SetWeightFactor(2.000000);
    lLink33->SetWidth       (3);

    HI::Link * lLink34 = lResult->mLinks.AddLink(lShape31, lShape21);
    assert(NULL != lLink34);

    lLink34->SetColor       ("black");
    lLink34->SetWeightFactor(2.000000);
    lLink34->SetWidth       (3);

    return lResult;
}
