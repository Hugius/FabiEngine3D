#include "audio_chunk.hpp"

AudioChunk::AudioChunk(const string& ID, const string& filePath, Mix_Chunk* chunk) :
	_ID(ID),
	_filePath(filePath),
	_chunk(chunk)
{

}

AudioChunk::AudioChunk(const string& ID, const string& filePath, Mix_Chunk* chunk, Vec3 position, float maxVolume, float maxDistance) :
	_ID(ID),
	_filePath(filePath),
	_chunk(chunk),
	_position(position),
	_maxVolume(maxVolume),
	_maxDistance(maxDistance),
	_hasPosition(true)
{

}

const std::string& AudioChunk::getID() const
{
	return _ID;
}

const string& AudioChunk::getFilePath() const
{
	return _filePath;
}

Mix_Chunk* AudioChunk::getMixChunk() const
{
	return _chunk;
}

void AudioChunk::setPosition(Vec3 value)
{
	_position = value;
	_hasPosition = true;
}

void AudioChunk::translate(Vec3 value)
{
	_position += value;
}

void AudioChunk::setMaxDistance(float value)
{
	_maxDistance = value;
}

void AudioChunk::setMaxVolume(float value)
{
	_maxVolume = value;
}

Vec3 AudioChunk::getPosition() const
{
	return _position;
}

float AudioChunk::getMaxDistance() const
{
	return _maxDistance;
}

float AudioChunk::getMaxVolume() const
{
	return _maxVolume;
}

bool AudioChunk::is3D() const
{
	return _hasPosition;
}