#pragma once

#include <string>
#include <SDL\\SDL_mixer.h>
#include <GLM\\glm.hpp>

using glm::vec3;
using std::string;

class AudioChunk final
{
public:
	AudioChunk(const string& ID, const string& filePath, Mix_Chunk* chunk);
	AudioChunk(const string& ID, const string& filePath, Mix_Chunk* chunk, vec3 position, float maxDistance);

	const string& getID() const;
	const string& getFilePath() const;

	Mix_Chunk* getMixChunk() const;

	void setPosition(vec3 position);

	vec3 getPosition() const;

	float getMaxDistance() const;

	bool hasPosition() const;

private:
	string _ID = "";
	string _filePath = "";
	
	Mix_Chunk* _chunk = nullptr;

	vec3 _position = vec3(0.0f);

	float _maxDistance = 0.0f;

	bool _hasPosition = false;
};