#pragma once

#include "sound.hpp"
#include "music.hpp"
#include "audio_loader.hpp"

class AudioManager final
{
public:
	AudioManager(AudioLoader& audioLoader);

	// VOID
	void createSound(const string& ID, const string& fileName);
	void createMusic(const string& fileName);
	void deleteSound(const string& ID);
	void deleteAllSounds();
	void deleteAllMusic();

	// BOOL
	const bool isSoundExisting(const string& ID) const;

	// MISCELLANEOUS
	vector<Sound>& getSounds();
	vector<Music>& getMusic();
	Sound& getSound(const string& ID);

private:
	// INT
	const int _findIndex(const string& ID) const;

	// MISCELLANEOUS
	vector<Sound> _soundList;
	vector<Music> _musicList;
	AudioLoader& _audioLoader;
};