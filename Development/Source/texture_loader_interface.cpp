#include "texture_loader.hpp"
#include "logger.hpp"
#include "configuration.hpp"

#include <future>
#include <set>

TextureLoader::TextureLoader(RenderBus& renderBus)
	:
	_renderBus(renderBus)
{

}

void TextureLoader::cacheTexturesMultiThreaded2D(const vector<string>& filePaths, bool isMipmapped, bool isAnisotropic)
{
	// Temporary values
	vector<std::future<SDL_Surface*>> threads;
	vector<bool> cacheStatuses;
	unsigned int finishedThreadCount = 0;

	// Remove duplicates
	auto tempFilePaths = std::set<string>(filePaths.begin(), filePaths.end());
	auto uniqueFilePaths = vector<string>(tempFilePaths.begin(), tempFilePaths.end());

	// Start all loading threads
	for (const auto& filePath : uniqueFilePaths)
	{
		// Check if texture is not already cached
		if (_textureCache2D.find(filePath) == _textureCache2D.end())
		{
			threads.push_back(std::async(std::launch::async, &TextureLoader::_loadImage, this, filePath));
			cacheStatuses.push_back(false);
		}
		else
		{
			cacheStatuses.push_back(true);
			finishedThreadCount++;
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
				if (threads[i].wait_until(std::chrono::system_clock::time_point::min()) == std::future_status::ready)
				{
					// Retrieve the SDL image
					auto loadedImage = threads[i].get();

					// Update thread status
					cacheStatuses[i] = true;
					finishedThreadCount++;

					// Check image status
					if (loadedImage == nullptr)
					{
						Logger::throwWarning("Cannot load image file: \"" + uniqueFilePaths[i] + "\"!");
					}
					else
					{
						// Load OpenGL texture
						auto loadedTexture = _convertToTexture2D(uniqueFilePaths[i], loadedImage, isMipmapped, isAnisotropic);

						// Free image memory
						SDL_FreeSurface(loadedImage);

						// Check texture status
						if (loadedTexture != 0)
						{
							// Cache texture
							_textureCache2D[uniqueFilePaths[i]] = loadedTexture;
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
	vector<vector<std::future<SDL_Surface*>>> threads;
	vector<bool> cacheStatuses;

	// Start all loading threads
	for (const auto& filePaths : filePathsList)
	{
		// Check if texture is not already cached
		if (_textureCache3D.find(filePaths) == _textureCache3D.end())
		{
			// 6 threads for every 3D texture
			cacheStatuses.push_back(false);
			threads.push_back({});
			for (const auto& filePath : filePaths)
			{
				threads.back().push_back(std::async(std::launch::async, &TextureLoader::_loadImage, this, filePath));
			}
		}
		else
		{
			cacheStatuses.push_back(true);
		}
	}

	// Wait for all threads to finish
	for (size_t i = 0; i < cacheStatuses.size(); i++)
	{
		// Check if texture is not processed yet
		if (!cacheStatuses[i])
		{
			// 6 images for every 3D texture
			array<SDL_Surface*, 6> loadedImages;
			for (size_t j = 0; j < threads[i].size(); j++)
			{
				// Save loaded image
				loadedImages[j] = threads[i][j].get();

				// Error logging
				if (loadedImages[j] == nullptr && !filePathsList[i][j].empty())
				{
					Logger::throwWarning("Cannot load image file: \"" + filePathsList[i][j] + "\"!");
				}
			}

			// Load OpenGL texture
			GLuint loadedTexture = _convertToTexture3D(filePathsList[i], loadedImages);

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
				_textureCache3D[filePathsList[i]] = loadedTexture;
			}
		}
	}
}

GLuint TextureLoader::getTexture2D(const string& filePath, bool isMipmapped, bool isAnisotropic)
{
BEGIN:
	auto it = _textureCache2D.find(filePath);
	if (it == _textureCache2D.end()) // Not in map (yet)
	{
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
				_textureCache2D.insert(std::make_pair(filePath, loadedTexture));

				// Return cached texture
				goto BEGIN;
			}
		}
	}

	return it->second;
}

GLuint TextureLoader::getTexture3D(const array<string, 6>& filePaths)
{
BEGIN:
	auto it = _textureCache3D.find(filePaths);
	if (it == _textureCache3D.end()) // Not in map (yet)
	{
		// Temporary values
		vector<std::future<SDL_Surface*>> threads;
		array<SDL_Surface*, 6> loadedImages = { };

		// Start all loading threads
		for (size_t i = 0; i < filePaths.size(); i++)
		{
			threads.push_back(std::async(std::launch::async, &TextureLoader::_loadImage, this, filePaths[i]));
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
		GLuint loadedTexture = _convertToTexture3D(filePaths, loadedImages);

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
			_textureCache3D.insert(std::make_pair(filePaths, loadedTexture));

			// Return cached texture
			goto BEGIN;
		}
	}

	return it->second;
}

GLuint TextureLoader::getText(const string& textContent, const string& fontPath)
{
BEGIN:
	auto it = _textCache.find(make_pair(textContent, fontPath));
	if (it == _textCache.end()) // Not in map (yet)
	{
		GLuint loadedTexture = _loadText(textContent, fontPath);

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

	return it->second;
}

const vector<float>* TextureLoader::getBitmapPixels(const string& filePath)
{
BEGIN:
	auto it = _bitmapCache.find(filePath);
	if (it == _bitmapCache.end()) // Not in map (yet)
	{
		auto loadedPixels = _loadBitmapPixels(filePath);

		// Check pixels status
		if (loadedPixels.empty())
		{
			return nullptr;
		}
		else
		{
			// Cache pixels
			_bitmapCache.insert(std::make_pair(filePath, loadedPixels));

			// Return cached pixels
			goto BEGIN;
		}
	}

	return &it->second;
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