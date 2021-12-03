#include "music.hpp"

Music::Music(const string& audioPath, Mix_Music* dataPointer)
	:
	_audioPath(audioPath),
	_dataPointer(dataPointer)
{

}

const string& Music::getAudioPath() const
{
	return _audioPath;
}

Mix_Music* Music::getDataPointer() const
{
	return _dataPointer;
}