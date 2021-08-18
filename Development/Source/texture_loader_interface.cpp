#include "texture_loader.hpp"
#include "logger.hpp"
#include "configuration.hpp"

#include <future>
#include <set>

using std::set;
using std::future;
using std::launch;
using std::future_status;
using std::chrono::system_clock;

TextureLoader::TextureLoader(RenderBus& renderBus)
	:
	_renderBus(renderBus)
{

}

void TextureLoader::cacheTexturesMultiThreaded2D(const vector<string>& filePaths, bool isMipmapped, bool isAnisotropic)
{
	// Temporary values
	vector<future<SDL_Surface*>> threads;
	vector<string> finalFilePaths;
	vector<bool> cacheStatuses;
	unsigned int finishedThreadCount = 0;

	// Remove duplicates
	auto tempFilePaths = set<string>(filePaths.begin(), filePaths.end());
	auto uniqueFilePaths = vector<string>(tempFilePaths.begin(), tempFilePaths.end());

	// Start all loading threads
	for (const auto& filePath : uniqueFilePaths)
	{
		// Check if texture is not already cached
		if (_textureCache2D.find(filePath) == _textureCache2D.end())
		{
			threads.push_back(async(launch::async, &TextureLoader::_loadImage, this, filePath));
			finalFilePaths.push_back(filePath);
			cacheStatuses.push_back(false);
		}
	}

	// Wait for all threads to finish
	while (finishedThreadCount != cacheStatuses.size())
	{
		// For all threads
		for (size_t i = 0; i < cacheStatuses.size(); i++)
		{
			// Check if texture is not processed yet
			if (!cacheStatuses[i])
			{
				// Check if thread is finished
				if (threads[i].wait_until(system_clock::time_point::min()) == future_status::ready)
				{
					// Retrieve the SDL image
					auto loadedImage = threads[i].get();

					// Update thread status
					cacheStatuses[i] = true;
					finishedThreadCount++;

					// Check image status
					if (loadedImage == nullptr)
					{
						Logger::throwWarning("Cannot load image file: \"" + finalFilePaths[i] + "\"!");
					}
					else
					{
						// Load OpenGL texture
						auto loadedTexture = _convertToTexture2D(finalFilePaths[i], loadedImage, isMipmapped, isAnisotropic);

						// Free image memory
						SDL_FreeSurface(loadedImage);

						// Check texture status
						if (loadedTexture != 0)
						{
							// Cache texture
							_textureCache2D[finalFilePaths[i]] = loadedTexture;
						}
					}
				}
			}
		}
	}
}

void TextureLoader::cacheTexturesMultiThreaded3D(const vector<array<string, 6>>& filePathsList)
{
	// Temporary values
	vector<vector<future<SDL_Surface*>>> threads;
	vector<array<string, 6>> finalFilePathsList;
	vector<bool> cacheStatuses;
	unsigned int finishedThreadCount = 0;

	// Start all loading threads
	for (const auto& filePaths : filePathsList)
	{
		// Check if texture is not already cached
		if (_textureCache3D.find(filePaths) == _textureCache3D.end())
		{
			// 6 threads for every 3D texture
			threads.push_back({});
			for (const auto& filePath : filePaths)
			{
				threads.back().push_back(async(launch::async, &TextureLoader::_loadImage, this, filePath));
			}
			finalFilePathsList.push_back(filePaths);
			cacheStatuses.push_back(false);
		}
	}

	// Wait for all threads to finish
	while (finishedThreadCount != cacheStatuses.size())
	{
		// For all threads
		for (size_t i = 0; i < cacheStatuses.size(); i++)
		{
			// Check if texture is not processed yet
			if (!cacheStatuses[i])
			{
				// Check if all 6 threads are finished
				bool threadsAreFinished = true;
				for (size_t j = 0; j < threads[i].size(); j++)
				{
					// Check if thread is finished
					if (threads[i][i].wait_until(system_clock::time_point::min()) != future_status::ready)
					{
						threadsAreFinished = false;
					}
				}

				// Process threads if finished
				array<SDL_Surface*, 6> loadedImages;
				if (threadsAreFinished)
				{
					// Update thread status
					cacheStatuses[i] = true;
					finishedThreadCount++;

					// 6 images for every 3D texture
					for (size_t j = 0; j < threads[i].size(); j++)
					{
						// Save loaded image
						loadedImages[j] = threads[i][j].get();

						// Error logging
						if ((loadedImages[j] == nullptr) && !finalFilePathsList[i][j].empty())
						{
							Logger::throwWarning("Cannot load image file: \"" + finalFilePathsList[i][j] + "\"!");
						}
					}

					// Load OpenGL texture
					TextureID loadedTexture = _convertToTexture3D(finalFilePathsList[i], loadedImages);

					// Free images memory
					for (const auto& image : loadedImages)
					{
						// Only if memory is present
						if (image != nullptr)
						{
							SDL_FreeSurface(image);
						}
					}

					// Check texture status
					if (loadedTexture != 0)
					{
						// Cache texture
						_textureCache3D[finalFilePathsList[i]] = loadedTexture;
					}
				}
			}
		}
	}
}

TextureID TextureLoader::getTexture2D(const string& filePath, bool isMipmapped, bool isAnisotropic)
{
BEGIN:
	// Search cache
	auto iterator = _textureCache2D.find(filePath);

	// Return from cache
	if (iterator != _textureCache2D.end())
	{
		return iterator->second;
	}

	// Load SDL image
	auto loadedImage = _loadImage(filePath);

	// Check image status
	if (loadedImage == nullptr)
	{
		Logger::throwWarning("Cannot load image file: \"" + filePath + "\"!");
		return 0;
	}
	else
	{
		// Load OpenGL texture
		auto loadedTexture = _convertToTexture2D(filePath, loadedImage, isMipmapped, isAnisotropic);

		// Free image memory
		SDL_FreeSurface(loadedImage);

		// Check texture status
		if (loadedTexture == 0)
		{
			return 0;
		}
		else
		{
			// Cache texture
			_textureCache2D.insert(make_pair(filePath, loadedTexture));

			// Return cached texture
			goto BEGIN;
		}
	}
}

TextureID TextureLoader::getTexture3D(const array<string, 6>& filePaths)
{
BEGIN:
	// Search cache
	auto iterator = _textureCache3D.find(filePaths);

	// Return from cache
	if (iterator != _textureCache3D.end())
	{
		return iterator->second;
	}

	// Temporary values
	vector<future<SDL_Surface*>> threads;
	array<SDL_Surface*, 6> loadedImages = {};

	// Start all loading threads
	for (size_t i = 0; i < filePaths.size(); i++)
	{
		threads.push_back(async(launch::async, &TextureLoader::_loadImage, this, filePaths[i]));
	}

	// Wait for all threads to finish
	for (size_t i = 0; i < threads.size(); i++)
	{
		// Save loaded image
		loadedImages[i] = threads[i].get();

		// Error logging
		if (loadedImages[i] == nullptr && !filePaths[i].empty())
		{
			Logger::throwWarning("Cannot load image file: \"" + filePaths[i] + "\"!");
		}
	}

	// Load OpenGL texture
	TextureID loadedTexture = _convertToTexture3D(filePaths, loadedImages);

	// Free images memory
	for (const auto& image : loadedImages)
	{
		// Only if memory is present
		if (image != nullptr)
		{
			SDL_FreeSurface(image);
		}
	}

	// Determine if needs to be cached
	if (loadedTexture == 0)
	{
		return 0;
	}
	else
	{
		// Cache texture
		_textureCache3D.insert(make_pair(filePaths, loadedTexture));

		// Return cached texture
		goto BEGIN;
	}
}

TextureID TextureLoader::getText(const string& textContent, const string& fontPath)
{
BEGIN:
	// Search cache
	auto iterator = _textCache.find(make_pair(textContent, fontPath));

	// Return from cache
	if (iterator != _textCache.end())
	{
		return iterator->second;
	}
	
	// Load OpenGL texture
	TextureID loadedTexture = _loadText(textContent, fontPath);

	// Determine if needs to be cached
	if (loadedTexture == 0)
	{
		return 0;
	}
	else
	{
		_textCache.insert(make_pair(make_pair(textContent, fontPath), loadedTexture));
		goto BEGIN;
	}
}

const vector<float>* TextureLoader::getBitmapPixels(const string& filePath)
{
BEGIN:
	// Search cache
	auto iterator = _bitmapCache.find(filePath);

	// Return from cache
	if (iterator != _bitmapCache.end())
	{
		return &iterator->second;
	}

	// Load pixels
	auto loadedPixels = _loadBitmapPixels(filePath);

	// Check pixels status
	if (loadedPixels.empty())
	{
		return nullptr;
	}
	else
	{
		// Cache pixels
		_bitmapCache.insert(make_pair(filePath, loadedPixels));

		// Return cached pixels
		goto BEGIN;
	}
}

void TextureLoader::clearTextureCache2D(const string& filePath)
{
	if (_textureCache2D.find(filePath) != _textureCache2D.end())
	{
		glDeleteTextures(1, &_textureCache2D[filePath]);
		_textureCache2D.erase(filePath);
	}
}

void TextureLoader::clearTextureCache3D(const array<string, 6>& filePaths)
{
	if (_textureCache3D.find(filePaths) != _textureCache3D.end())
	{
		glDeleteTextures(1, &_textureCache3D[filePaths]);
		_textureCache3D.erase(filePaths);
	}
}

void TextureLoader::clearFontCache(const string& filePath)
{
	if (_fontCache.find(filePath) != _fontCache.end())
	{
		TTF_CloseFont(_fontCache[filePath]);
		_fontCache.erase(filePath);
	}
}

void TextureLoader::clearTextCache(const string& textContent, const string& fontPath)
{
	if (_textCache.find(make_pair(textContent, fontPath)) != _textCache.end())
	{
		glDeleteTextures(1, &_textCache[make_pair(textContent, fontPath)]);
		_textCache.erase(make_pair(textContent, fontPath));
	}
}

void TextureLoader::clearBitmapCache(const string& filePath)
{
	if (_bitmapCache.find(filePath) != _bitmapCache.end())
	{
		_bitmapCache.erase(filePath);
	}
}

void TextureLoader::reloadAnisotropicFiltering()
{
	for (auto& [path, texture] : _textureCache2D)
	{
		// Bind
		glBindTexture(GL_TEXTURE_2D, texture);

		// Get current quality
		int currentQuality;
		glGetIntegerv(GL_TEXTURE_MAX_ANISOTROPY_EXT, &currentQuality);

		// Set new quality
		if (currentQuality >= 1 && currentQuality <= Config::MAX_ANISOTROPIC_FILTERING_QUALITY)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, static_cast<int>(_renderBus.getAnisotropicFilteringQuality()));
		}

		// Unbind
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}