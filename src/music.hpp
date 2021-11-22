#pragma once

#include <SDL\\SDL_mixer.h>

class Music final
{
public:
	Music(Mix_Music* dataPointer);

	// MISCELLANEOUS
	Mix_Music* getDataPointer() const;

private:
	// MISCELLANEOUS
	Mix_Music* _dataPointer = nullptr;
};