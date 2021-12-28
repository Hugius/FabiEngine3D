#pragma once

#include "render_bus.hpp"
#include "render_utils.hpp"

#include <SDL/SDL.h>
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

	void cache2dTexture(const string& filePath, bool isMipmapped, bool isAnisotropic);
	void cache3dTexture(const array<string, 6>& filePaths);
	void cacheBitmap(const string& filePath);
	void cacheFont(const string& filePath);
	void cache2dTextures(const vector<string>& filePaths, bool isMipmapped, bool isAnisotropic);
	void cache3dTextures(const vector<array<string, 6>>& filePathsList);
	void cacheBitmaps(const vector<string>& filePaths);
	void cacheFonts(const vector<string>& filePaths);
	void clear2dTextureCache(const string& filePath);
	void clear3dTextureCache(const array<string, 6>& filePaths);
	void clearBitmapCache(const string& filePath);
	void clearFontCache(const string& filePath);
	void clear2dTexturesCache();
	void clear3dTexturesCache();
	void clearBitmapsCache();
	void clearFontsCache();
	void setAnisotropicFilteringQuality(unsigned int value);

	const vector<float>* loadBitmap(const string& filePath);

	const unsigned int getAnisotropicFilteringQuality() const;

	const TextureID load2dTexture(const string& filePath, bool isMipmapped, bool isAnisotropic);
	const TextureID load2dTexture(const string& textContent, const string& fontPath);
	const TextureID load3dTexture(const array<string, 6>& filePaths);

private:
	void _reloadAnisotropicFiltering();

	vector<float> _loadBitmap(const string& filePath);

	SDL_Surface* _loadSurface(const string& filePath);
	TextureID _convertInto2dTexture(SDL_Surface* surface, const string& filePath, bool isMipmapped, bool isAnisotropic);
	TextureID _convertInto3dTexture(const array<SDL_Surface*, 6>& surfaces, const array<string, 6>& filePaths);

	map<string, vector<float>> _bitmapCache;

	unsigned int _anisotropicFilteringQuality = Config::MIN_ANISOTROPIC_FILTERING_QUALITY;

	RenderBus& _renderBus;
	map<string, TextureID> _2dTextureCache;
	map<array<string, 6>, TextureID> _3dTextureCache;
	map<pair<string, string>, TextureID> _textCache;
	map<string, TTF_Font*> _fontCache;
};