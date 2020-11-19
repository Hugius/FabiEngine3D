#pragma once

#include "audio_chunk.hpp"
#include "audio_music.hpp"
#include "camera_manager.hpp"

#include <map>
#include <string>
#include <vector>
#include <GLM\\glm.hpp>

using glm::vec3;
using glm::mat4;
using std::string;

class AudioPlayer final
{
public:
	AudioPlayer();
	~AudioPlayer() = default;

	void allocateChannels(int count);
	void update(CameraManager& camera, std::vector<AudioChunk>& chunks, std::vector<AudioMusic>& music);	
	void setChunksEnabled(bool val);
	void stopAllChunks();
	void playChunk(AudioChunk& chunk, int loops, int initialVolume, bool noRestart, int fadeMillis);
	void pauseChunk(AudioChunk& chunk);
	void resumeChunk(AudioChunk& chunk);
	void stopChunk(AudioChunk& chunk, int fadeMillis);
	void setChunkVolume(AudioChunk& chunk, int volume);
	void setMusicEnabled(bool val);
	void pauseMusic();
	void resumeMusic();
	void setMusicVolume(int volume);
	void stopMusic();

	bool isChunkPlaying(AudioChunk& chunk);
	bool isChunkPaused(AudioChunk& chunk);
	bool isMusicPlaying();
	bool isMusicPaused();
	
	int getChunkVolume(AudioChunk& chunk);
	int getMusicVolume();
	int getUsedChannelCount();
	int getAllocatedChannelCount();

private:
	int _getChunkChannel(AudioChunk& chunk);
	bool _isInMap(AudioChunk& chunk);

	int _getFreeChannel();

	std::map<int, string> _channelMap;

	int _musicIndex = 0;

	bool _chunksEnabled = true;
	bool _musicEnabled = true;
};