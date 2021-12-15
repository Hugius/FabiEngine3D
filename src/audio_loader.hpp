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

	// VOID
	void cacheChunk(const string& filePath);
	void cacheChunks(const vector<string>& filePaths);
	void clearChunkCache(const string& filePath);
	void clearChunksCache();

	// MISCELLANEOUS
	Mix_Chunk* loadChunk(const string& filePath);

private:
	// VOID
	void _throwLoadedMessage(const string& filePath);

	// CHAR
	const char* _loadWaveFile(const string& filePath) const;

	// MISCELLANEOUS
	Mix_Chunk* _loadChunk(const string& filePath, unsigned char* data) const;

	// MISCELLANEOUS
	map<string, Mix_Chunk*> _chunkCache;
};