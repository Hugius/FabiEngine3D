#include "audio_player.hpp"
#include "logger.hpp"
#include "configuration.hpp"
#include "tools.hpp"

#include <algorithm>

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
				if (isSoundPlaying(sound))
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
					_updateSoundVolume(sound); // Update playing volume

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
					Mix_SetPanning(_getUsedChannel(sound), leftStrength, rightStrength); // Apply stereo panning
				}
			}
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

void AudioPlayer::pauseAllSounds()
{
	if (_isSoundsEnabled)
	{
		Mix_Pause(-1);
	}
}

void AudioPlayer::resumeAllSounds()
{
	if (_isSoundsEnabled)
	{
		Mix_Resume(-1);
	}
}

void AudioPlayer::stopAllSounds()
{
	if (_isSoundsEnabled)
	{
		Mix_HaltChannel(-1);
	}
}

void AudioPlayer::playSound(Sound& sound, int loops)
{
	if (_isSoundsEnabled)
	{
		if (_isSoundInChannelMap(sound))
		{
			Mix_PlayChannel(_getUsedChannel(sound), sound.getDataPointer(), loops); // Play sound again on same channel
		}
		else
		{
			int channel = _getFreeChannel();
			Mix_PlayChannel(channel, sound.getDataPointer(), loops); // Play sound on new channel
			_channelMap[channel] = sound.getID();
		}
	}
}

void AudioPlayer::pauseSound(Sound& sound)
{
	if (_isSoundsEnabled)
	{
		if (_isSoundInChannelMap(sound))
		{
			Mix_Pause(_getUsedChannel(sound));
		}
		else
		{
			Logger::throwWarning("Trying to pause sound with ID \"", sound.getID(), " \", but was not playing!");
		}
	}
}

void AudioPlayer::resumeSound(Sound& sound)
{
	if (_isSoundsEnabled)
	{
		if (_isSoundInChannelMap(sound))
		{
			Mix_Resume(_getUsedChannel(sound));
		}
		else
		{
			Logger::throwWarning("Trying to resume sound with ID \"", sound.getID(), "\", but was not paused!");
		}
	}
}

void AudioPlayer::stopSound(Sound& sound, int fadeMillis)
{
	if (_isSoundsEnabled)
	{
		if (_isSoundInChannelMap(sound))
		{
			if (isSoundPaused(sound))
			{
				resumeSound(sound);
				Mix_HaltChannel(_getUsedChannel(sound));
			}
			else
			{
				Mix_FadeOutChannel(_getUsedChannel(sound), fadeMillis);
			}
		}
		else
		{
			Logger::throwWarning("Trying to stop sound with ID \"", sound.getID(), "\", but was not playing!");
		}
	}
}

void AudioPlayer::_updateSoundVolume(Sound& sound)
{
	if (_isSoundsEnabled)
	{
		if (_isSoundInChannelMap(sound))
		{
			auto intVolume = static_cast<int>(sound.getVolume() * 128.0f);
			Mix_Volume(_getUsedChannel(sound), intVolume);
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

void AudioPlayer::setMusicEnabled(bool value)
{
	_isMusicEnabled = value;
}

void AudioPlayer::playMusic(vector<Music>& musicList, bool forcePlay)
{
	if (_isMusicEnabled)
	{
		// Check if any music is existing
		if (!musicList.empty())
		{
			// Check if music is allowed to play
			if (!Mix_PlayingMusic() || forcePlay)
			{
				// Select next song
				if (musicList.size() == 1)
				{
					Mix_PlayMusic(musicList[0].getDataPointer(), 0);
				}
				else
				{
					auto musicIndex = Tools::getInst().getRandomInt(0, musicList.size() - 1);
					Mix_PlayMusic(musicList[musicIndex].getDataPointer(), 0);
				}
			}
		}
	}
}

void AudioPlayer::pauseMusic()
{
	if (_isMusicEnabled)
	{
		Mix_PauseMusic();
	}
}

void AudioPlayer::resumeMusic()
{
	if (_isMusicEnabled)
	{
		Mix_ResumeMusic();
	}
}

void AudioPlayer::stopMusic()
{
	if (_isMusicEnabled)
	{
		Mix_HaltMusic();
	}
}

void AudioPlayer::setMusicVolume(float volume)
{
	if (_isMusicEnabled)
	{
		_musicVolume = std::clamp(volume, 0.0f, 1.0f);
	}
}

bool AudioPlayer::isSoundPlaying(Sound& sound)
{
	if (_isSoundsEnabled)
	{
		if (_isSoundInChannelMap(sound))
		{
			if (Mix_Playing(_getUsedChannel(sound)))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}

	return false;
}

bool AudioPlayer::isSoundPaused(Sound& sound)
{
	if (_isSoundsEnabled)
	{
		if (_isSoundInChannelMap(sound))
		{
			if (Mix_Paused(_getUsedChannel(sound)))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}

	return false;
}

bool AudioPlayer::isMusicPlaying()
{
	if (_isMusicEnabled)
	{
		return Mix_PlayingMusic();
	}

	return false;
}

bool AudioPlayer::isMusicPaused()
{
	if (_isMusicEnabled)
	{
		return Mix_PausedMusic();
	}

	return false;
}

float AudioPlayer::getMusicVolume()
{
	if (_isMusicEnabled)
	{
		return static_cast<float>(Mix_VolumeMusic(-1)) / 128.0f;
	}

	return -1.0f;
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

int AudioPlayer::_getUsedChannel(Sound& sound)
{
	for (auto& pair : _channelMap)
	{
		if (pair.second == sound.getID())
		{
			return pair.first;
		}
	}

	Logger::throwError("Trying to get sound channel with ID \"", sound.getID(), "\", but does not exist!");
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

	Logger::throwError("Not enough audio channels availible!");
}