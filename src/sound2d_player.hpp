#pragma once

#include "sound2d.hpp"

#include <string>
#include <vector>

using std::string;
using std::vector;

class Sound2dPlayer final
{
public:
	Sound2dPlayer();

	// VOID
	void allocateChannels(unsigned int count);
	void update(vector<Sound2d>& sounds);
	void startSound(Sound2d& sound, int playCount, unsigned int fadeMS, bool mustForce);
	void pauseSound(Sound2d& sound);
	void resumeSound(Sound2d& sound);
	void stopSound(Sound2d& sound, unsigned int fadeMS);
	void pauseSounds(vector<Sound2d>& sounds);
	void resumeSounds(vector<Sound2d>& sounds);
	void stopSounds(vector<Sound2d>& sounds);

	// UNSIGNED INT
	const unsigned int getUsedChannelCount() const;
	const unsigned int getAllocatedChannelCount() const;

	// BOOL
	const bool isChannelAvailable() const;
	const bool isSoundStarted(Sound2d& sound) const;
	const bool isSoundPlaying(Sound2d& sound) const;
	const bool isSoundPaused(Sound2d& sound) const;

private:
	// VOID
	void _updateSoundVolume(Sound2d& sound);

	// INT
	const vector<int> _findChannels(Sound2d& sound) const;
	const int _getFreeChannel() const;

	// STRING
	vector<string> _channels;
};