#include "audio_player.hpp"
#include "logger.hpp"

void AudioPlayer::playSound3D(Sound3D& sound, int loops, unsigned int fadeMS, bool mustForcePlay)
{
	if(!isSoundStarted3D(sound) || mustForcePlay)
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
			_updateSoundVolume3D(sound);
		}
		else
		{
			Logger::throwError("AudioPlayer::playSound3D::1");
		}
	}
	else
	{
		Logger::throwError("AudioPlayer::playSound3D::2");
	}
}

void AudioPlayer::pauseAllSounds3D(vector<Sound3D>& soundList)
{
	for(const auto& sound : soundList)
	{
		for(size_t i = 0; i < _channels.size(); i++)
		{
			if(_channels[i] == sound.getID())
			{
				Mix_Pause(static_cast<int>(i));
			}
		}
	}
}

void AudioPlayer::pauseSound3D(Sound3D& sound)
{
	if(isSoundPlaying3D(sound))
	{
		if(!isSoundPaused3D(sound))
		{
			for(const auto& channel : _findSoundChannels3D(sound))
			{
				Mix_Pause(channel);
			}
		}
		else
		{
			Logger::throwError("AudioPlayer::pauseSound3D::1");
		}
	}
	else
	{
		Logger::throwError("AudioPlayer::pauseSound3D::2");
	}
}

void AudioPlayer::resumeAllSounds3D(vector<Sound3D>& soundList)
{
	for(const auto& sound : soundList)
	{
		for(size_t i = 0; i < _channels.size(); i++)
		{
			if(_channels[i] == sound.getID())
			{
				Mix_Resume(static_cast<int>(i));
			}
		}
	}
}

void AudioPlayer::resumeSound3D(Sound3D& sound)
{
	if(isSoundPaused3D(sound))
	{
		for(const auto& channel : _findSoundChannels3D(sound))
		{
			Mix_Resume(channel);
		}
	}
	else
	{
		Logger::throwError("AudioPlayer::resumeSound3D");
	}
}

void AudioPlayer::stopAllSounds3D(vector<Sound3D>& soundList)
{
	// Resume before stopping
	resumeAllSounds3D(soundList);

	// Stop sounds
	for(const auto& sound : soundList)
	{
		for(size_t i = 0; i < _channels.size(); i++)
		{
			if(_channels[i] == sound.getID())
			{
				Mix_HaltChannel(static_cast<int>(i));
			}
		}
	}
}

void AudioPlayer::stopSound3D(Sound3D& sound, unsigned int fadeMS)
{
	if(isSoundStarted3D(sound))
	{
		// Resume before stopping
		if(isSoundPaused3D(sound))
		{
			resumeSound3D(sound);
		}

		// Stop or fade
		if(fadeMS == 0)
		{
			// For every sound playback
			for(const auto& channel : _findSoundChannels3D(sound))
			{
				Mix_HaltChannel(channel);
			}
		}
		else
		{
			// For every sound playback
			for(const auto& channel : _findSoundChannels3D(sound))
			{
				Mix_FadeOutChannel(channel, fadeMS);
			}
		}

		// De-allocate channels
		for(const auto& channel : _findSoundChannels3D(sound))
		{
			_channels[channel] = "";
		}
	}
	else
	{
		Logger::throwError("AudioPlayer::stopSound3D");
	}
}

const bool AudioPlayer::isSoundStarted3D(Sound3D& sound) const
{
	for(const auto& soundID : _channels)
	{
		if(soundID == sound.getID())
		{
			return true;
		}
	}

	return false;
}

const bool AudioPlayer::isSoundPlaying3D(Sound3D& sound) const
{
	return (isSoundStarted3D(sound) && !isSoundPaused3D(sound));
}

const bool AudioPlayer::isSoundPaused3D(Sound3D& sound) const
{
	return (isSoundStarted3D(sound) && Mix_Paused(_findSoundChannels3D(sound).front()));
}

void AudioPlayer::_updateSoundVolume3D(Sound3D& sound)
{
	if(isSoundStarted3D(sound))
	{
		auto intVolume = static_cast<int>(sound.getVolume() * 128.0f);

		// For every sound playback
		for(const auto& channel : _findSoundChannels3D(sound))
		{
			Mix_Volume(channel, intVolume);
		}
	}
}

const vector<int> AudioPlayer::_findSoundChannels3D(Sound3D& sound) const
{
	vector<int> channels;

	for(size_t i = 0; i < _channels.size(); i++)
	{
		if(_channels[i] == sound.getID())
		{
			channels.push_back(static_cast<int>(i));
		}
	}

	// Find must never fail
	if(channels.empty())
	{
		Logger::throwError("AudioPlayer::_findSoundChannels3D");
	}

	return channels;
}