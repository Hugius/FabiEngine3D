#include "sound2d.hpp"

#include <algorithm>

using std::clamp;

Sound2D::Sound2D(const string& ID, const string& audioPath, Mix_Chunk* dataPointer)
	:
	_ID(ID),
	_audioPath(audioPath),
	_dataPointer(dataPointer)
{

}

const string& Sound2D::getID() const
{
	return _ID;
}

const string& Sound2D::getAudioPath() const
{
	return _audioPath;
}

Mix_Chunk* Sound2D::getDataPointer() const
{
	return _dataPointer;
}

void Sound2D::setVolume(float value)
{
	_volume = clamp(value, 0.0f, 1.0f);
}

const float Sound2D::getVolume() const
{
	return _volume;
}