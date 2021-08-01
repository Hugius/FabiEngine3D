#pragma once

#include "render_bus.hpp"
#include "render_utils.hpp"

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
	TextureLoader(RenderBus& renderBus);

	// Instant asset loading or caching
	TextureID getTexture2D(const string& filePath, bool isMipmapped, bool isAnisotropic);
	TextureID getTexture3D(const array<string, 6>& filePaths);
	TextureID getText(const string& textContent, const string& fontPath);
	const vector<float>* getBitmapPixels(const string& filePath);

	// Multithreaded caching
	void cacheTexturesMultiThreaded2D(const vector<string>& filePaths, bool isMipmapped, bool isAnisotropic);
	void cacheTexturesMultiThreaded3D(const vector<array<string, 6>>& filePathsList);

	// Cache clearing
	void clearTextureCache2D(const string& filePath);
	void clearTextureCache3D(const array<string, 6>& filePaths);
	void clearFontCache(const string& filePath);
	void clearTextCache(const string& textContent, const string& fontPath);
	void clearBitmapCache(const string& filePath);

	// Miscellaneous
	void reloadAnisotropicFiltering();

private:
	// Functions
	SDL_Surface* _loadImage(const string& filePath);
	TextureID _convertToTexture2D(const string& filePath, SDL_Surface* image, bool isMipmapped, bool isAnisotropic);
	TextureID _convertToTexture3D(const array<string, 6>& filePaths, const array<SDL_Surface*, 6>& images);
	TTF_Font* _loadFont(const string& filePath);
	TextureID _loadText(const string& textContent, const string& filePath);
	vector<float> _loadBitmapPixels(const string& filePath);

	// Instances
	RenderBus& _renderBus;

	// Caches
	map<string, TextureID>	_textureCache2D;
	map<array<string, 6>, TextureID> _textureCache3D;
	map<string, TTF_Font*> _fontCache;
	map<pair<string, string>, TextureID> _textCache;
	map<string, vector<float>> _bitmapCache;
};