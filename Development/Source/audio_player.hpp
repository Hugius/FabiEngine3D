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
	void setSoundEnabled(bool val);
	void setMusicEnabled(bool val);
	void stopAllSounds();
	void stopAllMusic();
	void playChunk(AudioChunk& chunk, int loops, int initialVolume, bool noRestart, int fadeMillis);
	void pauseChunk(AudioChunk& chunk);
	void resumeChunk(AudioChunk& chunk);
	void stopChunk(AudioChunk& chunk, int fadeMillis);
	void setChunkVolume(AudioChunk& chunk, int volume);
	void setMusicVolume(int volume);
	void setChannelDebugging(bool val);

	bool isPlaying(AudioChunk& chunk);

	int getVolume(AudioChunk& chunk);
	int getUsedChannelCount();
	int getAllocatedChannelCount();

private:
	std::pair<const int, string>& _getPair(AudioChunk& chunk);
	bool _isInMap(AudioChunk& chunk);

	int _getFreeChannel();

	std::map<int, string> _channelMap;

	int _musicIndex = 0;

	bool _debugging = false;
	bool _soundEnabled = true;
	bool _musicEnabled = true;
};