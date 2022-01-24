#pragma once

#include <string>
#include <SDL_mixer.h>

using std::string;

class Sound2d
{
public:
	Sound2d(const string& id, const string& audioPath, Mix_Chunk* dataPointer);

	void setVolume(float value);

	const string& getId() const;
	const string& getAudioPath() const;

	const float getVolume() const;

	Mix_Chunk* getDataPointer() const;

private:
	string _ID = "";
	string _audioPath = "";

	float _volume = 1.0f;

	Mix_Chunk* _dataPointer = nullptr;
};