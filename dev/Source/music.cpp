#include "music.hpp"

Music::Music(Mix_Music* dataPointer)
	:
	_dataPointer(dataPointer)
{

}

Mix_Music* Music::getDataPointer() const
{
	return _dataPointer;
}