
// Product HTML_Interface
// License https://creativecommons.org/licenses/by-nc-nd/4.0/legalcode

/// \author    KMS - Martin Dubois, P.Eng.
/// \copyright Copyright &copy; 2021 KMS
/// \file      Includes/HI/Server.h

#pragma once

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C++ ================================================================
#include <list>
#include <string>

// ===== Includes ===========================================================
#include <HI/Types.h>

namespace HI
{

    /// \brief Server
    class Server
    {

    public:

        /// \brief IRequestProcessor
        class IRequestProcessor
        {

        public:

            virtual void ProcessGet(Server * aServer, unsigned int aCode, const char * aRequest) = 0;

            virtual void ProcessPost(Server * aServer, unsigned int aCode, const char * aRequest) = 0;

        };

        Server();

        ~Server();

        void AddProcessor(unsigned int aCode, const char * aName, IRequestProcessor * aProcessor);

        uint16_t GetLocalPort() const;
        void     SetLocalPort(uint16_t aPort);

        void SetDebug(bool aDebug);

        void ParseArguments(int aCount, const char ** aVector);

        bool ParseAssignation(const char * aAssignation);

        /// \exception std::exception
        void Run();

        /// \exception std::exception
        void SendData(unsigned int aStatusCode, const char * aStatusName, unsigned int aDataSize_byte = 0, const void * aData = NULL);

        /// \exception std::exception
        void SendFile(FolderId aFolder, const char * aName, const char * aExtension);

        /// \exception std::exception
        void Start();

        void Stop();

    private:

        // --> INVALID --> INIT --> STARTED --> RUNNING --> STOPPING --> STOPPED
        //      |           |                    |
        //      +-----------+--------------------+--> ERROR
        typedef enum
        {
            STATE_ERROR   ,
            STATE_INVALID ,
            STATE_INIT    ,
            STATE_RUNNING ,
            STATE_STARTED ,
            STATE_STOPPING,
            STATE_STOPPED ,

            STATE_QTY
        }
        State;

        class Processor
        {

        public:

            Processor(const Processor & aIn);

            Processor(unsigned int aCode, const char * aName, IRequestProcessor * aProcessor);

            bool Match(const char * aRequest);

            void ProcessGet(Server * aServer, const char * aRequest);

            void ProcessPost(Server * aServer, const char * aRequest);

        private:

            unsigned int        mCode     ;
            std::string         mName     ;
            IRequestProcessor * mProcessor;

        };

        typedef std::list<Processor> ProcessorList;

        void CloseConnection();
        void CloseSocket    ();

        void ProcessGet    (const char * aRequest);
        void ProcessOptions(const char * aRequest);
        void ProcessPost   (const char * aRequest);
        void ProcessRequest(const char * aRequest);

        void ReceiveAndProcessRequest();

        void ReportError(const char * aMessage, int aCode = 0);

        void SendData(const void * aData, unsigned int aDataSize_byte);

        void SendErrorNotFound();

        void SendFile(const char * aFileName);
        void SendFile(unsigned int aStatusCode, const char * aStatusName, FolderId aFolder, const char * aName);
        void SendFile(unsigned int aStatusCode, const char * aStatusName, const char * aFileName);

        void SendHeader(unsigned int aStatusCode, const char * aStatusName, unsigned int aDataSize_byte);

        void Trace(const char * aMessage);

        struct
        {
            unsigned mDebug : 1;

            unsigned mReserved0 : 31;
        }
        mFlags;

        sockaddr_in   mBinded    ;
        ProcessorList mProcessors;
        SOCKET        mConnection;
        sockaddr_in   mLocal     ;
        SOCKET        mSocket    ;
        State         mState     ;

    };

}
