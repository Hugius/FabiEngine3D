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
	void createSound(const string& ID, const string& audioPath);
	void deleteSound(const string& ID);
	void deleteSounds();

	const bool isSoundExisting(const string& ID) const;

	Sound2d& getSound(const string& ID);
	vector<Sound2d>& getSounds();

private:
	const int _findSoundIndex(const string& ID) const;

	vector<Sound2d> _sounds;

	shared_ptr<AudioLoader> _audioLoader = nullptr;
};