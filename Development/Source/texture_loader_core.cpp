#include "texture_loader.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <SDL\\SDL_image.h>

SDL_Surface* TextureLoader::_loadImage(const string& filePath)
{
	// Disable libpng warnings
	auto temp = freopen("NUL:", "w", stderr);

	// Get application root directory
	string rootDir = Tools::getInst().getRootDirectory();
	string fullFilePath = string(rootDir + filePath);

	// Load actual image data
	SDL_Surface * image = IMG_Load(fullFilePath.c_str());
	if (image == nullptr)
	{
		Logger::throwWarning("Cannot open image: \"" + filePath + "\"");
	}

	// Return
	return image;
}

GLuint TextureLoader::_convertToTexture2D(const string& filePath, SDL_Surface* image, bool mipmap, bool aniso, bool repeat)
{
	// Generate OpenGL texture
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Determing the pixel format
	if (image->format->BytesPerPixel == 4)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
	}
	else if (image->format->BytesPerPixel == 3)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
	}
	else
	{
		Logger::throwWarning("Pixel format not recognized at texture: \"" + filePath + "\"");
		return 0;
	}

	// Mipmapping or not
	if (mipmap)
	{
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	// Anisotropic filtering
	if (aniso)
	{
		float temp;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &temp);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, temp);
	}

	// Repeat dimensions
	if (repeat)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
	}

	// Logging
	Logger::throwInfo("Loaded 2D texture: \"" + filePath + "\"");

	// Return new texture
	return texture;
}

GLuint TextureLoader::_convertToTexture3D(const array<string, 6>& filePaths, const array<SDL_Surface*, 6>& images)
{
	// Get application root directory
	string rootDir = Tools::getInst().getRootDirectory();

	// Temporary values
	GLuint texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

	// Validate image sizes
	int imageSize = -1;
	for (unsigned int i = 0; i < images.size(); i++)
	{
		// Check image status
		if (images[i] != nullptr)
		{
			// Check if resolution dimensions are the same
			if (images[i]->w != images[i]->h)
			{
				Logger::throwWarning("3D texture width must be same as height: \"" + filePaths[i] + "\"");
				return 0;
			}

			// Check if resolution dimensions are the same as all others
			if (imageSize != -1)
			{
				if (imageSize != images[i]->w)
				{
					Logger::throwWarning("All 3D textures must have the same resolution: \"" + filePaths[i] + "\"");
					return 0;
				}
			}
		}
	}

	// Add the face images to the texture buffer
	for (unsigned int i = 0; i < images.size(); i++)
	{
		// Check image status
		if (images[i] == nullptr)
		{
			// Black image
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, imageSize, imageSize, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
		}
		else
		{
			// Loaded image
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, images[i]->w, images[i]->h, 0, GL_RGB, GL_UNSIGNED_BYTE, images[i]->pixels);
		}

		// Logging
		Logger::throwInfo("Loaded 3D texture: \"" + filePaths[i] + "\"");
	}

	// OpenGL magic
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	// Return new texture
	return texture;
}

TTF_Font* TextureLoader::_loadFont(const string& fontPath)
{
	// Get application root directory
	string rootDir = Tools::getInst().getRootDirectory();

	// Load font
	auto it = _fontCache.find(fontPath);
	if (it == _fontCache.end()) //Not in map (yet)
	{
		// Try to load font
		TTF_Font* font = TTF_OpenFont((rootDir + fontPath).c_str(), 50);

		// Check if font loading is successful
		if (font == nullptr)
		{
			Logger::throwWarning("Cannot load font: \"" + fontPath + "\"");
			return nullptr;
		}
		else
		{
			// Save font to cache
			_fontCache.insert(std::make_pair(fontPath, font));
			Logger::throwInfo("Loaded font: \"" + fontPath + "\"");
			return font;
		}
	}

	return it->second; //Cache texture
}

GLuint TextureLoader::_loadText(const string& textContent, const string& fontPath)
{
	std::string newText;

	// No empty text
	if (textContent == "")
	{
		newText = " ";
	}
	else
	{
		newText = textContent;
	}

	// Load font
	auto font = _loadFont(fontPath);

	// Check if font loading went well
	if (font == nullptr)
	{
		return 0;
	}

	// Load color
	SDL_Color* sdlColor = new SDL_Color{ 255, 255, 255 };

	// Texture data of text
	SDL_Surface* surface = TTF_RenderText_Blended(font, newText.c_str(), *sdlColor);

	// OpenGL Texture
	GLuint tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);

	// Determine pixel format
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
		Logger::throwWarning("Pixel format not recognized while generating TEXT texture: \"" + textContent + "\"");
		return 0;
	}

	// Memory management
	SDL_FreeSurface(surface);

	return tex;
}

vector<float> TextureLoader::_loadBitmapPixels(const string& filePath) // http://stackoverflow.com/questions/1968561/getting-the-pixel-value-of-bmp-file
{
	// Get application root directory
	string rootDir = Tools::getInst().getRootDirectory();

	// Pixels
	vector<float> pixelIntensities;

	// Open file
	FILE* streamIn;
	fopen_s(&streamIn, (rootDir + filePath).c_str(), "rb");
	if (streamIn == (FILE*)0)
	{
		Logger::throwWarning("Cannot open bitmap image: \"" + filePath + "\"");
		return {};
	}

	// File header
	uint8_t header[54];
	uint32_t width, height = 5;
	for (int i = 0; i < 54; i++)
	{
		header[i] = getc(streamIn);
	}

	// Extract resolution
	width = (header[21] << 24) | (header[20] << 16) | (header[19] << 8) | header[18];
	height = (header[25] << 24) | (header[24] << 16) | (header[23] << 8) | header[22];

	// Read pixels
	auto size = static_cast<size_t>(width) * static_cast<size_t>(height);
	for (size_t i = 0; i < size; i++)
	{
		auto r = getc(streamIn);
		auto g = getc(streamIn);
		auto b = getc(streamIn);
		float value = static_cast<float>(r + g + b) / 3.0f;
		pixelIntensities.push_back((value));
	}

	// Close file
	fclose(streamIn);

	// Logging
	Logger::throwInfo("Loaded bitmap image: \"" + filePath + "\"");

	// Return new texture
	return pixelIntensities;
}