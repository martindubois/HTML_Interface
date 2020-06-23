
// Product HTML_Interface
// License https://creativecommons.org/licenses/by-nc-nd/4.0/legalcode

/// \author    KMS - Martin Dubois, P.Eng.
/// \copyright Copyright &copy; 2020 KMS. All rights reserved.
/// \file      Includes/HI/Shape.h
/// \brief     HI::Shape

#pragma once

// ===== C++ ================================================================
#include <string>

// ===== Includes ===========================================================
#include <HI/CSS_Colors.h>
#include <HI/Point.h>

namespace HI
{

    class CPP_Document;
    class Line        ;
    class SVG_Document;

    /// \brief HI::Shape
    class Shape
    {

    public:

        typedef enum
        {
            TYPE_ELLIPSE,
            TYPE_RECT   ,

            TYPE_QTY
        }
        Type;

        Shape();

        /// \param aTypeName The type
        /// \param aName     The name
        /// \param aType     See TYPE_...
        Shape(const char * aTypeName, const char * aName, Type aType = TYPE_RECT);

        virtual ~Shape();

        /// \retval false Do not delete
        /// \retval true  Delete when no longer needed
        bool GetAutoDelete() const;

        /// \return The bottom in pixel
        unsigned int GetBottom() const;

        /// \return This method return a pointer to an internal buffer.
        const char * GetName() const;

        /// \return The right in pixel
        unsigned int GetRight() const;

        /// \param aSizeX_pixel The method puts the width here.
        /// \param aSizeY_pixel The method puts the height here.
        void GetSize(unsigned int * aSizeX_pixel, unsigned int * aSizeY_pixel) const;

        /// \param aLine The line to look for intersection with
        /// \retval false No intersection
        /// \retval true  Intersection
        bool IsCrossing(const Line & aLine) const;

        virtual void SetAutoDelete();

        /// \param aColor The color
        void SetFillColor(CSS_Color aColor);

        /// \param aColor The color
        void SetFillColor(const char * aColor);

        /// If needed, SetName increase the shape width to fit the name length.
        /// \param aName The name
        void SetName(const char * aName);

        /// \param aTitle The title
        void SetTitle(const char * aTitle);

        /// \param aDoc   The document to generate into
        /// \param aIndex The index of the Shape into the document
        /// \exception std::exception
        virtual void Generate_CPP(CPP_Document * aDoc, unsigned int aIndex) const;

        /// \param aDoc The document to generate into
        /// \exception std::exception
        virtual void Generate_SVG(SVG_Document * aDoc) const;

        Point mCenter;

    // Internal

        unsigned int LinkCount_Get  () const;
        void         LinkCount_Inc  () const;
        void         LinkCount_Reset();

    private:

        void Init(Type aType);

        void Generate_SVG_Ellipse(SVG_Document * aDoc) const;
        void Generate_SVG_Rect   (SVG_Document * aDoc) const;

        struct
        {
            unsigned int mAutoDelete : 1;

            unsigned int mReserved0 : 31;
        }
        mFlags;

        std::string mName    ;
        std::string mTitle   ;
        Type        mType    ;
        std::string mTypeName;

        std::string mFillColor;

        unsigned int mSizeX_pixel;
        unsigned int mSizeY_pixel;

        mutable unsigned int mLinkCount;

    };

}
