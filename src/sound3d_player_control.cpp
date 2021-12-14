#include "sound3d_player.hpp"
#include "logger.hpp"

void Sound3dPlayer::playSound(Sound3d& sound, int loops, unsigned int fadeMS, bool mustForcePlay)
{
	// Check if sound is started
	if(isSoundStarted(sound) && !mustForcePlay)
	{
		Logger::throwError("Sound3dPlayer::playSound3d::1");
	}

	// Try to find free channel
	auto channel = _getFreeChannel();
	if(channel == -1)
	{
		Logger::throwError("Sound3dPlayer::playSound3d::2");
	}
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

	// Update volume
	_updateSoundVolume(sound);
}

void Sound3dPlayer::pauseSounds(vector<Sound3d>& sounds)
{
	for(const auto& sound : sounds)
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

void Sound3dPlayer::pauseSound(Sound3d& sound)
{
	// Check if sound is playing
	if(!isSoundPlaying(sound))
	{
		Logger::throwError("Sound3dPlayer::pauseSound3d::1");
	}

	// Check if sound paused
	if(isSoundPaused(sound))
	{
		Logger::throwError("Sound3dPlayer::pauseSound3d::2");
	}

	// Pause sound
	for(const auto& channel : _findChannels(sound))
	{
		Mix_Pause(channel);
	}
}

void Sound3dPlayer::resumeSounds(vector<Sound3d>& sounds)
{
	for(const auto& sound : sounds)
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

void Sound3dPlayer::resumeSound(Sound3d& sound)
{
	// Check if sound is not paused
	if(!isSoundPaused(sound))
	{
		Logger::throwError("Sound3dPlayer::resumeSound3d");
	}

	// Resume sound
	for(const auto& channel : _findChannels(sound))
	{
		Mix_Resume(channel);
	}
}

void Sound3dPlayer::stopSounds(vector<Sound3d>& sounds)
{
	// Resume before stopping
	resumeSounds(sounds);

	// Stop sounds
	for(const auto& sound : sounds)
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

void Sound3dPlayer::stopSound(Sound3d& sound, unsigned int fadeMS)
{
	// Check if sound is not started
	if(!isSoundStarted(sound))
	{
		Logger::throwError("Sound3dPlayer::stopSound3d");
	}

	// Resume before stopping
	if(isSoundPaused(sound))
	{
		resumeSound(sound);
	}

	// Stop or fade
	if(fadeMS == 0)
	{
		// Iterate through channels
		for(const auto& channel : _findChannels(sound))
		{
			Mix_HaltChannel(channel);
		}
	}
	else
	{
		// Iterate through channels
		for(const auto& channel : _findChannels(sound))
		{
			Mix_FadeOutChannel(channel, fadeMS);
		}
	}

	// De-allocate channels
	for(const auto& channel : _findChannels(sound))
	{
		_channels[channel] = "";
	}
}

const bool Sound3dPlayer::isSoundStarted(Sound3d& sound) const
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

const bool Sound3dPlayer::isSoundPlaying(Sound3d& sound) const
{
	return (isSoundStarted(sound) && !isSoundPaused(sound));
}

const bool Sound3dPlayer::isSoundPaused(Sound3d& sound) const
{
	return (isSoundStarted(sound) && Mix_Paused(_findChannels(sound)[0]));
}