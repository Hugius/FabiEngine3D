#include "texture_loader.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <SDL\\SDL_image.h>

// http://stackoverflow.com/questions/1968561/getting-the-pixel-value-of-bmp-file
vector<float> TextureLoader::_loadBitmap(const string& filePath)
{
	// Get application root directory
	const auto rootDirectoryPath = Tools::getRootDirectoryPath();

	// Temporary values
	vector<float> pixelIntensities;

	// Open file
	FILE* streamIn;
	fopen_s(&streamIn, (rootDirectoryPath + filePath).c_str(), "rb");
	if(streamIn == (FILE*)0)
	{
		return {};
	}

	// File header
	uint8_t header[54];
	uint32_t width, height = 5;
	for(int i = 0; i < 54; i++)
	{
		header[i] = getc(streamIn);
	}

	// Extract resolution
	width = (header[21] << 24) | (header[20] << 16) | (header[19] << 8) | header[18];
	height = (header[25] << 24) | (header[24] << 16) | (header[23] << 8) | header[22];

	// Read pixels
	auto size = static_cast<size_t>(width) * static_cast<size_t>(height);
	for(size_t i = 0; i < size; i++)
	{
		auto r = getc(streamIn);
		auto g = getc(streamIn);
		auto b = getc(streamIn);
		float value = (static_cast<float>(r + g + b) / 3.0f);
		pixelIntensities.push_back((value));
	}

	// Close file
	fclose(streamIn);

	// Return new texture
	return pixelIntensities;
}

SDL_Surface* TextureLoader::_loadSurface(const string& filePath)
{
	// Disable libpng warnings
	auto temp = freopen("NUL:", "w", stderr);

	// Get application root directory
	const auto rootDirectoryPath = Tools::getRootDirectoryPath();

	// Load SDL surface
	SDL_Surface* surface = IMG_Load(string(rootDirectoryPath + filePath).c_str());

	// Return
	return surface;
}

TTF_Font* TextureLoader::_loadFont(const string& filePath)
{
	// Get application root directory
	const auto rootDirectoryPath = Tools::getRootDirectoryPath();

	// Load TTF font
	TTF_Font* font = TTF_OpenFont((rootDirectoryPath + filePath).c_str(), 32);

	// Return
	return font;
}

TextureID TextureLoader::_convertIntoTexture(SDL_Surface* surface, const string& filePath, bool isMipmapped, bool isAnisotropic)
{
	// Generate OpenGL texture
	TextureID texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Determing the pixel format
	if(surface->format->BytesPerPixel == 4)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
	}
	else if(surface->format->BytesPerPixel == 3)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
	}
	else
	{
		Logger::throwWarning("Pixel format not recognized at image: \"" + filePath + "\"");
		return 0;
	}

	if(isMipmapped) // Mipmapping
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else // Normal filtering
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	// Anisotropic filtering
	if(isAnisotropic)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, static_cast<int>(_anisotropicFilteringQuality));
	}

	// Logging
	Logger::throwInfo("Loaded 2D texture: \"" + filePath + "\"");

	// Return new texture
	return texture;
}

TextureID TextureLoader::_convertIntoTexture(const array<SDL_Surface*, 6>& surfaces, const array<string, 6>& filePaths)
{
	// Get application root directory
	const auto rootDirectoryPath = Tools::getRootDirectoryPath();

	// Temporary values
	TextureID texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

	// Validate surface sizes
	int surfaceSize = -1;
	for(size_t i = 0; i < surfaces.size(); i++)
	{
		// Check surface status
		if(surfaces[i] != nullptr)
		{
			// Check if resolution dimensions are the same
			if(surfaces[i]->w != surfaces[i]->h)
			{
				Logger::throwWarning("3D texture width must be same as height: \"" + filePaths[i] + "\"");
				return 0;
			}

			// Check if resolution dimensions are the same as all others
			if(surfaceSize == -1)
			{
				surfaceSize = surfaces[i]->w;
			}
			else
			{
				if(surfaceSize != surfaces[i]->w)
				{
					Logger::throwWarning("All 3D textures must have the same resolution: \"" + filePaths[i] + "\"");
					return 0;
				}
			}
		}
	}

	// Add the face surfaces to the texture buffer
	for(size_t i = 0; i < surfaces.size(); i++)
	{
		// Check surface status
		if(surfaces[i] == nullptr)
		{
			// Black surface
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + static_cast<int>(i), 0, GL_RGB, surfaceSize, surfaceSize, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
		}
		else
		{
			// Loaded surface
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + static_cast<int>(i), 0, GL_RGB, surfaceSize, surfaceSize, 0, GL_RGB, GL_UNSIGNED_BYTE, surfaces[i]->pixels);

			// Logging
			Logger::throwInfo("Loaded 3D texture part: \"" + filePaths[i] + "\"");
		}
	}

	// OpenGL magic
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	// Return new texture
	return texture;
}

TextureID TextureLoader::_convertIntoTexture(TTF_Font* font, const string& textContent)
{
	// Load color
	SDL_Color* color = new SDL_Color{255, 255, 255, 255};

	// No empty text
	string finalTextContent = (textContent.empty() ? " " : textContent);

	// Texture data of text
	SDL_Surface* surface = TTF_RenderText_Blended(font, finalTextContent.c_str(), *color);

	// OpenGL Texture
	TextureID texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Determine pixel format
	if(surface->format->BytesPerPixel == 4)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
	}
	else if(surface->format->BytesPerPixel == 3)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
	}
	else
	{
		Logger::throwError("TextureLoader::_loadText");
	}

	// Memory management
	SDL_FreeSurface(surface);

	// Return
	return texture;
}

void TextureLoader::_reloadAnisotropicFiltering()
{
	for(const auto& [path, texture] : _textureCache2D)
	{
		// Bind
		glBindTexture(GL_TEXTURE_2D, texture);

		// Get current quality
		int currentQuality;
		glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &currentQuality);

		// Check if texture must be anisotropically filtered
		if((currentQuality >= Config::MIN_ANISOTROPIC_FILTERING_QUALITY) && (currentQuality <= Config::MAX_ANISOTROPIC_FILTERING_QUALITY))
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, static_cast<int>(_anisotropicFilteringQuality));
		}

		// Unbind
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}