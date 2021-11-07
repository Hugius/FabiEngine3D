#pragma once

#include <SDL\\SDL_mixer.h>

class Music final
{
public:
	Music(Mix_Music* dataPointer);

	// Miscellaneous
	Mix_Music* getDataPointer() const;

private:
	// Miscellaneous
	Mix_Music* _dataPointer = nullptr;
};