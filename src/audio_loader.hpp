#pragma once

#include "audio.hpp"

#include <vector>
#include <unordered_map>
#include <string>
#include <memory>

using std::vector;
using std::string;
using std::unordered_map;
using std::shared_ptr;

class AudioLoader final
{
public:
	void cacheAudio(const string& filePath, bool isCrucial);
	void cacheAudios(const vector<string>& filePaths, bool isCrucial);
	void clearAudioCache(const string& filePath);
	void clearAudiosCache();

	const shared_ptr<Audio> loadAudio(const string& filePath);

private:
	shared_ptr<Audio> _loadAudio(const string& filePath);

	unordered_map<string, shared_ptr<Audio>> _cache;

	static inline const unsigned int CHUNK_HEADER_SIZE = 12;
	static inline const unsigned int SUB_CHUNK_HEADER_SIZE = 8;
};