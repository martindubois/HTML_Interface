
// Product  HTML_Interface

/// \author KMS - Martin Dubois, P.Eng.
/// \file   Includes/HI/Browser.h

#pragma once

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== Includes ===========================================================
#include <HI/Types.h>

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

        void Close();

        void Open(FolderId aFolder, const char * aName);

        void Open(const char * aFolder, const char * aName);

        void Open(HTML_Document * aDocument);

        void Open(Server * aServer);

        void ParseArguments(int aCount, const char ** aVector);

        void Start(FolderId aFolder, const char * aName);

        void Start(const char * aFolder, const char * aName);

        void Start(HTML_Document * aDocument);

        void Wait();

    private:

    };

}
