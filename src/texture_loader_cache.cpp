#include "texture_loader.hpp"
#include "texture_loader.hpp"
#include "texture_loader.hpp"
#include "texture_loader.hpp"
#include "texture_loader.hpp"
#include "logger.hpp"

#include <future>
#include <set>

using std::set;
using std::future;
using std::launch;
using std::future_status;
using std::chrono::system_clock;

void TextureLoader::cache2dTextures(const vector<string>& filePaths, bool isMipmapped, bool isAnisotropic)
{
	// Temporary values
	vector<future<SDL_Surface*>> threads;
	vector<string> finalFilePaths;
	vector<bool> threadStatuses;
	unsigned int finishedThreadCount = 0;

	// Remove duplicates
	auto tempFilePaths = set<string>(filePaths.begin(), filePaths.end());
	auto uniqueFilePaths = vector<string>(tempFilePaths.begin(), tempFilePaths.end());

	// Start all loading threads
	for(const auto& filePath : uniqueFilePaths)
	{
		// Check if texture is not already cached
		if(_2dTextureCache.find(filePath) == _2dTextureCache.end())
		{
			threads.push_back(async(launch::async, &TextureLoader::_loadSurface, this, filePath));
			finalFilePaths.push_back(filePath);
			threadStatuses.push_back(false);
		}
	}

	// Wait for all threads to finish
	while(finishedThreadCount != threadStatuses.size())
	{
		// For all threads
		for(size_t i = 0; i < threadStatuses.size(); i++)
		{
			// Check if texture is not processed yet
			if(!threadStatuses[i])
			{
				// Check if thread is finished
				if(threads[i].wait_until(system_clock::time_point::min()) == future_status::ready)
				{
					// Retrieve return value
					auto loadedImage = threads[i].get();

					// Update thread status
					threadStatuses[i] = true;
					finishedThreadCount++;

					// Check image status
					if(loadedImage == nullptr)
					{
						Logger::throwWarning("Cannot load image: \"" + finalFilePaths[i] + "\"!");
					}
					else
					{
						// Load OpenGL texture
						auto loadedTexture = _convertInto2dTexture(loadedImage, finalFilePaths[i], isMipmapped, isAnisotropic);

						// Memory management
						SDL_FreeSurface(loadedImage);

						// Check texture status
						if(loadedTexture != 0)
						{
							// Cache texture
							_2dTextureCache[finalFilePaths[i]] = loadedTexture;
						}
					}
				}
			}
		}
	}
}

void TextureLoader::cache3dTextures(const vector<array<string, 6>>& filePathsList)
{
	// Temporary values
	vector<vector<future<SDL_Surface*>>> threads;
	vector<array<string, 6>> finalFilePathsList;
	vector<bool> threadStatuses;
	unsigned int finishedThreadCount = 0;

	// Start all loading threads
	for(const auto& filePaths : filePathsList)
	{
		// Check if texture is not already cached
		if(_3dTextureCache.find(filePaths) == _3dTextureCache.end())
		{
			// 6 threads for every 3D texture
			threads.push_back({});
			for(const auto& filePath : filePaths)
			{
				threads.back().push_back(async(launch::async, &TextureLoader::_loadSurface, this, filePath));
			}
			finalFilePathsList.push_back(filePaths);
			threadStatuses.push_back(false);
		}
	}

	// Wait for all threads to finish
	while(finishedThreadCount != threadStatuses.size())
	{
		// For all threads
		for(size_t i = 0; i < threadStatuses.size(); i++)
		{
			// Check if texture is not processed yet
			if(!threadStatuses[i])
			{
				// Check if all 6 threads are finished
				bool threadsAreFinished = true;
				for(size_t j = 0; j < threads[i].size(); j++)
				{
					// Check if thread is finished
					if(threads[i][i].wait_until(system_clock::time_point::min()) != future_status::ready)
					{
						threadsAreFinished = false;
					}
				}

				// Process threads if finished
				array<SDL_Surface*, 6> loadedImages;
				if(threadsAreFinished)
				{
					// Update thread status
					threadStatuses[i] = true;
					finishedThreadCount++;

					// 6 images for every 3D texture
					for(size_t j = 0; j < threads[i].size(); j++)
					{
						// Save loaded image
						loadedImages[j] = threads[i][j].get();

						// Error logging
						if((loadedImages[j] == nullptr) && !finalFilePathsList[i][j].empty())
						{
							Logger::throwWarning("Cannot load image: \"" + finalFilePathsList[i][j] + "\"!");
						}
					}

					// Load OpenGL texture
					TextureID loadedTexture = _convertInto3dTexture(loadedImages, finalFilePathsList[i]);

					// Memory management
					for(const auto& image : loadedImages)
					{
						// Only if memory is present
						if(image != nullptr)
						{
							SDL_FreeSurface(image);
						}
					}

					// Check texture status
					if(loadedTexture != 0)
					{
						// Cache texture
						_3dTextureCache[finalFilePathsList[i]] = loadedTexture;
					}
				}
			}
		}
	}
}

void TextureLoader::cacheBitmaps(const vector<string>& filePaths)
{
	// Temporary values
	vector<future<vector<float>>> threads;
	vector<string> finalFilePaths;
	vector<bool> threadStatuses;
	unsigned int finishedThreadCount = 0;

	// Remove duplicates
	auto tempFilePaths = set<string>(filePaths.begin(), filePaths.end());
	auto uniqueFilePaths = vector<string>(tempFilePaths.begin(), tempFilePaths.end());

	// Start all loading threads
	for(const auto& filePath : uniqueFilePaths)
	{
		// Check if bitmap is not already cached
		if(_bitmapCache.find(filePath) == _bitmapCache.end())
		{
			threads.push_back(async(launch::async, &TextureLoader::_loadBitmap, this, filePath));
			finalFilePaths.push_back(filePath);
			threadStatuses.push_back(false);
		}
	}

	// Wait for all threads to finish
	while(finishedThreadCount != threadStatuses.size())
	{
		// For all threads
		for(size_t i = 0; i < threadStatuses.size(); i++)
		{
			// Check if bitmap is not processed yet
			if(!threadStatuses[i])
			{
				// Check if thread is finished
				if(threads[i].wait_until(system_clock::time_point::min()) == future_status::ready)
				{
					// Retrieve return value
					auto loadedBitmap = threads[i].get();

					// Update thread status
					threadStatuses[i] = true;
					finishedThreadCount++;

					// Check bitmap status
					if(loadedBitmap.empty())
					{
						Logger::throwWarning("Cannot load bitmap: \"" + finalFilePaths[i] + "\"!");
					}
					else
					{
						// Cache bitmap
						_bitmapCache[finalFilePaths[i]] = loadedBitmap;

						// Logging
						Logger::throwInfo("Loaded bitmap: \"" + finalFilePaths[i] + "\"");
					}
				}
			}
		}
	}
}

void TextureLoader::cacheFonts(const vector<string>& filePaths)
{
	// Temporary values
	vector<future<TTF_Font*>> threads;
	vector<string> finalFilePaths;
	vector<bool> threadStatuses;
	unsigned int finishedThreadCount = 0;

	// Remove duplicates
	auto tempFilePaths = set<string>(filePaths.begin(), filePaths.end());
	auto uniqueFilePaths = vector<string>(tempFilePaths.begin(), tempFilePaths.end());

	// Start all loading threads
	for(const auto& filePath : uniqueFilePaths)
	{
		// Check if font is not already cached
		if(_fontCache.find(filePath) == _fontCache.end())
		{
			threads.push_back(async(launch::async, &TextureLoader::_loadFont, this, filePath));
			finalFilePaths.push_back(filePath);
			threadStatuses.push_back(false);
		}
	}

	// Wait for all threads to finish
	while(finishedThreadCount != threadStatuses.size())
	{
		// For all threads
		for(size_t i = 0; i < threadStatuses.size(); i++)
		{
			// Check if font is not processed yet
			if(!threadStatuses[i])
			{
				// Check if thread is finished
				if(threads[i].wait_until(system_clock::time_point::min()) == future_status::ready)
				{
					// Retrieve return value
					auto loadedFont = threads[i].get();

					// Update thread status
					threadStatuses[i] = true;
					finishedThreadCount++;

					// Check font status
					if(loadedFont == nullptr)
					{
						Logger::throwWarning("Cannot load font: \"" + finalFilePaths[i] + "\"!");
					}
					else
					{
						// Cache font
						_fontCache[finalFilePaths[i]] = loadedFont;

						// Logging
						Logger::throwInfo("Loaded font: \"" + finalFilePaths[i] + "\"");
					}
				}
			}
		}
	}
}

void TextureLoader::clear2dTextureCache(const string& filePath)
{
	if(_2dTextureCache.find(filePath) != _2dTextureCache.end())
	{
		glDeleteTextures(1, &_2dTextureCache[filePath]);
		_2dTextureCache.erase(filePath);
	}
}

void TextureLoader::clear3dTextureCache(const array<string, 6>& filePaths)
{
	if(_3dTextureCache.find(filePaths) != _3dTextureCache.end())
	{
		glDeleteTextures(1, &_3dTextureCache[filePaths]);
		_3dTextureCache.erase(filePaths);
	}
}

void TextureLoader::clearBitmapCache(const string& filePath)
{
	if(_bitmapCache.find(filePath) != _bitmapCache.end())
	{
		_bitmapCache.erase(filePath);
	}
}

void TextureLoader::clearFontCache(const string& filePath)
{
	// Clear font cache
	if(_fontCache.find(filePath) != _fontCache.end())
	{
		TTF_CloseFont(_fontCache[filePath]);
		_fontCache.erase(filePath);
	}

	// Clear text cache
	for(const auto& [key, textureID] : _textCache)
	{
		// Check if font corresponds
		if(key.second == filePath)
		{
			glDeleteTextures(1, &textureID);
			_textCache.erase(key);
		}
	}
}

void TextureLoader::clear2dTexturesCache()
{
	_2dTextureCache.clear();
}

void TextureLoader::clear3dTexturesCache()
{
	_3dTextureCache.clear();
}

void TextureLoader::clearBitmapsCache()
{
	_bitmapCache.clear();
}

void TextureLoader::clearFontsCache()
{
	_fontCache.clear();
	_textCache.clear();
}