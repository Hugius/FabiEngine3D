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

void AudioPlayer::update(CameraManager& camera, vector<AudioChunk>& chunkList, vector<AudioMusic>& musicList)
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

	// Update chunks
	if (_chunksEnabled)
	{
		for (auto& chunk : chunkList)
		{
			// Check if 3D chunk
			if (chunk.is3D())
			{
				// Check if emitting sound
				if (isChunkPlaying(chunk))
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
	else
	{
		Mix_HaltChannel(-1);
	}

	// Update music playlist
	if (_musicEnabled)
	{
		playMusic(musicList);
	}
	else
	{
		Mix_HaltMusic();
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

void AudioPlayer::playChunk(AudioChunk& chunk, int loops)
{
	if (_chunksEnabled)
	{
		if (_isInMap(chunk))
		{
			Mix_PlayChannel(_getChunkChannel(chunk), chunk.getMixChunk(), loops); // Play chunk again on same channel
		}
		else
		{
			int channel = _getFreeChannel();
			Mix_PlayChannel(channel, chunk.getMixChunk(), loops); // Play chunk on new channel
			_channelMap[channel] = chunk.getID();
		}
	}
}

void AudioPlayer::pauseChunk(AudioChunk& chunk)
{
	if (_isInMap(chunk))
	{
		Mix_Pause(_getChunkChannel(chunk));
	}
	else
	{
		Logger::throwWarning("Trying to pause audio chunk with ID \"", chunk.getID(), " \", but was not playing!");
	}
}

void AudioPlayer::resumeChunk(AudioChunk& chunk)
{
	if (_isInMap(chunk))
	{
		Mix_Resume(_getChunkChannel(chunk));
	}
	else
	{
		Logger::throwWarning("Trying to resume audio chunk with ID \'", chunk.getID(), " \', but was not paused!");
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
			Mix_FadeOutChannel(_getChunkChannel(chunk), fadeMillis);
		}
	}
	else
	{
		Logger::throwWarning("Trying to stop audio chunk with ID \'", chunk.getID(), " \', but was not playing!");
	}
}

void AudioPlayer::setChunkVolume(AudioChunk& chunk, int volume)
{
	if (_isInMap(chunk))
	{
		Mix_Volume(_getChunkChannel(chunk), volume);
	}
	else
	{
		Logger::throwWarning("Trying to set volume of audio chunk with ID \'", chunk.getID(), " \', but was not playing!");
	}
}

void AudioPlayer::setMusicEnabled(bool value)
{
	_musicEnabled = value;
}

void AudioPlayer::playMusic(vector<AudioMusic>& musicList)
{
	// Check if any music is existing
	if (!musicList.empty())
	{
		// Check if music is not playing yet
		if (!Mix_PlayingMusic())
		{
			// Select next song
			if (musicList.size() == 1)
			{
				Mix_PlayMusic(musicList[0].getMixMusic(), 0);
			}
			else
			{
				auto musicIndex = Tools::getInst().getRandomInt(0, musicList.size() - 1);
				Mix_PlayMusic(musicList[musicIndex].getMixMusic(), 0);
			}
		}
	}
}

void AudioPlayer::stopMusic()
{
	Mix_HaltMusic();
}

void AudioPlayer::setMusicVolume(int volume)
{
	Mix_VolumeMusic(volume);
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
		return Mix_Volume(_getChunkChannel(chunk), -1);
	}
	else
	{
		Logger::throwWarning("Trying to get volume of audio chunk with ID \'", chunk.getID(), " \', but was not playing!");
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
			count++;
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
			return pair.first;
		}
	}

	Logger::throwError("Trying to get audio chunk channel with ID \'", chunk.getID(), " \', but does not exist!");
}

bool AudioPlayer::_isInMap(AudioChunk& chunk)
{
	for (auto& pair : _channelMap)
	{
		if (pair.second == chunk.getID())
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