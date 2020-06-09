
// Product HTML_Interface

/// \author    KMS - Martin Dubois, P.Eng.
/// \copyright Copyright &copy; 2020 KMS. All rights reserved.
/// \file      Includes/HI/Line.h
/// \brief     HI::Line

#pragma once

// ===== Includes ===========================================================
#include <HI/Point.h>

// ===== HILib ==============================================================
class Straight;

namespace HI
{

    /// \brief HI::Line
    class Line
    {

    public:

        Line();

        /// \param aIn The initial value
        Line(const Line & aIn);

        /// \param aFrom The initial starting point
        /// \param aTo   The initial end point
        Line(const Point & aFrom, const Point & aTo);

        /// \param aFX_pixel The X coordinate of the start point
        /// \param aFY_pixel The Y coordinate of the start point
        /// \param aTX_pixel The X coordinate of the end point
        /// \param aTY_pixel The Y coordinate of the end point 
        Line(unsigned int aFX_pixel, unsigned int aFY_pixel, unsigned int aTX_pixel, unsigned int aTY_pixel);

        /// \return The length in pixel
        double GetLength() const;

        /// \param aLine Is the line crossing this line?
        /// \retval false No intersection
        /// \retval true  Intersection
        bool IsCrossing(const Line & aLine) const;

        /// \retval false The line is not horizontal
        /// \retval true  The line is horizontal
        bool IsHorizontal() const;

        /// \param aLine Is the line overlapping this line?
        /// \retval false No overlap
        /// \retval true  Overlap
        bool IsOverlapping(const Line & aLine) const;

        /// \retval false The line is not vertical
        /// \retval true  The line is vertical
        bool IsVertical() const;

        Point mFrom;
        Point mTo  ;

    private:

        void GetStraight(Straight * aOut) const;
        void GetDelta(double * aDX_pixel, double * aDY_pixel) const;

        bool IsCrossing_Vertical(const Line & aLine) const;

        bool IsOverlapping_Horizontal(const Line & aLine) const;
        bool IsOverlapping_Vertical  (const Line & aLine) const;

    };

}
