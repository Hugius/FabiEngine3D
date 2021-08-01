#pragma once

#include "sound.hpp"
#include "music.hpp"
#include "audio_loader.hpp"

class AudioManager final
{
public:
	AudioManager(AudioLoader& audioLoader);

	void addMusic(const string& fileName);
	void addSound(const string& ID, const string& fileName);
	void deleteMusic();
	void deleteSound(const string& ID);
	void deleteAllSounds();

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