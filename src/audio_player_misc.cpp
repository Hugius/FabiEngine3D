#include "audio_player.hpp"
#include "logger.hpp"

using std::clamp;
using std::max;

AudioPlayer::AudioPlayer()
{
	Mix_AllocateChannels(0);
}

void AudioPlayer::update(Camera& camera, vector<Music>& musics, vector<Sound2D>& sounds2D, vector<Sound3D>& sounds3D)
{
	// Update music
	if (!musics.empty())
	{
		// Check if music is not started
		if (!isMusicStarted())
		{
			// Select music
			unsigned int musicIndex;
			if (musics.size() == 1)
			{
				musicIndex = 0;
			}
			else
			{
				musicIndex = Math::getRandomInteger(0, static_cast<int>(musics.size() - 1));
			}

			// Play music
			Mix_PlayMusic(musics[musicIndex].getDataPointer(), 0);
		}
	}

	// Update 2D sounds
	for(auto& sound : sounds2D)
	{
		// Update sound volume
		_updateSoundVolume2D(sound);
	}

	// Update 3D sounds
	for(auto& sound : sounds3D)
	{
		// Check if sound is started
		if(isSoundStarted3D(sound))
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
			for(const auto& channel : _findSoundChannels3D(sound))
			{
				// Apply stereo panning
				Mix_SetPanning(channel, leftStrength, rightStrength);
			}
		}

		// Update sound volume
		_updateSoundVolume3D(sound);
	}

	// Update channels
	for (size_t i = 0; i < _channels.size(); i++)
	{
		// Check if audio stopped playing
		if (!Mix_Playing(static_cast<int>(i)) && !Mix_Paused(static_cast<int>(i)))
		{
			// De-allocate channel
			_channels[i] = "";
		}
	}
}

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