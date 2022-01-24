#include "sound2d_player.hpp"
#include "logger.hpp"
#include "configuration.hpp"

using std::clamp;

Sound2dPlayer::Sound2dPlayer()
{
	Mix_AllocateChannels(MAX_CHANNEL_COUNT);
}

void Sound2dPlayer::inject(shared_ptr<Sound2dManager> sound2dManager)
{
	_sound2dManager = sound2dManager;
}

void Sound2dPlayer::update()
{
	for(auto& sound : _sound2dManager->getSounds())
	{
		_updateSoundVolume(sound);
	}

	for(size_t i = 0; i < _channels.size(); i++)
	{
		if(!Mix_Playing(static_cast<int>(i)) && !Mix_Paused(static_cast<int>(i)))
		{
			_channels[i] = "";
		}
	}
}

const unsigned int Sound2dPlayer::getUsedChannelCount() const
{
	int count = 0;

	for(const auto& soundID : _channels)
	{
		if(soundID.empty())
		{
			count++;
		}
	}

	return count;
}

const unsigned int Sound2dPlayer::getAllocatedChannelCount() const
{
	return static_cast<unsigned int>(_channels.size());
}

const int Sound2dPlayer::_getFreeChannel() const
{
	for(size_t i = 0; i < _channels.size(); i++)
	{
		if(_channels[i].empty())
		{
			return static_cast<int>(i);
		}
	}

	return -1;
}

const bool Sound2dPlayer::isChannelAvailable() const
{
	for(size_t i = 0; i < _channels.size(); i++)
	{
		if(_channels[i].empty())
		{
			return true;
		}
	}

	return false;
}

void Sound2dPlayer::_updateSoundVolume(Sound2d& sound)
{
	if(isSoundStarted(sound))
	{
		for(const auto& channel : _findChannels(sound))
		{
			Mix_Volume(channel, static_cast<int>(sound.getVolume() * 128.0f));
		}
	}
}

const vector<unsigned int> Sound2dPlayer::_findChannels(Sound2d& sound) const
{
	vector<unsigned int> channels;

	for(size_t i = 0; i < _channels.size(); i++)
	{
		if(_channels[i] == sound.getId())
		{
			channels.push_back(static_cast<unsigned int>(i));
		}
	}

	if(channels.empty())
	{
		Logger::throwError("Sound2dPlayer::_findChannels");
	}

	return channels;
}