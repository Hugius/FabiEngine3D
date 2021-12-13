#include "sound2d.hpp"

#include <algorithm>

using std::clamp;

Sound2d::Sound2d(const string& ID, const string& audioPath, Mix_Chunk* dataPointer)
	:
	_ID(ID),
	_audioPath(audioPath),
	_dataPointer(dataPointer)
{

}

const string& Sound2d::getID() const
{
	return _ID;
}

const string& Sound2d::getAudioPath() const
{
	return _audioPath;
}

Mix_Chunk* Sound2d::getDataPointer() const
{
	return _dataPointer;
}

void Sound2d::setVolume(float value)
{
	_volume = clamp(value, 0.0f, 1.0f);
}

const float Sound2d::getVolume() const
{
	return _volume;
}