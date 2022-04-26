#pragma once

#define GLEW_STATIC

#include "image.hpp"

#include <array>
#include <memory>
#include <glew.h>

using std::array;
using std::shared_ptr;

class TextureBuffer final
{
public:
	TextureBuffer(unsigned int tboId);
	TextureBuffer(shared_ptr<Image> image);
	TextureBuffer(const array<shared_ptr<Image>, 6> & images);
	~TextureBuffer();

	void loadMipMapping();
	void loadAnisotropicFiltering(unsigned int quality);

	const int getTboId() const;

	const bool isMipMapped() const;
	const bool isAnisotropicallyFiltered() const;

private:
	unsigned int _tboId;

	bool _isMipMapped = false;
	bool _isAnisotropicallyFiltered = false;
};