#pragma once

#include <GLEW\\glew.h>
#include <SDL\\SDL_ttf.h>
#include <array>
#include <vector>
#include <map>
#include <string>

using std::pair;
using std::array;
using std::vector;
using std::string;
using std::map;

class TextureLoader final
{
public:
	TextureLoader()  = default;
	~TextureLoader() = default;

	// Instant asset loading or caching
	GLuint         getTexture2D(const string& filePath, bool mipmap, bool aniso, bool repeat = true);
	GLuint         getTexture3D(const array<string, 6>& filePaths);
	GLuint		   getText(const string& textContent, const string& fontPath);
	const vector<float>& getBitmapPixels(const string& filePath);

	// Multithreaded caching
	void cacheTexturesMultiThreaded2D(const vector<string>& filePaths);
	void cacheTexturesMultiThreaded3D(const vector<array<string, 6>>& filePaths);

	// Cache clearing
	void clearTextureCache2D(const string& filePath);
	void clearTextureCache3D(const array<string, 6>& filePaths);
	void clearFontCache(const string& filePath);
	void clearTextCache(const string& textContent, const string& fontPath);
	void clearBitmapCache(const string& filePath);

private:
	map<string, GLuint>				  _textureCache2D;
	map<array<string, 6>, GLuint>	  _textureCache3D;
	map<string, TTF_Font*>			  _fontCache;
	map<pair<string, string>, GLuint> _textCache;
	map<string, vector<float>>		  _bitmapCache;

	SDL_Surface*  _loadImage(const string& filePath);
	GLuint		  _convertToTexture2D(const string& filePath, SDL_Surface* image, bool mipmap, bool aniso, bool repeat);
	GLuint        _convertToTexture3D(const array<string, 6>& filePaths, const array<SDL_Surface*, 6>& images);
	TTF_Font*	  _loadFont(const string& filePath);
	GLuint        _loadText(const string& textContent, const string& filePath);
	vector<float> _loadBitmapPixels(const string& filePath);
};