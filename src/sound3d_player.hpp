#pragma once

#include "sound3d.hpp"
#include "camera.hpp"

#include <string>
#include <array>
#include <vector>

using std::string;
using std::array;
using std::vector;

class Sound3dPlayer final
{
public:
	Sound3dPlayer();

	// VOID
	void update(vector<Sound3d>& sounds, Camera& camera);
	void startSound(Sound3d& sound, int playCount, unsigned int fadeMS, bool mustForce);
	void pauseSound(Sound3d& sound);
	void resumeSound(Sound3d& sound);
	void stopSound(Sound3d& sound, unsigned int fadeMS);
	void pauseSounds(vector<Sound3d>& sounds);
	void resumeSounds(vector<Sound3d>& sounds);
	void stopSounds(vector<Sound3d>& sounds);

	// UNSIGNED INT
	const unsigned int getUsedChannelCount() const;
	const unsigned int getAllocatedChannelCount() const;

	// BOOL
	const bool isChannelAvailable() const;
	const bool isSoundStarted(Sound3d& sound) const;
	const bool isSoundPlaying(Sound3d& sound) const;
	const bool isSoundPaused(Sound3d& sound) const;

	// UNSIGNED INT
	static inline const unsigned int MAX_CHANNEL_COUNT = 1024;

private:
	// VOID
	void _updateSoundVolume(Sound3d& sound);

	// INT
	const vector<unsigned int> _findChannels(Sound3d& sound) const;
	const int _getFreeChannel() const;

	// STRING
	array<string, 1024> _channels;
};