
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

KMS_TEST_GROUP_LIST_BEGIN
    KMS_TEST_GROUP_LIST_ENTRY("Base")
KMS_TEST_GROUP_LIST_END

extern int Browser_Base      ();
extern int HTML_Document_Base();

KMS_TEST_LIST_BEGIN
    KMS_TEST_LIST_ENTRY(Browser_Base      , "Browser - Base"      , 0, 0)
    KMS_TEST_LIST_ENTRY(HTML_Document_Base, "HTML_Document - Base", 0, 0)
KMS_TEST_LIST_END

KMS_TEST_MAIN
