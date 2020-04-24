
// Product  HTML_Interface

/// \author KMS - Martin Dubois, P.Eng.
/// \file   Includes/Server.h

#pragma once

namespace HI
{

    /// \brief Server
    class Server
    {

    public:

        typedef bool (*GetHandler)(Context * aContext, Server * aServer, const char * aAddress);

        typedef bool (*PostHandler)(Context * aContext, Server * aServer, const char * aAddress);

        Server();

        ~Server();

        void SetRoot(FolderId aFolder);

        void SetRoot(const char * aFolder);

        void AddGetHandler(const char * aAddress, GetHandler aHandler, void * aContext);

        void AddPostHandler(const char * aAddress, PostHandler aHandler, void * aContext);

        void Run();

        void Stop();

    private:

    };

}
