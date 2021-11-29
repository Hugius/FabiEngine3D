#include "audio_player.hpp"
#include "logger.hpp"

using std::clamp;

void AudioPlayer::playMusic(vector<Music>& musicList, bool mustForcePlay)
{
	// Check if music is playing
	if(isMusicStarted() && !mustForcePlay)
	{
		Logger::throwError("AudioPlayer::playMusic::1");
	}

	// Check if music is not defined
	if(musicList.empty())
	{
		Logger::throwError("AudioPlayer::playMusic::2");
	}

	// Select next music
	unsigned int musicIndex;
	if(musicList.size() == 1)
	{
		musicIndex = 0;
	}
	else
	{
		musicIndex = Math::getRandomInteger(0, static_cast<int>(musicList.size() - 1));
	}

	// Play music
	Mix_PlayMusic(musicList[musicIndex].getDataPointer(), 0);

	// Update volume
	_updateMusicVolume();
}

void AudioPlayer::_updateMusicVolume()
{
	if(isMusicStarted())
	{
		Mix_VolumeMusic(static_cast<int>(_musicVolume * 128.0f));
	}
}

void AudioPlayer::setMusicVolume(float volume)
{
	_musicVolume = clamp(volume, 0.0f, 1.0f);
}

const float AudioPlayer::getMusicVolume() const
{
	return static_cast<float>(Mix_VolumeMusic(-1)) / 128.0f;
}

const bool AudioPlayer::isMusicStarted() const
{
	return Mix_PlayingMusic();
}

const bool AudioPlayer::isMusicPlaying() const
{
	return (isMusicStarted() && !isMusicPaused());
}

const bool AudioPlayer::isMusicPaused() const
{
	return Mix_PausedMusic();
}

void AudioPlayer::pauseMusic()
{
	// Check if music is not playing
	if(!isMusicPlaying())
	{
		Logger::throwError("AudioPlayer::pauseMusic::1");
	}

	// Check if music is paused
	if(isMusicPaused())
	{
		Logger::throwError("AudioPlayer::pauseMusic::2");
	}

	// Pause music
	Mix_PauseMusic();
}

void AudioPlayer::resumeMusic()
{
	// Check if music is not started
	if(!isMusicStarted())
	{
		Logger::throwError("AudioPlayer::resumeMusic::1");
	}

	// Check if music is not paused
	if(!isMusicPaused())
	{
		Logger::throwError("AudioPlayer::resumeMusic::2");
	}

	// Resume music
	Mix_ResumeMusic();
}

void AudioPlayer::stopMusic()
{
	// Resume before stopping
	if(isMusicPaused())
	{
		resumeMusic();
	}

	// Check if music is not started
	if(!isMusicStarted())
	{
		Logger::throwError("AudioPlayer::stopMusic");
	}

	// Stop music
	Mix_HaltMusic();
}