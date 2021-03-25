#pragma once

#include "mathematics.hpp"

#include <string>
#include <SDL\\SDL_mixer.h>

using std::string;

class AudioChunk final
{
public:
	AudioChunk(const string& ID, const string& filePath, Mix_Chunk* chunk);
	AudioChunk(const string& ID, const string& filePath, Mix_Chunk* chunk, Vec3 position, float maxVolume, float maxDistance);

	void setPosition(Vec3 value);
	void translate(Vec3 value);
	void setMaxDistance(float value);
	void setMaxVolume(float value);

	const string& getID() const;
	const string& getFilePath() const;

	Mix_Chunk* getMixChunk() const;

	Vec3 getPosition() const;

	float getMaxDistance() const;
	float getMaxVolume() const;

	bool is3D() const;

private:
	string _ID = "";
	string _filePath = "";
	
	Mix_Chunk* _chunk = nullptr;

	Vec3 _position = Vec3(0.0f);

	float _maxDistance = 0.0f;
	float _maxVolume = 1.0f;

	bool _is3D = false;
};