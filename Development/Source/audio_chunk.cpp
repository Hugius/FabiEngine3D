#include "audio_chunk.hpp"

AudioChunk::AudioChunk(const std::string& ID, Mix_Chunk* chunk) :
	_ID(ID),
	_chunk(chunk)
{

}

AudioChunk::AudioChunk(const std::string& ID, Mix_Chunk* chunk, vec3 position, float maxDistance) :
	_ID(ID),
	_chunk(chunk),
	_position(position),
	_maxDistance(maxDistance),
	_hasPosition(true)
{

}

const std::string& AudioChunk::getID() const
{
	return _ID;
}

Mix_Chunk* AudioChunk::getMixChunk() const
{
	return _chunk;
}

void AudioChunk::setPosition(vec3 position)
{
	_position = position;
}

vec3 AudioChunk::getPosition() const
{
	return _position;
}

float AudioChunk::getMaxDistance() const
{
	return _maxDistance;
}

bool AudioChunk::hasPosition() const
{
	return _hasPosition;
}