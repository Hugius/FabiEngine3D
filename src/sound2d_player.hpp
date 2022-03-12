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
	void pauseSound(const string& id, unsigned int index);
	void resumeSound(const string& id, unsigned int index);
	void stopSound(const string& id, unsigned int index);
	void setSoundVolume(const string& id, unsigned int index, float value);

	const float getSoundVolume(const string& id, unsigned int index) const;

	const int getPlayCount(const string& id, unsigned int index) const;

	const unsigned int getStartedSoundCount(const string& id) const;

	const bool isSoundStarted(const string& id, unsigned int index) const;
	const bool isSoundPaused(const string& id, unsigned int index) const;
	const bool isChannelAvailable() const;
	const bool isDeviceConnected() const;

private:
	void _terminateSound(const string& id, unsigned int index);
	void _terminateSounds();
	void _processVolumeChange(unsigned int sampleCount, short* originalSamples, short* currentSamples, float volume);

	static inline constexpr unsigned int MAX_CHANNEL_COUNT = 1024;

	unordered_map<string, vector<shared_ptr<StartedSound2D>>> _startedSounds;

	shared_ptr<Sound2dManager> _sound2dManager = nullptr;

	unsigned int _channelCounter = 0;
};