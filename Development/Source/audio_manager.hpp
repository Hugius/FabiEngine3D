#pragma once

#include "sound.hpp"
#include "music.hpp"
#include "audio_loader.hpp"

class AudioManager final
{
public:
	AudioManager(AudioLoader& audioLoader);

	// Voids
	void createSound(const string& ID, const string& filename);
	void createMusic(const string& filename);
	void deleteSound(const string& ID);
	void deleteAllSounds();
	void deleteAllMusic();

	// Booleans
	bool isSoundExisting(const string& ID);

	// Miscellaneous
	vector<Sound>& getSounds();
	vector<Music>& getMusic();
	Sound& getSound(const string& ID);

private:
	// Integers
	int _findIndex(const string& ID);

	// Miscellaneous
	vector<Sound> _soundList;
	vector<Music> _musicList;
	AudioLoader& _audioLoader;
};