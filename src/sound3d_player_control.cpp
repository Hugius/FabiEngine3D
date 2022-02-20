#include "sound3d_player.hpp"
#include "logger.hpp"

void Sound3dPlayer::startSound(Sound3d& sound, int playCount, unsigned int fadeMS, bool mustForce)
{
	if((playCount < -1) || (playCount == 0))
	{
		abort();
	}

	if(isSoundStarted(sound) && !mustForce)
	{
		abort();
	}

	auto channel = _getFreeChannel();

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

void Sound3dPlayer::pauseSounds(vector<Sound3d>& sounds)
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

void Sound3dPlayer::pauseSound(Sound3d& sound)
{
	if(!isSoundStreaming(sound))
	{
		abort();
	}

	if(isSoundPaused(sound))
	{
		abort();
	}

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
			if(_channels[i] == sound.getId())
			{
				Mix_Resume(static_cast<int>(i));
			}
		}
	}
}

void Sound3dPlayer::resumeSound(Sound3d& sound)
{
	if(!isSoundPaused(sound))
	{
		abort();
	}

	for(const auto& channel : _findChannels(sound))
	{
		Mix_Resume(channel);
	}
}

void Sound3dPlayer::stopSounds(vector<Sound3d>& sounds)
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

void Sound3dPlayer::stopSound(Sound3d& sound, unsigned int fadeMS)
{
	if(!isSoundStarted(sound))
	{
		abort();
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

const bool Sound3dPlayer::isSoundStarted(Sound3d& sound) const
{
	for(const auto& soundId : _channels)
	{
		if(soundId == sound.getId())
		{
			return true;
		}
	}

	return false;
}

const bool Sound3dPlayer::isSoundStreaming(Sound3d& sound) const
{
	return (isSoundStarted(sound) && !isSoundPaused(sound));
}

const bool Sound3dPlayer::isSoundPaused(Sound3d& sound) const
{
	return (isSoundStarted(sound) && Mix_Paused(_findChannels(sound)[0]));
}