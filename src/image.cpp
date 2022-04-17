#pragma warning(disable:6386)

#include "image.hpp"

#include <stdlib.h>

Image::Image(unsigned char * pixels, unsigned int width, unsigned int height, PixelFormatType pixelFormat)
	:
	_pixels(pixels),
	_width(width),
	_height(height),
	_pixelFormat(pixelFormat)
{
	if(_pixels == nullptr)
	{
		abort();
	}

	if((_width == 0) || (_height == 0))
	{
		abort();
	}
}

Image::~Image()
{
	delete[] _pixels;
}

void Image::flipX()
{
	const auto byteFormat = (_pixelFormat == PixelFormatType::RGB ? 3 : 4);
	const auto size = (_width * _height * byteFormat);
	auto newPixels = new unsigned char[size];

	for(unsigned y = 0; y < _height; y++)
	{
		for(unsigned x = 0; x < _width; x++)
		{
			const auto index1 = ((x * byteFormat) + (y * _width * byteFormat));
			const auto index2 = (((_width - x - 1) * byteFormat) + (y * _width * byteFormat));

			if(byteFormat == 3)
			{
				newPixels[index1 + 0] = _pixels[index2 + 0];
				newPixels[index1 + 1] = _pixels[index2 + 1];
				newPixels[index1 + 2] = _pixels[index2 + 2];
			}
			if(byteFormat == 4)
			{
				newPixels[index1 + 0] = _pixels[index2 + 0];
				newPixels[index1 + 1] = _pixels[index2 + 1];
				newPixels[index1 + 2] = _pixels[index2 + 2];
				newPixels[index1 + 3] = _pixels[index2 + 3];
			}
		}
	}

	delete[] _pixels;
	_pixels = newPixels;
}

void Image::flipY()
{
	const auto byteFormat = (_pixelFormat == PixelFormatType::RGB ? 3 : 4);
	const auto size = (_width * _height * byteFormat);
	auto newPixels = new unsigned char[size];

	for(unsigned y = 0; y < _height; y++)
	{
		for(unsigned x = 0; x < _width; x++)
		{
			const auto index1 = ((x * byteFormat) + (y * _width * byteFormat));
			const auto index2 = ((x * byteFormat) + ((_height - y - 1) * _width * byteFormat));

			if(byteFormat == 3)
			{
				newPixels[index1 + 0] = _pixels[index2 + 0];
				newPixels[index1 + 1] = _pixels[index2 + 1];
				newPixels[index1 + 2] = _pixels[index2 + 2];
			}
			if(byteFormat == 4)
			{
				newPixels[index1 + 0] = _pixels[index2 + 0];
				newPixels[index1 + 1] = _pixels[index2 + 1];
				newPixels[index1 + 2] = _pixels[index2 + 2];
				newPixels[index1 + 3] = _pixels[index2 + 3];
			}
		}
	}

	delete[] _pixels;
	_pixels = newPixels;
}

const unsigned char * Image::getPixels() const
{
	return _pixels;
}

const unsigned int Image::getWidth() const
{
	return _width;
}

const unsigned int Image::getHeight() const
{
	return _height;
}

const PixelFormatType Image::getPixelFormat() const
{
	return _pixelFormat;
}