#pragma once

#include "mathematics.hpp"

#include <string>
#include <SDL\\SDL_mixer.h>

using std::string;

class Sound final
{
public:
	Sound(const string& ID, const string& filePath, Mix_Chunk* dataPointer);

	void make3D(Vec3 position, float maxVolume, float maxDistance);
	void setPosition(Vec3 value);
	void translate(Vec3 value);
	void setVolume(float value);
	void setMaxVolume(float value);
	void setMaxDistance(float value);

	const string& getID() const;
	const string& getFilePath() const;

	Mix_Chunk* getDataPointer() const;

	Vec3 getPosition() const;

	float getVolume() const;
	float getMaxVolume() const;
	float getMaxDistance() const;

	bool is3D() const;

private:
	string _ID = "";
	string _filePath = "";
	
	Mix_Chunk* _dataPointer = nullptr;

	Vec3 _position = Vec3(0.0f);

	float _volume = 1.0f;
	float _maxVolume = 0.0f;
	float _maxDistance = 0.0f;

	bool _is3D = false;
};