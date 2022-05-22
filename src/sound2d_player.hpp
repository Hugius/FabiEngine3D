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
	void startSound2d(const string & sound2dId, int playCount, int startMilliseconds);
	void pauseSound2d(const string & sound2dId, int index);
	void resumeSound2d(const string & sound2dId, int index);
	void stopSound2d(const string & sound2dId, int index);
	void setSound2dVolume(const string & sound2dId, int index, float value);
	void setSound2dLeftIntensity(const string & sound2dId, int index, float value);
	void setSound2dRightIntensity(const string & sound2dId, int index, float value);

	const float getSound2dVolume(const string & sound2dId, int index) const;
	const float getSound2dLeftIntensity(const string & sound2dId, int index) const;
	const float getSound2dRightIntensity(const string & sound2dId, int index) const;

	const int getStartedSound2dCount(const string & sound2dId) const;
	const int getSound2dCurrentMilliseconds(const string & sound2dId, int index) const;
	const int getSound2dPlayCount(const string & sound2dId, int index) const;

	const bool isSound2dStarted(const string & sound2dId, int index) const;
	const bool isSound2dPaused(const string & sound2dId, int index) const;
	const bool isDeviceConnected() const;

private:
	void _terminateSound2d(const string & sound2dId, int index);
	void _terminateSound2ds();
	void _updateSamplesVolume(int originalSampleCount, int startedSampleCount, short * originalSamples, short * startedSamples, float volume, float leftIntensity, float rightIntensity);

	unordered_map<string, vector<shared_ptr<StartedSound2D>>> _startedSound2ds = {};

	vector<pair<string, int>> _volumeThreadQueue = {};

	shared_ptr<Sound2dManager> _sound2dManager = nullptr;

	future<void> _volumeThread = {};
};