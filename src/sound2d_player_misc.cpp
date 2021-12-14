#include "sound2d_player.hpp"
#include "logger.hpp"
#include "configuration.hpp"

using std::clamp;

Sound2dPlayer::Sound2dPlayer()
{
	Mix_AllocateChannels(0);
}

void Sound2dPlayer::update(vector<Sound2d>& sounds)
{
	// Update sounds
	for(auto& sound : sounds)
	{
		_updateSoundVolume(sound);
	}

	// Update channels
	for(size_t i = 0; i < _channels.size(); i++)
	{
		// Check if sound stopped playing
		if(!Mix_Playing(static_cast<int>(i)) && !Mix_Paused(static_cast<int>(i)))
		{
			// De-allocate channel
			_channels[i] = "";
		}
	}
}

void Sound2dPlayer::allocateChannels(unsigned int count)
{
	// Limit count
	count = clamp(count, Config::MIN_SOUND_CHANNELS, Config::MAX_SOUND_CHANNELS);

	// Allocate sound channels
	Mix_AllocateChannels(count);

	// Initialize sound channels
	_channels.clear();
	for(unsigned int i = 0; i < count; i++)
	{
		_channels.push_back("");
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

const vector<int> Sound2dPlayer::_findChannels(Sound2d& sound) const
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
		Logger::throwError("Sound2dPlayer::_findChannels");
	}

	// Return
	return channels;
}