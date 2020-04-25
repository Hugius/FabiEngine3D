#include "audio_music.hpp"

AudioMusic::AudioMusic(Mix_Music* music) :
	_music(music)
{
	
}

Mix_Music* AudioMusic::getMixMusic() const
{
	return _music;
}
