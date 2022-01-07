#include "texture_buffer.hpp"
#include "configuration.hpp"

using std::clamp;

TextureBuffer::TextureBuffer(BufferID ID)
	:
	_ID(ID)
{

}

TextureBuffer::TextureBuffer(shared_ptr<Image> image)
{
	glGenTextures(1, &_ID);
	glBindTexture(GL_TEXTURE_2D, _ID);

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
	glGenTextures(1, &_ID);

	glBindTexture(GL_TEXTURE_CUBE_MAP, _ID);

	unsigned int imageSize = 0;
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
			glTexImage2D(cubeIndex, 0, GL_RGB, imageSize, imageSize, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
			continue;
		}

		if(images[i]->getPixelFormat() == PixelFormat::RGB)
		{
			glTexImage2D(cubeIndex, 0, GL_RGB, images[i]->getWidth(), images[i]->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, images[i]->getPixels());
		}
		if(images[i]->getPixelFormat() == PixelFormat::RGBA)
		{
			glTexImage2D(cubeIndex, 0, GL_RGBA, images[i]->getWidth(), images[i]->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, images[i]->getPixels());
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
	glDeleteTextures(1, &_ID);
}

const BufferID TextureBuffer::getID() const
{
	return _ID;
}

void TextureBuffer::loadMipMapping()
{
	glBindTexture(GL_TEXTURE_2D, _ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureBuffer::loadAnisotropicFiltering(unsigned int quality)
{
	quality = clamp(quality, Config::MIN_ANISOTROPIC_FILTERING_QUALITY, Config::MAX_ANISOTROPIC_FILTERING_QUALITY);

	glBindTexture(GL_TEXTURE_2D, _ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY, static_cast<int>(quality));

	glBindTexture(GL_TEXTURE_2D, 0);
}

const bool TextureBuffer::hasAnisotropicFiltering() const
{
	int currentQuality;

	glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY, &currentQuality);

	return ((currentQuality >= Config::MIN_ANISOTROPIC_FILTERING_QUALITY) && (currentQuality <= Config::MAX_ANISOTROPIC_FILTERING_QUALITY));
}