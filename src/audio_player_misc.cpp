#include "audio_player.hpp"
#include "logger.hpp"
#include "tools.hpp"

using std::max;
using std::clamp;

AudioPlayer::AudioPlayer()
{
	Mix_AllocateChannels(0);
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

void AudioPlayer::update(Camera& camera, vector<Sound>& soundList, vector<Music>& musicList)
{
	// Update channel management
	for(size_t i = 0; i < _channels.size(); i++)
	{
		// Check if audio stopped playing
		if(!Mix_Playing(static_cast<int>(i)) && !Mix_Paused(static_cast<int>(i)))
		{
			// De-allocate channel
			_channels[i] = "";
		}
	}

	// Update sound management
	if(_isSoundsEnabled)
	{
		// For every sound
		for(auto& sound : soundList)
		{
			// Check if 3D sound
			if(sound.is3D())
			{
				// Check if emitting sound
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
					Matrix44 rotationMatrix = Math::createRotationMatrixY(Math::convertToRadians(90.0f));
					Vec3 soundDirection = (cameraPosition - sound.getPosition());
					Vec4 result = (rotationMatrix * Vec4(soundDirection.x, soundDirection.y, soundDirection.z, 1.0f));
					soundDirection = Vec3(result.x, result.y, result.z);
					soundDirection = Math::normalize(soundDirection);
					float dot = Math::calculateDotProduct(soundDirection, cameraDirection);
					float range = ((dot / 2.0f) + 0.5f);
					Uint8 leftStrength = Uint8(255.0f * range);
					Uint8 rightStrength = Uint8(255.0f - leftStrength);

					// For every sound playback
					for(const auto& channel : _findSoundChannels(sound))
					{
						Mix_SetPanning(channel, leftStrength, rightStrength); // Apply stereo panning
					}
				}
			}

			// Update playing volume
			_updateSoundVolume(sound);
		}
	}

	// Update music management
	if(_isMusicEnabled)
	{
		playMusic(musicList, false);
		_updateMusicVolume();
	}
}

void AudioPlayer::setSoundsEnabled(bool value)
{
	if(!value)
	{
		stopAllSounds();
	}

	_isSoundsEnabled = value;
}

void AudioPlayer::setMusicEnabled(bool value)
{
	if(!value)
	{
		stopMusic();
	}

	_isMusicEnabled = value;
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

void AudioPlayer::_updateSoundVolume(Sound& sound)
{
	if(_isSoundsEnabled)
	{
		if(isSoundStarted(sound))
		{
			auto intVolume = static_cast<int>(sound.getVolume() * 128.0f);

			// For every sound playback
			for(const auto& channel : _findSoundChannels(sound))
			{
				Mix_Volume(channel, intVolume);
			}
		}
	}
}

void AudioPlayer::_updateMusicVolume()
{
	if(_isMusicEnabled)
	{
		auto intVolume = static_cast<int>(_musicVolume * 128.0f);
		Mix_VolumeMusic(intVolume);
	}
}

const  vector<int> AudioPlayer::_findSoundChannels(Sound& sound) const
{
	vector<int> channels;

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
		Logger::throwError("AudioPlayer::_findSoundChannels");
	}

	return channels;
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