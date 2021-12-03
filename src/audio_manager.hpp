#pragma once

#include "music.hpp"
#include "sound_2d.hpp"
#include "sound_3d.hpp"
#include "audio_loader.hpp"

class AudioManager final
{
public:
	AudioManager(AudioLoader& audioLoader);

	// VOID
	void update();
	void createMusic(const string& audioPath);
	void createSound2D(const string& ID, const string& audioPath);
	void createSound3D(const string& ID, const string& audioPath);
	void deleteMusic();
	void deleteSounds2D();
	void deleteSounds3D();
	void deleteSound2D(const string& ID);
	void deleteSound3D(const string& ID);

	// BOOL
	const bool isSoundExisting2D(const string& ID) const;
	const bool isSoundExisting3D(const string& ID) const;

	// MISCELLANEOUS
	vector<Music>& getMusics();
	vector<Sound2D>& getSounds2D();
	vector<Sound3D>& getSounds3D();
	Sound2D& getSound2D(const string& ID);
	Sound3D& getSound3D(const string& ID);

private:
	// INT
	const int _findSoundIndex2D(const string& ID) const;
	const int _findSoundIndex3D(const string& ID) const;

	// MISCELLANEOUS
	vector<Music> _musics;
	vector<Sound2D> _sounds2D;
	vector<Sound3D> _sounds3D;
	AudioLoader& _audioLoader;
};