#include "texture_loader.hpp"
#include "texture_loader.hpp"
#include "texture_loader.hpp"
#include "texture_loader.hpp"
#include "texture_loader.hpp"
#include "logger.hpp"
#include "tools.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <STB/stb_image.h>

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

/* http://stackoverflow.com/questions/1968561/getting-the-pixel-value-of-bmp-file */
vector<float> TextureLoader::_loadBitmapData(const string& filePath)
{
	const auto rootDirectoryPath = Tools::getRootDirectoryPath();

	vector<float> pixelIntensities;

	FILE* streamIn;
	fopen_s(&streamIn, (rootDirectoryPath + filePath).c_str(), "rb");
	if (streamIn == (FILE*)0)
	{
		return {};
	}

	uint8_t header[54];
	uint32_t width, height = 5;
	for (int i = 0; i < 54; i++)
	{
		header[i] = getc(streamIn);
	}

	width = (header[21] << 24) | (header[20] << 16) | (header[19] << 8) | header[18];
	height = (header[25] << 24) | (header[24] << 16) | (header[23] << 8) | header[22];

	auto size = static_cast<size_t>(width) * static_cast<size_t>(height);
	for (size_t i = 0; i < size; i++)
	{
		auto r = getc(streamIn);
		auto g = getc(streamIn);
		auto b = getc(streamIn);
		float value = (static_cast<float>(r + g + b) / 3.0f);
		pixelIntensities.push_back((value));
	}

	fclose(streamIn);

	return pixelIntensities;
}

shared_ptr<TextureData> TextureLoader::_loadTextureData(const string& filePath)
{
	const auto rootDirectoryPath = Tools::getRootDirectoryPath();

	stbi_set_flip_vertically_on_load(true);

	int width, height, channelCount;
	unsigned char* pixels = stbi_load(string(rootDirectoryPath + filePath).c_str(), &width, &height, &channelCount, 0);

	return make_shared<TextureData>(pixels,
		static_cast<unsigned int>(width),
		static_cast<unsigned int>(height),
		static_cast<unsigned int>(channelCount));
}

TextureID TextureLoader::_create2dTexture(shared_ptr<TextureData> textureData, const string& filePath, bool isMipmapped, bool isAnisotropic)
{
	TextureID texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	if (textureData->getChannelCount() == 4)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureData->getWidth(), textureData->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData->getPixels());
	}
	else if (textureData->getChannelCount() == 3)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureData->getWidth(), textureData->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, textureData->getPixels());
	}
	else
	{
		Logger::throwWarning("Pixel format not recognized at image: \"" + filePath + "\"");
		return 0;
	}

	if (isMipmapped)
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

	if (isAnisotropic)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, static_cast<int>(_anisotropicFilteringQuality));
	}

	Logger::throwInfo("Loaded texture: \"" + filePath + "\"");

	return texture;
}

TextureID TextureLoader::_create3dTexture(const array<shared_ptr<TextureData>, 6>& textures, const array<string, 6>& filePaths)
{
	const auto rootDirectoryPath = Tools::getRootDirectoryPath();

	TextureID texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

	int surfaceSize = -1;
	for (size_t i = 0; i < textures.size(); i++)
	{
		if (textures[i] != nullptr)
		{
			if (textures[i]->getWidth() != textures[i]->getHeight())
			{
				Logger::throwWarning("3D texture width must be same as height: \"" + filePaths[i] + "\"");
				return 0;
			}

			if (surfaceSize == -1)
			{
				surfaceSize = textures[i]->getWidth();
			}
			else
			{
				if (surfaceSize != textures[i]->getWidth())
				{
					Logger::throwWarning("All 3D textures must have the same resolution: \"" + filePaths[i] + "\"");
					return 0;
				}
			}
		}
	}

	for (size_t i = 0; i < textures.size(); i++)
	{
		if (textures[i] == nullptr)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + static_cast<int>(i), 0, GL_RGB, surfaceSize, surfaceSize, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + static_cast<int>(i), 0, GL_RGB, surfaceSize, surfaceSize, 0, GL_RGB, GL_UNSIGNED_BYTE, textures[i]->getPixels());

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
	for (const auto& [path, texture] : _2dTextureCache)
	{
		glBindTexture(GL_TEXTURE_2D, texture);

		int currentQuality;
		glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &currentQuality);

		if ((currentQuality >= Config::MIN_ANISOTROPIC_FILTERING_QUALITY) && (currentQuality <= Config::MAX_ANISOTROPIC_FILTERING_QUALITY))
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