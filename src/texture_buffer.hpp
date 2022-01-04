#pragma once

#include "image.hpp"

#include <string>
#include <array>
#include <memory>
#include <glew.h>

using std::array;
using std::string;
using std::shared_ptr;

using BufferID = GLuint;

class TextureBuffer final
{
public:
	TextureBuffer(BufferID ID);
	TextureBuffer(shared_ptr<Image> image, bool isMipmapped, bool isAnisotropic);
	TextureBuffer(const array<shared_ptr<Image>, 6>& images);
	~TextureBuffer();

	const BufferID getID();

private:
	BufferID _ID;
};