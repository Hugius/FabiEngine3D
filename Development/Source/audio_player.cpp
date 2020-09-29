#include "audio_player.hpp"
#include "logger.hpp"
#include "configuration.hpp"

#include <GLM\\gtc\\matrix_transform.hpp>
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
	for (int i = 0; i < count; i++)
	{
		_channelMap.insert(std::make_pair(i, ""));
	}
}

void AudioPlayer::update(CameraManager& camera, std::vector<AudioChunk>& chunks, std::vector<AudioMusic>& music)
{
	// Channel debugging
	if (_debugging)
	{
		system("cls");

		for (auto& element : _channelMap)
		{
			Logger::throwDebug("Channel", std::to_string(element.first + 1), " : ", element.second);
		}
	}

	// Update stopped playing
	for (auto& channelPair : _channelMap)
	{
		if (!Mix_Playing(channelPair.first) && !Mix_Paused(channelPair.first)) // If audio stopped playing, but is not paused
		{
			channelPair.second = ""; // De-allocate channel
		}
	}

	// Update sound disable
	if (!_soundEnabled)
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
		if (chunk.hasPosition())
		{
			if (isPlaying(chunk)) // If emitting sound
			{
				// Distance
				auto cameraPos = camera.getPosition(); // Camera position
				float xDiff = fabsf(chunk.getPosition().x - cameraPos.x); // Difference between camera X & point X
				float yDiff = fabsf(chunk.getPosition().y - cameraPos.y); // Difference between camera Y & point Y
				float zDiff = fabsf(chunk.getPosition().z - cameraPos.z); // Difference between camera Z & point Z
				float maxDiff = max(xDiff, max(yDiff, zDiff)); // Maximum difference
				float volume = 128.0f - ((maxDiff / chunk.getMaxDistance()) * 128.0f); // Calculate volume
				volume = std::clamp(volume, 0.0f, 128.0f); // Clamp to minimum and maximum
				setChunkVolume(chunk, int(volume)); // Apply volume

				// Panning
				auto cameraFront = camera.getFront(); // From camera vector
				mat4 rotationMatrix(1.0f); // Identity matrix
				rotationMatrix = glm::rotate(rotationMatrix, glm::radians(90.0f), vec3(0.0f, 1.0f, 0.0f)); // 90 degrees rotation
				vec3 pointVector = cameraPos - chunk.getPosition(); // To camera vector
				pointVector = vec3(rotationMatrix * glm::vec4(pointVector, 1.0f)); // Rotate direction
				pointVector = glm::normalize(pointVector); // Normalize
				float dot = glm::dot(pointVector, cameraFront); // Dot product
				float range = (dot / 2.0f) + 0.5f; // Convert (-1 to 1) scale to (0.0f to 1.0f) scale
				Uint8 leftStrength = Uint8(255.0f * range); // Left ear
				Uint8 rightStrength = Uint8(255.0f - (255.0f * range)); // Right ear
				Mix_SetPanning(_getPair(chunk).first, leftStrength, rightStrength); // Apply stereo panning
			}
		}
	}
}

void AudioPlayer::setSoundEnabled(bool val)
{
	_soundEnabled = val;
}

void AudioPlayer::setMusicEnabled(bool val)
{
	_musicEnabled = val;
}

void AudioPlayer::stopAllSounds()
{
	Mix_HaltChannel(-1);
}

void AudioPlayer::stopAllMusic()
{
	Mix_HaltMusic();
}

void AudioPlayer::playChunk(AudioChunk& chunk, int loops, int initialVolume, bool noRestart, int fadeMillis)
{
	if (_soundEnabled)
	{
		if (_isInMap(chunk)) // If already playing
		{
			if (!noRestart)
			{
				if (fadeMillis == 0)
				{
					Mix_PlayChannel(_getPair(chunk).first, chunk.getMixChunk(), loops); // Play chunk again on same channel
				}
				else
				{
					Mix_FadeInChannel(_getPair(chunk).first, chunk.getMixChunk(), loops, fadeMillis); // Fade in chunk again on same channel
				}
				setChunkVolume(chunk, initialVolume);
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
			setChunkVolume(chunk, initialVolume);
		}
	}
}

void AudioPlayer::pauseChunk(AudioChunk& chunk)
{
	if (_isInMap(chunk))
	{
		Mix_Pause(_getPair(chunk).first); // Pause chunk
	}
	else
	{
		Logger::throwWarning("Trying to pause audio chunk with ID \'", chunk.getID(), " \', but was not playing!"); // Warning
	}
}

void AudioPlayer::resumeChunk(AudioChunk& chunk)
{
	if (_isInMap(chunk))
	{
		Mix_Resume(_getPair(chunk).first); // Resume chunk
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
		Mix_FadeOutChannel(_getPair(chunk).first, fadeMillis); // Stop chunk
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
		Mix_Volume(_getPair(chunk).first, volume); // Set volume
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

void AudioPlayer::setChannelDebugging(bool val)
{
	_debugging = val;
}

bool AudioPlayer::isPlaying(AudioChunk& chunk)
{
	if (_isInMap(chunk))
	{
		if (Mix_Playing(_getPair(chunk).first))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

int AudioPlayer::getVolume(AudioChunk& chunk)
{
	if (_isInMap(chunk))
	{
		return Mix_Volume(_getPair(chunk).first, -1); // Get volume
	}
	else
	{
		Logger::throwWarning("Trying to get volume of audio chunk with ID \'", chunk.getID(), " \', but was not playing!"); // Warning
	}
}

int AudioPlayer::getUsedChannelCount()
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

int AudioPlayer::getAllocatedChannelCount()
{
	return _channelMap.size();
}

std::pair<const int, string>& AudioPlayer::_getPair(AudioChunk& chunk)
{
	for (auto& pair : _channelMap)
	{
		if (pair.second == chunk.getID())
		{
			return pair; // If chunk found, return
		}
	}

	Logger::throwError("Trying to get audio chunk pair with ID \'", chunk.getID(), " \', but does not exist!"); // Error
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