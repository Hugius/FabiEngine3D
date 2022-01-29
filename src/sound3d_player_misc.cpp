#include "sound3d_player.hpp"
#include "logger.hpp"

using std::max;
using std::clamp;

Sound3dPlayer::Sound3dPlayer()
{
	Mix_AllocateChannels(MAX_CHANNEL_COUNT);
}

void Sound3dPlayer::inject(shared_ptr<Sound3dManager> sound3dManager)
{
	_sound3dManager = sound3dManager;
}

void Sound3dPlayer::inject(shared_ptr<Camera> camera)
{
	_camera = camera;
}

void Sound3dPlayer::update()
{
	for(auto& sound : _sound3dManager->getSounds())
	{
		if(isSoundStarted(sound))
		{
			const auto cameraPosition = _camera->getPosition();
			const auto distance = Math::calculateDistance(cameraPosition, sound.getPosition());
			const auto volume = (1.0f - (distance / sound.getMaxDistance()));
			sound.setVolume(clamp(volume, 0.0f, 1.0f) * sound.getMaxVolume());

			const auto cameraDirection = _camera->getFrontVector();
			const auto soundDirection = (cameraPosition - sound.getPosition());
			const auto rotationMatrix = Math::createRotationMatrixY(Math::convertToRadians(90.0f));
			const auto rotatedSoundDirection = (rotationMatrix * fvec4(soundDirection.x, soundDirection.y, soundDirection.z, 1.0f));
			const auto normalizedSoundDirection = Math::normalize(fvec3(rotatedSoundDirection.x, rotatedSoundDirection.y, rotatedSoundDirection.z));
			const auto dotProduct = Math::calculateDotProduct(normalizedSoundDirection, cameraDirection);
			const auto panningRange = ((dotProduct * 0.5f) + 0.5f);
			const auto leftIntensity = Uint8(255.0f * panningRange);
			const auto rightIntensity = Uint8(255 - leftIntensity);

			for(const auto& channel : _findChannels(sound))
			{
				Mix_SetPanning(channel, leftIntensity, rightIntensity);
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

	for(const auto& soundId : _channels)
	{
		if(soundId.empty())
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
		if(_channels[i] == sound.getId())
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