#pragma once

class Image final
{
public:
	Image(unsigned char * pixels, unsigned int width, unsigned int height, unsigned int bitsPerPixel);
	~Image();

	void flipX();
	void flipY();

	const unsigned char * getPixels() const;

	const unsigned int getWidth() const;
	const unsigned int getHeight() const;

	const unsigned int getBitsPerPixel() const;

private:
	const unsigned char * _pixels;

	const unsigned int _width;
	const unsigned int _height;

	const unsigned int _bitsPerPixel;
};