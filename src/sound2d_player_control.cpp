#include "sound2d_player.hpp"
#include "logger.hpp"

void Sound2dPlayer::playSound(Sound2d& sound, int timesToPlay, unsigned int fadeMS, bool mustForcePlay)
{
	// Validate play count
	if((timesToPlay < -1) || (timesToPlay == 0))
	{
		Logger::throwError("Sound2dPlayer::playSound3d::1");
	}

	// Check if sound is started
	if(isSoundStarted(sound) && !mustForcePlay)
	{
		Logger::throwError("Sound2dPlayer::playSound::2");
	}

	// Try to find free channel
	auto channel = _getFreeChannel();
	if(channel == -1)
	{
		Logger::throwError("Sound2dPlayer::playSound::3");
	}
	_channels[channel] = sound.getID();

	// Play or fade
	if(fadeMS == 0)
	{
		Mix_PlayChannel(channel, sound.getDataPointer(), (timesToPlay - 1));
	}
	else
	{
		Mix_FadeInChannel(channel, sound.getDataPointer(), (timesToPlay - 1), fadeMS);
	}

	// Update volume
	_updateSoundVolume(sound);
}

void Sound2dPlayer::pauseSounds(vector<Sound2d>& sounds)
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

void Sound2dPlayer::pauseSound(Sound2d& sound)
{
	// Check if sound is playing
	if(!isSoundPlaying(sound))
	{
		Logger::throwError("Sound2dPlayer::pauseSound::1");
	}

	// Check if sound paused
	if(isSoundPaused(sound))
	{
		Logger::throwError("Sound2dPlayer::pauseSound::2");
	}

	// Pause sound
	for(const auto& channel : _findChannels(sound))
	{
		Mix_Pause(channel);
	}
}

void Sound2dPlayer::resumeSounds(vector<Sound2d>& sounds)
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

void Sound2dPlayer::resumeSound(Sound2d& sound)
{
	// Check if sound is not paused
	if(!isSoundPaused(sound))
	{
		Logger::throwError("Sound2dPlayer::resumeSound");
	}

	// Resume sound
	for(const auto& channel : _findChannels(sound))
	{
		Mix_Resume(channel);
	}
}

void Sound2dPlayer::stopSounds(vector<Sound2d>& sounds)
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

void Sound2dPlayer::stopSound(Sound2d& sound, unsigned int fadeMS)
{
	// Check if sound is not started
	if(!isSoundStarted(sound))
	{
		Logger::throwError("Sound2dPlayer::stopSound");
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

const bool Sound2dPlayer::isSoundStarted(Sound2d& sound) const
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

const bool Sound2dPlayer::isSoundPlaying(Sound2d& sound) const
{
	return (isSoundStarted(sound) && !isSoundPaused(sound));
}

const bool Sound2dPlayer::isSoundPaused(Sound2d& sound) const
{
	return (isSoundStarted(sound) && Mix_Paused(_findChannels(sound)[0]));
}