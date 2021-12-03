#pragma once

#include <string>
#include <SDL\\SDL_mixer.h>

using std::string;

class Sound2D
{
public:
	Sound2D(const string& ID, const string& audioPath, Mix_Chunk* dataPointer);

	// VOID
	void setVolume(float value);

	// STRING
	const string& getID() const;
	const string& getAudioPath() const;

	// FLOAT
	const float getVolume() const;

	// MISCELLANEOUS
	Mix_Chunk* getDataPointer() const;

private:
	// STRING
	string _ID = "";
	string _audioPath = "";

	// FLOAT
	float _volume = 1.0f;

	// MISCELLANEOUS
	Mix_Chunk* _dataPointer = nullptr;
};