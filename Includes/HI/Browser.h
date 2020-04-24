
// Product  HTML_Interface

/// \author KMS - Martin Dubois, P.Eng.
/// \file   Includes/Browser.h

#pragma once

namespace HI
{

    class HTML_Document;
    class Server       ;

    /// \brief Browses
    class Browser
    {

    public:

        Browser();

        ~Browser();

        bool Close();

        bool Open(FolderId aFolder, const char * aName);

        bool Open(const char * aFolder, const char * aName);

        bool Open(HTML_Document * aDocument);

        bool Open(Server * aServer);

        bool Start(const char * aFileName);

        bool Start(HTM_Document * aDocument);

        bool Wait();

    private:

    };

}
