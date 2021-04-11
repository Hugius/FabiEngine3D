#pragma once

#include "sound.hpp"
#include "music.hpp"
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

	void allocateChannels(int count);
	void update(CameraManager& camera, vector<Sound>& soundList, vector<Music>& musicList);	
	void setSoundsEnabled(bool value);
	void pauseAllSounds();
	void resumeAllSounds();
	void stopAllSounds();
	void playSound(Sound& sound, int loops);
	void pauseSound(Sound& sound);
	void resumeSound(Sound& sound);
	void stopSound(Sound& sound, int fadeMillis);
	void setMusicEnabled(bool value);
	void playMusic(vector<Music>& musicList, bool forcePlay = false);
	void pauseMusic();
	void resumeMusic();
	void stopMusic();
	void setMusicVolume(float volume);

	float getMusicVolume();

	unsigned int getUsedChannelCount();
	unsigned int getAllocatedChannelCount();

	bool isSoundPlaying(Sound& sound);
	bool isSoundPaused(Sound& sound);
	bool isMusicPlaying();
	bool isMusicPaused();

private:
	void _updateSoundVolume(Sound& sound);
	void _updateMusicVolume();

	int _getUsedChannel(Sound& sound);

	int _getFreeChannel();

	bool _isSoundInChannelMap(Sound& sound);

	std::map<int, string> _channelMap;

	float _musicVolume = 1.0f;

	bool _isSoundsEnabled = true;
	bool _isMusicEnabled = true;
};