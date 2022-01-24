#pragma once

#include "sound3d.hpp"
#include "audio_loader.hpp"

#include <memory>

using std::shared_ptr;

class Sound3dManager final
{
public:
	void inject(shared_ptr<AudioLoader> audioLoader);
	void update();
	void createSound(const string& id, const string& audioPath);
	void deleteSound(const string& id);
	void deleteSounds();

	const bool isSoundExisting(const string& id) const;

	Sound3d& getSound(const string& id);
	vector<Sound3d>& getSounds();

private:
	const int _findSoundIndex(const string& id) const;

	vector<Sound3d> _sounds;

	shared_ptr<AudioLoader> _audioLoader = nullptr;
};