#include "image.hpp"

Image::Image(unsigned char* pixels, unsigned int width, unsigned int height, PixelFormat pixelFormat)
	:
	_pixels(pixels),
	_width(width),
	_height(height),
	_pixelFormat(pixelFormat)
{

}

Image::~Image()
{
	delete[] _pixels;
}

const unsigned char* Image::getPixels()
{
	return _pixels;
}

const unsigned int Image::getWidth()
{
	return _width;
}

const unsigned int Image::getHeight()
{
	return _height;
}

const PixelFormat Image::getPixelFormat()
{
	return _pixelFormat;
}