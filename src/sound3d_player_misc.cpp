#include "sound3d_player.hpp"
#include "logger.hpp"

using std::max;
using std::clamp;

Sound3dPlayer::Sound3dPlayer()
{
	Mix_AllocateChannels(0);
}

void Sound3dPlayer::update(vector<Sound3d>& sounds, Camera& camera)
{
	// Update sounds
	for(auto& sound : sounds)
	{
		// Check if sound is started
		if(isSoundStarted(sound))
		{
			// Distance
			auto cameraPosition = camera.getPosition(); // Camera position
			float xDifference = fabsf(sound.getPosition().x - cameraPosition.x); // Difference between camera X & point X
			float yDifference = fabsf(sound.getPosition().y - cameraPosition.y); // Difference between camera Y & point Y
			float zDifference = fabsf(sound.getPosition().z - cameraPosition.z); // Difference between camera Z & point Z
			float maxDifference = max(xDifference, max(yDifference, zDifference)); // Maximum difference
			float volume = sound.getMaxVolume() - ((maxDifference / sound.getMaxDistance()) * sound.getMaxVolume()); // Calculate volume
			volume = clamp(volume, 0.0f, sound.getMaxVolume()); // Clamp to maximum
			sound.setVolume(volume); // Update sound volume

			// Panning
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

			// Iterate through channels
			for(const auto& channel : _findChannels(sound))
			{
				// Apply stereo panning
				Mix_SetPanning(channel, leftStrength, rightStrength);
			}
		}

		// Update sound volume
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

void Sound3dPlayer::allocateChannels(unsigned int count)
{
	// Limit count
	count = clamp(count, Config::MIN_SOUND_CHANNELS, Config::MAX_SOUND_CHANNELS);

	// Allocate sound channels
	Mix_AllocateChannels(count);

	// Initialize sound channels to none
	_channels.clear();
	for(unsigned int i = 0; i < count; i++)
	{
		_channels.push_back("");
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

const vector<int> Sound3dPlayer::_findChannels(Sound3d& sound) const
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
		Logger::throwError("SoundPlayer::_findChannels");
	}

	// Return
	return channels;
}