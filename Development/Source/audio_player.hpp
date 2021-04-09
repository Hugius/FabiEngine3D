#pragma once

#include "audio_chunk.hpp"
#include "audio_music.hpp"
#include "camera_manager.hpp"
#include "mathematics.hpp"

#include <map>
#include <string>
#include <vector>

using std::string;
using std::vector;

class AudioPlayer final
{
public:
	AudioPlayer();
	~AudioPlayer() = default;

	// Functions
	void allocateChannels(int count);
	void update(CameraManager& camera, vector<AudioChunk>& chunkList, vector<AudioMusic>& musicList);	
	void setChunksEnabled(bool value);
	void pauseAllChunks();
	void resumeAllChunks();
	void stopAllChunks();
	void playChunk(AudioChunk& chunk, int loops);
	void pauseChunk(AudioChunk& chunk);
	void resumeChunk(AudioChunk& chunk);
	void stopChunk(AudioChunk& chunk, int fadeMillis);
	void setChunkVolume(AudioChunk& chunk, int volume);
	void setMusicEnabled(bool value);
	void playMusic(vector<AudioMusic>& musicList);
	void pauseMusic();
	void resumeMusic();
	void stopMusic();
	void setMusicVolume(int volume);

	// Booleans
	bool isChunkPlaying(AudioChunk& chunk);
	bool isChunkPaused(AudioChunk& chunk);
	bool isMusicPlaying();
	bool isMusicPaused();
	
	// Integers
	int getChunkVolume(AudioChunk& chunk);
	int getMusicVolume();

	// Unsigned integers
	unsigned int getUsedChannelCount();
	unsigned int getAllocatedChannelCount();

private:
	int _getChunkChannel(AudioChunk& chunk);
	bool _isInMap(AudioChunk& chunk);

	int _getFreeChannel();

	std::map<int, string> _channelMap;

	bool _chunksEnabled = true;
	bool _musicEnabled = true;
};