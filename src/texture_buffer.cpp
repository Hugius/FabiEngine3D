#include "texture_buffer.hpp"
#include "configuration.hpp"

using std::clamp;

TextureBuffer::TextureBuffer(unsigned int id)
	:
	_id(id)
{

}

TextureBuffer::TextureBuffer(shared_ptr<Image> image)
{
	glGenTextures(1, &_id);
	glBindTexture(GL_TEXTURE_2D, _id);

	if(image->getPixelFormat() == PixelFormat::RGB)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->getWidth(), image->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, image->getPixels());
	}
	if(image->getPixelFormat() == PixelFormat::RGBA)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->getWidth(), image->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image->getPixels());
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

TextureBuffer::TextureBuffer(const array<shared_ptr<Image>, 6>& images)
{
	glGenTextures(1, &_id);

	glBindTexture(GL_TEXTURE_CUBE_MAP, _id);

	unsigned int imageSize = 1;
	for(const auto& image : images)
	{
		if(image != nullptr)
		{
			imageSize = image->getWidth();
			break;
		}
	}

	for(size_t i = 0; i < images.size(); i++)
	{
		const auto cubeIndex = (GL_TEXTURE_CUBE_MAP_POSITIVE_X + static_cast<unsigned int>(i));

		if(images[i] == nullptr)
		{
			unsigned char* pixels = new unsigned char[imageSize * imageSize * 3];

			for(unsigned int i = 0; i < (imageSize * imageSize * 3); i++)
			{
				pixels[i] = 255;
			}

			glTexImage2D(cubeIndex, 0, GL_RGB, imageSize, imageSize, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);

			delete[] pixels;
		}
		else
		{
			glTexImage2D(cubeIndex, 0, GL_RGB, imageSize, imageSize, 0, GL_RGB, GL_UNSIGNED_BYTE, images[i]->getPixels());
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
	glDeleteTextures(1, &_id);
}

const unsigned int TextureBuffer::getId() const
{
	return _id;
}

void TextureBuffer::loadMipMapping()
{
	glBindTexture(GL_TEXTURE_2D, _id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureBuffer::loadAnisotropicFiltering(unsigned int quality)
{
	glBindTexture(GL_TEXTURE_2D, _id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY, static_cast<int>(quality));

	glBindTexture(GL_TEXTURE_2D, 0);
}

const unsigned int TextureBuffer::getAnisotropicFilteringQuality() const
{
	int quality;

	glGetIntegerv(GL_TEXTURE_MAX_ANISOTROPY, &quality);

	return quality;
}