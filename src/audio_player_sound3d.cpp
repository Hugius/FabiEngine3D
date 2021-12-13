#include "audio_player.hpp"
#include "logger.hpp"

void AudioPlayer::playSound3d(Sound3d& sound, int loops, unsigned int fadeMS, bool mustForcePlay)
{
	// Check if sound is started
	if(isSound3dStarted(sound) && !mustForcePlay)
	{
		Logger::throwError("AudioPlayer::playSound3d::1");
	}

	// Try to find free channel
	auto channel = _getFreeChannel();
	if(channel == -1)
	{
		Logger::throwError("AudioPlayer::playSound3d::2");
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

void AudioPlayer::pauseAllSound3d(vector<Sound3d>& sounds)
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

void AudioPlayer::pauseSound3d(Sound3d& sound)
{
	// Check if sound is playing
	if(!isSound3dPlaying(sound))
	{
		Logger::throwError("AudioPlayer::pauseSound3d::1");
	}

	// Check if sound paused
	if(isSound3dPaused(sound))
	{
		Logger::throwError("AudioPlayer::pauseSound3d::2");
	}

	// Pause sound
	for(const auto& channel : _findChannels(sound))
	{
		Mix_Pause(channel);
	}
}

void AudioPlayer::resumeAllSound3d(vector<Sound3d>& sounds)
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

void AudioPlayer::resumeSound3d(Sound3d& sound)
{
	// Check if sound is not paused
	if(!isSound3dPaused(sound))
	{
		Logger::throwError("AudioPlayer::resumeSound3d");
	}

	// Resume sound
	for(const auto& channel : _findChannels(sound))
	{
		Mix_Resume(channel);
	}
}

void AudioPlayer::stopAllSound3d(vector<Sound3d>& sounds)
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

void AudioPlayer::stopSound3d(Sound3d& sound, unsigned int fadeMS)
{
	// Check if sound is not started
	if(!isSound3dStarted(sound))
	{
		Logger::throwError("AudioPlayer::stopSound3d");
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

const bool AudioPlayer::isSound3dStarted(Sound3d& sound) const
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

const bool AudioPlayer::isSound3dPlaying(Sound3d& sound) const
{
	return (isSound3dStarted(sound) && !isSound3dPaused(sound));
}

const bool AudioPlayer::isSound3dPaused(Sound3d& sound) const
{
	return (isSound3dStarted(sound) && Mix_Paused(_findChannels(sound)[0]));
}

void AudioPlayer::_updateSound3dVolume(Sound3d& sound)
{
	if(isSound3dStarted(sound))
	{
		for(const auto& channel : _findChannels(sound))
		{
			Mix_Volume(channel, static_cast<int>(sound.getVolume() * 128.0f));
		}
	}
}

const vector<int> AudioPlayer::_findChannels(Sound3d& sound) const
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