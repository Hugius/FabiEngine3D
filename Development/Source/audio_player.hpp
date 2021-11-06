#pragma once

#include "sound.hpp"
#include "music.hpp"
#include "camera.hpp"
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

	// Voids
	void allocateChannels(unsigned int count);
	void update(Camera& camera, vector<Sound>& soundList, vector<Music>& musicList);
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

	// Decimals
	float getMusicVolume();

	// Integers
	unsigned int getUsedChannelCount();
	unsigned int getAllocatedChannelCount();

	// Booleans
	bool isChannelAvailable();
	bool isSoundsEnabled();
	bool isSoundStarted(Sound& sound);
	bool isSoundPlaying(Sound& sound);
	bool isSoundPaused(Sound& sound);
	bool isMusicEnabled();
	bool isMusicStarted();
	bool isMusicPlaying();
	bool isMusicPaused();

private:
	// Voids
	void _updateSoundVolume(Sound& sound);
	void _updateMusicVolume();

	// Integers
	vector<int> _findSoundChannels(Sound& sound);
	int _getFreeChannel();

	// Strings
	vector<string> _channels;

	// Decimals
	float _musicVolume = 1.0f;

	// Booleans
	bool _isSoundsEnabled = true;
	bool _isMusicEnabled = true;
};