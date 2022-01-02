#include "texture_loader.hpp"
#include "logger.hpp"
#include "tools.hpp"

#pragma warning(disable:6385)
#pragma warning(disable:6386)

using std::clamp;

TextureLoader::TextureLoader(RenderBus& renderBus)
	:
	_renderBus(renderBus)
{

}

shared_ptr<Image> TextureLoader::_loadImage(const string& filePath, bool mustFlip)
{
	const auto rootPath = Tools::getRootDirectoryPath();

	auto file = fopen(string(rootPath + filePath).c_str(), "rb");
	if(file == nullptr)
	{
		return nullptr;
	}

	auto header = new uint8_t[54];
	for(int i = 0; i < 54; i++)
	{
		header[i] = getc(file);
	}

	uint32_t rawWidth = ((header[21] << 24) | (header[20] << 16) | (header[19] << 8) | header[18]);
	uint32_t rawHeight = ((header[25] << 24) | (header[24] << 16) | (header[23] << 8) | header[22]);
	uint16_t rawFormat = ((header[29] << 8) | header[28]);

	if((rawWidth == 0) || (rawHeight == 0))
	{
		return nullptr;
	}

	if((rawFormat != 8) && (rawFormat != 24) && (rawFormat != 32))
	{
		return nullptr;
	}

	const auto width = static_cast<unsigned int>(rawWidth);
	const auto height = static_cast<unsigned int>(rawHeight);
	const auto bitFormat = static_cast<unsigned int>(rawFormat);
	const auto byteFormat = (bitFormat / 8);
	const auto size = (width * height * byteFormat);
	const auto pixels = new unsigned char[size];

	for(unsigned i = 0; i < size; i++)
	{
		pixels[i] = static_cast<unsigned char>(getc(file));
	}

	auto correctedPixels = new unsigned char[size];
	for(unsigned y = 0; y < height; y++)
	{
		for(unsigned x = 0; x < width; x++)
		{
			const unsigned int index1 = ((x * byteFormat) + (y * width * byteFormat));
			const unsigned int index2 = (mustFlip ? ((x * byteFormat) + ((height - y - 1) * width * byteFormat)) : index1);

			if(byteFormat == 1)
			{
				correctedPixels[index1 + 0] = pixels[index2 + 0];
			}
			if(byteFormat == 3)
			{
				correctedPixels[index1 + 0] = pixels[index2 + 2];
				correctedPixels[index1 + 1] = pixels[index2 + 1];
				correctedPixels[index1 + 2] = pixels[index2 + 0];
			}
			if(byteFormat == 4)
			{
				correctedPixels[index1 + 0] = pixels[index2 + 2];
				correctedPixels[index1 + 1] = pixels[index2 + 1];
				correctedPixels[index1 + 2] = pixels[index2 + 0];
				correctedPixels[index1 + 3] = pixels[index2 + 3];
			}
		}
	}

	delete[] header;
	delete[] pixels;
	fclose(file);

	return make_shared<Image>(correctedPixels,
							  static_cast<unsigned int>(width),
							  static_cast<unsigned int>(height),
							  PixelFormat(bitFormat == 8 ? PixelFormat::GRAY : bitFormat == 24 ? PixelFormat::RGB : PixelFormat::RGBA));
}

TextureID TextureLoader::_create2dTexture(shared_ptr<Image> image, const string& filePath, bool isMipmapped, bool isAnisotropic)
{
	TextureID texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	if(image->getPixelFormat() == PixelFormat::GRAY)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, image->getWidth(), image->getHeight(), 0, GL_RED, GL_UNSIGNED_BYTE, image->getPixels());
	}
	if(image->getPixelFormat() == PixelFormat::RGB)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->getWidth(), image->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, image->getPixels());
	}
	if(image->getPixelFormat() == PixelFormat::RGBA)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->getWidth(), image->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image->getPixels());
	}

	if(isMipmapped)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	if(isAnisotropic)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, static_cast<int>(_anisotropicFilteringQuality));
	}

	return texture;
}

TextureID TextureLoader::_create3dTexture(const array<shared_ptr<Image>, 6>& images, const array<string, 6>& filePaths)
{
	TextureID texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

	for(size_t i = 0; i < images.size(); i++)
	{
		const auto image = images[i];
		const auto index = (GL_TEXTURE_CUBE_MAP_POSITIVE_X + static_cast<unsigned int>(i));

		if(image == nullptr)
		{
			glTexImage2D(index, 0, GL_RGB, images[i]->getWidth(), images[i]->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
			continue;
		}

		if(image->getPixelFormat() == PixelFormat::GRAY)
		{
			glTexImage2D(index, 0, GL_RED, image->getWidth(), image->getHeight(), 0, GL_RED, GL_UNSIGNED_BYTE, image->getPixels());
		}
		if(image->getPixelFormat() == PixelFormat::RGB)
		{
			glTexImage2D(index, 0, GL_RGB, image->getWidth(), image->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, image->getPixels());
		}
		if(image->getPixelFormat() == PixelFormat::RGBA)
		{
			glTexImage2D(index, 0, GL_RGBA, image->getWidth(), image->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image->getPixels());
		}
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	return texture;
}

void TextureLoader::_reloadAnisotropicFiltering()
{
	for(const auto& [path, texture] : _2dTextureCache)
	{
		glBindTexture(GL_TEXTURE_2D, texture);

		int currentQuality;
		glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &currentQuality);

		if((currentQuality >= Config::MIN_ANISOTROPIC_FILTERING_QUALITY) && (currentQuality <= Config::MAX_ANISOTROPIC_FILTERING_QUALITY))
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, static_cast<int>(_anisotropicFilteringQuality));
		}

		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void TextureLoader::setAnisotropicFilteringQuality(unsigned int value)
{
	_anisotropicFilteringQuality = clamp(value, Config::MIN_ANISOTROPIC_FILTERING_QUALITY, Config::MAX_ANISOTROPIC_FILTERING_QUALITY);
	_reloadAnisotropicFiltering();
}

const unsigned int TextureLoader::getAnisotropicFilteringQuality()const
{
	return _anisotropicFilteringQuality;
}