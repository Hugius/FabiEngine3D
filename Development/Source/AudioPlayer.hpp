#pragma once

#include <map>
#include <string>
#include <vector>
#include <GLM/glm.hpp>

using glm::vec3;
using glm::mat4;
using std::string;

#include "AudioChunk.hpp"
#include "AudioMusic.hpp"
#include "CameraManager.hpp"

class AudioPlayer final
{
public:
	AudioPlayer();
	~AudioPlayer() = default;

	void update(CameraManager& camera, std::vector<AudioChunk>& chunks, std::vector<AudioMusic>& music, float delta);	
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

private:
	std::pair<const int, string>& _getPair(AudioChunk& chunk);
	bool _isInMap(AudioChunk& chunk);

	int _getFreeChannel();

	std::map<int, string> _channelMap;

	int _musicIndex = 0;

	bool _debugging = false;
	bool _soundEnabled = true;
	bool _musicEnabled = true;

	float _totalDelta = 0.0f;
};