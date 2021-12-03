#pragma once

#include <SDL\\SDL_mixer.h>

#include <string>

using std::string;

class Music final
{
public:
	Music(const string& audioPath, Mix_Music* dataPointer);

	// STRING
	const string& getAudioPath() const;

	// MISCELLANEOUS
	Mix_Music* getDataPointer() const;

private:
	// STRING
	string _audioPath = "";

	// MISCELLANEOUS
	Mix_Music* _dataPointer = nullptr;
};