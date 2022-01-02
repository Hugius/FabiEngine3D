#pragma once

#include "image.hpp"
#include "render_utils.hpp"

#include <string>
#include <array>
#include <memory>

using std::string;
using std::array;
using std::shared_ptr;

class TextureBuffer final
{
public:
	TextureBuffer(shared_ptr<Image> image, bool isMipmapped, bool isAnisotropic);
	TextureBuffer(const array<shared_ptr<Image>, 6>& images);
	~TextureBuffer();

	const BufferID getTexture();

private:
	BufferID _texture;
};