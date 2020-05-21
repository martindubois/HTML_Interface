
// Author     KMS - Martin Dubois, P.Eng.
// Copyright  (C) 2020 KMS. All rights reserved.
// Product	  HTML_Interface
// File       HILib_Test/HILib_Test.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

#include <KmsBase.h>

// ===== Interface ==========================================================
#include <KmsTest.h>

// Test
/////////////////////////////////////////////////////////////////////////////

// Setup-A  A user must close launched browser.
// Setup-B  A user must follow the instructions.
KMS_TEST_GROUP_LIST_BEGIN
    KMS_TEST_GROUP_LIST_ENTRY("Base"   )
    KMS_TEST_GROUP_LIST_ENTRY("Setup-A")
    KMS_TEST_GROUP_LIST_ENTRY("Setup-B")
    KMS_TEST_GROUP_LIST_END

extern int Browser_Base      ();
extern int Browser_SetupA    ();
extern int CSS_Document_Base ();
extern int HTML_Document_Base();
extern int SVG_Document_Base ();
extern int Server_Base       ();
extern int Server_SetupB     ();

KMS_TEST_LIST_BEGIN
    KMS_TEST_LIST_ENTRY(Browser_Base      , "Browser - Base"      , 0, 0)
    KMS_TEST_LIST_ENTRY(Browser_SetupA    , "Browser - Setup A"   , 1, KMS_TEST_FLAG_INTERACTION_NEEDED)
    KMS_TEST_LIST_ENTRY(CSS_Document_Base , "CSS_Document - Base" , 0, 0)
    KMS_TEST_LIST_ENTRY(HTML_Document_Base, "HTML_Document - Base", 0, 0)
    KMS_TEST_LIST_ENTRY(SVG_Document_Base , "SVG_Document - Base" , 0, 0)
    KMS_TEST_LIST_ENTRY(Server_Base       , "Server - Base"       , 0, 0)
    KMS_TEST_LIST_ENTRY(Server_SetupB     , "Server - Setup B"    , 2, KMS_TEST_FLAG_INTERACTION_NEEDED)
KMS_TEST_LIST_END

KMS_TEST_MAIN
