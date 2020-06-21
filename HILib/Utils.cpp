
// Author     KMS - Martin Dubois, P.Eng.
// Copyright  (C) 2000 KMS. All rights reserved.
// Product    HTML_Interface
// File       HILib/Utils.cpp

// CODE REVIEW 2020-06-21 KMS - Martin Dubois, P.Eng.

// TEST COVERAGE 2020-06-21 KMS - Martin Dubois, P.Eng.

// ===== C ==================================================================
#include <assert.h>
#include <io.h>
#include <stdio.h>

// ===== C++ ================================================================
#include <exception>

// ===== Windows ============================================================
#include <Windows.h>

// ===== HILib ==============================================================
#include "OS.h"

#include "Utils.h"

// Static variable
/////////////////////////////////////////////////////////////////////////////

static bool sInitDone;

static char sFolder_Exec  [1024];
static char sFolder_Static[1024];
static char sFolder_Temp  [1024];

static const char * sFolders[HI::FOLDER_QTY] = { sFolder_Exec, sFolder_Static, sFolder_Temp, NULL };

// Static function declarations
/////////////////////////////////////////////////////////////////////////////

static void Init_Exec  ();
static void Init_Static();
static void Init_Temp  ();

static void Initialize();

// Functions
/////////////////////////////////////////////////////////////////////////////

// aOut       [---;-W-]
// aExtension [--O;R--]
void Utl_MakeFileName(char * aOut, unsigned int aOutSize_byte, HI::FolderId aFolder, const char * aName, const char * aExtension)
{
    assert(NULL           != aOut         );
    assert(             0 <  aOutSize_byte);
    assert(HI::FOLDER_QTY >  aFolder      );
    assert(NULL           != aName        );

    if (!sInitDone)
    {
        Initialize();
    }

    Utl_MakeFileName(aOut, aOutSize_byte, sFolders[aFolder], aName, aExtension);
}

// aOut       [---;-W-]
// aName      [---;R--]
// aExtension [--O;R--]
void Utl_MakeFileName(char * aOut, unsigned int aOutSize_byte, const char * aFolder, const char * aName, const char * aExtension)
{
    assert(NULL != aOut         );
    assert(   0 <  aOutSize_byte);
    assert(NULL != aName        );

    memset(aOut, 0, aOutSize_byte);

    int lRet;

    if (NULL == aFolder)
    {
        if (NULL == aExtension)
        {
            // NOT TESTED Utils.Folder
            //            Retrieve filename relative to the current folder
            //            without extension.
            lRet = sprintf_s(aOut, aOutSize_byte, "%s", aName);
        }
        else
        {
            lRet = sprintf_s(aOut, aOutSize_byte, "%s.%s", aName, aExtension);
        }
    }
    else
    {
        if (NULL == aExtension)
        {
            // NOT TESTED Utils.Folder
            //            Retrieve filename without extension.
            lRet = sprintf_s(aOut, aOutSize_byte, "%s\\%s", aFolder, aName);
        }
        else
        {
            lRet = sprintf_s(aOut, aOutSize_byte, "%s\\%s.%s", aFolder, aName, aExtension);
        }
    }

    if (0 >= lRet)
    {
        // NOT TESTED Utils.Folder.Error
        //            sprintf_s( , , ,  ) or sprintf_s( , , , ,  ) fails.
        Utl_ThrowError("ERROR", __LINE__, "sprintf_s failed", lRet);
    }
}

void Utl_ThrowError(const char * aType, unsigned int aCode, const char * aMessage, int aData)
{
    assert(NULL != aType   );
    assert(   0 != aCode   );
    assert(NULL != aMessage);

    char lWhat[128];

    sprintf_s(lWhat, "%s  %u  %s", aType, aCode, aMessage);

    throw std::exception(lWhat, aData);
}

// NOT TESTED Utils.Verify
//            Utl_VerifyReturn detects an error.

void Utl_VerifyReturn(int aRet)
{
    if (0 >= aRet)
    {
        Utl_ThrowError("ERROR", __LINE__, "Write failed", aRet);
    }
}

void Utl_VerifyReturn(int aRet, unsigned int aMax)
{
    if (0 >= aRet)
    {
        Utl_ThrowError("ERROR", __LINE__, "Formating failed", aRet);
    }

    if (aMax <= static_cast<unsigned int>(aRet))
    {
        Utl_ThrowError("ERROR", __LINE__, "Formating failed", aRet);
    }
}

// Static functions
/////////////////////////////////////////////////////////////////////////////

void Init_Exec()
{
    char lFolder[1024];

    OS_GetModuleFileName(lFolder, sizeof(lFolder));

    char * lPtr = strrchr(lFolder, '\\');
    if (NULL == lPtr)
    {
        // NOT TESTED Utils.Folder.Error
        //            strrchr( ,  ) fails.
        Utl_ThrowError("ERROR", __LINE__, "strrchr( ,  )  failed");
    }

    *lPtr = '\0';

    strncpy_s(sFolder_Exec, lFolder, sizeof(sFolder_Exec) - 1);
}

void Init_Static()
{
    char lFolder[1024];

    strcpy_s(lFolder, sFolder_Exec);

    unsigned int i = 0;
    while (NULL != OS_BINARIES[i])
    {
        char * lPtr = strstr(lFolder, OS_BINARIES[i]);
        if (NULL != lPtr)
        {
            *lPtr = '\0';
            break;
        }

        i++;
    }

    int lRet = sprintf_s(sFolder_Static, "%s\\Static", lFolder);
    Utl_VerifyReturn(lRet, sizeof(sFolder_Static));
}

void Init_Temp()
{
    char lTemp[1000];

    OS_GetEnvironmentVariable("TEMP", lTemp, sizeof(lTemp));

    unsigned int lProcessId = OS_GetCurrentProcessId();

    int lRet = sprintf_s(sFolder_Temp, "%s\\HTML_Interface_%08x", lTemp, lProcessId);
    Utl_VerifyReturn(lRet, sizeof(sFolder_Temp));

    OS_CreateDirectory(sFolder_Temp);
}

void Initialize()
{
    assert(!sInitDone);

    Init_Exec  ();
    Init_Static();
    Init_Temp  ();

    sInitDone = true;
}
