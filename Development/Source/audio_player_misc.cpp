#include "audio_player.hpp"
#include "logger.hpp"
#include "tools.hpp"

AudioPlayer::AudioPlayer()
{
	Mix_AllocateChannels(0);
}

void AudioPlayer::allocateChannels(int count)
{
	// Allocate audio channels
	Mix_AllocateChannels(count);

	// Initialize audio channels to none
	_channelMap.clear();
	for (unsigned int i = 0; i < count; i++)
	{
		_channelMap.insert(std::make_pair(i, ""));
	}
}

void AudioPlayer::update(CameraManager& camera, vector<Sound>& soundList, vector<Music>& musicList)
{
	// Update channel management
	for (auto& channelPair : _channelMap)
	{
		// Check if audio stopped playing, but is not paused
		if (!Mix_Playing(channelPair.first) && !Mix_Paused(channelPair.first))
		{
			// De-allocate channel
			channelPair.second = "";
		}
	}

	// Update sound management
	if (_isSoundsEnabled)
	{
		// For every sound
		for (auto& sound : soundList)
		{
			// Check if 3D sound
			if (sound.is3D())
			{
				// Check if emitting sound
				if (isSoundStarted(sound))
				{
					// Distance
					auto cameraPos = camera.getPosition(); // Camera position
					float xDiff = fabsf(sound.getPosition().x - cameraPos.x); // Difference between camera X & point X
					float yDiff = fabsf(sound.getPosition().y - cameraPos.y); // Difference between camera Y & point Y
					float zDiff = fabsf(sound.getPosition().z - cameraPos.z); // Difference between camera Z & point Z
					float maxDiff = std::max(xDiff, std::max(yDiff, zDiff)); // Maximum difference
					float volume = sound.getMaxVolume() - ((maxDiff / sound.getMaxDistance()) * sound.getMaxVolume()); // Calculate volume
					volume = std::clamp(volume, 0.0f, sound.getMaxVolume()); // Clamp to maximum
					sound.setVolume(volume); // Update sound volume

					// Panning
					auto cameraFront = camera.getFront(); // From camera vector
					Matrix44 rotationMatrix = Matrix44::createRotationY(Math::degreesToRadians(90.0f));
					Vec3 pointVector = cameraPos - sound.getPosition(); // To camera vector
					Vec4 result = rotationMatrix * Vec4(pointVector.x, pointVector.y, pointVector.z, 1.0f);
					pointVector = Vec3(result.x, result.y, result.z); // Rotate direction
					pointVector.normalize(); // Normalize
					float dot = pointVector.dot(cameraFront); // Dot product
					float range = (dot / 2.0f) + 0.5f; // Convert (-1 to 1) scale to (0.0f to 1.0f) scale
					Uint8 leftStrength = Uint8(255.0f * range); // Left ear
					Uint8 rightStrength = Uint8(255.0f - (255.0f * range)); // Right ear
					Mix_SetPanning(_findSoundChannel(sound), leftStrength, rightStrength); // Apply stereo panning
				}
			}

			// Update playing volume
			_updateSoundVolume(sound);
		}
	}
	else
	{
		Mix_HaltChannel(-1);
	}

	// Update music management
	if (_isMusicEnabled)
	{
		playMusic(musicList);
		_updateMusicVolume();
	}
	else
	{
		Mix_HaltMusic();
	}
}

void AudioPlayer::setSoundsEnabled(bool value)
{
	_isSoundsEnabled = value;
}

void AudioPlayer::setMusicEnabled(bool value)
{
	_isMusicEnabled = value;
}

unsigned int AudioPlayer::getUsedChannelCount()
{
	int count = 0;

	for (auto& element : _channelMap)
	{
		if (element.second != "")
		{
			count++;
		}
	}

	return count;
}

unsigned int AudioPlayer::getAllocatedChannelCount()
{
	return _channelMap.size();
}

void AudioPlayer::_updateSoundVolume(Sound& sound)
{
	if (_isSoundsEnabled)
	{
		if (isSoundStarted(sound))
		{
			auto intVolume = static_cast<int>(sound.getVolume() * 128.0f);
			Mix_Volume(_findSoundChannel(sound), intVolume);
		}
	}
}

void AudioPlayer::_updateMusicVolume()
{
	if (_isMusicEnabled)
	{
		auto intVolume = static_cast<int>(_musicVolume * 128.0f);
		Mix_VolumeMusic(intVolume);
	}
}

int AudioPlayer::_findSoundChannel(Sound& sound)
{
	for (auto& pair : _channelMap)
	{
		if (pair.second == sound.getID())
		{
			return pair.first;
		}
	}

	Logger::throwError("Trying to get corresponding channel of sound with ID \"", sound.getID(), "\"!");
}

bool AudioPlayer::_isSoundInChannelMap(Sound& sound)
{
	for (auto& pair : _channelMap)
	{
		if (pair.second == sound.getID())
		{
			return true;
		}
	}

	return false;
}

int AudioPlayer::_getFreeChannel()
{
	for (auto& element : _channelMap)
	{
		if (element.second == "")
		{
			return element.first;
		}
	}

	Logger::throwError("Not enough audio channels available!");
}