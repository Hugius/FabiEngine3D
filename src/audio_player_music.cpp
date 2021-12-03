#include "audio_player.hpp"
#include "logger.hpp"

using std::clamp;

void AudioPlayer::setMusicVolume(float volume)
{
	Mix_VolumeMusic(static_cast<int>(clamp(volume, 0.0f, 1.0f) * 128.0f));
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