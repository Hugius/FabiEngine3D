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
	std::pair<const int, string>& p_getPair(AudioChunk& chunk);
	bool p_isInMap(AudioChunk& chunk);

	int p_getFreeChannel();

	std::map<int, string> p_channelMap;

	int p_musicIndex = 0;

	bool p_debugging = false;
	bool p_soundEnabled = true;
	bool p_musicEnabled = true;

	float p_totalDelta = 0.0f;
};