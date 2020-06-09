
// Product HTML_Interface

/// \author    KMS - Martin Dubois, P.Eng.
/// \copyright Copyright &copy; 2020 KMS. All rights reserved.
/// \file      Includes/HI/Point.h
/// \brief     HI::Point

#pragma once

namespace HI
{

    /// \brief HI::Point
    class Point
    {

    public:

        Point();

        /// \param aIn The value to copy
        Point(const Point & aIn);

        /// \param aX X coordinate
        /// \param aY Y coordinate
        Point(unsigned int aX, unsigned int aY);

        /// \param aValue The value to assign
        const Point & operator = (const Point & aValue);

        /// \param aB The value to compare
        bool operator == (const Point & aB) const;

        /// \return This method returns the X coordinate
        unsigned int GetX() const;

        /// \return This method returns the Y coordinate
        unsigned int GetY() const;

        /// \param aX X coordinate
        /// \param aY Y coordinate
        void Set(unsigned int aX, unsigned int aY);

    private:

        unsigned int mX_pixel;
        unsigned int mY_pixel;

    };

    // Public
    /////////////////////////////////////////////////////////////////////////

    inline Point::Point() : mX_pixel(0), mY_pixel(0)
    {
    }

    inline Point::Point(unsigned int aX_pixel, unsigned int aY_pixel) : mX_pixel(aX_pixel), mY_pixel(aY_pixel)
    {
    }

    inline unsigned int Point::GetX() const
    {
        return mX_pixel;
    }

    inline unsigned int Point::GetY() const
    {
        return mY_pixel;
    }

}
