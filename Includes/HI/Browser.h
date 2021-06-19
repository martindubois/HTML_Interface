
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
            CHROME,
            EDGE,

            DEFAULT_BROWSER,

            NO_BROWSER,

            BROWSER_TYPE_QTY
        }
        BrowserType;

        Browser();

        ~Browser();

        bool IsOpen();

        void SetAppMode(bool aIn = true);

        void SetKioskMode(bool aIn = true);

        void SetPrefered(BrowserType aIn);

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

        void BuildCmd_Chrome(const char* aFileName, char* aOut, unsigned int aOutSize_byte);
        void BuildCmd_Edge  (const char* aFileName, char* aOut, unsigned int aOutSize_byte);

        void Open        (const char * aFileName);
        bool Open_Chrome (const char * aFileName);
        bool Open_Default(const char * aFileName);
        bool Open_Edge   (const char * aFileName);
        bool Open_Process(const char * aExec, const char * aCommand);

        void Start       (const char* aFileName);
        bool Start_Chrome(const char* aFileName);
        bool Start_Edge  (const char* aFileName);

        State State_Get();

        bool mAppMode  ;
        bool mKioskMode;

        BrowserType mPrefered;

        void* mProcess;
        State mState  ;

    };

}
