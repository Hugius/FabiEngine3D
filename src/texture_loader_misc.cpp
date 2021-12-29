#include "texture_loader.hpp"
#include "texture_loader.hpp"
#include "texture_loader.hpp"
#include "texture_loader.hpp"
#include "texture_loader.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <SDL\\SDL_image.h>

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
vector<float> TextureLoader::_loadBitmap(const string& filePath)
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

SDL_Surface* TextureLoader::_loadSurface(const string& filePath)
{
	auto temp = freopen("NUL:", "w", stderr);

	const auto rootDirectoryPath = Tools::getRootDirectoryPath();

	SDL_Surface* surface = IMG_Load(string(rootDirectoryPath + filePath).c_str());

	return surface;
}

TextureID TextureLoader::_convertInto2dTexture(SDL_Surface* surface, const string& filePath, bool isMipmapped, bool isAnisotropic)
{
	TextureID texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	if (surface->format->BytesPerPixel == 4)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
	}
	else if (surface->format->BytesPerPixel == 3)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
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

TextureID TextureLoader::_convertInto3dTexture(const array<SDL_Surface*, 6>& surfaces, const array<string, 6>& filePaths)
{
	const auto rootDirectoryPath = Tools::getRootDirectoryPath();

	TextureID texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

	int surfaceSize = -1;
	for (size_t i = 0; i < surfaces.size(); i++)
	{
		if (surfaces[i] != nullptr)
		{
			if (surfaces[i]->w != surfaces[i]->h)
			{
				Logger::throwWarning("3D texture width must be same as height: \"" + filePaths[i] + "\"");
				return 0;
			}

			if (surfaceSize == -1)
			{
				surfaceSize = surfaces[i]->w;
			}
			else
			{
				if (surfaceSize != surfaces[i]->w)
				{
					Logger::throwWarning("All 3D textures must have the same resolution: \"" + filePaths[i] + "\"");
					return 0;
				}
			}
		}
	}

	for (size_t i = 0; i < surfaces.size(); i++)
	{
		if (surfaces[i] == nullptr)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + static_cast<int>(i), 0, GL_RGB, surfaceSize, surfaceSize, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + static_cast<int>(i), 0, GL_RGB, surfaceSize, surfaceSize, 0, GL_RGB, GL_UNSIGNED_BYTE, surfaces[i]->pixels);

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