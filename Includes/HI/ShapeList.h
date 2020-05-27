
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
        void AddShape(const char * aTypeName, const char * aName, Shape::Type aType = Shape::TYPE_RECT);

        /// \param aX_pixel
        /// \param aY_pixel
        /// \return This method returns a pointer to the found Shape or NULL.
        const Shape * FindByCenter(unsigned int aX_pixel, unsigned int aY_pixel) const;

        /// \param aSizeX_pixel The method puts the diagram width there.
        /// \param aSizeY_pixel The method puts the diagram height there.
        void GetDiagramSize(unsigned int * aSizeX_pixel, unsigned int * aSizeY_pixel) const;

        /// \param aSizeX_pixel The method puts the maximum shape width there.
        /// \param aSizeY_pixel The method puts the maximum shape height there.
        void GetMaximumSize(unsigned int * aSizeX_pixel, unsigned int * aSizeY_pixel) const;

        /// \param aIndex The index of the shape
        /// \return This method returns the pointer to the shape or NULL if the index is not valid.
        Shape * GetShape(unsigned int aIndex);

        /// \param aDoc The document to generate into
        /// \exception std::exception
        void Generate_SVG(HI::SVG_Document * aDoc) const;

    // internal:

        Shape * Iterator_Get  ();
        void    Iterator_Next ();
        void    Iterator_Reset();

        void PositionShapes(Grid * aGrid);

    private:

        void ComputeGrid(Grid * aGrid) const;

        typedef std::list<Shape *> InternalList;

        InternalList::iterator mIterator;
        InternalList           mShapes  ;

    };

}
