#pragma once

#include <SDL\\SDL_mixer.h>
#include <map>
#include <string>
#include <vector>

using std::string;
using std::map;
using std::vector;

class AudioLoader final
{
public:
	~AudioLoader();

	// Voids
	void cacheChunksMultiThreaded(const vector<string>& filePaths);
	void cacheMusicMultiThreaded(const vector<string>& filePaths);
	void clearChunkCache(const string& filePath);
	void clearMusicCache(const string& filePath);

	// Miscellaneous
	Mix_Chunk* getChunkDataPointer(const string& filePath);
	Mix_Music* getMusicDataPointer(const string& filePath);

private:
	// Voids
	void _throwLoadedMessage(const string& filePath);

	// Characters
	char* _loadWaveFile(const string& filePath);

	// Miscellaneous
	Mix_Chunk* _loadChunk(const string& filePath, unsigned char* data);
	Mix_Music* _loadMusic(const string& filePath);

	// Miscellaneous
	map<string, Mix_Chunk*> _chunkCache;
	map<string, Mix_Music*> _musicCache;
};