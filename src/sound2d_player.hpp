#pragma once

#include "sound2d_manager.hpp"
#include "started_sound2d.hpp"

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
	void inject(shared_ptr<Sound2dManager> sound2dManager);
	void update();
	void startSound(const string& id, int playCount);
	void pauseSound(const string& id);
	void resumeSound(const string& id);
	void stopSound(const string& id);
	void setSoundVolume(const string& id, float value);
	void setSoundSpeed(const string& id, float value);
	void setSoundPitch(const string& id, float value);

	const float getSoundVolume(const string& id) const;
	const float getSoundSpeed(const string& id) const;
	const float getSoundPitch(const string& id) const;

	const bool isChannelAvailable() const;
	const bool isSoundStarted(const string& id) const;
	const bool isSoundPaused(const string& id) const;

private:
	static inline constexpr unsigned int MAX_CHANNEL_COUNT = 1024;

	unordered_map<string, vector<shared_ptr<StartedSound2D>>> _startedSounds;

	shared_ptr<Sound2dManager> _sound2dManager = nullptr;

	unsigned int _channelCounter = 0;
};