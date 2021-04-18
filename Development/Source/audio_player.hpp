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
	void setMusicEnabled(bool value);
	void playSound(Sound& sound, int loops, int fadeMS, bool forcePlay = false);
	void playMusic(vector<Music>& musicList, bool forcePlay = false);
	void pauseAllSounds();
	void pauseSound(Sound& sound);
	void pauseMusic();
	void resumeAllSounds();
	void resumeSound(Sound& sound);
	void resumeMusic();
	void stopAllSounds();
	void stopSound(Sound& sound, int fadeMS);
	void stopMusic();
	void setMusicVolume(float volume);

	float getMusicVolume();

	unsigned int getUsedChannelCount();
	unsigned int getAllocatedChannelCount();

	bool isSoundStarted(Sound& sound);
	bool isSoundPlaying(Sound& sound);
	bool isSoundPaused(Sound& sound);
	bool isMusicStarted();
	bool isMusicPlaying();
	bool isMusicPaused();

private:
	void _updateSoundVolume(Sound& sound);
	void _updateMusicVolume();

	vector<int> _findSoundChannels(Sound& sound);

	int _getFreeChannel();

	vector<string> _channels;

	float _musicVolume = 1.0f;

	bool _isSoundsEnabled = true;
	bool _isMusicEnabled = true;
};