#include "audio_player.hpp"
#include "logger.hpp"
#include "configuration.hpp"

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

void AudioPlayer::update(CameraManager& camera, std::vector<AudioChunk>& chunks, std::vector<AudioMusic>& music)
{
	// Update stopped playing
	for (auto& channelPair : _channelMap)
	{
		if (!Mix_Playing(channelPair.first) && !Mix_Paused(channelPair.first)) // If audio stopped playing, but is not paused
		{
			channelPair.second = ""; // De-allocate channel
		}
	}

	// Update sound disable
	if (!_chunksEnabled)
	{
		Mix_HaltChannel(-1);
	}
	
	// Music
	if (_musicEnabled)
	{
		if (!music.empty()) // Music added
		{
			if (!Mix_PlayingMusic()) // If music is not playing yet
			{
				// Select next song
				if (music.size() == 1)
				{
					_musicIndex = 0;
				}
				else
				{
					srand((unsigned int)time(NULL));
					_musicIndex = rand() % music.size();
				}

				// Play song
				Mix_PlayMusic(music[_musicIndex].getMixMusic(), 0);
			}
		}
		else // No music added
		{
			if (Mix_PlayingMusic()) // If music still playing
			{
				Mix_HaltMusic(); // Stop playng
			}
		}
	}
	else
	{
		Mix_HaltMusic();
	}

	// Update point chunks
	for (auto& chunk : chunks)
	{
		if (chunk.is3D())
		{
			if (isChunkPlaying(chunk)) // If emitting sound
			{
				// Distance
				auto cameraPos = camera.getPosition(); // Camera position
				float xDiff = fabsf(chunk.getPosition().x - cameraPos.x); // Difference between camera X & point X
				float yDiff = fabsf(chunk.getPosition().y - cameraPos.y); // Difference between camera Y & point Y
				float zDiff = fabsf(chunk.getPosition().z - cameraPos.z); // Difference between camera Z & point Z
				float maxDiff = std::max(xDiff, std::max(yDiff, zDiff)); // Maximum difference
				float volume = chunk.getMaxVolume() - ((maxDiff / chunk.getMaxDistance()) * chunk.getMaxVolume()); // Calculate volume
				volume = std::clamp(volume, 0.0f, chunk.getMaxVolume()); // Clamp to minimum and maximum
				setChunkVolume(chunk, static_cast<int>(volume * 128.0f)); // Apply volume

				// Panning
				auto cameraFront = camera.getFront(); // From camera vector
				Matrix44 rotationMatrix = Matrix44::createRotationY(Math::degreesToRadians(90.0f));
				Vec3 pointVector = cameraPos - chunk.getPosition(); // To camera vector
				Vec4 result = rotationMatrix * Vec4(pointVector.x, pointVector.y, pointVector.z, 1.0f);
				pointVector = Vec3(result.x, result.y, result.z); // Rotate direction
				pointVector.normalize(); // Normalize
				float dot = pointVector.dot(cameraFront); // Dot product
				float range = (dot / 2.0f) + 0.5f; // Convert (-1 to 1) scale to (0.0f to 1.0f) scale
				Uint8 leftStrength = Uint8(255.0f * range); // Left ear
				Uint8 rightStrength = Uint8(255.0f - (255.0f * range)); // Right ear
				Mix_SetPanning(_getChunkChannel(chunk), leftStrength, rightStrength); // Apply stereo panning
			}
		}
	}
}

void AudioPlayer::setChunksEnabled(bool value)
{
	_chunksEnabled = value;
}

void AudioPlayer::pauseAllChunks()
{
	Mix_Pause(-1);
}

void AudioPlayer::resumeAllChunks()
{
	Mix_Resume(-1);
}

void AudioPlayer::setMusicEnabled(bool value)
{
	_musicEnabled = value;
}

void AudioPlayer::pauseMusic()
{
	Mix_PauseMusic();
}

void AudioPlayer::resumeMusic()
{
	Mix_ResumeMusic();
}

void AudioPlayer::stopAllChunks()
{
	Mix_HaltChannel(-1);
}

void AudioPlayer::playChunk(AudioChunk& chunk, int loops, int initialVolume, bool noRestart, int fadeMillis)
{
	if (_chunksEnabled)
	{
		// 3D chunks have volume based on distance
		if (chunk.is3D())
		{
			initialVolume = 0;
		}

		if (_isInMap(chunk)) // If already playing
		{
			if (!noRestart)
			{
				if (fadeMillis == 0)
				{
					Mix_PlayChannel(_getChunkChannel(chunk), chunk.getMixChunk(), loops); // Play chunk again on same channel
				}
				else
				{
					Mix_FadeInChannel(_getChunkChannel(chunk), chunk.getMixChunk(), loops, fadeMillis); // Fade in chunk again on same channel
				}

				setChunkVolume(chunk, initialVolume); // Set volume
			}
		}
		else // If not playing yet
		{
			int channel = _getFreeChannel(); // Allocate new channel

			if (fadeMillis == 0)
			{
				Mix_PlayChannel(channel, chunk.getMixChunk(), loops); // Play chunk
			}
			else
			{
				Mix_FadeInChannel(channel, chunk.getMixChunk(), loops, fadeMillis); // Fade in chunk
			}

			_channelMap[channel] = chunk.getID(); // Assign to new channel

			setChunkVolume(chunk, initialVolume); // Set volume
		}
	}
}

void AudioPlayer::pauseChunk(AudioChunk& chunk)
{
	if (_isInMap(chunk))
	{
		Mix_Pause(_getChunkChannel(chunk)); // Pause chunk
	}
	else
	{
		Logger::throwWarning("Trying to pause audio chunk with ID \"", chunk.getID(), " \", but was not playing!"); // Warning
	}
}

void AudioPlayer::resumeChunk(AudioChunk& chunk)
{
	if (_isInMap(chunk))
	{
		Mix_Resume(_getChunkChannel(chunk)); // Resume chunk
	}
	else
	{
		Logger::throwWarning("Trying to resume audio chunk with ID \'", chunk.getID(), " \', but was not paused!"); // Warning
	}
}

void AudioPlayer::stopChunk(AudioChunk& chunk, int fadeMillis)
{
	if (_isInMap(chunk))
	{
		if (isChunkPaused(chunk))
		{
			resumeChunk(chunk);
			Mix_HaltChannel(_getChunkChannel(chunk));
		}
		else
		{
			Mix_FadeOutChannel(_getChunkChannel(chunk), fadeMillis); // Stop chunk
		}
	}
	else
	{
		Logger::throwWarning("Trying to stop audio chunk with ID \'", chunk.getID(), " \', but was not playing!"); // Warning
	}
}

void AudioPlayer::setChunkVolume(AudioChunk& chunk, int volume)
{
	if (_isInMap(chunk))
	{
		Mix_Volume(_getChunkChannel(chunk), volume); // Set volume
	}
	else
	{
		Logger::throwWarning("Trying to set volume of audio chunk with ID \'", chunk.getID(), " \', but was not playing!"); // Warning
	}
}

void AudioPlayer::setMusicVolume(int volume)
{
	Mix_VolumeMusic(volume);
}

void AudioPlayer::stopMusic()
{
	Mix_HaltMusic();
}

bool AudioPlayer::isChunkPlaying(AudioChunk& chunk)
{
	if (_isInMap(chunk))
	{
		if (Mix_Playing(_getChunkChannel(chunk)))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	return false;
}

bool AudioPlayer::isChunkPaused(AudioChunk& chunk)
{
	if (_isInMap(chunk))
	{
		if (Mix_Paused(_getChunkChannel(chunk)))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	return false;
}

bool AudioPlayer::isMusicPlaying()
{
	return Mix_PlayingMusic();
}

bool AudioPlayer::isMusicPaused()
{
	return Mix_PausedMusic();
}

int AudioPlayer::getChunkVolume(AudioChunk& chunk)
{
	if (_isInMap(chunk))
	{
		return Mix_Volume(_getChunkChannel(chunk), -1); // Get volume
	}
	else
	{
		Logger::throwWarning("Trying to get volume of audio chunk with ID \'", chunk.getID(), " \', but was not playing!"); // Warning
	}

	return -1;
}

int AudioPlayer::getMusicVolume()
{
	return Mix_VolumeMusic(-1);
}

unsigned int AudioPlayer::getUsedChannelCount()
{
	int count = 0;

	for (auto& element : _channelMap)
	{
		if (element.second != "")
		{
			count++; // Count amount of currently used channels
		}
	}

	return count;
}

unsigned int AudioPlayer::getAllocatedChannelCount()
{
	return _channelMap.size();
}

int AudioPlayer::_getChunkChannel(AudioChunk& chunk)
{
	for (auto& pair : _channelMap)
	{
		if (pair.second == chunk.getID())
		{
			return pair.first; // If chunk found, return channel
		}
	}

	Logger::throwError("Trying to get audio chunk channel with ID \'", chunk.getID(), " \', but does not exist!"); // Error
}

bool AudioPlayer::_isInMap(AudioChunk& chunk)
{
	for (auto& pair : _channelMap)
	{
		if (pair.second == chunk.getID())
		{
			return true; // Chunk found
		}
	}

	return false; // Chunk not found
}

int AudioPlayer::_getFreeChannel()
{
	for (auto& element : _channelMap)
	{
		if (element.second == "")
		{
			return element.first; // Get first free channel
		}
	}

	Logger::throwError("Not enough audio channels availible!"); // Error
}