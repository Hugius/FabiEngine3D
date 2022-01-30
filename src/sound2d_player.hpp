#pragma once

#include "sound2d_manager.hpp"

#include <string>
#include <array>
#include <vector>
#include <memory>

using std::string;
using std::array;
using std::vector;
using std::shared_ptr;

class Sound2dPlayer final
{
public:
	Sound2dPlayer();

	void inject(shared_ptr<Sound2dManager> sound2dManager);
	void update();
	void startSound(Sound2d& sound, int playCount, unsigned int fadeMS, bool mustForce);
	void pauseSound(Sound2d& sound);
	void resumeSound(Sound2d& sound);
	void stopSound(Sound2d& sound, unsigned int fadeMS);
	void pauseSounds(vector<Sound2d>& sounds);
	void resumeSounds(vector<Sound2d>& sounds);
	void stopSounds(vector<Sound2d>& sounds);

	const unsigned int getUsedChannelCount() const;
	const unsigned int getAllocatedChannelCount() const;

	const bool isChannelAvailable() const;
	const bool isSoundStarted(Sound2d& sound) const;
	const bool isSoundPlaying(Sound2d& sound) const;
	const bool isSoundPaused(Sound2d& sound) const;

private:
	void _updateSoundVolume(Sound2d& sound);

	const vector<unsigned int> _findChannels(Sound2d& sound) const;
	const int _getFreeChannel() const;

	static inline constexpr unsigned int MAX_CHANNEL_COUNT = 1024;
	array<string, MAX_CHANNEL_COUNT> _channels;

	shared_ptr<Sound2dManager> _sound2dManager = nullptr;
};