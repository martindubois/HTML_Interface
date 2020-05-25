
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

    class HTML_Document;
    class SVG_Document ;

    /// \brief HI::Diagram
    class Diagram
    {

    public:

        Diagram();

        ~Diagram();

        /// \param aSizeX_pixel The method puts the diagram width there.
        /// \param aSizeY_pixel The method puts the diagram height there.
        void GetSize(unsigned int * aSizeX_pixel, unsigned int * aSizeY_pixel) const;

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

        /// \aDoc The document to create the SVG document into
        /// \exception std::exception
        void Generate_SVG(HTML_Document * aDoc);

        /// \aDoc The SVG document to generate code into
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

        void         PositionShapes(Grid * aGrid);
        unsigned int PositionShape (Grid * aGrid, Shape * aShape);

    };

}
