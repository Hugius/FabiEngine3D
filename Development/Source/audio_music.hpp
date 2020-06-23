#pragma once

#include <SDL\\SDL_mixer.h>

class AudioMusic final
{
public:
	AudioMusic(Mix_Music* music);

	Mix_Music* getMixMusic() const;

private:
	Mix_Music* _music = nullptr;
};