#pragma once

#include "sound2d.hpp"
#include "sound3d.hpp"
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
	void update(Camera& camera, vector<Music>& mucisList, vector<Sound2d>& sound2dList, vector<Sound3d>& sound3dList);
	void pauseMusic();
	void resumeMusic();
	void stopMusic();
	void setMusicVolume(float volume);
	void playSound2d(Sound2d& sound, int loops, unsigned int fadeMS, bool mustForcePlay);
	void pauseSound2d(Sound2d& sound);
	void resumeSound2d(Sound2d& sound);
	void stopSound2d(Sound2d& sound, unsigned int fadeMS);
	void pauseAllSound2d(vector<Sound2d>& sounds);
	void resumeAllSound2d(vector<Sound2d>& sounds);
	void stopAllSound2d(vector<Sound2d>& sounds);
	void playSound3d(Sound3d& sound, int loops, unsigned int fadeMS, bool mustForcePlay);
	void pauseSound3d(Sound3d& sound);
	void resumeSound3d(Sound3d& sound);
	void stopSound3d(Sound3d& sound, unsigned int fadeMS);
	void pauseAllSound3d(vector<Sound3d>& sounds);
	void resumeAllSound3d(vector<Sound3d>& sounds);
	void stopAllSound3d(vector<Sound3d>& sounds);

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
	const bool isSound2dStarted(Sound2d& sound) const;
	const bool isSound2dPlaying(Sound2d& sound) const;
	const bool isSound2dPaused(Sound2d& sound) const;
	const bool isSound3dStarted(Sound3d& sound) const;
	const bool isSound3dPlaying(Sound3d& sound) const;
	const bool isSound3dPaused(Sound3d& sound) const;

private:
	// VOID
	void _updateSound2dVolume(Sound2d& sound);
	void _updateSound3dVolume(Sound3d& sound);

	// INT
	const vector<int> _findChannels(Sound2d& sound) const;
	const vector<int> _findChannels(Sound3d& sound) const;
	const int _getFreeChannel() const;

	// STRING
	vector<string> _channels;
};