
// Author    KMS - Martin Dubois, P.Eng.
// Copyright (C) 2020-2021 KMS. All rights reserved.
// Product   HTML_Interface
// File      HILib_Test/Server.h

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== Import/Includes ====================================================
#include <KmsTest.h>

// ===== Includes ===========================================================
#include <HI/Browser.h>
#include <HI/Server.h>

// Constants
/////////////////////////////////////////////////////////////////////////////

static const char * ARG_0[] = { "HILib_Test.exe", "Server.Debug=true", "Useless" };

// Needed class
/////////////////////////////////////////////////////////////////////////////

class Processor : public HI::Server::IRequestProcessor
{

public:

    // ===== HI::Server::IRequestProcessor ==================================

    virtual void ProcessGet (HI::Server * aServer, unsigned int aCode, const char * aRequest);
    virtual void ProcessPost(HI::Server * aServer, unsigned int aCode, const char * aRequest);

};

void Processor::ProcessGet(HI::Server * aServer, unsigned int aCode, const char * aRequest)
{
    assert(NULL != aServer );
    assert(NULL != aRequest);

    aServer->Stop();
}

void Processor::ProcessPost(HI::Server * aServer, unsigned int aCode, const char * aRequest)
{
    assert(NULL != aServer);
    assert(NULL != aRequest);

}

// Tests
/////////////////////////////////////////////////////////////////////////////

KMS_TEST_BEGIN(Server_Base)

    HI::Browser lB0;
    Processor   lP0;
    HI::Server  lS0;

    lS0.SetDebug(true);

    lS0.ParseArguments(3, ARG_0);

    lS0.AddProcessor(0, "Tests/Stop", &lP0);

    lS0.Start();

    lB0.Open(&lS0, "Tests/AutoClose");

    lB0.Close();

KMS_TEST_END

KMS_TEST_BEGIN(Server_SetupB)

    HI::Browser lB0;
    Processor   lP0;
    HI::Server  lS0;

    lS0.SetDebug(true);

    lS0.AddProcessor(0, "Tests/Stop", &lP0);

    lS0.Start();

    lB0.Open(&lS0, "Tests/Server_SetupB");

    lS0.Run(&lB0);

    lB0.Close();

KMS_TEST_END
