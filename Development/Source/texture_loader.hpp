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

	// Voids
	void cacheTexturesMultiThreaded2D(const vector<string>& filePaths, bool isMipmapped, bool isAnisotropic);
	void cacheTexturesMultiThreaded3D(const vector<array<string, 6>>& filePathsList);
	void cacheFontsMultiThreaded(const vector<string>& filePaths);
	void clearTextureCache2D(const string& filePath);
	void clearTextureCache3D(const array<string, 6>& filePaths);
	void clearFontCache(const string& filePath);
	void clearTextCache(const string& textContent, const string& fontPath);
	void clearBitmapCache(const string& filePath);
	void reloadAnisotropicFiltering();

	// Floats
	const vector<float>* getBitmapPixels(const string& filePath);

	// Miscellaneous
	TextureID getTexture2D(const string& filePath, bool isMipmapped, bool isAnisotropic);
	TextureID getTexture3D(const array<string, 6>& filePaths);
	TextureID getText(const string& textContent, const string& fontPath);

private:
	// Floats
	vector<float> _loadBitmap(const string& filePath);

	// Miscellaneous
	SDL_Surface* _loadSurface(const string& filePath);
	TTF_Font* _loadFont(const string& filePath);
	TextureID _loadText(const string& textContent, const string& fontPath);
	TextureID _loadTexture2D(const string& filePath, SDL_Surface* image, bool isMipmapped, bool isAnisotropic);
	TextureID _loadTexture3D(const array<string, 6>& filePaths, const array<SDL_Surface*, 6>& images);

	// Instances
	RenderBus& _renderBus;

	// Floats
	map<string, vector<float>> _bitmapCache;

	// Miscellaneous
	map<string, TextureID> _textureCache2D;
	map<array<string, 6>, TextureID> _textureCache3D;
	map<pair<string, string>, TextureID> _textCache;
	map<string, TTF_Font*> _fontCache;
};