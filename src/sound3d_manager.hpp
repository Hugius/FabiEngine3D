#pragma once

#include "sound3d.hpp"
#include "audio_loader.hpp"

class Sound3dManager final
{
public:
	Sound3dManager(AudioLoader& audioLoader);

	// VOID
	void update();
	void createSound(const string& ID, const string& audioPath);
	void deleteSound(const string& ID);
	void deleteSounds();

	// BOOL
	const bool isSoundExisting(const string& ID) const;

	// MISCELLANEOUS
	Sound3d& getSound(const string& ID);
	vector<Sound3d>& getSounds();

private:
	// INT
	const int _findSoundIndex(const string& ID) const;

	// MISCELLANEOUS
	vector<Sound3d> _sounds;
	AudioLoader& _audioLoader;
};