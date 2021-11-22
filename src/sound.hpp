#pragma once

#include "mathematics.hpp"

#include <string>
#include <SDL\\SDL_mixer.h>

using std::string;

class Sound final
{
public:
	Sound(const string& ID, const string& filePath, Mix_Chunk* dataPointer);

	// VOID
	void make3D(fvec3 position, float maxVolume, float maxDistance);
	void setPosition(fvec3 value);
	void move(fvec3 value);
	void setVolume(float value);
	void setMaxVolume(float value);
	void setMaxDistance(float value);

	// STRING
	const string& getID() const;
	const string& getFilePath() const;

	// FVEC3
	const fvec3 getPosition() const;

	// FLOAT
	const float getVolume() const;
	const float getMaxVolume() const;
	const float getMaxDistance() const;

	// BOOL
	const bool is3D() const;

	// Miscellaneous
	Mix_Chunk* getDataPointer() const;

private:
	// STRING
	string _ID = "";
	string _filePath = "";

	// FVEC3
	fvec3 _position = fvec3(0.0f);

	// FLOAT
	float _volume = 1.0f;
	float _maxVolume = 0.0f;
	float _maxDistance = 0.0f;

	// BOOL
	bool _is3D = false;

	// Miscellaneous
	Mix_Chunk* _dataPointer = nullptr;
};