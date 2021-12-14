#include "sound_player.hpp"
#include "logger.hpp"

void SoundPlayer::playSound3d(Sound3d& sound, int loops, unsigned int fadeMS, bool mustForcePlay)
{
	// Check if sound is started
	if(isSound3dStarted(sound) && !mustForcePlay)
	{
		Logger::throwError("SoundPlayer::playSound3d::1");
	}

	// Try to find free channel
	auto channel = _getFreeChannel();
	if(channel == -1)
	{
		Logger::throwError("SoundPlayer::playSound3d::2");
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
	_updateSound3dVolume(sound);
}

void SoundPlayer::pauseAllSound3d(vector<Sound3d>& sounds)
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

void SoundPlayer::pauseSound3d(Sound3d& sound)
{
	// Check if sound is playing
	if(!isSound3dPlaying(sound))
	{
		Logger::throwError("SoundPlayer::pauseSound3d::1");
	}

	// Check if sound paused
	if(isSound3dPaused(sound))
	{
		Logger::throwError("SoundPlayer::pauseSound3d::2");
	}

	// Pause sound
	for(const auto& channel : _findChannels(sound))
	{
		Mix_Pause(channel);
	}
}

void SoundPlayer::resumeAllSound3d(vector<Sound3d>& sounds)
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

void SoundPlayer::resumeSound3d(Sound3d& sound)
{
	// Check if sound is not paused
	if(!isSound3dPaused(sound))
	{
		Logger::throwError("SoundPlayer::resumeSound3d");
	}

	// Resume sound
	for(const auto& channel : _findChannels(sound))
	{
		Mix_Resume(channel);
	}
}

void SoundPlayer::stopAllSound3d(vector<Sound3d>& sounds)
{
	// Resume before stopping
	resumeAllSound3d(sounds);

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

void SoundPlayer::stopSound3d(Sound3d& sound, unsigned int fadeMS)
{
	// Check if sound is not started
	if(!isSound3dStarted(sound))
	{
		Logger::throwError("SoundPlayer::stopSound3d");
	}

	// Resume before stopping
	if(isSound3dPaused(sound))
	{
		resumeSound3d(sound);
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

const bool SoundPlayer::isSound3dStarted(Sound3d& sound) const
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

const bool SoundPlayer::isSound3dPlaying(Sound3d& sound) const
{
	return (isSound3dStarted(sound) && !isSound3dPaused(sound));
}

const bool SoundPlayer::isSound3dPaused(Sound3d& sound) const
{
	return (isSound3dStarted(sound) && Mix_Paused(_findChannels(sound)[0]));
}

void SoundPlayer::_updateSound3dVolume(Sound3d& sound)
{
	if(isSound3dStarted(sound))
	{
		for(const auto& channel : _findChannels(sound))
		{
			Mix_Volume(channel, static_cast<int>(sound.getVolume() * 128.0f));
		}
	}
}

const vector<int> SoundPlayer::_findChannels(Sound3d& sound) const
{
	// Temporary values
	vector<int> channels;

	// Find sound channels
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
		Logger::throwError("SoundPlayer::_findChannels");
	}

	// Return
	return channels;
}