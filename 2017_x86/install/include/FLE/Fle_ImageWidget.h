#pragma once
#ifndef Fle_ImageWidget_h__
#define Fle_ImageWidget_h__

/*********************************************************************************
created:	2017/01/30   12:51AM
filename: 	Fle_ImageWidget.h
file base:	Fle_ImageWidget
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	customized image widget with load, save, zoom/pan support.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_ImageUtil.h>
#include <Fl/Fl_Widget.H>

#include <opencv2/opencv.hpp>

namespace R3D
{

class FL_ESSENTIALS_EXPORT Fle_ImageWidget : public Fl_Widget
{
public:
	// Description:
	// Constructor to create a image widget inside the parent window.
	// By default, image draw type is ImageDrawType::Fit.
	// Note: zooming only wors with ImageDrawType::Center.
	Fle_ImageWidget(int _x, int _y, int _w, int _h, const char* _title = 0);
	// Description:
	// Destructor to release data.
	virtual ~Fle_ImageWidget();

	// Description:
	// Function to release the internal image data that clears the image widget.
	void clear(const cv::Vec3b& _color = cv::Vec3b(0, 0, 0));

	// Description:
	// Function to set image draw type, meaning that how the image should be drawn inside the window.
	// Note: zooming only wors with ImageDrawType::Center.
	void setImageDrawType(const Fle_ImageDrawType _type) { m_dtype = _type; resetZoom(); }
	// Description:
	// Function to get the image draw type.
	Fle_ImageDrawType getImageDrawType() const { return m_dtype; }

	// Description:
	// Function to set an image as background.
	void setImage(const cv::Mat& _image);
	// Description:
	// Function to get a clone of the background image.
	cv::Mat getImage() const;
	// Description:
	// Function to load an image from the given file path.
	// _filename should a file name plus extension.
	bool loadImage(const std::string& _filename);
	// Description:
	// Function to load an image from the path specified by setFilePath();
	bool loadImage();
	// Description:
	// Function to save the current image to disk.
	// example:
	// vector<int> compression_params;
	// compression_params.push_back(IMWRITE_PNG_COMPRESSION);
	// compression_params.push_back(9);
	// saveImage("D:\\a.png", compression_params);
	bool saveImage(const std::string& _filename, const std::vector<int>& _compression_params = std::vector<int>()) const;

	// Description:
	// Function to set the file path used for loadImage().
	// _filename should a file name plus extension.
	void setFileLocation(const std::string& _filename) { m_filename = _filename; }
	// Description:
	// Function to get the file path used for loadImage().
	std::string getFileLocation() const { return m_filename; }

	// Description:
	// Function to get the loaded image size.
	cv::Size getImageSize() const;

	// Description:
	// Function to reset zooming using the given image size.
	void resetZoom(const cv::Size& _img_size);
	// Description:
	// Function to reset zooming.
	void resetZoom();
	// Description:
	// Function that resizes the size of this widget with a scale of 0.8.
	void zoomOut();
	// Description:
	// Function that resizes the size of this widget with a scale of 1.2.
	void zoomIn();
	// Description:
	// Function that resizes the size of this widget with a scale of _factor.
	void scaleImage(const double _factor);

	// Description:
	// Function to set zoom in and out factors.
	// Default factor for zoom-in is _f[0] = 1.2.
	// Default factor for zoom-out is _f[0] = 0.8.
	void setZoomInOutFactors(const cv::Vec2d& _f) { m_zoom_factors = _f; }
	// Description:
	// Function to get zoom in and out factors.
	cv::Vec2d getZoomInOutFactors() const { return m_zoom_factors; }

	// Description:
	// Function to set the region of interest for the image to be displayed.
	void setRoi(const cv::Rect& _roi);
	// Description:
	// Function to get the region of interest.
	cv::Rect getRoi() const;
	// Description:
	// Function to reset the region of interest to display the full image size.
	void resetRoi();

protected:
	// Description:
	// A virtual function that is expected to be overridden in the derived class for
	// drawing FLTK widgets such as 
	void draw() override;
	// Description:
	// Overloaded function that is being called inside the draw() function.
	void drawImage(const int _x, const int _y, const int _w, const int _h);

	cv::Mat m_image;
	cv::Size m_isize;
	cv::Vec2d m_zoom_factors;
	Fle_ImageDrawType m_dtype;
	std::string m_filename;
	double m_zoom;
	cv::Rect m_roi;
};

}

#endif // Fle_ImageWidget_h__