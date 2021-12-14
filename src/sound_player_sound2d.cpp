#include "sound_player.hpp"
#include "logger.hpp"

void SoundPlayer::playSound2d(Sound2d& sound, int loops, unsigned int fadeMS, bool mustForcePlay)
{
	// Check if sound is started
	if(isSound2dStarted(sound) && !mustForcePlay)
	{
		Logger::throwError("SoundPlayer::playSound2d::1");
	}

	// Try to find free channel
	auto channel = _getFreeChannel();
	if(channel == -1)
	{
		Logger::throwError("SoundPlayer::playSound2d::2");
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
	_updateSound2dVolume(sound);
}

void SoundPlayer::pauseAllSound2d(vector<Sound2d>& sounds)
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

void SoundPlayer::pauseSound2d(Sound2d& sound)
{
	// Check if sound is playing
	if(!isSound2dPlaying(sound))
	{
		Logger::throwError("SoundPlayer::pauseSound2d::1");
	}

	// Check if sound paused
	if(isSound2dPaused(sound))
	{
		Logger::throwError("SoundPlayer::pauseSound2d::2");
	}

	// Pause sound
	for(const auto& channel : _findChannels(sound))
	{
		Mix_Pause(channel);
	}
}

void SoundPlayer::resumeAllSound2d(vector<Sound2d>& sounds)
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

void SoundPlayer::resumeSound2d(Sound2d& sound)
{
	// Check if sound is not paused
	if(!isSound2dPaused(sound))
	{
		Logger::throwError("SoundPlayer::resumeSound2d");
	}

	// Resume sound
	for(const auto& channel : _findChannels(sound))
	{
		Mix_Resume(channel);
	}
}

void SoundPlayer::stopAllSound2d(vector<Sound2d>& sounds)
{
	// Resume before stopping
	resumeAllSound2d(sounds);

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

void SoundPlayer::stopSound2d(Sound2d& sound, unsigned int fadeMS)
{
	// Check if sound is not started
	if(!isSound2dStarted(sound))
	{
		Logger::throwError("SoundPlayer::stopSound2d");
	}

	// Resume before stopping
	if(isSound2dPaused(sound))
	{
		resumeSound2d(sound);
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

const bool SoundPlayer::isSound2dStarted(Sound2d& sound) const
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

const bool SoundPlayer::isSound2dPlaying(Sound2d& sound) const
{
	return (isSound2dStarted(sound) && !isSound2dPaused(sound));
}

const bool SoundPlayer::isSound2dPaused(Sound2d& sound) const
{
	return (isSound2dStarted(sound) && Mix_Paused(_findChannels(sound)[0]));
}

void SoundPlayer::_updateSound2dVolume(Sound2d& sound)
{
	if(isSound2dStarted(sound))
	{
		for(const auto& channel : _findChannels(sound))
		{
			Mix_Volume(channel, static_cast<int>(sound.getVolume() * 128.0f));
		}
	}
}

const vector<int> SoundPlayer::_findChannels(Sound2d& sound) const
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