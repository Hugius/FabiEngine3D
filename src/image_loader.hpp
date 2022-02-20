#pragma once

#include "render_storage.hpp"
#include "image.hpp"

#include <array>
#include <vector>
#include <unordered_map>
#include <string>

using std::pair;
using std::array;
using std::vector;
using std::string;
using std::unordered_map;
using std::shared_ptr;
using std::make_shared;

class ImageLoader final
{
public:
	void cacheImage(const string& filePath, bool isCrucial);
	void cacheImages(const vector<string>& filePaths, bool isCrucial);
	void clearImageCache(const string& filePath);
	void clearImagesCache();

	const shared_ptr<Image> loadImage(const string& filePath);

private:
	shared_ptr<Image> _loadImage(const string& filePath);

	unordered_map<string, shared_ptr<Image>> _cache;
};