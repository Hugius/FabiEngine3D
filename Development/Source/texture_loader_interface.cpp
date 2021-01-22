#include "texture_loader.hpp"
#include "logger.hpp"

#include <future>

GLuint TextureLoader::getText(const string& textContent, const string& fontPath)
{
	begin: auto it = _textCache.find(make_pair(textContent, fontPath));
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
			goto begin;
		}
	}

	return it->second; // Cache texture
}

void TextureLoader::cacheTextures(const vector<string>& filePaths)
{
	// Temporary values
	vector<std::future<SDL_Surface*>> threads;
	vector<bool> threadStatuses;
	unsigned int finishedThreadCount = 0;

	// Start all loading threads
	for (unsigned int i = 0; i < filePaths.size(); i++)
	{
		threads.push_back(std::async(std::launch::async, &TextureLoader::_loadImage, this, filePaths[i]));
		threadStatuses.push_back(false);
	}
	
	// Wait for all threads to finish
	begin:
	for (unsigned int i = 0; i < threads.size(); i++)
	{
		// Check if thread is valid
		if (threads[i].valid())
		{
			// Check if thread was not already finished
			if (!threadStatuses[i])
			{
				// Check if thread is finished
				if (threads[i].wait_until(std::chrono::system_clock::time_point::min()) == std::future_status::ready)
				{
					// Retrieve the SDL image
					auto loadedImage = threads[i].get();

					// Update thread status
					threadStatuses[i] = true;
					finishedThreadCount++;

					// Check image status
					if (loadedImage != nullptr)
					{
						// Load OpenGL texture
						auto loadedTexture = _convertToTexture(filePaths[i], loadedImage, true, true, true);

						// Check texture status
						if (loadedTexture != 0)
						{
							// Logging
							Logger::throwInfo("Loaded texture: \"" + filePaths[i] + "\"");

							// Cache texture
							_textureCache[filePaths[i]] = loadedTexture;
						}
					}

					// Free image memory
					SDL_FreeSurface(loadedImage);
				}
			}
		}
	}

	// Check if a thread is not finished yet
	if (finishedThreadCount != threads.size())
	{
		goto begin;
	}
}

GLuint TextureLoader::getTexture(const string& filePath, bool mipmap, bool aniso, bool repeat)
{
	begin: auto it = _textureCache.find(filePath);
	if (it == _textureCache.end()) // Not in map (yet)
	{
		// Load SDL image
		auto loadedImage = _loadImage(filePath);

		// Check image status
		if (loadedImage == nullptr)
		{
			return 0;
		}
		else
		{
			// Load OpenGL texture
			auto loadedTexture = _convertToTexture(filePath, loadedImage, mipmap, aniso, repeat);

			// Free image memory
			SDL_FreeSurface(loadedImage);

			// Check texture status
			if (loadedTexture == 0)
			{
				return 0;
			}
			else
			{
				// Logging
				Logger::throwInfo("Loaded texture: \"" + filePath + "\"");
				
				// Cache texture
				_textureCache.insert(std::make_pair(filePath, loadedTexture));

				// Return cached texture
				goto begin;
			}
		}
	}
	
	return it->second; // Cache texture
}

GLuint TextureLoader::getCubeMap(const array<string, 6>& filePaths)
{
	begin: auto it = _cubeMapCache.find(filePaths);
	if (it == _cubeMapCache.end()) // Not in map (yet)
	{
		GLuint loadedTexture = _loadCubeMap(filePaths);

		// Determine if needs to be cached
		if (loadedTexture == 0)
		{
			return 0;
		}
		else
		{
			_cubeMapCache.insert(std::make_pair(filePaths, loadedTexture));
			goto begin;
		}
	}

	return it->second; // Cache texture
}

const vector<float>& TextureLoader::getHeightMap(const string& filePath)
{
	begin: auto it = _heightMapCache.find(filePath);
	if (it == _heightMapCache.end()) // Not in map (yet)
	{
		auto loadedPixels = _loadHeightMap(filePath);

		// Determine if needs to be cached
		if (loadedPixels.empty())
		{
			return {};
		}
		else
		{
			_heightMapCache.insert(std::make_pair(filePath, loadedPixels));
			goto begin;
		}
	}

	return it->second; // Cache texture
}

void TextureLoader::clearTextCache(const string& textContent, const string& fontPath)
{
	if (_textCache.find(make_pair(textContent, fontPath)) != _textCache.end())
	{
		glDeleteTextures(1, &_textCache[make_pair(textContent, fontPath)]);
		_textCache.erase(make_pair(textContent, fontPath));
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

void TextureLoader::clearTextureCache(const string& filePath)
{
	if (_textureCache.find(filePath) != _textureCache.end())
	{
		glDeleteTextures(1, &_textureCache[filePath]);
		_textureCache.erase(filePath);
	}
}

void TextureLoader::clearCubeMapCache(const array<string, 6>& filePaths)
{
	if (_cubeMapCache.find(filePaths) != _cubeMapCache.end())
	{
		glDeleteTextures(1, &_cubeMapCache[filePaths]);
		_cubeMapCache.erase(filePaths);
	}
}

void TextureLoader::clearHeightMapCache(const string& filePath)
{
	if (_heightMapCache.find(filePath) != _heightMapCache.end())
	{
		_heightMapCache.erase(filePath);
	}
}