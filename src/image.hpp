#pragma once

class Image final
{
public:
	Image(unsigned char* pixels, unsigned int width, unsigned int height, unsigned int channelCount);

	const unsigned char* getPixels();

	const unsigned int getWidth();
	const unsigned int getHeight();
	const unsigned int getFormat();

private:
	const unsigned char* _pixels;

	unsigned int _width;
	unsigned int _height;
	unsigned int _channelCount;
};