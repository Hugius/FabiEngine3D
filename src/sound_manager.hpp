#pragma once

#include "sound2d.hpp"
#include "sound3d.hpp"
#include "audio_loader.hpp"

class SoundManager final
{
public:
	SoundManager(AudioLoader& audioLoader);

	// VOID
	void update();
	void createSound2d(const string& ID, const string& audioPath);
	void createSound3d(const string& ID, const string& audioPath);
	void deleteAllSound2d();
	void deleteAllSound3d();
	void deleteSound2d(const string& ID);
	void deleteSound3d(const string& ID);

	// BOOL
	const bool isSound2dExisting(const string& ID) const;
	const bool isSound3dExisting(const string& ID) const;

	// MISCELLANEOUS
	vector<Sound2d>& getAllSound2d();
	vector<Sound3d>& getAllSound3d();
	Sound2d& getSound2d(const string& ID);
	Sound3d& getSound3d(const string& ID);

private:
	// INT
	const int _findSound2dIndex(const string& ID) const;
	const int _findSound3dIndex(const string& ID) const;

	// MISCELLANEOUS
	vector<Sound2d> _sound2dList;
	vector<Sound3d> _sound3dList;
	AudioLoader& _audioLoader;
};