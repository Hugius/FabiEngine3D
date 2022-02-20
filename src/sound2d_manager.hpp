#pragma once

#include "sound2d.hpp"
#include "audio_loader.hpp"

#include <memory>

using std::shared_ptr;

class Sound2dManager final
{
public:
	void inject(shared_ptr<AudioLoader> audioLoader);
	void update();
	void createSound(const string& id, const string& audioPath);
	void deleteSound(const string& id);
	void deleteSounds();

	const bool isSoundExisting(const string& id) const;
	const bool isSoundsExisting() const;

	Sound2d& getSound(const string& id);
	vector<Sound2d>& getSounds();

private:
	const int _findSoundIndex(const string& id) const;

	vector<Sound2d> _sounds;

	shared_ptr<AudioLoader> _audioLoader = nullptr;
};