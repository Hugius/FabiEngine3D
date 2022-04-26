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
	void startSound(const string & id, int playCount);
	void pauseSound(const string & id, int index);
	void resumeSound(const string & id, int index);
	void stopSound(const string & id, int index);
	void setSoundVolume(const string & id, int index, float value);
	void setSoundLeftIntensity(const string & id, int index, float value);
	void setSoundRightIntensity(const string & id, int index, float value);

	const float getSoundVolume(const string & id, int index) const;
	const float getSoundLeftIntensity(const string & id, int index) const;
	const float getSoundRightIntensity(const string & id, int index) const;

	const int getStartedSoundCount(const string & id) const;
	const int getSoundTime(const string & id, int index) const;

	const int getPlayCount(const string & id, int index) const;

	const bool isSoundStarted(const string & id, int index) const;
	const bool isSoundPaused(const string & id, int index) const;
	const bool isDeviceConnected() const;

private:
	void _terminateSound(const string & id, int index);
	void _terminateSounds();
	void _updateSamplesVolume(int sampleCount, short * originalSamples, short * startedSamples, float volume, float leftIntensity, float rightIntensity);

	unordered_map<string, vector<shared_ptr<StartedSound2D>>> _startedSounds = {};

	vector<pair<string, int>> _volumeThreadQueue;

	shared_ptr<Sound2dManager> _sound2dManager = nullptr;

	future<void> _volumeThread = {};
};