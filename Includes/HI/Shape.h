
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
            TYPE_IMAGE  ,
            TYPE_RECT   ,

            TYPE_QTY
        }
        Type;

        Shape();

        /// \param aTypeName The type name
        /// \param aName     The name of the shape
        /// \param aType     See HI::Shape::Type
        Shape(const char * aTypeName, const char * aName, Type aType = TYPE_RECT);

        virtual ~Shape();

        /// \param aText The text to append to the title
        void AppendToTitle(const char * aText);

        /// \retval false Do not delete
        /// \retval true  Delete when no longer needed
        bool GetAutoDelete() const;

        /// \return The bottom coordonate in pixel
        unsigned int GetBottom() const;

        /// \return The left coordonate in pixel
        unsigned int GetLeft() const;

        /// \return This method return a pointer to an internal buffer.
        const char * GetName() const;

        /// \return The right coordonate in pixel
        unsigned int GetRight() const;

        /// \param aSizeX_pixel The method puts the width here.
        /// \param aSizeY_pixel The method puts the height here.
        void GetSize(unsigned int * aSizeX_pixel, unsigned int * aSizeY_pixel) const;

        /// \return The top coordonate in pixel
        unsigned int GetTop() const;

        /// \param aLine The line to look for intersection with
        /// \retval false No intersection
        /// \retval true  Intersection
        bool IsCrossing(const Line & aLine) const;

        virtual void SetAutoDelete();

        /// \param aColor The fill color
        void SetFillColor(CSS_Color aColor);

        /// \param aColor The fill color
        void SetFillColor(const char * aColor);
        
        /// This method also set the type to TYPE_IMAGE.
        /// \param aFolder See HI::FolderId
        /// \param aImage  The name of the image, including the extension
        void SetImage(HI::FolderId aFolder, const char * aImage);

        /// This method also set the type to TYPE_IMAGE.
        /// \param aFolder The folder
        /// \param aImage  The name of the image, including the extension
        void SetImage(const char * aFolder, const char * aImage);

        /// This method also set the type to TYPE_IMAGE.
        /// \param aURL The complete image URL
        void SetImageURL(const char * aURL);

        /// If needed, SetName increase the shape width to fit the name length.
        /// \param aName The name
        void SetName(const char * aName);

        void SetNameOnImage();

        /// \param aSizeX_pixel The width in pixel
        /// \param aSizeY_pixel The height in pixel
        void SetSize(unsigned int aSizeX_pixel, unsigned int aSizeY_pixel);

        /// \param aStrokeWidth_pixel The line width in pixel
        void SetStrokeWidth(unsigned int aStrokeWidth_pixel);

        void SetTypeOnImage();

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
        void Generate_SVG_HWXY   (SVG_Document * aDoc) const;
        void Generate_SVG_Image  (SVG_Document * aDoc) const;
        void Generate_SVG_Name   (SVG_Document * aDoc) const;
        void Generate_SVG_Rect   (SVG_Document * aDoc) const;
        void Generate_SVG_Shape  (SVG_Document * aDoc) const;
        void Generate_SVG_Texts  (SVG_Document * aDoc) const;
        void Generate_SVG_Title  (SVG_Document * aDoc) const;
        void Generate_SVG_Type   (SVG_Document * aDoc) const;

        struct
        {
            unsigned int mAutoDelete  : 1;
            unsigned int mNameOnImage : 1;
            unsigned int mTypeOnImage : 1;

            unsigned int mReserved0 : 29;
        }
        mFlags;

        std::string mFillColor;
        std::string mImageURL ;
        std::string mName     ;
        std::string mTitle    ;
        Type        mType     ;
        std::string mTypeName ;

        unsigned int mSizeX_pixel;
        unsigned int mSizeY_pixel;

        unsigned int mStrokeWidth_pixel;

        mutable unsigned int mLinkCount;

    };

}
