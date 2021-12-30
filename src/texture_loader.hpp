#pragma once

#include "render_bus.hpp"
#include "render_utils.hpp"
#include "image.hpp"

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
using std::shared_ptr;
using std::make_shared;

class TextureLoader final
{
public:
	TextureLoader(RenderBus& renderBus);

	void cache2dTexture(const string& filePath, bool isMipmapped, bool isAnisotropic);
	void cache3dTexture(const array<string, 6>& filePaths);
	void cacheBitmap(const string& filePath);
	void cache2dTextures(const vector<string>& filePaths, bool isMipmapped, bool isAnisotropic);
	void cache3dTextures(const vector<array<string, 6>>& filePathsList);
	void cacheBitmaps(const vector<string>& filePaths);
	void clear2dTextureCache(const string& filePath);
	void clear3dTextureCache(const array<string, 6>& filePaths);
	void clearBitmapCache(const string& filePath);
	void clear2dTexturesCache();
	void clear3dTexturesCache();
	void clearBitmapsCache();
	void setAnisotropicFilteringQuality(unsigned int value);

	const vector<float>* loadBitmap(const string& filePath);

	const unsigned int getAnisotropicFilteringQuality() const;

	const TextureID load2dTexture(const string& filePath, bool isMipmapped, bool isAnisotropic);
	const TextureID load3dTexture(const array<string, 6>& filePaths);

private:
	void _reloadAnisotropicFiltering();
	void _unloadImage(shared_ptr<Image> image);

	vector<float> _loadBitmap(const string& filePath);

	shared_ptr<Image> _loadImage(const string& filePath);
	TextureID _create2dTexture(shared_ptr<Image> image, const string& filePath, bool isMipmapped, bool isAnisotropic);
	TextureID _create3dTexture(const array<shared_ptr<Image>, 6 >& images, const array<string, 6>& filePaths);

	map<string, vector<float>> _bitmapCache;

	unsigned int _anisotropicFilteringQuality = Config::MIN_ANISOTROPIC_FILTERING_QUALITY;

	RenderBus& _renderBus;
	map<string, TextureID> _2dTextureCache;
	map<array<string, 6>, TextureID> _3dTextureCache;
};