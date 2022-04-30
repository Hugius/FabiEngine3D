#pragma once

#include "sound3d_manager.hpp"
#include "started_sound3d.hpp"
#include "camera.hpp"

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

class Sound3dPlayer final
{
public:
	void inject(shared_ptr<Sound3dManager> sound3dManager);
	void inject(shared_ptr<Camera> camera);
	void update();
	void startSound(const string & sound3dId, int playCount);
	void pauseSound(const string & sound3dId, int index);
	void resumeSound(const string & sound3dId, int index);
	void stopSound(const string & sound3dId, int index);

	const float getSoundVolume(const string & sound3dId, int index) const;
	const float getSoundLeftIntensity(const string & sound3dId, int index) const;
	const float getSoundRightIntensity(const string & sound3dId, int index) const;

	const int getStartedSoundCount(const string & sound3dId) const;
	const int getSoundTime(const string & sound3dId, int index) const;

	const int getPlayCount(const string & sound3dId, int index) const;

	const bool isSound3dStarted(const string & sound3dId, int index) const;
	const bool isSoundPaused(const string & sound3dId, int index) const;
	const bool isDeviceConnected() const;

private:
	void _terminateSound3d(const string & sound3dId, int index);
	void _terminateSound3ds();
	void _updateSamplesVolume(int sampleCount, short * originalSamples, short * currentSamples, float volume, float leftIntensity, float rightIntensity);

	unordered_map<string, vector<shared_ptr<StartedSound3D>>> _startedSound3ds = {};

	vector<pair<string, int>> _volumeThreadQueue;

	shared_ptr<Sound3dManager> _sound3dManager = nullptr;
	shared_ptr<Camera> _camera = nullptr;

	future<void> _volumeThread = {};
};