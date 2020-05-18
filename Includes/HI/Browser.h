
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

        typedef enum
        {
            PREFERED_CHROME ,
            PREFERED_DEFAULT,
            PREFERED_NONE   ,

            PREFERED_QTY
        }
        Prefered;

        Browser();

        ~Browser();

        void SetPrefered(Prefered aIn);

        /// \exception std::exception
        void Close();

        void Detach();

        /// \exception std::exception
        void Open(FolderId aFolder, const char * aName);

        /// \exception std::exception
        void Open(const char * aFolder, const char * aName);

        /// \exception std::exception
        void Open(HTML_Document * aDocument);

        /// \exception std::exception
        void Open(const Server * aServer, const char * aName);

        void ParseArguments(int aCount, const char ** aVector);

        bool ParseAssignation(const char * aAssignation);

        /// \exception std::exception
        void Start(FolderId aFolder, const char * aName);

        /// \exception std::exception
        void Start(const char * aFolder, const char * aName);

        /// \exception std::exception
        void Start(HTML_Document * aDocument);

        void Wait();

    private:

        // --> INIT <--+
        //      |      |
        //      +--> OPEN
        typedef enum
        {
            STATE_INIT,
            STATE_OPEN,

            STATE_QTY
        }
        State;

        void Open        (const char * aFileName);
        bool Open_Chrome (const char * aFileName);
        bool Open_Default(const char * aFileName);
        bool Open_Process(const char * aExec, const char * aCommand);

        void Start(const char * aFileName);

        Prefered mPrefered;
        void   * mProcess ;
        State    mState   ;

    };

}
