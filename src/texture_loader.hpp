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

	void cacheImage(const string& filePath);
	void cache2dTexture(const string& filePath, bool isMipmapped, bool isAnisotropic);
	void cache3dTexture(const array<string, 6>& filePaths);
	void cacheImages(const vector<string>& filePaths);
	void cache2dTextures(const vector<string>& filePaths, bool isMipmapped, bool isAnisotropic);
	void cache3dTextures(const vector<array<string, 6>>& filePathsList);
	void clearImageCache(const string& filePath);
	void clear2dTextureCache(const string& filePath);
	void clear3dTextureCache(const array<string, 6>& filePaths);
	void clearImagesCache();
	void clear2dTexturesCache();
	void clear3dTexturesCache();
	void setAnisotropicFilteringQuality(unsigned int value);

	const unsigned int getAnisotropicFilteringQuality() const;

	const shared_ptr<Image> loadImage(const string& filePath);
	const TextureID load2dTexture(const string& filePath, bool isMipmapped, bool isAnisotropic);
	const TextureID load3dTexture(const array<string, 6>& filePaths);

private:
	void _reloadAnisotropicFiltering();

	shared_ptr<Image> _loadImage(const string& filePath, bool mustFlip);

	TextureID _create2dTexture(shared_ptr<Image> image, const string& filePath, bool isMipmapped, bool isAnisotropic);
	TextureID _create3dTexture(const array<shared_ptr<Image>, 6 >& images, const array<string, 6>& filePaths);

	unsigned int _anisotropicFilteringQuality = Config::MIN_ANISOTROPIC_FILTERING_QUALITY;

	RenderBus& _renderBus;
	map<string, shared_ptr<Image>> _imageCache;
	map<string, TextureID> _2dTextureCache;
	map<array<string, 6>, TextureID> _3dTextureCache;
};