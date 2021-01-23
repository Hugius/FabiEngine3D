#pragma once

#include <map>
#include <string>
#include <SDL\\SDL_mixer.h>

using std::string;

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

	Mix_Chunk* _loadChunk(const string& filePath);
	Mix_Music* _loadMusic(const string& filePath);
};