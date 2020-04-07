#include <SDL/SDL_image.h>

#include <WE3D/TextureLoader.hpp>
#include <WE3D/Logger.hpp>

GLuint TextureLoader::p_loadText(const string& text, const string &fontPath)
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
	auto font = p_loadFont(fontPath);

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
		Logger::getInst().throwError("Pixel format not recognized at text texture: " + text + ".ttf");
	}

	// Memory management
	SDL_FreeSurface(surface);

	return tex;
}

GLuint TextureLoader::p_loadTexture(const string & filePath, bool mipmap, bool aniso, bool repeat)
{
	// Load actual texture
	SDL_Surface * surface = IMG_Load((filePath + ".png").c_str());
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
		Logger::getInst().throwError("Pixel format not recognized at image: " + filePath + ".png");
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
	Logger::getInst().throwInfo("Loaded PNG texture: " + filePath + ".png");

	// Return new texture
	return tex;
}

// http://stackoverflow.com/questions/1968561/getting-the-pixel-value-of-bmp-file
vector<float> TextureLoader::p_loadHeightmap(const string & filePath, int size)
{
	vector<float> pixelColors;

	FILE * streamIn;
	fopen_s(&streamIn, (filePath + ".bmp").c_str(), "rb");
	if (streamIn == (FILE *)0) 
	{
		Logger::getInst().throwError("Could not open heightmap: " + filePath + ".bmp");
	}

	int byte;
	for (int i = 0; i < 54; i++) byte = getc(streamIn);

	for (int i = 0; i < (size * size); i++)
	{
		pixelColors.push_back(0.0f);
		auto r = getc(streamIn);
		auto g = getc(streamIn);
		auto b = getc(streamIn);
		pixelColors.back() = static_cast<float>(r);
	}

	fclose(streamIn);

	// Logging
	Logger::getInst().throwInfo("Loaded BMP heightmap: " + filePath + ".bmp");

	// Return new texture
	return pixelColors;
}

GLuint TextureLoader::p_loadCubemap(const string & filePath)
{
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
		SDL_Surface * surface = IMG_Load((filePath + fileNames[i] + ".png").c_str());
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

TTF_Font * TextureLoader::p_loadFont(const string & fontPath)
{
	auto it = p_fontMap.find(fontPath);
	if (it == p_fontMap.end()) //Not in map (yet)
	{
		// Font loading
		TTF_Font * font = TTF_OpenFont((fontPath + ".ttf").c_str(), 50);
		if (font == nullptr)
		{
			Logger::getInst().throwError(string("Font could not be loaded: " + fontPath + ".ttf").c_str());
		}
		p_fontMap.insert(std::make_pair(fontPath, font));

		Logger::getInst().throwInfo("Loaded font: " + fontPath + ".ttf");

		return font; //Use new texture
	}

	return it->second; //Cache texture
}