
// Author    KMS - Martin Dubois, P.Eng.
// Copyright (C) 2020 KMS. All rights reserved.
// Product   HTML_Interface
// File      HILib/Utils.h

// CODE REVIEW 2020-07-11 KMS - Martin Dubois, P.Eng.

#pragma once

// ===== Includes ===========================================================
#include <HI/Types.h>

// Constants
/////////////////////////////////////////////////////////////////////////////

#define EOL "\n"

// Functions
/////////////////////////////////////////////////////////////////////////////

extern void Utl_MakeFileName(char * aOut, unsigned int aOutSize_byte, HI::FolderId aFolder, const char * aName, const char * aExtension);
extern void Utl_MakeFileName(char * aOut, unsigned int aOutSize_byte, const char * aFolder, const char * aName, const char * aExtension);

extern void Utl_ThrowError(const char * aType, unsigned int aCode, const char * aMessage, int aData = 0);

extern void Utl_VerifyReturn(int aRet);
extern void Utl_VerifyReturn(int aRet, unsigned int aMax);

extern void Utl_WriteCString(FILE * aOut, const char * aIn);
