#pragma once

#include "image.hpp"

#include <array>
#include <memory>
#include <glew.h>

using std::array;
using std::shared_ptr;

class TextureBuffer final
{
public:
	TextureBuffer(unsigned int id);
	TextureBuffer(shared_ptr<Image> image);
	TextureBuffer(const array<shared_ptr<Image>, 6>& images);
	~TextureBuffer();

	void loadMipMapping();
	void loadAnisotropicFiltering(unsigned int quality);

	const unsigned int getAnisotropicFilteringQuality() const;
	const unsigned int getId() const;

private:
	unsigned int _id;
};