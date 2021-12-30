#include "image.hpp"

Image::Image(unsigned char* pixels, unsigned int width, unsigned int height, unsigned int channelCount)
	:
	_pixels(pixels),
	_width(width),
	_height(height),
	_channelCount(channelCount)
{

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

const unsigned int Image::getChannelCount()
{
	return _channelCount;
}