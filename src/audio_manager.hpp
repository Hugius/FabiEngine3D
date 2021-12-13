#pragma once

#include "music.hpp"
#include "sound2d.hpp"
#include "sound3d.hpp"
#include "audio_loader.hpp"

class AudioManager final
{
public:
	AudioManager(AudioLoader& audioLoader);

	// VOID
	void update();
	void createMusic(const string& audioPath);
	void createSound2d(const string& ID, const string& audioPath);
	void createSound3d(const string& ID, const string& audioPath);
	void deleteMusic();
	void deleteAllSound2d();
	void deleteAllSound3d();
	void deleteSound2d(const string& ID);
	void deleteSound3d(const string& ID);

	// BOOL
	const bool isSound2dExisting(const string& ID) const;
	const bool isSound3dExisting(const string& ID) const;

	// MISCELLANEOUS
	vector<Music>& getAllMusic();
	vector<Sound2d>& getAllSound2d();
	vector<Sound3d>& getAllSound3d();
	Sound2d& getSound2d(const string& ID);
	Sound3d& getSound3d(const string& ID);

private:
	// INT
	const int _findSound2dIndex(const string& ID) const;
	const int _findSound3dIndex(const string& ID) const;

	// MISCELLANEOUS
	vector<Music> _musicList;
	vector<Sound2d> _sound2dList;
	vector<Sound3d> _sound3dList;
	AudioLoader& _audioLoader;
};