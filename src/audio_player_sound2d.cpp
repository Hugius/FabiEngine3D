#include "audio_player.hpp"
#include "logger.hpp"

void AudioPlayer::playSound2d(Sound2d& sound, int loops, unsigned int fadeMS, bool mustForcePlay)
{
	// Check if sound is started
	if(isSound2dStarted(sound) && !mustForcePlay)
	{
		Logger::throwError("AudioPlayer::playSound2d::1");
	}

	// Try to find free channel
	auto channel = _getFreeChannel();
	if(channel == -1)
	{
		Logger::throwError("AudioPlayer::playSound2d::2");
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

void AudioPlayer::pauseAllSound2d(vector<Sound2d>& sounds)
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

void AudioPlayer::pauseSound2d(Sound2d& sound)
{
	// Check if sound is playing
	if(!isSound2dPlaying(sound))
	{
		Logger::throwError("AudioPlayer::pauseSound2d::1");
	}

	// Check if sound paused
	if(isSound2dPaused(sound))
	{
		Logger::throwError("AudioPlayer::pauseSound2d::2");
	}

	// Pause sound
	for(const auto& channel : _findChannels(sound))
	{
		Mix_Pause(channel);
	}
}

void AudioPlayer::resumeAllSound2d(vector<Sound2d>& sounds)
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

void AudioPlayer::resumeSound2d(Sound2d& sound)
{
	// Check if sound is not paused
	if(!isSound2dPaused(sound))
	{
		Logger::throwError("AudioPlayer::resumeSound2d");
	}

	// Resume sound
	for(const auto& channel : _findChannels(sound))
	{
		Mix_Resume(channel);
	}
}

void AudioPlayer::stopAllSound2d(vector<Sound2d>& sounds)
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

void AudioPlayer::stopSound2d(Sound2d& sound, unsigned int fadeMS)
{
	// Check if sound is not started
	if(!isSound2dStarted(sound))
	{
		Logger::throwError("AudioPlayer::stopSound2d");
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

const bool AudioPlayer::isSound2dStarted(Sound2d& sound) const
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

const bool AudioPlayer::isSound2dPlaying(Sound2d& sound) const
{
	return (isSound2dStarted(sound) && !isSound2dPaused(sound));
}

const bool AudioPlayer::isSound2dPaused(Sound2d& sound) const
{
	return (isSound2dStarted(sound) && Mix_Paused(_findChannels(sound)[0]));
}

void AudioPlayer::_updateSound2dVolume(Sound2d& sound)
{
	if(isSound2dStarted(sound))
	{
		for(const auto& channel : _findChannels(sound))
		{
			Mix_Volume(channel, static_cast<int>(sound.getVolume() * 128.0f));
		}
	}
}

const vector<int> AudioPlayer::_findChannels(Sound2d& sound) const
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
		Logger::throwError("AudioPlayer::_findChannels");
	}

	// Return
	return channels;
}