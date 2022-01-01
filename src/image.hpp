#pragma once

class Image final
{
public:
	Image(unsigned char* pixels, unsigned int width, unsigned int height, unsigned int format);
	~Image();

	const unsigned char* getPixels();

	const unsigned int getWidth();
	const unsigned int getHeight();
	const unsigned int getFormat();

private:
	const unsigned char* _pixels;

	const unsigned int _width;
	const unsigned int _height;
	const unsigned int _format;
};