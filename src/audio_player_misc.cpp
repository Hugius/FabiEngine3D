#include "audio_player.hpp"

using std::clamp;

void AudioPlayer::allocateChannels(unsigned int count)
{
	// Limit count
	count = clamp(count, Config::MIN_AUDIO_CHANNELS, Config::MAX_AUDIO_CHANNELS);

	// Allocate audio channels
	Mix_AllocateChannels(count);

	// Initialize audio channels to none
	_channels.clear();
	for(unsigned int i = 0; i < count; i++)
	{
		_channels.push_back("");
	}
}

const unsigned int AudioPlayer::getUsedChannelCount() const
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

const unsigned int AudioPlayer::getAllocatedChannelCount() const
{
	return static_cast<unsigned int>(_channels.size());
}

const  int AudioPlayer::_getFreeChannel() const
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

const bool AudioPlayer::isChannelAvailable() const
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