#pragma once

#include "pixel_format_type.hpp"

class Image final
{
public:
	Image(unsigned char * pixels, unsigned int width, unsigned int height, PixelFormatType pixelFormat);
	~Image();

	void flipX();
	void flipY();

	const unsigned char * getPixels() const;

	const unsigned int getWidth() const;
	const unsigned int getHeight() const;

	const PixelFormatType getPixelFormat() const;

private:
	const unsigned char * _pixels;

	const unsigned int _width;
	const unsigned int _height;

	const PixelFormatType _pixelFormat;
};