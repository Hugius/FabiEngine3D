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

	// VOID
	void cache2dTexturesMultiThreaded(const vector<string>& filePaths, bool isMipmapped, bool isAnisotropic);
	void cache3dTexturesMultiThreaded(const vector<array<string, 6>>& filePathsList);
	void cacheBitmapsMultiThreaded(const vector<string>& filePaths);
	void cacheFontsMultiThreaded(const vector<string>& filePaths);
	void clearTextureCache(const string& filePath);
	void clearTextureCache(const array<string, 6>& filePaths);
	void clearBitmapCache(const string& filePath);
	void clearFontCache(const string& filePath);
	void setAnisotropicFilteringQuality(unsigned int value);

	// FLOAT
	const vector<float>* loadBitmap(const string& filePath);

	// UNSIGNED INT
	const unsigned int getAnisotropicFilteringQuality() const;

	// MISCELLANEOUS
	const TextureID load2dTexture(const string& filePath, bool isMipmapped, bool isAnisotropic);
	const TextureID load2dTexture(const string& textContent, const string& fontPath);
	const TextureID load3dTexture(const array<string, 6>& filePaths);

private:
	// VOID
	void _reloadAnisotropicFiltering();

	// FLOAT
	vector<float> _loadBitmap(const string& filePath);

	// MISCELLANEOUS
	SDL_Surface* _loadSurface(const string& filePath);
	TTF_Font* _loadFont(const string& filePath);
	TextureID _convertInto2dTexture(SDL_Surface* surface, const string& filePath, bool isMipmapped, bool isAnisotropic);
	TextureID _convertInto2dTexture(TTF_Font* font, const string& textContent);
	TextureID _convertInto3dTexture(const array<SDL_Surface*, 6>& surfaces, const array<string, 6>& filePaths);

	// FLOAT
	map<string, vector<float>> _bitmapCache;

	// UNSIGNED INT
	unsigned int _anisotropicFilteringQuality = Config::MIN_ANISOTROPIC_FILTERING_QUALITY;

	// MISCELLANEOUS
	RenderBus& _renderBus;
	map<string, TextureID> _2dTextureCache;
	map<array<string, 6>, TextureID> _3dTextureCache;
	map<pair<string, string>, TextureID> _textCache;
	map<string, TTF_Font*> _fontCache;
};