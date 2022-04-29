#pragma once

#include "audio_loader.hpp"
#include "wave_buffer_cache.hpp"
#include "sound2d.hpp"

#include <memory>

using std::shared_ptr;

class Sound2dManager final
{
public:
	void inject(shared_ptr<AudioLoader> audioLoader);
	void inject(shared_ptr<WaveBufferCache> waveBufferCache);
	void createSound2d(const string & sound2dId, const string & audioPath);
	void deleteSound2d(const string & sound2dId);
	void deleteSound2ds();

	const unordered_map<string, shared_ptr<Sound2d>> & getSound2ds() const;

	const shared_ptr<Sound2d> getSound2d(const string & sound2dId) const;

	const bool isSound2dExisting(const string & sound2dId) const;
	const bool isSound2dsExisting() const;

private:
	unordered_map<string, shared_ptr<Sound2d>> _sound2ds = {};

	shared_ptr<AudioLoader> _audioLoader = nullptr;
	shared_ptr<WaveBufferCache> _waveBufferCache = nullptr;
};