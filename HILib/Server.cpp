
// Author     KMS - Martin Dubois, P.Eng.
// Copyright  (C) 2020 KMS. All rights reserved.
// Procuct    HTML_Interface
// File       HILib/Server.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>
#include <stdio.h>

// ===== C++ ================================================================
#include <exception>

// ===== Windows ============================================================
#include <winsock2.h>
#include <WS2tcpip.h>

// ===== Includes ===========================================================
#include <HI/Server.h>

// ===== HILib ==============================================================
#include "HTTP.h"
#include "OS.h"
#include "Utils.h"

// Constants
/////////////////////////////////////////////////////////////////////////////

#define MAX_REQUEST_SIZE_byte (1024)

namespace HI
{

    // Public
    /////////////////////////////////////////////////////////////////////////

    Server::Server() : mConnection(INVALID_SOCKET), mSocket(INVALID_SOCKET), mState(STATE_INVALID)
    {
        OS_Socket_Startup();

        memset(&mBinded, 0, sizeof(mBinded));
        memset(&mLocal , 0, sizeof(mLocal ));

        mLocal.sin_family = AF_INET;

        int lRet = inet_pton(AF_INET, "127.0.0.1", &mLocal.sin_addr.S_un.S_addr);
        assert(1 == lRet);

        mState = STATE_INIT;
    }

    Server::~Server()
    {
        if (INVALID_SOCKET != mConnection)
        {
            CloseConnection();
        }

        if (INVALID_SOCKET != mSocket)
        {
            CloseSocket();
        }

        OS_Socket_Cleanup();
    }

    // aProcessor [---;RW-]
    void Server::AddProcessor(unsigned int aCode, const char * aName, IRequestProcessor * aProcessor)
    {
        assert(NULL != aName     );
        assert(NULL != aProcessor);

        mProcessors.push_back(Processor(aCode, aName, aProcessor));
    }

    uint16_t Server::GetPort() const
    {
        assert(0 != mBinded.sin_port);

        return ntohs(mBinded.sin_port);
    }

    void Server::SetDebug(bool aDebug)
    {
        mFlags.mDebug = aDebug;

        Trace("Server::SetDebug( true )");
    }

    // aVector [---;R--] [---;R--]
    void Server::ParseArguments(int aCount, const char ** aVector)
    {
        assert(   1 <= aCount );
        assert(NULL != aVector);

        for (int i = 1; i < aCount; i++)
        {
            assert(NULL != aVector[i]);

            ParseAssignation(aVector[i]);
        }
    }

    bool Server::ParseAssignation(const char * aAssignation)
    {
        assert(NULL != aAssignation);

        if (0 == strcmp("Server.Debug=false", aAssignation)) { mFlags.mDebug = false; return false; }
        if (0 == strcmp("Server.Debug=true" , aAssignation)) { mFlags.mDebug = true ; return true ; }

        return false;
    }

    void Server::Run()
    {
        assert(INVALID_SOCKET != mSocket);
        assert(STATE_STARTED  == mState );

        mState = STATE_RUNNING;

        do
        {
            assert(INVALID_SOCKET == mConnection);

            sockaddr_in lClient;
            int         lSize_byte = sizeof(lClient);

            memset(&lClient, 0, sizeof(lClient));

            mConnection = accept(mSocket, reinterpret_cast<sockaddr *>(&lClient), &lSize_byte);
            if (INVALID_SOCKET == mConnection)
            {
                // NOT TESTED  Server.Error
                //             accept( , ,  ) fails.
                ReportError("ERROR  112  accept( , ,  )  failed");
            }
            
            ReceiveAndProcessRequest();

            CloseConnection();
        }
        while (STATE_RUNNING == mState);

        if (STATE_STOPPING == mState)
        {
            mState = STATE_STOPPED;
        }
    }

    // aExtension [--O:R--]
    void Server::SendFile(FolderId aFolder, const char * aName, const char * aExtension)
    {
        assert(FOLDER_QTY >  aFolder);
        assert(NULL       != aName  );

        char lFileName[1024];

        Utl_MakeFileName(lFileName, sizeof(lFileName), aFolder, aName, aExtension);

        SendFile(lFileName);
    }

    void Server::Start()
    {
        assert(INVALID_SOCKET == mSocket);
        assert(STATE_INIT     == mState );

        memset(&mBinded, 0, sizeof(mBinded));

        mSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (INVALID_SOCKET == mSocket)
        {
            // NOT TESTED  Server.Error
            //             socket( , ,  ) fails
            ReportError("ERROR  152  socket( , ,  )  failed");
        }

        int lRet = bind(mSocket, reinterpret_cast<sockaddr *>(&mLocal), sizeof(mLocal));
        if (0 != lRet)
        {
            // NOT TESTED  Server.Error
            //             bind( , ,  ) fails.
            ReportError("ERROR  160  bind( , ,  )  failed", lRet);
        }

        int lSize_byte = sizeof(mBinded);

        lRet = getsockname(mSocket, reinterpret_cast<sockaddr *>(&mBinded), &lSize_byte);
        if (0 != lRet)
        {
            // NOT TESTED  Server.Error
            //             getsockname( , ,  ) fails.
            ReportError("ERROR  170  getsockname( , ,  )  failed", lRet);
        }

        lRet = listen(mSocket, 1);
        if (0 != lRet)
        {
            // NOT TESTED  Server.Error
            //             listen( ,  ) fails.
            ReportError("ERROR  178  listen( ,  )  failed", lRet);
        }

        mState = STATE_STARTED;
    }

    void Server::Stop()
    {
        Trace("Stop()");

        assert(STATE_RUNNING == mState);

        mState = STATE_STOPPING;
    }

    // Private
    /////////////////////////////////////////////////////////////////////////

    Server::Processor::Processor(const Server::Processor & aIn) : mCode(aIn.mCode), mName(aIn.mName), mProcessor(aIn.mProcessor)
    {
        assert(NULL != (&aIn));
    }

    Server::Processor::Processor(unsigned int aCode, const char * aName, IRequestProcessor * aProcessor) : mCode(aCode), mName(aName), mProcessor(aProcessor)
    {
        assert(NULL != aName     );
        assert(NULL != aProcessor);
    }

    bool Server::Processor::Match(const char * aRequest)
    {
        assert(NULL != aRequest);

        assert(0 < mName.size());

        return (0 == strncmp(mName.c_str(), aRequest, mName.size()));
    }

    void Server::Processor::ProcessGet(Server * aServer, const char * aRequest)
    {
        assert(NULL != aServer );
        assert(NULL != aRequest);

        assert(0 < mName.size());

        mProcessor->ProcessGet(aServer, mCode, aRequest + mName.size());
    }

    void Server::Processor::ProcessPost(Server * aServer, const char * aRequest)
    {
        assert(NULL != aServer );
        assert(NULL != aRequest);

        assert(0 < mName.size());

        mProcessor->ProcessPost(aServer, mCode, aRequest + mName.size());
    }

    void Server::CloseConnection()
    {
        assert(INVALID_SOCKET != mConnection);

        OS_Socket_Close(mConnection);

        mConnection = INVALID_SOCKET;
    }

    void Server::CloseSocket()
    {
        assert(INVALID_SOCKET != mSocket);

        OS_Socket_Close(mSocket);

        mSocket = INVALID_SOCKET;
    }

    void Server::ProcessGet(const char * aRequest)
    {
        assert(NULL != aRequest);

        for (ProcessorList::iterator lIt = mProcessors.begin(); lIt != mProcessors.end(); lIt++)
        {
            if (lIt->Match(aRequest))
            {
                lIt->ProcessGet(this, aRequest);
                return;
            }
        }

        SendFile(FOLDER_STATIC, aRequest, NULL);
    }

    void Server::ProcessPost(const char * aRequest)
    {
        assert(NULL != aRequest);

        for (ProcessorList::iterator lIt = mProcessors.begin(); lIt != mProcessors.end(); lIt++)
        {
            if (lIt->Match(aRequest))
            {
                lIt->ProcessPost(this, aRequest);
                return;
            }
        }
    }

    void Server::ProcessRequest(const char * aRequest)
    {
        assert(NULL != aRequest);

        if (mFlags.mDebug)
        {
            printf("Server::ProcessRequest( \"%s\" )\n", aRequest);
        }

        char lRequest[MAX_REQUEST_SIZE_byte];

        if (1 == sscanf_s(aRequest, "GET /%s", lRequest, static_cast<unsigned int>(sizeof(lRequest))))
        {
            ProcessGet(lRequest);
        }
        else if (1 == sscanf_s(aRequest, "POST /%s", lRequest, static_cast<unsigned int>(sizeof(lRequest))))
        {
            ProcessPost(lRequest);
        }
        else
        {
            // NOT TESTED  Server.Error
            //             Invalid request
            ReportError("ERROR  299  Invalid request");
        }
    }

    void Server::ReceiveAndProcessRequest()
    {
        assert(INVALID_SOCKET != mConnection);

        char lRequest[MAX_REQUEST_SIZE_byte];

        memset(&lRequest, 0, sizeof(lRequest));

        int lRet = recv(mConnection, lRequest, sizeof(lRequest) - 1, 0);
        if ((0 > lRet) || (sizeof(lRequest) < lRet))
        {
            // NOT TESTED  Server.Error
            //             recv( , , ,  ) fails.
            ReportError("ERROR  316  recv( , , ,  )  failed", lRet);
        }

        ProcessRequest(lRequest);
    }

    void Server::ReportError(const char * aMessage, int aCode)
    {
        assert(NULL != aMessage);

        if (mFlags.mDebug)
        {
            printf("Server::ReportError( \"%s\", %d )\n", aMessage, aCode);

            OS_Socket_ErrorInfo();
        }

        mState = STATE_ERROR;

        throw std::exception(aMessage, aCode);
    }

    void Server::SendData(const void * aData, unsigned int aDataSize_byte)
    {
        assert(NULL != aData         );
        assert(   0 <  aDataSize_byte);

        int lRet = send(mConnection, reinterpret_cast<const char *>(aData), aDataSize_byte, 0);
        if (aDataSize_byte != lRet)
        {
            // NOT TESTED  Server.Error
            //             send( , , ,  ) fails.
            throw std::exception("ERROR  348  send( , , ,  )  failed", lRet);
        }
    }

    void Server::SendErrorNotFound()
    {
        SendFile(HTTP_ERROR_NOT_FOUND, HTTP_ERROR_NOT_FOUND_STRING, FOLDER_STATIC, "ErrorNotFound");
    }

    void Server::SendFile(const char * aFileName)
    {
        assert(NULL != aFileName);

        void       * lData;
        unsigned int lDataSize_byte;

        if (OS_ReadFile(aFileName, &lData, &lDataSize_byte))
        {
            SendHeader(HTTP_OK, HTTP_OK_STRING, lDataSize_byte);

            SendData(lData, lDataSize_byte);

            delete[] lData;
        }
        else
        {
            SendErrorNotFound();
        }
    }

    void Server::SendFile(unsigned int aStatusCode, const char * aStatusName, FolderId aFolder, const char * aName)
    {
        assert(NULL       != aStatusName);
        assert(FOLDER_QTY >  aFolder    );
        assert(NULL       != aName      );

        char lFileName[1024];

        Utl_MakeFileName(lFileName, sizeof(lFileName), aFolder, aName, "html");

        SendFile(aStatusCode, aStatusName, lFileName);
    }

    void Server::SendFile(unsigned int aStatusCode, const char * aStatusName, const char * aFileName)
    {
        assert(NULL != aStatusName);
        assert(NULL != aFileName  );

        if (mFlags.mDebug)
        {
            printf("Server::SendHeader( %u, \"%s\", \"%s\" )\n", aStatusCode, aStatusName, aFileName);
        }

        void       * lData;
        unsigned int lDataSize_byte;

        if (OS_ReadFile(aFileName, &lData, &lDataSize_byte))
        {
            SendHeader(aStatusCode, aStatusName, lDataSize_byte);

            SendData(lData, lDataSize_byte);

            delete[] lData;
        }
        else
        {
            if (HTTP_ERROR_NOT_FOUND == aStatusCode)
            {
                SendHeader(aStatusCode, aStatusName, 0);
            }
            else
            {
                SendErrorNotFound();
            }
        }
    }

    void Server::SendHeader(unsigned int aStatusCode, const char * aStatusName, unsigned int aDataSize_byte)
    {
        assert(NULL != aStatusName);

        if (mFlags.mDebug)
        {
            printf("Server::SendHeader( %u, \"%s\", %u bytes )\n", aStatusCode, aStatusName, aDataSize_byte);
        }

        char lTimeStr[32];

        OS_GetTime(lTimeStr, sizeof(lTimeStr));

        char lHeader[256];

        sprintf_s(lHeader,
            "HTTP/1.1 %u %s\r\n"
            "Date: %s GMT\r\n"
            "Server: HTML_Interface\r\n"
            "Content-Length: %u\r\n"
            "Content-Type: text/html\r\n"
            "\r\n",
            aStatusCode, aStatusName,
            lTimeStr,
            aDataSize_byte);
        
        SendData(lHeader, strlen(lHeader));
    }

    void Server::Trace(const char * aMessage)
    {
        assert(NULL != aMessage);

        if (mFlags.mDebug)
        {
            printf("%s\n", aMessage);
        }
    }
    
}
