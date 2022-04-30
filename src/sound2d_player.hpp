#pragma once

#include "sound2d_manager.hpp"
#include "started_sound2d.hpp"

#include <string>
#include <array>
#include <vector>
#include <memory>
#include <future>

using std::string;
using std::array;
using std::vector;
using std::shared_ptr;
using std::pair;
using std::future;

class Sound2dPlayer final
{
public:
	void inject(shared_ptr<Sound2dManager> sound2dManager);
	void update();
	void startSound(const string & sound2dId, int playCount);
	void pauseSound(const string & sound2dId, int index);
	void resumeSound(const string & sound2dId, int index);
	void stopSound(const string & sound2dId, int index);
	void setSoundVolume(const string & sound2dId, int index, float value);
	void setSoundLeftIntensity(const string & sound2dId, int index, float value);
	void setSoundRightIntensity(const string & sound2dId, int index, float value);

	const float getSoundVolume(const string & sound2dId, int index) const;
	const float getSoundLeftIntensity(const string & sound2dId, int index) const;
	const float getSoundRightIntensity(const string & sound2dId, int index) const;

	const int getStartedSoundCount(const string & sound2dId) const;
	const int getSoundTime(const string & sound2dId, int index) const;

	const int getPlayCount(const string & sound2dId, int index) const;

	const bool isSound2dStarted(const string & sound2dId, int index) const;
	const bool isSoundPaused(const string & sound2dId, int index) const;
	const bool isDeviceConnected() const;

private:
	void _terminateSound(const string & sound2dId, int index);
	void _terminateSound2ds();
	void _updateSamplesVolume(int sampleCount, short * originalSamples, short * startedSamples, float volume, float leftIntensity, float rightIntensity);

	unordered_map<string, vector<shared_ptr<StartedSound2D>>> _startedSound2ds = {};

	vector<pair<string, int>> _volumeThreadQueue;

	shared_ptr<Sound2dManager> _sound2dManager = nullptr;

	future<void> _volumeThread = {};
};