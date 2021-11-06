#include "audio_player.hpp"
#include "logger.hpp"
#include "tools.hpp"

using std::clamp;

void AudioPlayer::playSound(Sound& sound, int loops, int fadeMS, bool forcePlay)
{
	if(_isSoundsEnabled)
	{
		if(!isSoundStarted(sound) || forcePlay)
		{
			// Try to find free channel
			auto channel = _getFreeChannel();
			if(channel != -1)
			{
				_channels[channel] = sound.getID();

				// Play or fade
				if(fadeMS == 0)
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
				Logger::throwError("AudioPlayer::playSound::1");
			}
		}
		else
		{
			Logger::throwError("AudioPlayer::playSound::2");
		}
	}
}

void AudioPlayer::playMusic(vector<Music>& musicList, bool forcePlay)
{
	if(_isMusicEnabled)
	{
		// Check if any music is existing
		if(!musicList.empty())
		{
			// Check if music is allowed to play
			if(!isMusicStarted() || forcePlay)
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
}

void AudioPlayer::pauseAllSounds()
{
	if(_isSoundsEnabled)
	{
		Mix_Pause(-1);
	}
}

void AudioPlayer::pauseSound(Sound& sound)
{
	if(_isSoundsEnabled)
	{
		if(isSoundPlaying(sound))
		{
			if(!isSoundPaused(sound))
			{
				for(const auto& channel : _findSoundChannels(sound))
				{
					Mix_Pause(channel);
				}
			}
			else
			{
				Logger::throwError("AudioPlayer::pauseSound::1");
			}
		}
		else
		{
			Logger::throwError("AudioPlayer::pauseSound::2");
		}
	}
}

void AudioPlayer::pauseMusic()
{
	if(_isMusicEnabled)
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
}

void AudioPlayer::resumeAllSounds()
{
	if(_isSoundsEnabled)
	{
		Mix_Resume(-1);
	}
}

void AudioPlayer::resumeSound(Sound& sound)
{
	if(_isSoundsEnabled)
	{
		if(isSoundPaused(sound))
		{
			for(const auto& channel : _findSoundChannels(sound))
			{
				Mix_Resume(channel);
			}
		}
		else
		{
			Logger::throwError("AudioPlayer::resumeSound");
		}
	}
}

void AudioPlayer::resumeMusic()
{
	if(_isMusicEnabled)
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
}

void AudioPlayer::stopAllSounds()
{
	if(_isSoundsEnabled)
	{
		// Resume before stopping
		resumeAllSounds();

		// Stop sounds
		Mix_HaltChannel(-1);
	}
}

void AudioPlayer::stopSound(Sound& sound, int fadeMS)
{
	if(_isSoundsEnabled)
	{
		if(isSoundStarted(sound))
		{
			// Resume before stopping
			if(isSoundPaused(sound))
			{
				resumeSound(sound);
			}

			// Stop or fade
			if(fadeMS == 0)
			{
				// For every sound playback
				for(const auto& channel : _findSoundChannels(sound))
				{
					Mix_HaltChannel(channel);
				}
			}
			else
			{
				// For every sound playback
				for(const auto& channel : _findSoundChannels(sound))
				{
					Mix_FadeOutChannel(channel, fadeMS);
				}
			}

			// De-allocate channels
			for(const auto& channel : _findSoundChannels(sound))
			{
				_channels[channel] = "";
			}
		}
		else
		{
			Logger::throwError("AudioPlayer::stopSound");
		}
	}
}

void AudioPlayer::stopMusic()
{
	if(_isMusicEnabled)
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
}

void AudioPlayer::setMusicVolume(float volume)
{
	if(_isMusicEnabled)
	{
		_musicVolume = clamp(volume, 0.0f, 1.0f);
	}
}

const float AudioPlayer::getMusicVolume() const
{
	if(_isMusicEnabled)
	{
		return static_cast<float>(Mix_VolumeMusic(-1)) / 128.0f;
	}

	return -1.0f;
}

const bool AudioPlayer::isChannelAvailable() const
{
	for(size_t i = 0; i < _channels.size(); i++)
	{
		if(_channels[i].empty())
		{
			return true;
		}
	}

	return false;
}

const bool AudioPlayer::isSoundsEnabled() const
{
	return _isSoundsEnabled;
}

const bool AudioPlayer::isSoundStarted(Sound& sound) const
{
	if(_isSoundsEnabled)
	{
		for(const auto& soundID : _channels)
		{
			if(soundID == sound.getID())
			{
				return true;
			}
		}
	}

	return false;
}

const bool AudioPlayer::isSoundPlaying(Sound& sound) const
{
	if(_isSoundsEnabled)
	{
		return (isSoundStarted(sound) && !isSoundPaused(sound));
	}

	return false;
}

const bool AudioPlayer::isSoundPaused(Sound& sound) const
{
	if(_isSoundsEnabled)
	{
		return (isSoundStarted(sound) && Mix_Paused(_findSoundChannels(sound).front()));
	}

	return false;
}

const bool AudioPlayer::isMusicEnabled() const
{
	return _isMusicEnabled;
}

const bool AudioPlayer::isMusicStarted() const
{
	if(_isMusicEnabled)
	{
		return Mix_PlayingMusic();
	}

	return false;
}

const bool AudioPlayer::isMusicPlaying() const
{
	if(_isMusicEnabled)
	{
		return (isMusicStarted() && !isMusicPaused());
	}

	return false;
}

const bool AudioPlayer::isMusicPaused() const
{
	if(_isMusicEnabled)
	{
		return Mix_PausedMusic();
	}

	return false;
}