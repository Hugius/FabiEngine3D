#include <SDL/SDL_image.h>

#include "TextureLoader.hpp"
#include "Logger.hpp"

GLuint TextureLoader::_loadText(const string& text, const string &fontPath)
{
	std::string newText;

	// No empty text
	if (text == "")
	{
		newText = " ";
	}
	else
	{
		newText = text;
	}

	// Load font
	auto font = _loadFont(fontPath);

	// Load color
	SDL_Color * sdlColor = new SDL_Color{ 255, 255, 255 };
	if (sdlColor == nullptr)
	{
		Logger::getInst().throwError("Color could not be created at rgb: " + std::to_string(sdlColor->r) + std::to_string(sdlColor->g) + std::to_string(sdlColor->b));
	}

	// Texture data of text
	SDL_Surface * surface = TTF_RenderText_Blended(font, newText.c_str(), *sdlColor);

	// OpenGL Texture
	GLuint tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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
		Logger::getInst().throwError("Pixel format not recognized at text texture: " + text);
	}

	// Memory management
	SDL_FreeSurface(surface);

	return tex;
}

GLuint TextureLoader::_loadTexture(const string& filePath, bool mipmap, bool aniso, bool repeat)
{
	// Get application root directory
	char buffer[256]; size_t len = sizeof(buffer);
	GetModuleFileName(NULL, buffer, len);
	string fullDir = buffer;
	fullDir = fullDir.substr(0, fullDir.size() - 25);

	// Load actual texture data
	SDL_Surface * surface = IMG_Load((fullDir + filePath + ".png").c_str());
	if (surface == nullptr)
	{
		Logger::getInst().throwError("Texture error: " + string(SDL_GetError()));
	}

	// Generate OpenGL texture
	GLuint tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	// Determing the pixel format
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
		Logger::getInst().throwError("Pixel format not recognized at image: " + filePath);
	}

	// Memory management
	SDL_FreeSurface(surface);

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
	Logger::getInst().throwInfo("Loaded texture: " + filePath + ".png");

	// Return new texture
	return tex;
}

// http://stackoverflow.com/questions/1968561/getting-the-pixel-value-of-bmp-file
vector<float> TextureLoader::_loadHeightmap(const string & filePath, int size)
{
	// Pixels
	vector<float> pixelIntensities;

	// Open file
	FILE * streamIn;
	fopen_s(&streamIn, (filePath + ".bmp").c_str(), "rb");
	if (streamIn == (FILE *)0) 
	{
		Logger::getInst().throwError("Could not open heightmap: " + filePath + ".bmp");
	}

	// File header
	int byte;
	for (int i = 0; i < 54; i++) byte = getc(streamIn);

	// Read pixels
	for (int i = 0; i < (size * size); i++)
	{
		pixelIntensities.push_back(0.0f);
		auto r = getc(streamIn);
		auto g = getc(streamIn);
		auto b = getc(streamIn);
		pixelIntensities.back() = static_cast<float>(r);
	}

	// Close file
	fclose(streamIn);

	// Logging
	Logger::getInst().throwInfo("Loaded BMP heightmap: " + filePath + ".bmp");

	// Return new texture
	return pixelIntensities;
}

GLuint TextureLoader::_loadCubemap(const string & filePath)
{
	// Get application root directory
	char buffer[256]; size_t len = sizeof(buffer);
	GetModuleFileName(NULL, buffer, len);
	string fullDir = buffer;
	fullDir = fullDir.substr(0, fullDir.size() - 25);

	// Init
	GLuint textureID;
	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	vector<string> fileNames = { "right", "left", "top", "bottom", "back", "front" };

	// Add the faces images to the texture buffer(textureID)
	for (GLuint i = 0; i < fileNames.size(); i++)
	{
		// Load SDL surface
		SDL_Surface * surface = IMG_Load((fullDir + filePath + fileNames[i] + ".png").c_str());
		if (surface == nullptr) 
		{
			Logger::getInst().throwError("Skybox textures could not be loaded: " + string(SDL_GetError()));
		}

		// Convert to OpenGL texture
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);

		// Logging
		Logger::getInst().throwInfo("Loaded cubemap texture: " + filePath + fileNames[i] + ".png");
	}

	// OpenGL magic
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	// Return new texture
	return textureID;
}

TTF_Font * TextureLoader::_loadFont(const string& fontPath)
{
	// Get application root directory
	char buffer[256]; size_t len = sizeof(buffer);
	GetModuleFileName(NULL, buffer, len);
	string fullDir = buffer;
	fullDir = fullDir.substr(0, fullDir.size() - 25);

	// Load font
	auto it = _fontMap.find(fontPath);
	if (it == _fontMap.end()) //Not in map (yet)
	{
		// Font loading
		TTF_Font * font = TTF_OpenFont((fullDir + fontPath + ".ttf").c_str(), 25);
		if (font == nullptr)
		{
			Logger::getInst().throwError("Texture error: " + string(SDL_GetError()));
		}
		_fontMap.insert(std::make_pair(fontPath, font));

		Logger::getInst().throwInfo("Loaded font: " + string(fontPath + ".ttf"));

		return font; //Use new texture
	}

	return it->second; //Cache texture
}