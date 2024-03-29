
// Product HTML_Interface

/// \author    KMS - Martin Dubois, P.Eng.
/// \copyright Copyright &copy; 2020 KMS. All rights reserved.
/// \file      Includes/HI/Diagram.h
/// \brief     HI::Diagram

#pragma once

// ===== Includes ===========================================================
#include <HI/LinkList.h>
#include <HI/ShapeList.h>
#include <HI/Types.h>

// ===== HILib ==============================================================
class Grid;

namespace HI
{

    class CPP_Document ;
    class HTML_Document;
    class SVG_Document ;

    /// \brief HI::Diagram
    class Diagram
    {

    public:

        Diagram();

        ~Diagram();

        /// \param aColor
        void SetBackgroundColor(CSS_Color aColor);

        /// \param aColor
        void SetBackgroundColor(const char * aColor);

        /// \param aSizeX_pixel The method puts the diagram width there.
        /// \param aSizeY_pixel The method puts the diagram height there.
        void GetSize(unsigned int * aSizeX_pixel, unsigned int * aSizeY_pixel) const;

        void SetDebug();

        /// \param aFolder See FOLDER_...
        /// \param aName   The file name, without extension
        /// \exception std::exception
        void Generate_CPP(FolderId aFolder, const char * aName);

        /// \param aFolder The folder name or NULL to create the file into the current folder
        /// \param aName   The file name, without extension
        /// \exception std::exception
        void Generate_CPP(const char * aFolder, const char * aName);

        /// \param aFolder See FOLDER_...
        /// \param aName   The file name, without extension
        /// \param aTitle  The title
        /// \exception std::exception
        void Generate_HTML(FolderId aFolder, const char * aName, const char * aTitle);

        /// \param aFolder The folder name or NULL to create the file into the current folder
        /// \param aName   The file name, without extension
        /// \param aTitle  The title
        /// \exception std::exception
        void Generate_HTML(const char * aFolder, const char * aName, const char * aTitle);

        /// \param aDoc The document to create the SVG document into
        /// \exception std::exception
        void Generate_SVG(HTML_Document * aDoc);

        /// \param aDoc The SVG document to generate code into
        /// \exception std::exception
        void Generate_SVG(SVG_Document * aDoc);

        /// \param aFolder See FOLDER_...
        /// \param aName   The file name, without extension
        /// \exception std::exception
        void Generate_SVG(FolderId aFolder, const char * aName);

        /// \param aFolder The folder name or NULL to create the file into the current folder
        /// \param aName   The file name, without extension
        /// \exception std::exception
        void Generate_SVG(const char aFolder, const char * aName);

        void PositionShapes();

        ShapeList mShapes;
        LinkList  mLinks ;

    private:

        void DebugIteration(unsigned int aIteration);

        void Generate_CPP(CPP_Document * aDoc) const;

        void         PositionShapes(Grid * aGrid);
        unsigned int PositionShape (Grid * aGrid, Shape * aShape);

        void RetrieveDiagramSize(SVG_Document * aDoc);

        struct
        {
            unsigned mDebug : 1;

            unsigned mReserved0 : 31;
        }
        mFlags;

        std::string mBackgroundColor;

    };

}
