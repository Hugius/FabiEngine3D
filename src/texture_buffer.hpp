#pragma once

#include "image.hpp"

#include <array>
#include <memory>
#include <glew.h>

using std::array;
using std::shared_ptr;

using BufferId = GLuint;

class TextureBuffer final
{
public:
	TextureBuffer(BufferId id);
	TextureBuffer(shared_ptr<Image> image);
	TextureBuffer(const array<shared_ptr<Image>, 6>& images);
	~TextureBuffer();

	void loadMipMapping();
	void loadAnisotropicFiltering(unsigned int quality);

	const unsigned int getAnisotropicFilteringQuality() const;

	const BufferId getId() const;

private:
	BufferId _id;
};