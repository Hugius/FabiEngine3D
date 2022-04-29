#pragma once

#include "audio_loader.hpp"
#include "wave_buffer_cache.hpp"
#include "sound3d.hpp"

#include <memory>

using std::shared_ptr;

class Sound3dManager final
{
public:
	void inject(shared_ptr<AudioLoader> audioLoader);
	void inject(shared_ptr<WaveBufferCache> waveBufferCache);
	void createSound3d(const string & sound3dId, const string & audioPath);
	void deleteSound3d(const string & sound3dId);
	void deleteSound3ds();

	const unordered_map<string, shared_ptr<Sound3d>> & getSound3ds() const;

	const shared_ptr<Sound3d> getSound3d(const string & sound3dId) const;

	const bool isSound3dExisting(const string & sound3dId) const;
	const bool isSound3dsExisting() const;

private:
	unordered_map<string, shared_ptr<Sound3d>> _sound3ds = {};

	shared_ptr<AudioLoader> _audioLoader = nullptr;
	shared_ptr<WaveBufferCache> _waveBufferCache = nullptr;
};