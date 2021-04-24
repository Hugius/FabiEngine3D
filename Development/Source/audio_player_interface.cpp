#include "audio_player.hpp"
#include "logger.hpp"
#include "tools.hpp"

void AudioPlayer::playSound(Sound& sound, int loops, int fadeMS, bool forcePlay)
{
	if (_isSoundsEnabled)
	{
		if (!isSoundStarted(sound) || forcePlay)
		{
			// Try to find free channel
			auto channel = _getFreeChannel();
			if (channel != -1)
			{
				_channels[channel] = sound.getID();

				// Play or fade
				if (fadeMS == 0)
				{
					Mix_PlayChannel(channel, sound.getDataPointer(), loops);
				}
				else
				{
					Mix_FadeInChannel(channel, sound.getDataPointer(), loops, fadeMS);
				}

				// Set volume
				_updateSoundVolume(sound);
			}
			else
			{
				Logger::throwWarning("Trying to play sound with ID \"", sound.getID(), "\": no audio channels available!");
			}
		}
		else
		{
			Logger::throwWarning("Trying to play sound with ID \"", sound.getID(), "\": sound is already started!");
		}
	}
}

void AudioPlayer::playMusic(vector<Music>& musicList, bool forcePlay)
{
	if (_isMusicEnabled)
	{
		// Check if any music is existing
		if (!musicList.empty())
		{
			// Check if music is allowed to play
			if (!isMusicStarted() || forcePlay)
			{
				// Select next song
				unsigned int musicIndex;
				if (musicList.size() == 1)
				{
					musicIndex = 0;
				}
				else
				{
					musicIndex = Tools::getInst().getRandomInt(0, musicList.size() - 1);
				}

				// Play music
				Mix_PlayMusic(musicList[musicIndex].getDataPointer(), 0);

				// Set volume
				_updateMusicVolume();
			}
		}
	}
}

void AudioPlayer::pauseAllSounds()
{
	if (_isSoundsEnabled)
	{
		Mix_Pause(-1);
	}
}

void AudioPlayer::pauseSound(Sound& sound)
{
	if (_isSoundsEnabled)
	{
		if (isSoundPlaying(sound))
		{
			if (!isSoundPaused(sound))
			{
				// For every sound playback
				for (auto& channel : _findSoundChannels(sound))
				{
					Mix_Pause(channel);
				}
			}
			else
			{
				Logger::throwWarning("Trying to pause sound with ID \"", sound.getID(), "\": sound is already paused!");
			}
		}
		else
		{
			Logger::throwWarning("Trying to pause sound with ID \"", sound.getID(), "\": sound is not playing!");
		}
	}
}

void AudioPlayer::pauseMusic()
{
	if (_isMusicEnabled)
	{
		if (isMusicPlaying())
		{
			if (!isMusicPaused())
			{
				Mix_PauseMusic();
			}
			else
			{
				Logger::throwWarning("Trying to pause music playlist: music is already paused!");
			}
		}
		else
		{
			Logger::throwWarning("Trying to pause music playlist: music is not playing!");
		}
	}
}

void AudioPlayer::resumeAllSounds()
{
	if (_isSoundsEnabled)
	{
		Mix_Resume(-1);
	}
}

void AudioPlayer::resumeSound(Sound& sound)
{
	if (_isSoundsEnabled)
	{
		if (isSoundStarted(sound) && isSoundPaused(sound))
		{
			// For every sound playback
			for (auto& channel : _findSoundChannels(sound))
			{
				Mix_Resume(channel);
			}
		}
		else
		{
			Logger::throwWarning("Trying to resume sound with ID \"", sound.getID(), "\": sound is not paused!");
		}
	}
}

void AudioPlayer::resumeMusic()
{
	if (_isMusicEnabled)
	{
		if (isMusicStarted() && isMusicPaused())
		{
			Mix_ResumeMusic();
		}
		else
		{
			Logger::throwWarning("Trying to resume music playlist: music is not paused!");
		}
	}
}

void AudioPlayer::stopAllSounds()
{
	if (_isSoundsEnabled)
	{
		// Resume before stopping
		resumeAllSounds();

		// Stop sounds
		Mix_HaltChannel(-1);
	}
}

void AudioPlayer::stopSound(Sound& sound, int fadeMS)
{
	if (_isSoundsEnabled)
	{
		if (isSoundStarted(sound))
		{
			// Resume before stopping
			if (isSoundPaused(sound))
			{
				resumeSound(sound);
			}

			// Stop or fade
			if (fadeMS == 0)
			{
				// For every sound playback
				for (auto& channel : _findSoundChannels(sound))
				{
					Mix_HaltChannel(channel);
				}
			}
			else
			{
				// For every sound playback
				for (auto& channel : _findSoundChannels(sound))
				{
					Mix_FadeOutChannel(channel, fadeMS);
				}
			}

			// De-allocate channels
			for (auto& channel : _findSoundChannels(sound))
			{
				_channels[channel] = "";
			}
		}
		else
		{
			Logger::throwWarning("Trying to stop sound with ID \"", sound.getID(), "\": sound is not playing!");
		}
	}
}

void AudioPlayer::stopMusic(bool forceStop)
{
	if (_isMusicEnabled)
	{
		// Resume before stopping
		if (isMusicPaused())
		{
			resumeMusic();
		}

		// Check if music is playing
		if (isMusicPlaying() || forceStop)
		{
			Mix_HaltMusic();
		}
		else
		{
			Logger::throwWarning("Trying to stop music playlist: music is not playing!");
		}
	}
}

void AudioPlayer::setMusicVolume(float volume)
{
	if (_isMusicEnabled)
	{
		_musicVolume = std::clamp(volume, 0.0f, 1.0f);
	}
}

float AudioPlayer::getMusicVolume()
{
	if (_isMusicEnabled)
	{
		return static_cast<float>(Mix_VolumeMusic(-1)) / 128.0f;
	}

	return -1.0f;
}

bool AudioPlayer::isSoundStarted(Sound& sound)
{
	if (_isSoundsEnabled)
	{
		for (auto& soundID : _channels)
		{
			if (soundID == sound.getID())
			{
				return true;
			}
		}
	}

	return false;
}

bool AudioPlayer::isSoundPlaying(Sound& sound)
{
	if (_isSoundsEnabled)
	{
		return (isSoundStarted(sound) && !isSoundPaused(sound));
	}

	return false;
}

bool AudioPlayer::isSoundPaused(Sound& sound)
{
	if (_isSoundsEnabled)
	{

		return (isSoundStarted(sound) && Mix_Paused(_findSoundChannels(sound).front()));
	}

	return false;
}

bool AudioPlayer::isMusicStarted()
{
	if (_isMusicEnabled)
	{
		return Mix_PlayingMusic();
	}

	return false;
}

bool AudioPlayer::isMusicPlaying()
{
	if (_isMusicEnabled)
	{
		return (isMusicStarted() && !isMusicPaused());
	}

	return false;
}

bool AudioPlayer::isMusicPaused()
{
	if (_isMusicEnabled)
	{
		return (isMusicStarted() && Mix_PausedMusic());
	}

	return false;
}