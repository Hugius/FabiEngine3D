#pragma once

#include "render_bus.hpp"
#include "render_utils.hpp"
#include "image.hpp"

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

class ImageLoader final
{
public:
	void cacheImage(const string& filePath);
	void cacheImages(const vector<string>& filePaths);
	void clearImageCache(const string& filePath);
	void clearImagesCache();

	const shared_ptr<Image> loadImage(const string& filePath);

private:
	shared_ptr<Image> _loadImage(const string& filePath, bool mustFlip);

	map<string, shared_ptr<Image>> _imageCache;
};