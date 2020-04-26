
// Author     KMS - Martin Dubois, P.Eng.
// Copyright  (C) 2000 KMS. All rights reserved.
// Product    HTML_Interface
// File       HILib/Utils.cpp

// CODE REVIEW 2020-04-26 KMS - Martin Dubois, P.Eng.

// TEST COVERAGE 2020-04-26 KMS - Martin Dubois, P.Eng.

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>
#include <io.h>
#include <stdio.h>

// ===== C++ ================================================================
#include <exception>

// ===== Windows ============================================================
#include <Windows.h>

// ===== HILib ==============================================================
#include "Utils.h"

// Constants
/////////////////////////////////////////////////////////////////////////////

static const char * BINARIES[] =
{

#ifdef _DEBUG
    "\\x64\\Debug"  ,
    "\\Debug"       ,
#else
    "\\x64\\Release",
    "\\Release"     ,
#endif

    NULL
};

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
// aName      [---;R--]
// aExtension [---;R--]
void Utl_MakeFileName(char * aOut, unsigned int aOutSize_byte, HI::FolderId aFolder, const char * aName, const char * aExtension)
{
    assert(NULL           != aOut         );
    assert(             0 <  aOutSize_byte);
    assert(HI::FOLDER_QTY >  aFolder      );
    assert(NULL           != aName        );
    assert(NULL           != aExtension   );

    if (!sInitDone)
    {
        Initialize();
    }

    Utl_MakeFileName(aOut, aOutSize_byte, sFolders[aFolder], aName, aExtension);
}

// aOut       [---;-W-]
// aFolder    [---;R--]
// aName      [---;R--]
// aExtension [---;R--]
void Utl_MakeFileName(char * aOut, unsigned int aOutSize_byte, const char * aFolder, const char * aName, const char * aExtension)
{
    assert(NULL != aOut         );
    assert(   0 <  aOutSize_byte);
    assert(NULL != aName        );
    assert(NULL != aExtension   );

    memset(aOut, 0, aOutSize_byte);

    int lRet;

    if (NULL == aFolder)
    {
        // NOT TESTED Folder.Current
        lRet = sprintf_s(aOut, aOutSize_byte, "%s.%s", aName, aExtension);
    }
    else
    {
        lRet = sprintf_s(aOut, aOutSize_byte, "%s\\%s.%s", aFolder, aName, aExtension);
    }

    if (0 >= lRet)
    {
        // NOT TESTED Folder.Error
        //            sprintf_s fail
        throw std::exception("ERROR  sprintf_s( , , , ,  )  failed", lRet);
    }
}

void Utl_VerifyReturn(int aRet)
{
    if (0 >= aRet)
    {
        // NOT TESTED Document.Error
        //            VerifyReturn detect an error
        throw std::exception("ERROR  Write failed", aRet);
    }
}

void Utl_VerifyReturn(int aRet, unsigned int aMax)
{
    if (0 >= aRet)
    {
        // NOT TESTED Document.Error
        //            VerifyReturn detect an error
        throw std::exception("ERROR  Formating failed", aRet);
    }

    if (aMax <= static_cast<unsigned int>(aRet))
    {
        // NOT TESTED Document.Error
        //            VerifyReturn detect an error
        throw std::exception("ERROR  Formating failed", aRet);
    }
}

// Static functions
/////////////////////////////////////////////////////////////////////////////

void Init_Exec()
{
    char lFolder[1024];

    DWORD lSize_byte = GetModuleFileName(NULL, lFolder, sizeof(lFolder));
    if ((0 >= lSize_byte) || (sizeof(lFolder) <= lSize_byte))
    {
        // NOT TESTED Folder.Error
        //            GetModuleFileName fail
        throw std::exception("ERROR  GetModuleFileName( , ,  )  failed");
    }

    char * lPtr = strrchr(lFolder, '\\');
    if (NULL == lPtr)
    {
        // NOT TESTED Folder.Error
        //            strrchr fail
        throw std::exception("ERROR  strrchr( ,  )  failed");
    }

    *lPtr = '\0';

    strncpy_s(sFolder_Exec, lFolder, sizeof(sFolder_Exec) - 1);
}

void Init_Static()
{
    char lFolder[1024];

    strcpy_s(lFolder, sFolder_Exec);

    unsigned int i = 0;
    while (NULL != BINARIES[i])
    {
        char * lPtr = strstr(lFolder, BINARIES[i]);
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

    DWORD lSize_byte = GetEnvironmentVariable("TEMP", lTemp, sizeof(lTemp));
    if ((0 >= lSize_byte) || (sizeof(lTemp) <= lSize_byte))
    {
        // NOT TESTED Folder.Error
        //            GetEnvironmentVariable fail
        throw std::exception("ERROR  GetEnvironmentVariable( , ,  )  failed");
    }

    DWORD lProcessId = GetCurrentProcessId();

    int lRet = sprintf_s(sFolder_Temp, "%s\\HTML_Interface_%08x", lTemp, lProcessId);
    Utl_VerifyReturn(lRet, sizeof(sFolder_Temp));

    if (!CreateDirectory(sFolder_Temp, NULL))
    {
        // NOT TESTED Folder.Error
        //            CreateDirectory fail
        switch (GetLastError())
        {
        case ERROR_ALREADY_EXISTS: break;

        default:
            throw std::exception("ERROR  CreateDirectory( ,  )  failed");
        }
    }
}

void Initialize()
{
    assert(!sInitDone);

    Init_Exec  ();
    Init_Static();
    Init_Temp  ();

    sInitDone = true;
}
