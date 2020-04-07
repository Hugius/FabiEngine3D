#include <WE3D/AudioChunk.hpp>

AudioChunk::AudioChunk(const std::string& ID, Mix_Chunk* chunk) :
	p_ID(ID),
	p_chunk(chunk)
{

}

AudioChunk::AudioChunk(const std::string& ID, Mix_Chunk* chunk, vec3 position, float maxDistance) :
	p_ID(ID),
	p_chunk(chunk),
	p_position(position),
	p_maxDistance(maxDistance),
	p_hasPosition(true)
{

}

const std::string& AudioChunk::getID() const
{
	return p_ID;
}

Mix_Chunk* AudioChunk::getMixChunk() const
{
	return p_chunk;
}

void AudioChunk::setPosition(vec3 position)
{
	p_position = position;
}

vec3 AudioChunk::getPosition() const
{
	return p_position;
}

float AudioChunk::getMaxDistance() const
{
	return p_maxDistance;
}

bool AudioChunk::hasPosition() const
{
	return p_hasPosition;
}