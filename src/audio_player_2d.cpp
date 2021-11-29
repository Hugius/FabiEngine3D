#include "audio_player.hpp"
#include "logger.hpp"

void AudioPlayer::playSound2D(Sound2D& sound, int loops, unsigned int fadeMS, bool mustForcePlay)
{
	// Check if sound is started
	if(isSoundStarted2D(sound) && !mustForcePlay)
	{
		Logger::throwError("AudioPlayer::playSound2D::1");
	}

	// Try to find free channel
	auto channel = _getFreeChannel();
	if(channel == -1)
	{
		Logger::throwError("AudioPlayer::playSound2D::2");
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
	_updateSoundVolume2D(sound);
}

void AudioPlayer::pauseAllSounds2D(vector<Sound2D>& soundList)
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

void AudioPlayer::pauseSound2D(Sound2D& sound)
{
	// Check if sound is playing
	if(!isSoundPlaying2D(sound))
	{
		Logger::throwError("AudioPlayer::pauseSound2D::1");
	}

	// Check if sound paused
	if(isSoundPaused2D(sound))
	{
		Logger::throwError("AudioPlayer::pauseSound2D::2");
	}

	// Pause sound
	for(const auto& channel : _findSoundChannels2D(sound))
	{
		Mix_Pause(channel);
	}
}

void AudioPlayer::resumeAllSounds2D(vector<Sound2D>& soundList)
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

void AudioPlayer::resumeSound2D(Sound2D& sound)
{
	// Check if sound is not paused
	if(!isSoundPaused2D(sound))
	{
		Logger::throwError("AudioPlayer::resumeSound2D");
	}

	// Resume sound
	for(const auto& channel : _findSoundChannels2D(sound))
	{
		Mix_Resume(channel);
	}
}

void AudioPlayer::stopAllSounds2D(vector<Sound2D>& soundList)
{
	// Resume before stopping
	resumeAllSounds2D(soundList);

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

void AudioPlayer::stopSound2D(Sound2D& sound, unsigned int fadeMS)
{
	// Check if sound is not started
	if(!isSoundStarted2D(sound))
	{
		Logger::throwError("AudioPlayer::stopSound2D");
	}

	// Resume before stopping
	if(isSoundPaused2D(sound))
	{
		resumeSound2D(sound);
	}

	// Stop or fade
	if(fadeMS == 0)
	{
		// For every sound playback
		for(const auto& channel : _findSoundChannels2D(sound))
		{
			Mix_HaltChannel(channel);
		}
	}
	else
	{
		// For every sound playback
		for(const auto& channel : _findSoundChannels2D(sound))
		{
			Mix_FadeOutChannel(channel, fadeMS);
		}
	}

	// De-allocate channels
	for(const auto& channel : _findSoundChannels2D(sound))
	{
		_channels[channel] = "";
	}
}

const bool AudioPlayer::isSoundStarted2D(Sound2D& sound) const
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

const bool AudioPlayer::isSoundPlaying2D(Sound2D& sound) const
{
	return (isSoundStarted2D(sound) && !isSoundPaused2D(sound));
}

const bool AudioPlayer::isSoundPaused2D(Sound2D& sound) const
{
	return (isSoundStarted2D(sound) && Mix_Paused(_findSoundChannels2D(sound).front()));
}

void AudioPlayer::_updateSoundVolume2D(Sound2D& sound)
{
	if(isSoundStarted2D(sound))
	{
		for(const auto& channel : _findSoundChannels2D(sound))
		{
			Mix_Volume(channel, static_cast<int>(sound.getVolume() * 128.0f));
		}
	}
}

const vector<int> AudioPlayer::_findSoundChannels2D(Sound2D& sound) const
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
		Logger::throwError("AudioPlayer::_findSoundChannels2D");
	}

	// Return
	return channels;
}