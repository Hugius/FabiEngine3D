#pragma once

#include "image.hpp"

#include <string>
#include <array>
#include <memory>
#include <glew.h>

using std::array;
using std::string;
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

	const bool hasAnisotropicFiltering() const;
	const BufferId getId() const;

private:
	BufferId _id;
};