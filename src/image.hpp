#pragma once

#include "pixel_format.hpp"

class Image final
{
public:
	Image(unsigned char* pixels, unsigned int width, unsigned int height, PixelFormat pixelFormat);
	~Image();

	const unsigned char* getPixels();

	const unsigned int getWidth();
	const unsigned int getHeight();

	const PixelFormat getPixelFormat();

private:
	const unsigned char* _pixels;

	const unsigned int _width;
	const unsigned int _height;

	const PixelFormat _pixelFormat;
};