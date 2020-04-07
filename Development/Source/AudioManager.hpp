#pragma once

#include <vector>

#include "AudioChunk.hpp"
#include "AudioMusic.hpp"
#include "AudioLoader.hpp"

class AudioManager final
{
public:
	AudioManager(AudioLoader& audioLoader);

	void deleteAllMusic();
	void deleteAllChunks();
	void addMusic(const string& fileName);
	void removeMusic();
	void addGlobalChunk(const string& ID, const string& fileName);
	void addPointChunk(const string& ID, const string& fileName, vec3 position, float maxDistance);
	void removeChunk(const string& ID);

	bool isChunkExisting(const string& ID);

	AudioChunk& getChunk(const string& ID);

	std::vector<AudioChunk>& getChunks();
	std::vector<AudioMusic>& getMusic();

private:
	void _checkValidAdd(const string& ID);

	std::vector<AudioChunk> _chunks;
	std::vector<AudioMusic> _musicList;

	AudioLoader& _audioLoader;

	int _findIndex(const string& ID);
};