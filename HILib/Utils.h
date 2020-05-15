
// Author     KMS - Martin Dubois, P.Eng.
// Copyright  (C) 2020 KMS. All rights reserved.
// Product    HTML_Interface
// File       HILib/Utils.h

#pragma once

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== Includes ===========================================================
#include <HI/Types.h>

// Functions
/////////////////////////////////////////////////////////////////////////////

extern void Utl_MakeFileName(char * aOut, unsigned int aOutSize_byte, HI::FolderId aFolder, const char * aName, const char * aExtension);
extern void Utl_MakeFileName(char * aOut, unsigned int aOutSize_byte, const char * aFolder, const char * aName, const char * aExtension);

extern void Utl_VerifyReturn(int aRet);
extern void Utl_VerifyReturn(int aRet, unsigned int aMax);

