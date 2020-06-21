
// Author     KMS - Martin Dubois, P.Eng.
// Copyright  (C) 2000 KMS. All rights reserved.
// Product    HTML_Interface
// File       HILib/OS_Windows.cpp

// CODE REVIEW 2020-06-21 KMS - Martin Dubois, P.Eng.

// ===== C ==================================================================
#include <assert.h>
#include <stdio.h>
#include <time.h>

// ===== C++ ================================================================
#include <exception>

// ===== Windows ============================================================
#include <Windows.h>

// ===== HILib ==============================================================
#include "OS.h"
#include "Utils.h"

// Constants
/////////////////////////////////////////////////////////////////////////////

#define INVALID_PROCESS reinterpret_cast<void *>(1)

const char * OS_BINARIES[] =
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

const char * OS_CHROME_EXE = "C:\\Program Files (x86)\\Google\\Chrome\\Application\\chrome.exe";

// Static variable
/////////////////////////////////////////////////////////////////////////////

static unsigned int sCount;

// Static function declarations
/////////////////////////////////////////////////////////////////////////////

static void CloseProcessInfo(PROCESS_INFORMATION * aPI);

// Functions
/////////////////////////////////////////////////////////////////////////////

unsigned int OS_GetCurrentProcessId()
{
    return GetCurrentProcessId();
}

// aOut [---;-W-]
void OS_GetEnvironmentVariable(const char * aName, char * aOut, unsigned int aOutSize_byte)
{
    assert(NULL != aName        );
    assert(NULL != aOut         );
    assert(   0 <  aOutSize_byte);

    memset(aOut, 0, aOutSize_byte);

    DWORD lSize_byte = GetEnvironmentVariable(aName, aOut, aOutSize_byte);
    if ((0 >= lSize_byte) || (aOutSize_byte <= lSize_byte))
    {
        // NOT TESTED OS.Environment.Error
        //            GetEnvironmentVariable( , ,  ) fails.
        Utl_ThrowError("ERROR", __LINE__, "GetEnvironmentVariable( , ,  )  failed");
    }
}

// aOut [---;-W-]
void OS_GetModuleFileName(char * aOut, unsigned int aOutSize_byte)
{
    assert(NULL != aOut         );
    assert(   0 <  aOutSize_byte);

    memset(aOut, 0, aOutSize_byte);

    DWORD lSize_byte = GetModuleFileName(NULL, aOut, aOutSize_byte);
    if ((0 >= lSize_byte) || (aOutSize_byte <= lSize_byte))
    {
        // NOT TESTED OS.Module.Error
        //            GetModuleFileName( , ,  ) fails.
        Utl_ThrowError("ERROR", __LINE__, "GetModuleFileName( , ,  )  failed");
    }
}

// TESTED OS.Time
//        Get current time in ASCII format (HILib_Test.exe group 2)

// aOut [---;-W-]
void OS_GetTime(char * aOut, unsigned int aOutSize_byte)
{
    assert(NULL != aOut         );
    assert(0    <  aOutSize_byte);

    memset(aOut, 0, sizeof(aOutSize_byte));

    __int64 lT;

    _time64(&lT);

    struct tm lTM;

    errno_t lErr = _gmtime64_s(&lTM, &lT);
    assert(0 == lErr);

    lErr = asctime_s(aOut, aOutSize_byte, &lTM);
    assert(0 == lErr);
}

void OS_CreateDirectory(const char * aName)
{
    assert(NULL != aName);

    if (!CreateDirectory(aName, NULL))
    {
        // NOT TESTED OS.Directory.Error
        //            CreateDirectory( ,  ) fails.
        switch (GetLastError())
        {
        case ERROR_ALREADY_EXISTS: break;

        default:
            Utl_ThrowError("ERROR", __LINE__, "CreateDirectory( ,  )  failed");
        }
    }
}

// TESTED OS.File
//        Read file in specialy allocated memory (HILib_Test.exe group 2)

// aOut          [---;-W-] The caller must delete the buffer.
// aOutSize_byte [---;-W-]
bool OS_ReadFile(const char * aFileName, void ** aOut, unsigned int * aOutSize_byte)
{
    assert(NULL != aFileName    );
    assert(NULL != aOut         );
    assert(NULL != aOutSize_byte);

    (*aOut         ) = NULL;
    (*aOutSize_byte) =    0;

    bool lResult = false;

    HANDLE lFile = CreateFile(aFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    if (INVALID_HANDLE_VALUE != lFile)
    {
        (*aOutSize_byte) = GetFileSize(lFile, NULL);
        if ((INVALID_FILE_SIZE != (*aOutSize_byte)) && (0 < (*aOutSize_byte)))
        {
            unsigned char * lData = new unsigned char [(*aOutSize_byte)];
            assert(NULL != lData);

            DWORD lInfo_byte;

            if (::ReadFile(lFile, lData, *aOutSize_byte, &lInfo_byte, NULL) && ((*aOutSize_byte) == lInfo_byte))
            {
                (*aOut) = lData;
                lResult = true;
            }
            else
            {
                // NOT TESTED OS.File.Error
                //            ReadFile( , , , ,  ) fails.
                delete[] lData;
            }
        }

        BOOL lRetB = CloseHandle(lFile);
        assert(lRetB);
    }

    return lResult;
}

// ===== Open ===============================================================

void * OS_Open_Default(const char * aFileName)
{
    assert(NULL != aFileName);

    SHELLEXECUTEINFO lSEI;

    memset(&lSEI, 0, sizeof(lSEI));

    lSEI.cbSize = sizeof(lSEI)           ;
    lSEI.fMask  = SEE_MASK_NOCLOSEPROCESS;
    lSEI.lpFile = aFileName              ;
    lSEI.lpVerb = "open"                 ;
    lSEI.nShow  = SW_SHOWDEFAULT         ;

    if (!ShellExecuteEx(&lSEI))
    {
        return NULL;
    }

    if (NULL == lSEI.hProcess)
    {
        return INVALID_PROCESS;
    }

    return lSEI.hProcess;
}

// ===== Process ============================================================

// aProcess [D--;---;
void OS_Process_Close(void * aProcess)
{
    assert(NULL != aProcess);

    if (INVALID_PROCESS != aProcess)
    {
        BOOL lRetB = CloseHandle(aProcess);
        assert(lRetB);
    }
}

void * OS_Process_Create(const char * aExec, const char * aCommand)
{
    assert(NULL != aExec   );
    assert(NULL != aCommand);

    PROCESS_INFORMATION lPI;
    STARTUPINFO         lSI;

    memset(&lPI, 0, sizeof(lPI));
    memset(&lSI, 0, sizeof(lSI));

    lSI.cb = sizeof(lSI);

    BOOL lRetB = CreateProcess(aExec, const_cast<char *>(aCommand), NULL, NULL, FALSE, 0, NULL, NULL, &lSI, &lPI);
    if (!lRetB)
    {
        return NULL;
    }

    lRetB = CloseHandle(lPI.hThread);
    assert(lRetB);

    return lPI.hProcess;
}

void OS_Process_Terminate(void * aProcess)
{
    assert(NULL != aProcess);

    if (INVALID_PROCESS != aProcess)
    {
        BOOL lRet1 = TerminateProcess(aProcess, 0);

        BOOL lRet2 = CloseHandle(aProcess);
        assert(lRet2);

        if (!lRet1)
        {
            Utl_ThrowError("ERROR", __LINE__, "TerminateProcess(  )  failed");
        }
    }
}

// ===== Socket =============================================================

void OS_Socket_Cleanup()
{
    sCount--;
    if (0 == sCount)
    {
        int lRet = WSACleanup();
        assert(0 == lRet);
    }
}

void OS_Socket_Close(SOCKET aSocket)
{
    assert(INVALID_SOCKET != aSocket);

    int lRet = closesocket(aSocket);
    assert(0 == lRet);
}

void OS_Socket_ErrorInfo()
{
    DWORD lLastError = WSAGetLastError();

    const char * lErrorName;

    switch (lLastError)
    {
    case WSANOTINITIALISED: lErrorName = "WASNOTINITIALISED"; break;
    case WSAENETDOWN      : lErrorName = "WSAENETDOWN"      ; break;
    case WSAEFAULT        : lErrorName = "WSAEFAULT"        ; break;
    case WSAENOTCONN      : lErrorName = "WSAENOTCONN"      ; break;
    case WSAEINTR         : lErrorName = "WSAEINTR"         ; break;
    case WSAEINPROGRESS   : lErrorName = "WSAEINPROGRESS"   ; break;
    case WSAENETRESET     : lErrorName = "WSAENETRESET"     ; break;
    case WSAENOTSOCK      : lErrorName = "WSAENOTSOCK"      ; break;
    case WSAETIMEDOUT     : lErrorName = "WSAETIMEDOUT"     ; break;

    default: lErrorName = "Unknown";
    }

    printf("    0x%08x - %s\n", lLastError, lErrorName);
}

void OS_Socket_Startup()
{
    sCount++;
    if (1 == sCount)
    {
        WSADATA lData;

        int lRet = WSAStartup(MAKEWORD(2, 2), &lData);
        if (0 != lRet)
        {
            // NOT TESTED  OS.Socket.Error
            //             WSAStartup( ,  ) fail
            Utl_ThrowError("ERROR", __LINE__, "WSAStartup( ,  )  failed", lRet);
        }
    }
}

// ===== Start ==============================================================

// TESTED OS.Start
//        Start a process (HILib_Test.exe group 1)

bool OS_Start_Process(const char * aExec, const char * aCommand)
{
    assert(NULL != aExec   );
    assert(NULL != aCommand);

    PROCESS_INFORMATION lPI;
    STARTUPINFO         lSI;

    memset(&lPI, 0, sizeof(lPI));
    memset(&lSI, 0, sizeof(lSI));

    lSI.cb = sizeof(lSI);

    BOOL lRetB = CreateProcess(aExec, const_cast<char *>(aCommand), NULL, NULL, FALSE, 0, NULL, NULL, &lSI, &lPI);
    if (lRetB)
    {
        CloseProcessInfo(&lPI);
    }

    return lRetB;
}

// NOT TESTED OS.Start
//            Start the OS default browser.

bool OS_Start_Default(const char * aFileName)
{
    assert(NULL != aFileName);

    HINSTANCE lRet = ShellExecute(NULL, "open", aFileName, NULL, NULL, SW_SHOWDEFAULT);
    return (32 < reinterpret_cast<__int64>(lRet));
}

// Static functions
/////////////////////////////////////////////////////////////////////////////

// aPI [---;R--]
void CloseProcessInfo(PROCESS_INFORMATION * aPI)
{
    assert(NULL != aPI);

    BOOL lRetB = CloseHandle(aPI->hProcess);
    assert(lRetB);

    lRetB = CloseHandle(aPI->hThread);
    assert(lRetB);
}
