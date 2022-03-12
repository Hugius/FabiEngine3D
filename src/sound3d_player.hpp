#pragma once

#include "sound3d_manager.hpp"
#include "started_sound3d.hpp"
#include "camera.hpp"

#include <string>
#include <array>
#include <vector>
#include <memory>

using std::string;
using std::array;
using std::vector;
using std::shared_ptr;

class Sound3dPlayer final
{
public:
	void inject(shared_ptr<Sound3dManager> sound3dManager);
	void inject(shared_ptr<Camera> camera);
	void update();
	void startSound(const string& id, int playCount);
	void pauseSound(const string& id, unsigned int index);
	void resumeSound(const string& id, unsigned int index);
	void stopSound(const string& id, unsigned int index);

	const float getSoundVolume(const string& id, unsigned int index) const;
	const float getSoundLeftIntensity(const string& id, unsigned int index) const;
	const float getSoundRightIntensity(const string& id, unsigned int index) const;

	const int getPlayCount(const string& id, unsigned int index) const;

	const unsigned int getStartedSoundCount(const string& id) const;

	const bool isSoundStarted(const string& id, unsigned int index) const;
	const bool isSoundPaused(const string& id, unsigned int index) const;
	const bool isChannelAvailable() const;
	const bool isDeviceConnected() const;

private:
	void _terminateSound(const string& id, unsigned int index);
	void _terminateSounds();
	void _processVolumeChange(unsigned int sampleCount, short* originalSamples, short* currentSamples, float volume, float leftIntensity, float rightIntensity);

	static inline constexpr unsigned int MAX_CHANNEL_COUNT = 1024;

	unordered_map<string, vector<shared_ptr<StartedSound3D>>> _startedSounds;

	shared_ptr<Sound3dManager> _sound3dManager = nullptr;
	shared_ptr<Camera> _camera = nullptr;

	unsigned int _channelCounter = 0;
};