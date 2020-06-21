
// Product HTML_Interface

/// \author    KMS - Martin Dubois, P.Eng.
/// \copyright Copyright &copy; 2020 KMS. All rights reserved.
/// \file      Includes/HI/ShapeList.h
/// \brief     HI::ShapeList

#pragma once

// ===== C++ ================================================================
#include <list>

// ===== Includes ===========================================================
#include <HI/Shape.h>

// ===== HILib ==============================================================
class Grid;

namespace HI
{

    class CPP_Document;
    class SVG_Document;

    /// \brief HI::ShapeList
    class ShapeList
    {

    public:

        ShapeList();

        ~ShapeList();

        /// \param aShape The Shape instance to add
        void AddShape(Shape * aShape);

        /// \param aTypeName The type
        /// \param aName     The name
        /// \param aType     See Shape::TYPE_...
        /// \return This method returns a pointer to the new instance.
        Shape * AddShape(const char * aTypeName, const char * aName, Shape::Type aType = Shape::TYPE_RECT);

        /// \param aCenter
        /// \return This method returns a pointer to the found Shape or NULL.
        const Shape * FindByCenter(const Point & aCenter) const;

        /// \param aSizeX_pixel The method puts the diagram width there.
        /// \param aSizeY_pixel The method puts the diagram height there.
        void GetDiagramSize(unsigned int * aSizeX_pixel, unsigned int * aSizeY_pixel) const;

        /// \param aShape
        /// \return This method returns the index of the shape into the list.
        /// \exception std::exception
        unsigned int GetIndex(const Shape * aShape) const;

        /// \param aSizeX_pixel The method puts the maximum shape width there.
        /// \param aSizeY_pixel The method puts the maximum shape height there.
        void GetMaximumSize(unsigned int * aSizeX_pixel, unsigned int * aSizeY_pixel) const;

        /// \param aIndex The index of the shape
        /// \return This method returns the pointer to the shape or NULL if the index is not valid.
        Shape * GetShape(unsigned int aIndex);

        /// \param aDoc The document to generate into
        /// \exception std::exception
        void Generate_CPP(HI::CPP_Document * aDoc) const;

        /// \param aDoc The document to generate into
        /// \exception std::exception
        void Generate_SVG(HI::SVG_Document * aDoc) const;

        // internal:

        Shape * Iterator_Get  ();
        void    Iterator_Next ();
        void    Iterator_Reset();

        void PositionShapes(Grid * aGrid);

        void LinkCounts_Reset();
        void LinkCounts_Sort ();

    private:

        void ComputeGrid(Grid * aGrid) const;

        typedef std::list<Shape *> InternalList;

        InternalList::iterator mIterator;
        InternalList           mShapes  ;

    };

}
