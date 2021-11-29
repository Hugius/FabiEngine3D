#include "audio_player.hpp"
#include "logger.hpp"

using std::clamp;

void AudioPlayer::_updateMusicVolume()
{
	Mix_VolumeMusic(static_cast<int>(_musicVolume * 128.0f));
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

void AudioPlayer::playMusic(vector<Music>& musicList, bool mustForcePlay)
{
	// Check if any music is existing
	if(!musicList.empty())
	{
		// Check if music is allowed to play
		if(!isMusicStarted() || mustForcePlay)
		{
			// Select next song
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

			// Set volume
			_updateMusicVolume();
		}
	}
}

void AudioPlayer::pauseMusic()
{
	if(isMusicPlaying())
	{
		if(!isMusicPaused())
		{
			Mix_PauseMusic();
		}
		else
		{
			Logger::throwError("AudioPlayer::pauseMusic::1");
		}
	}
	else
	{
		Logger::throwError("AudioPlayer::pauseMusic::2");
	}
}

void AudioPlayer::resumeMusic()
{
	if(isMusicStarted() && isMusicPaused())
	{
		Mix_ResumeMusic();
	}
	else
	{
		Logger::throwError("AudioPlayer::resumeMusic");
	}
}

void AudioPlayer::stopMusic()
{
	// Resume before stopping
	if(isMusicPaused())
	{
		resumeMusic();
	}

	// Check if music is started
	if(isMusicStarted())
	{
		Mix_HaltMusic();
	}
	else
	{
		Logger::throwError("AudioPlayer::stopMusic");
	}
}