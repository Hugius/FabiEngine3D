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
	void startSound(const string& id, int playCount, bool mustForce);
	void pauseSound(const string& id);
	void resumeSound(const string& id);
	void stopSound(const string& id);

	const unsigned int getUsedChannelCount() const;
	const unsigned int getAllocatedChannelCount() const;

	const bool isChannelAvailable() const;
	const bool isSoundStarted(const string& id) const;
	const bool isSoundPaused(const string& id) const;

private:
	void _updateSoundVolume(Sound2d& sound);

	const vector<unsigned int> _findChannels(Sound2d& sound) const;
	const int _getFreeChannel() const;

	static inline constexpr unsigned int MAX_CHANNEL_COUNT = 1024;
	array<string, MAX_CHANNEL_COUNT> _channels;

	shared_ptr<Sound2dManager> _sound2dManager = nullptr;
};