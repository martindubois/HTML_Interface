
// Author    KMS - Martin Dubois, P.Eng.
// Copyright (C) 2020-2021 KMS. All rights reserved.
// Product   HTML_Interface
// File      HILib/OS.h

#pragma once

// Constants
/////////////////////////////////////////////////////////////////////////////

extern const char * OS_BINARIES[];

extern const char * OS_CHROME_EXE;
extern const char * OS_EDGE_EXE;

// Functions
/////////////////////////////////////////////////////////////////////////////

extern unsigned int OS_GetCurrentProcessId();

extern void OS_GetEnvironmentVariable(const char * aName, char * aOut, unsigned int aOutSize_byte);

extern void OS_GetModuleFileName(char * aOut, unsigned int aOutSize_byte);

extern void OS_GetTime(char * aOut, unsigned int aOutSize_byte);

extern void OS_CreateDirectory(const char * aName);

extern bool OS_ReadFile(const char * aFileName, void ** aOut, unsigned int * aOutSize_byte);

// ===== Open ===============================================================

extern void * OS_Open_Default(const char * aFileName);

// ===== Process ============================================================

extern void   OS_Process_Close    (void * aProcess);
extern void * OS_Process_Create   (const char * aExec, const char * aCommand);
extern bool   OS_Process_IsRunning(void * aProcess);
extern void   OS_Process_Terminate(void * aProcess);

// ===== Socket =============================================================

extern void OS_Socket_Cleanup  ();
extern void OS_Socket_Close    (SOCKET aSocket);
extern void OS_Socket_ErrorInfo();
extern void OS_Socket_Startup  ();

// ===== Start ==============================================================

extern bool OS_Start_Process(const char * aExec, const char * aCommand);
extern bool OS_Start_Default(const char * aFileName);
