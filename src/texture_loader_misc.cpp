#include "texture_loader.hpp"
#include "logger.hpp"
#include "tools.hpp"

using std::clamp;

TextureLoader::TextureLoader(RenderBus& renderBus)
	:
	_renderBus(renderBus)
{

}

void TextureLoader::cache2dTexture(const string& filePath, bool isMipmapped, bool isAnisotropic)
{
	load2dTexture(filePath, isMipmapped, isAnisotropic);
}

void TextureLoader::cache3dTexture(const array<string, 6>& filePaths)
{
	load3dTexture(filePaths);
}

void TextureLoader::cacheBitmap(const string& filePath)
{
	loadBitmap(filePath);
}

vector<float> TextureLoader::_loadBitmap(const string& filePath)
{
	vector<float> result;

	auto image = _loadImage(filePath, false);
	auto pixels = image->getPixels();

	if(image->getFormat() != 8)
	{

	}

	for(unsigned int i = 0; i < (image->getWidth() * image->getHeight()); i++)
	{
		result.push_back(static_cast<float>(pixels[i]) / 255.0f);
	}

	return result;
}

shared_ptr<Image> TextureLoader::_loadImage(const string& filePath, bool mustFlip)
{
	const auto rootPath = Tools::getRootDirectoryPath();

	auto file = fopen(string(rootPath + filePath).c_str(), "rb");
	if(file == nullptr)
	{
		return nullptr;
	}

	uint8_t header[54];
	for(int i = 0; i < 54; i++)
	{
		header[i] = getc(file);
	}

	uint32_t rawWidth, rawHeight;
	uint16_t rawFormat;
	rawWidth = ((header[21] << 24) | (header[20] << 16) | (header[19] << 8) | header[18]);
	rawHeight = ((header[25] << 24) | (header[24] << 16) | (header[23] << 8) | header[22]);
	rawFormat = ((header[29] << 8) | header[28]);

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
	const auto format = (static_cast<unsigned int>(rawFormat) / 8);
	const auto size = (width * height * format);
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
			const unsigned int index1 = ((x * format) + (y * width * format));
			const unsigned int index2 = (mustFlip ? ((x * format) + ((height - y - 1) * width * format)) : index1);

			if(format == 1)
			{
				correctedPixels[index1 + 0] = pixels[index2 + 0];
			}
			if(format == 3)
			{
				correctedPixels[index1 + 0] = pixels[index2 + 2];
				correctedPixels[index1 + 1] = pixels[index2 + 1];
				correctedPixels[index1 + 2] = pixels[index2 + 0];
			}
			if(format == 4)
			{
				correctedPixels[index1 + 0] = pixels[index2 + 2];
				correctedPixels[index1 + 1] = pixels[index2 + 1];
				correctedPixels[index1 + 2] = pixels[index2 + 0];
				correctedPixels[index1 + 3] = pixels[index2 + 3];
			}
		}
	}

	fclose(file);

	return make_shared<Image>(correctedPixels,
							  static_cast<unsigned int>(width),
							  static_cast<unsigned int>(height),
							  static_cast<unsigned int>(format));
}

TextureID TextureLoader::_create2dTexture(shared_ptr<Image> image, const string& filePath, bool isMipmapped, bool isAnisotropic)
{
	TextureID texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	if(image->getFormat() == 3)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->getWidth(), image->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, image->getPixels());
	}
	if(image->getFormat() == 4)
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

	Logger::throwInfo("Loaded texture: \"" + filePath + "\"");

	return texture;
}

TextureID TextureLoader::_create3dTexture(const array<shared_ptr<Image>, 6>& images, const array<string, 6>& filePaths)
{
	unsigned int imageSize = 0;
	for(size_t i = 0; i < images.size(); i++)
	{
		if(images[i] != nullptr)
		{
			if(images[i]->getWidth() != images[i]->getHeight())
			{
				Logger::throwWarning("3D texture resolution must be squared: \"" + filePaths[i] + "\"");
				return 0;
			}

			if(imageSize == 0)
			{
				imageSize = images[i]->getWidth();
			}
			else
			{
				if(imageSize != images[i]->getWidth())
				{
					Logger::throwWarning("3D texture resolution must be the same: \"" + filePaths[i] + "\"");
					return 0;
				}
			}
		}
	}

	TextureID texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

	for(size_t i = 0; i < images.size(); i++)
	{
		if(images[i] == nullptr)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + static_cast<int>(i), 0, GL_RGB, imageSize, imageSize, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + static_cast<int>(i), 0, GL_RGB, imageSize, imageSize, 0, GL_RGB, GL_UNSIGNED_BYTE, images[i]->getPixels());

			Logger::throwInfo("Loaded texture: \"" + filePaths[i] + "\"");
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