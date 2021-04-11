#pragma once

#include <SDL\\SDL_mixer.h>

class Music final
{
public:
	Music(Mix_Music* dataPointer);

	Mix_Music* getDataPointer() const;

private:
	Mix_Music* _dataPointer = nullptr;
};