
// Product HTML_Interface
// License https://creativecommons.org/licenses/by-nc-nd/4.0/legalcode

/// \author    KMS - Martin Dubois, P.Eng.
/// \copyright Copyright &copy; 2020 KMS. All rights reserved.
/// \file      Includes/HI/Link.h
/// \brief     HI::Link

#pragma once

// ===== Includes ===========================================================
#include <HI/CSS_Colors.h>
#include <HI/Line.h>

namespace HI
{

    class CPP_Document;
    class SVG_Document;
    class Shape       ;
    class ShapeList   ;

    /// \brief HI::Link
    class Link
    {

    public:

        Link();

        /// \param aFrom The Shape where the link begins
        /// \param aTo   The Shape where the link ends
        Link(const Shape * aFrom, const Shape * aTo);

        ~Link();

        /// \retval false Do not delete
        /// \retval true  Delete when no longer needed
        bool GetAutoDelete() const;

        /// \return This method returns a pointer to the shape at the start of the link.
        const Shape * GetFrom() const;

        /// \return The length of the link in pixel
        double GetLength() const;

        /// \return See HI::Line
        Line GetLine() const;

        /// \param aShape One of the two connected shapes
        /// \return This method returns the pointer to the other connected shape.
        const Shape * GetOtherShape(const Shape * aShape) const;

        /// \return This method returns a pointer to the shape at the end of the link.
        const Shape * GetTo() const;

        /// \return This method returns the length * the weight factor.
        double GetWeight() const;

        /// \param aShape The shape of interreset
        /// \retval false Not connected
        /// \retval true  Connected
        bool IsConnectedTo(const Shape * aShape) const;

        virtual void SetAutoDelete();

        /// \param aColor The color
        void SetColor(CSS_Color aColor);

        /// \param aColor The color
        void SetColor(const char * aColor);

        /// \param aDashArray The dash array
        void SetDashArray(const char * aDashArray);

        /// \param aWeightFactor
        void SetWeightFactor(double aWeightFactor);

        /// \param aWidth_pixel The line width in pixel
        void SetWidth(unsigned int aWidth_pixel);

        /// \param aDoc    The document to generate into
        /// \param aIndex
        /// \param aShapes
        /// \exception std::exception
        void Generate_CPP(HI::CPP_Document * aDoc, unsigned int aIndex, const ShapeList & aShapes) const;

        /// \param aDoc The document to generate into
        /// \exception std::exception
        void Generate_SVG(HI::SVG_Document * aDoc) const;

    private:

        void Init();

        struct
        {
            unsigned mAutoDelete : 1;

            unsigned mReserved0 : 31;
        }
        mFlags;

        std::string mColor;
        std::string mDashArray;

        const Shape * mFrom;
        const Shape * mTo  ;

        double       mWeightFactor;
        unsigned int mWidth_pixel ;

    };

}
