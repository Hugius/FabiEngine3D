#pragma once

#include <SDL_mixer.h>
#include <unordered_map>
#include <string>
#include <vector>

using std::string;
using std::unordered_map;
using std::vector;

class AudioLoader final
{
public:
	~AudioLoader();

	void cacheChunk(const string& filePath);
	void cacheChunks(const vector<string>& filePaths);
	void clearChunkCache(const string& filePath);
	void clearChunksCache();

	Mix_Chunk* loadChunk(const string& filePath);

private:
	void _throwLoadedMessage(const string& filePath);

	const char* _loadWaveFile(const string& filePath) const;

	Mix_Chunk* _loadChunk(const string& filePath, unsigned char* data) const;

	unordered_map<string, Mix_Chunk*> _cache;
};