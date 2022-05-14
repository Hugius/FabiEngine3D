#include "texture_buffer.hpp"

using std::min;

TextureBuffer::TextureBuffer(unsigned int tboId)
	:
	_tboId(tboId)
{

}

TextureBuffer::TextureBuffer(shared_ptr<Image> image)
{
	glGenTextures(1, &_tboId);

	glBindTexture(GL_TEXTURE_2D, _tboId);

	if(image->getBitsPerPixel() == 24)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->getWidth(), image->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, image->getPixels());
	}
	if(image->getBitsPerPixel() == 32)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->getWidth(), image->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image->getPixels());
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

TextureBuffer::TextureBuffer(const array<shared_ptr<Image>, 6> & images)
{
	glGenTextures(1, &_tboId);

	glBindTexture(GL_TEXTURE_CUBE_MAP, _tboId);

	int imageSize = 1;

	for(const auto & image : images)
	{
		if(image != nullptr)
		{
			imageSize = image->getWidth();

			break;
		}
	}

	for(int index = 0; index < static_cast<int>(images.size()); index++)
	{
		const auto cubeIndex = (GL_TEXTURE_CUBE_MAP_POSITIVE_X + static_cast<int>(index));

		if(images[index] == nullptr)
		{
			unsigned char * pixels = new unsigned char[imageSize * imageSize * 3];

			for(int index = 0; index < (imageSize * imageSize * 3); index++)
			{
				pixels[index] = 255;
			}

			glTexImage2D(cubeIndex, 0, GL_RGB, imageSize, imageSize, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);

			delete[] pixels;
		}
		else
		{
			glTexImage2D(cubeIndex, 0, GL_RGB, imageSize, imageSize, 0, GL_RGB, GL_UNSIGNED_BYTE, images[index]->getPixels());
		}
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

TextureBuffer::~TextureBuffer()
{
	glDeleteTextures(1, &_tboId);
}

const unsigned int TextureBuffer::getTboId() const
{
	return _tboId;
}

const bool TextureBuffer::isMipMapped() const
{
	return _isMipMapped;
}

const bool TextureBuffer::isAnisotropicallyFiltered() const
{
	return _isAnisotropicallyFiltered;
}

void TextureBuffer::loadMipMapping()
{
	glBindTexture(GL_TEXTURE_2D, _tboId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	_isMipMapped = true;
}

void TextureBuffer::loadAnisotropicFiltering(int quality)
{
	glBindTexture(GL_TEXTURE_2D, _tboId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY, quality);

	glBindTexture(GL_TEXTURE_2D, 0);

	_isAnisotropicallyFiltered = true;
}