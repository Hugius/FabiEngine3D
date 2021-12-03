#pragma once

#include "sound_2d.hpp"
#include "sound_3d.hpp"
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

	// VOID
	void allocateChannels(unsigned int count);
	void update(Camera& camera, vector<Music>& musicList, vector<Sound2D>& soundList2D, vector<Sound3D>& soundList3D);
	void pauseMusic();
	void resumeMusic();
	void stopMusic();
	void setMusicVolume(float volume);
	void playSound2D(Sound2D& sound, int loops, unsigned int fadeMS, bool mustForcePlay);
	void pauseSound2D(Sound2D& sound);
	void resumeSound2D(Sound2D& sound);
	void stopSound2D(Sound2D& sound, unsigned int fadeMS);
	void pauseAllSounds2D(vector<Sound2D>& soundList);
	void resumeAllSounds2D(vector<Sound2D>& soundList);
	void stopAllSounds2D(vector<Sound2D>& soundList);
	void playSound3D(Sound3D& sound, int loops, unsigned int fadeMS, bool mustForcePlay);
	void pauseSound3D(Sound3D& sound);
	void resumeSound3D(Sound3D& sound);
	void stopSound3D(Sound3D& sound, unsigned int fadeMS);
	void pauseAllSounds3D(vector<Sound3D>& soundList);
	void resumeAllSounds3D(vector<Sound3D>& soundList);
	void stopAllSounds3D(vector<Sound3D>& soundList);

	// FLOAT
	const float getMusicVolume() const;

	// UNSIGNED INT
	const unsigned int getUsedChannelCount() const;
	const unsigned int getAllocatedChannelCount() const;

	// BOOL
	const bool isChannelAvailable() const;
	const bool isMusicStarted() const;
	const bool isMusicPlaying() const;
	const bool isMusicPaused() const;
	const bool isSoundStarted2D(Sound2D& sound) const;
	const bool isSoundPlaying2D(Sound2D& sound) const;
	const bool isSoundPaused2D(Sound2D& sound) const;
	const bool isSoundStarted3D(Sound3D& sound) const;
	const bool isSoundPlaying3D(Sound3D& sound) const;
	const bool isSoundPaused3D(Sound3D& sound) const;

private:
	// VOID
	void _updateSoundVolume2D(Sound2D& sound);
	void _updateSoundVolume3D(Sound3D& sound);

	// INT
	const vector<int> _findSoundChannels2D(Sound2D& sound) const;
	const vector<int> _findSoundChannels3D(Sound3D& sound) const;
	const int _getFreeChannel() const;

	// STRING
	vector<string> _channels;
};