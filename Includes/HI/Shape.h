
// Product HTML_Interface

/// \author    KMS - Martin Dubois, P.Eng.
/// \copyright Copyright &copy; 2020 KMS. All rights reserved.
/// \file      Includes/HI/Shape.h
/// \brief     HI::Shape

#pragma once

// ===== C++ ================================================================
#include <string>

namespace HI
{

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

        /// \retval false Cannot move
        /// \retval true  Can move
        bool CanMove() const;

        /// \retval false Do not delete
        /// \retval true  Delete when no longer needed
        bool GetAutoDelete() const;

        /// \return The bottom in pixel
        unsigned int GetBottom() const;

        /// \param aX_pixel The method puts the X value there.
        /// \param aY_pixel The method puts the Y value there.
        void GetCenter(unsigned int * aX_pixel, unsigned int * aY_pixel) const;

        /// \return This method return a pointer to an internal buffer.
        const char * GetName() const;

        /// \return The right in pixel
        unsigned int GetRight() const;

        /// \param aSizeX_pixel The method puts the width here.
        /// \param aSizeY_pixel The method puts the height here.
        void GetSize(unsigned int * aSizeX_pixel, unsigned int * aSizeY_pixel) const;

        /// \param aX_pixel
        /// \param aY_pixel
        /// \retval false No
        /// \retval true  Yes
        bool IsCenterAt(unsigned int aX_pixel, unsigned int aY_pixel) const;

        void SetAutoDelete();

        /// \param aX_pixel The X position
        /// \param aY_pixel The y position
        void SetCenter(unsigned int aX_pixel, unsigned int aY_pixel);

        void SetDoNotMove();

        /// If needed, SetName increase the shape width to fit the name length.
        /// \param aName The name
        void SetName(const char * aName);

        /// \param aX_pixel The width
        /// \param aY_pixel The height
        void SetSize(unsigned int aX_pixel, unsigned int aY_pixel);

        /// \param aType See TYPE_...
        void SetType(Type aType);

        /// \param aTypeName The type
        void SetTypeName(const char * aTypeName);

        /// \param aDoc The document to generate into
        /// \exception std::exception
        virtual void Generate_SVG(HI::SVG_Document * aDoc) const;

    private:

        void Init(Type aType);

        struct
        {
            unsigned int mAutoDelete : 1;
            unsigned int mDoNotMove  : 1;

            unsigned int mReserved0 : 30;
        }
        mFlags;

        std::string mName    ;
        Type        mType    ;
        std::string mTypeName;

        unsigned int mCenterX_pixel;
        unsigned int mCenterY_pixel;

        unsigned int mSizeX_pixel;
        unsigned int mSizeY_pixel;

    };

}
