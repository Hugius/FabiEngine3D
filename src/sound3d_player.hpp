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
	void startSound3d(const string & sound3dId, int playCount);
	void pauseSound3d(const string & sound3dId, int index);
	void resumeSound3d(const string & sound3dId, int index);
	void stopSound3d(const string & sound3dId, int index);

	const float getSound3dVolume(const string & sound3dId, int index) const;
	const float getSound3dLeftIntensity(const string & sound3dId, int index) const;
	const float getSound3dRightIntensity(const string & sound3dId, int index) const;

	const int getStartedSound3dCount(const string & sound3dId) const;
	const int getSound3dTime(const string & sound3dId, int index) const;

	const int getSound3dPlayCount(const string & sound3dId, int index) const;

	const bool isSound3dStarted(const string & sound3dId, int index) const;
	const bool isSound3dPaused(const string & sound3dId, int index) const;
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