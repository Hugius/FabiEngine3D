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
	void createSound(const string& id, const string& audioPath);
	void deleteSound(const string& id);
	void deleteSounds();

	const bool isSoundExisting(const string& id) const;
	const bool isSoundsExisting() const;

	const shared_ptr<Sound2d> getSound(const string& id) const;
	const unordered_map<string, shared_ptr<Sound2d>>& getSounds() const;

private:
	unordered_map<string, shared_ptr<Sound2d>> _sounds;

	shared_ptr<AudioLoader> _audioLoader = nullptr;
	shared_ptr<WaveBufferCache> _waveBufferCache = nullptr;
};