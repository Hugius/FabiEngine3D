#pragma once

#include <map>
#include <string>
#include <SDL\\SDL_mixer.h>
#include <vector>

using std::string;
using std::vector;

class AudioLoader final
{
public:
	AudioLoader() = default;
	~AudioLoader();
	
	Mix_Chunk* getChunk(const string& filePath);
	Mix_Music* getMusic(const string& filePath);

	void cacheChunksMultiThreaded(const vector<string>& filePaths);
	void clearChunkCache(const string& filePath);
	void clearMusicCache(const string& filePath);

private:
	std::map<string, Mix_Chunk*> _chunkCache;
	std::map<string, Mix_Music*> _musicCache;

	Mix_Chunk* _loadChunk(const string& filePath, unsigned char* data);
	Mix_Music* _loadMusic(const string& filePath);

	void _throwLoadedMessage(const string& filePath);

	char* _loadWaveFile(const std::string& filePath);
};