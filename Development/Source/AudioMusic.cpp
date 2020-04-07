#include <WE3D/AudioMusic.hpp>

AudioMusic::AudioMusic(Mix_Music* music) :
	p_music(music)
{
	
}

Mix_Music* AudioMusic::getMixMusic() const
{
	return p_music;
}
