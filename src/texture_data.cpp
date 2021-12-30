#include "texture_data.hpp"

TextureData::TextureData(unsigned char* pixels, unsigned int width, unsigned int height, unsigned int channelCount)
	:
	_pixels(pixels),
	_width(width),
	_height(height),
	_channelCount(channelCount)
{

}

const unsigned char* TextureData::getPixels()
{
	return _pixels;
}

const unsigned int TextureData::getWidth()
{
	return _width;
}

const unsigned int TextureData::getHeight()
{
	return _height;
}

const unsigned int TextureData::getChannelCount()
{
	return _channelCount;
}