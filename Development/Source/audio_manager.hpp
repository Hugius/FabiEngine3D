#pragma once

#include "sound.hpp"
#include "music.hpp"
#include "audio_loader.hpp"

class AudioManager final
{
public:
	AudioManager(AudioLoader& audioLoader);

	void createSound(const string& ID, const string& filename);
	void createMusic(const string& filename);
	void deleteSound(const string& ID);
	void deleteAllSounds();
	void deleteMusic();

	bool isSoundExisting(const string& ID);

	Sound& getSound(const string& ID);

	vector<Sound>& getSounds();
	vector<Music>& getMusic();

private:
	vector<Sound> _soundList;
	vector<Music> _musicList;

	AudioLoader& _audioLoader;

	int _findIndex(const string& ID);
};