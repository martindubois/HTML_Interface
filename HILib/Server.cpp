
// Author    KMS - Martin Dubois, P.Eng.
// Copyright (C) 2020-2021 KMS. All rights reserved.
// License   https://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
// Procuct   HTML_Interface
// File      HILib/Server.cpp

#include "Component.h"

// ===== C ==================================================================
#include <stdio.h>

// ===== C++ ================================================================
#include <exception>

// ===== Windows ============================================================
#include <winsock2.h>
#include <WS2tcpip.h>

// ===== Includes ===========================================================
#include <HI/Browser.h>
#include <HI/Server.h>
#include <HTTP.h>

// ===== HILib ==============================================================
#include "Errors.h"
#include "OS.h"
#include "Utils.h"

// Constants
/////////////////////////////////////////////////////////////////////////////

#define MAX_REQUEST_SIZE_byte (1024)

namespace HI
{

    // Public
    /////////////////////////////////////////////////////////////////////////

    // TODO HILib.Server
    //      Ass many other CONTENT_TYPE_ constants
    const char* Server::CONTENT_TYPE_HTML = "text/html";
    const char* Server::CONTENT_TYPE_JSON = "application/json";

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

    uint16_t Server::GetLocalPort() const
    {
        assert(0 != mBinded.sin_port);

        return ntohs(mBinded.sin_port);
    }

    void Server::SetLocalPort(uint16_t aPort)
    {
        mLocal.sin_port = htons(aPort);
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

    void Server::Run(Browser * aBrowser)
    {
        assert(INVALID_SOCKET != mSocket);
        assert(STATE_STARTED  == mState );

        mState = STATE_RUNNING;

        TIMEVAL lTimeout;

        lTimeout.tv_sec = 1;
        lTimeout.tv_usec = 0;

        do
        {
            assert(INVALID_SOCKET == mConnection);

            fd_set lReadSet;

            FD_ZERO(&lReadSet);
            FD_SET(mSocket, &lReadSet);

            int lRet = select(1, &lReadSet, NULL, NULL, &lTimeout);
            switch (lRet)
            {
            case 0:
                if ((NULL != aBrowser) && (!aBrowser->IsOpen()))
                {
                    Stop();
                }
                break;

            case 1:
                sockaddr_in lClient;
                int         lSize_byte;
                
                lSize_byte = sizeof(lClient);

                memset(&lClient, 0, sizeof(lClient));

                mConnection = accept(mSocket, reinterpret_cast<sockaddr*>(&lClient), &lSize_byte);
                if (INVALID_SOCKET == mConnection)
                {
                    ReportError(ERROR_112 "(NOT TESTED)");
                }

                ReceiveAndProcessRequest();

                CloseConnection();
                break;

            case SOCKET_ERROR: ReportError(ERROR_000 " (NOT TESTED)");

            default: assert(false);
            }
        }
        while (STATE_RUNNING == mState);

        if (STATE_STOPPING == mState)
        {
            mState = STATE_STOPPED;
        }
    }

    void Server::SendResponse(unsigned int aStatusCode, const char* aStatusName, const char* aContentType, unsigned int aDataSize_byte, const void* aData)
    {
        SendHeader(aStatusCode, aStatusName, aContentType, aDataSize_byte);

        if (0 < aDataSize_byte)
        {
            SendData(aData, aDataSize_byte);
        }
    }

    // aExtension [--O:R--]
    void Server::SendResponse(FolderId aFolder, const char * aName, const char * aExtension)
    {
        assert(FOLDER_QTY >  aFolder);
        assert(NULL       != aName  );

        char lFileName[1024];

        Utl_MakeFileName(lFileName, sizeof(lFileName), aFolder, aName, aExtension);

        // TODO HILib.Server
        //      Use a content type based on the extension
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
            ReportError(ERROR_152 " (NOT TESTED)");
        }

        int lRet = bind(mSocket, reinterpret_cast<sockaddr *>(&mLocal), sizeof(mLocal));
        if (0 != lRet)
        {
            ReportError(ERROR_160 " (NOT TESTED)", lRet);
        }

        int lSize_byte = sizeof(mBinded);

        lRet = getsockname(mSocket, reinterpret_cast<sockaddr *>(&mBinded), &lSize_byte);
        if (0 != lRet)
        {
            ReportError(ERROR_170 " (NOT TESTED)", lRet);
        }

        lRet = listen(mSocket, 1);
        if (0 != lRet)
        {
            ReportError(ERROR_178 " (NOT TESTED)", lRet);
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

    void Server::ProcessGet(const char * aSelector, const char * aRequest)
    {
        for (ProcessorList::iterator lIt = mProcessors.begin(); lIt != mProcessors.end(); lIt++)
        {
            if (lIt->Match(aSelector))
            {
                lIt->ProcessGet(this, aRequest);
                return;
            }
        }

        SendResponse(FOLDER_STATIC, aSelector, NULL);
    }

    void Server::ProcessOptions(const char * aSelector)
    {
        for (ProcessorList::iterator lIt = mProcessors.begin(); lIt != mProcessors.end(); lIt++)
        {
            if (lIt->Match(aSelector))
            {
                char lTimeStr[32];

                OS_GetTime(lTimeStr, sizeof(lTimeStr));

                char lHeader[256];

                // TODO HILib.Server
                //      Associate flags with processor in order to indicate
                //      if GET or POST are allowed.

                sprintf_s(lHeader,
                    "HTTP/1.1 %u %s\r\n"
                    "Date: %s GMT\r\n"
                    "Server: HTML_Interface\r\n"
                    "Access-Control-Allow-Origin: *\r\n"
                    "Access-Control-Allow-Methods: GET, POST, OPTIONS\r\n"
                    "Access-Control-Allow-Headers: Content-Type\r\n"
                    "\r\n",
                    HTTP_NO_CONTENT, HTTP_NO_CONTENT_STRING,
                    lTimeStr);

                SendData(lHeader, static_cast<unsigned int>(strlen(lHeader)));
                break;
            }
        }
    }

    void Server::ProcessPost(const char * aSelector, const char * aRequest)
    {
        for (ProcessorList::iterator lIt = mProcessors.begin(); lIt != mProcessors.end(); lIt++)
        {
            if (lIt->Match(aSelector))
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

        char lSelector[MAX_REQUEST_SIZE_byte];

        if (1 == sscanf_s(aRequest, "GET /%s", lSelector SIZE_INFO(sizeof(lSelector))))
        {
            ProcessGet(lSelector, aRequest);
        }
        else if (1 == sscanf_s(aRequest, "OPTIONS /%s", lSelector SIZE_INFO(sizeof(lSelector))))
        {
            ProcessOptions(lSelector);
        }
        else if (1 == sscanf_s(aRequest, "POST /%s", lSelector SIZE_INFO(sizeof(lSelector))))
        {
            ProcessPost(lSelector, aRequest);
        }
        else
        {
            ReportError(ERROR_299 " (NOT TESTED)");
        }
    }

    void Server::ReceiveAndProcessRequest()
    {
        assert(INVALID_SOCKET != mConnection);

        char lRequest[MAX_REQUEST_SIZE_byte];

        memset(&lRequest, 0, sizeof(lRequest));

        DWORD lTimeout_ms = 200;

        int lRet = setsockopt(mConnection, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<char *>(&lTimeout_ms), sizeof(lTimeout_ms));
        assert(0 == lRet);
        
        for (unsigned int lRetry = 0; lRetry < 3; lRetry ++)
        {
            lRet = recv(mConnection, lRequest, sizeof(lRequest) - 1, 0);
            if (0 != lRet)
            {
                break;
            }
        }

        if ((0 < lRet) && (sizeof(lRequest) > lRet))
        {
            ProcessRequest(lRequest);
        }
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
            Utl_ThrowError("ERROR", __LINE__, "send( , , ,  )  failed", lRet);
        }
    }

    void Server::SendErrorNotFound()
    {
        SendFile(HTTP_NOT_FOUND, HTTP_NOT_FOUND_STRING, FOLDER_STATIC, "ErrorNotFound");
    }

    void Server::SendFile(const char * aFileName)
    {
        assert(NULL != aFileName);

        void       * lData;
        unsigned int lDataSize_byte;

        if (OS_ReadFile(aFileName, &lData, &lDataSize_byte))
        {
            SendHeader(HTTP_OK, HTTP_OK_STRING, CONTENT_TYPE_HTML, lDataSize_byte);

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
            printf("Server::SendFile( %u, \"%s\", \"%s\" )\n", aStatusCode, aStatusName, aFileName);
        }

        void       * lData;
        unsigned int lDataSize_byte;

        if (OS_ReadFile(aFileName, &lData, &lDataSize_byte))
        {
            SendHeader(aStatusCode, aStatusName, CONTENT_TYPE_HTML, lDataSize_byte);

            SendData(lData, lDataSize_byte);

            delete[] lData;
        }
        else
        {
            if (HTTP_NOT_FOUND == aStatusCode)
            {
                SendHeader(aStatusCode, aStatusName);
            }
            else
            {
                SendErrorNotFound();
            }
        }
    }

    void Server::SendHeader(unsigned int aStatusCode, const char* aStatusName, const char* aContentType, unsigned int aDataSize_byte)
    {
        assert(NULL != aStatusName);

        if (mFlags.mDebug)
        {
            printf("Server::SendHeader( %u, \"%s\", \"%s\", %u bytes )\n", aStatusCode, aStatusName, aContentType, aDataSize_byte);
        }

        char lTimeStr[32];

        OS_GetTime(lTimeStr, sizeof(lTimeStr));

        char lHeader[256];

        // TODO HILib.Server
        //      The 2 first line of header are always the same, use the same
        //      code to generate them.

        if (NULL == aContentType)
        {
            sprintf_s(lHeader,
                "HTTP/1.1 %u %s\r\n"
                "Date: %s GMT\r\n"
                "Server: HTML_Interface\r\n"
                "Content-Length: %u\r\n"
                "Access-Control-Allow-Origin: *\r\n"
                "\r\n",
                aStatusCode, aStatusName,
                lTimeStr,
                aDataSize_byte);
        }
        else
        {
            sprintf_s(lHeader,
                "HTTP/1.1 %u %s\r\n"
                "Date: %s GMT\r\n"
                "Server: HTML_Interface\r\n"
                "Content-Length: %u\r\n"
                "Content-Type: %s\r\n"
                "Access-Control-Allow-Origin: *\r\n"
                "\r\n",
                aStatusCode, aStatusName,
                lTimeStr,
                aDataSize_byte,
                aContentType);
        }
        
        SendData(lHeader, static_cast<unsigned int>(strlen(lHeader)));
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
