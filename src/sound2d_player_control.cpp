#include "sound2d_player.hpp"
#include "logger.hpp"

void Sound2dPlayer::startSound(Sound2d& sound, int playCount, unsigned int fadeMS, bool mustForce)
{
	if((playCount < -1) || (playCount == 0))
	{
		Logger::throwError("Sound2dPlayer::startSound::1");
	}

	if(isSoundStarted(sound) && !mustForce)
	{
		Logger::throwError("Sound2dPlayer::startSound::2");
	}

	auto channel = _getFreeChannel();
	if(channel == -1)
	{
		Logger::throwError("Sound2dPlayer::startSound::3");
		return;
	}
	_channels[channel] = sound.getId();

	if(fadeMS == 0)
	{
		Mix_PlayChannel(channel, sound.getDataPointer(), (playCount - 1));
	}
	else
	{
		Mix_FadeInChannel(channel, sound.getDataPointer(), (playCount - 1), fadeMS);
	}

	_updateSoundVolume(sound);
}

void Sound2dPlayer::pauseSounds(vector<Sound2d>& sounds)
{
	for(const auto& sound : sounds)
	{
		for(size_t i = 0; i < _channels.size(); i++)
		{
			if(_channels[i] == sound.getId())
			{
				Mix_Pause(static_cast<int>(i));
			}
		}
	}
}

void Sound2dPlayer::pauseSound(Sound2d& sound)
{
	if(!isSoundPlaying(sound))
	{
		Logger::throwError("Sound2dPlayer::pauseSound::1");
	}

	if(isSoundPaused(sound))
	{
		Logger::throwError("Sound2dPlayer::pauseSound::2");
	}

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
			if(_channels[i] == sound.getId())
			{
				Mix_Resume(static_cast<int>(i));
			}
		}
	}
}

void Sound2dPlayer::resumeSound(Sound2d& sound)
{
	if(!isSoundPaused(sound))
	{
		Logger::throwError("Sound2dPlayer::resumeSound");
	}

	for(const auto& channel : _findChannels(sound))
	{
		Mix_Resume(channel);
	}
}

void Sound2dPlayer::stopSounds(vector<Sound2d>& sounds)
{
	resumeSounds(sounds);

	for(const auto& sound : sounds)
	{
		for(size_t i = 0; i < _channels.size(); i++)
		{
			if(_channels[i] == sound.getId())
			{
				Mix_HaltChannel(static_cast<int>(i));
			}
		}
	}
}

void Sound2dPlayer::stopSound(Sound2d& sound, unsigned int fadeMS)
{
	if(!isSoundStarted(sound))
	{
		Logger::throwError("Sound2dPlayer::stopSound");
	}

	if(isSoundPaused(sound))
	{
		resumeSound(sound);
	}

	if(fadeMS == 0)
	{
		for(const auto& channel : _findChannels(sound))
		{
			Mix_HaltChannel(channel);
		}
	}
	else
	{
		for(const auto& channel : _findChannels(sound))
		{
			Mix_FadeOutChannel(channel, fadeMS);
		}
	}

	for(const auto& channel : _findChannels(sound))
	{
		_channels[channel] = "";
	}
}

const bool Sound2dPlayer::isSoundStarted(Sound2d& sound) const
{
	for(const auto& soundID : _channels)
	{
		if(soundID == sound.getId())
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