#include "sound3d_player.hpp"
#include "logger.hpp"

using std::max;
using std::clamp;

Sound3dPlayer::Sound3dPlayer()
{
	Mix_AllocateChannels(MAX_CHANNEL_COUNT);
}

void Sound3dPlayer::update(vector<Sound3d>& sounds, Camera& camera)
{
	for(auto& sound : sounds)
	{
		if(isSoundStarted(sound))
		{
			auto cameraPosition = camera.getPosition();
			float xDifference = fabsf(sound.getPosition().x - cameraPosition.x);
			float yDifference = fabsf(sound.getPosition().y - cameraPosition.y);
			float zDifference = fabsf(sound.getPosition().z - cameraPosition.z);
			float maxDifference = max(xDifference, max(yDifference, zDifference));
			float volume = sound.getMaxVolume() - ((maxDifference / sound.getMaxDistance()) * sound.getMaxVolume());
			volume = clamp(volume, 0.0f, sound.getMaxVolume());
			sound.setVolume(volume);

			auto cameraDirection = camera.getFrontVector();
			mat44 rotationMatrix = Math::createRotationMatrixY(Math::convertToRadians(90.0f));
			fvec3 soundDirection = (cameraPosition - sound.getPosition());
			fvec4 result = (rotationMatrix * fvec4(soundDirection.x, soundDirection.y, soundDirection.z, 1.0f));
			soundDirection = fvec3(result.x, result.y, result.z);
			soundDirection = Math::normalize(soundDirection);
			float dot = Math::calculateDotProduct(soundDirection, cameraDirection);
			float range = ((dot / 2.0f) + 0.5f);
			Uint8 leftStrength = Uint8(255.0f * range);
			Uint8 rightStrength = Uint8(255.0f - leftStrength);

			for(const auto& channel : _findChannels(sound))
			{
				Mix_SetPanning(channel, leftStrength, rightStrength);
			}
		}

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

const unsigned int Sound3dPlayer::getUsedChannelCount() const
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

const unsigned int Sound3dPlayer::getAllocatedChannelCount() const
{
	return static_cast<unsigned int>(_channels.size());
}

const  int Sound3dPlayer::_getFreeChannel() const
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

const bool Sound3dPlayer::isChannelAvailable() const
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

void Sound3dPlayer::_updateSoundVolume(Sound3d& sound)
{
	if(isSoundStarted(sound))
	{
		for(const auto& channel : _findChannels(sound))
		{
			Mix_Volume(channel, static_cast<int>(sound.getVolume() * 128.0f));
		}
	}
}

const vector<unsigned int> Sound3dPlayer::_findChannels(Sound3d& sound) const
{
	vector<unsigned int> channels;

	for(size_t i = 0; i < _channels.size(); i++)
	{
		if(_channels[i] == sound.getID())
		{
			channels.push_back(static_cast<unsigned int>(i));
		}
	}

	if(channels.empty())
	{
		Logger::throwError("SoundPlayer::_findChannels");
	}

	return channels;
}