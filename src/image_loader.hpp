#pragma once

#include "image.hpp"

#include <vector>
#include <unordered_map>
#include <string>
#include <memory>

using std::vector;
using std::string;
using std::unordered_map;
using std::shared_ptr;

class ImageLoader final
{
public:
	void cacheImage(const string & filePath, bool isCrucial);
	void cacheImages(const vector<string> & filePaths, bool isCrucial);
	void clearImageCache(const string & filePath);
	void clearImagesCache();

	const shared_ptr<Image> loadImage(const string & filePath);

private:
	shared_ptr<Image> _loadImage(const string & filePath) const;

	static inline constexpr unsigned int HEADER_SIZE = 18;

	unordered_map<string, shared_ptr<Image>> _cache = {};
};