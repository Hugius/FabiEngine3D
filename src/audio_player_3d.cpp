#include "audio_player.hpp"
#include "logger.hpp"

void AudioPlayer::playSound3D(Sound3D& sound, int loops, unsigned int fadeMS, bool mustForcePlay)
{
	// Check if sound is started
	if(isSoundStarted3D(sound) && !mustForcePlay)
	{
		Logger::throwError("AudioPlayer::playSound3D::1");
	}

	// Try to find free channel
	auto channel = _getFreeChannel();
	if(channel == -1)
	{
		Logger::throwError("AudioPlayer::playSound3D::2");
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
	_updateSoundVolume3D(sound);
}

void AudioPlayer::pauseAllSounds3D(vector<Sound3D>& sounds)
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

void AudioPlayer::pauseSound3D(Sound3D& sound)
{
	// Check if sound is playing
	if(!isSoundPlaying3D(sound))
	{
		Logger::throwError("AudioPlayer::pauseSound3D::1");
	}

	// Check if sound paused
	if(isSoundPaused3D(sound))
	{
		Logger::throwError("AudioPlayer::pauseSound3D::2");
	}

	// Pause sound
	for(const auto& channel : _findSoundChannels3D(sound))
	{
		Mix_Pause(channel);
	}
}

void AudioPlayer::resumeAllSounds3D(vector<Sound3D>& sounds)
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

void AudioPlayer::resumeSound3D(Sound3D& sound)
{
	// Check if sound is not paused
	if(!isSoundPaused3D(sound))
	{
		Logger::throwError("AudioPlayer::resumeSound3D");
	}

	// Resume sound
	for(const auto& channel : _findSoundChannels3D(sound))
	{
		Mix_Resume(channel);
	}
}

void AudioPlayer::stopAllSounds3D(vector<Sound3D>& sounds)
{
	// Resume before stopping
	resumeAllSounds3D(sounds);

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

void AudioPlayer::stopSound3D(Sound3D& sound, unsigned int fadeMS)
{
	// Check if sound is not started
	if(!isSoundStarted3D(sound))
	{
		Logger::throwError("AudioPlayer::stopSound3D");
	}

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
		for(const auto& channel : _findSoundChannels3D(sound))
		{
			Mix_Volume(channel, static_cast<int>(sound.getVolume() * 128.0f));
		}
	}
}

const vector<int> AudioPlayer::_findSoundChannels3D(Sound3D& sound) const
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
		Logger::throwError("AudioPlayer::_findSoundChannels3D");
	}

	// Return
	return channels;
}