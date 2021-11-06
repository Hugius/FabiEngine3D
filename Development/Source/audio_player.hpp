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
	const float getMusicVolume() const;

	// Integers
	const unsigned int getUsedChannelCount() const;
	const unsigned int getAllocatedChannelCount() const;

	// Booleans
	const bool isChannelAvailable() const;
	const bool isSoundsEnabled() const;
	const bool isSoundStarted(Sound& sound) const;
	const bool isSoundPlaying(Sound& sound) const;
	const bool isSoundPaused(Sound& sound) const;
	const bool isMusicEnabled() const;
	const bool isMusicStarted() const;
	const bool isMusicPlaying() const;
	const bool isMusicPaused() const;

private:
	// Voids
	void _updateSoundVolume(Sound& sound);
	void _updateMusicVolume();

	// Integers
	const vector<int> _findSoundChannels(Sound& sound)  const;
	const int _getFreeChannel() const;

	// Strings
	vector<string> _channels;

	// Decimals
	float _musicVolume = 1.0f;

	// Booleans
	bool _isSoundsEnabled = true;
	bool _isMusicEnabled = true;
};