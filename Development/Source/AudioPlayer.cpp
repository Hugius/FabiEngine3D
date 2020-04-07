#include <GLM/gtc/matrix_transform.hpp>
#include <algorithm>

#include <WE3D/AudioPlayer.hpp>
#include <WE3D/Logger.hpp>
#include <WE3D/Configuration.hpp>

AudioPlayer::AudioPlayer()
{
	// Allocate audio channels
	Mix_AllocateChannels(Config::getInst().getTotalAudioChannels());

	// Initialize audio channels to none
	for (int i = 0; i < Config::getInst().getTotalAudioChannels(); i++)
	{
		p_channelMap.insert(std::make_pair(i, ""));
	}
}

void AudioPlayer::update(CameraManager& camera, std::vector<AudioChunk>& chunks, std::vector<AudioMusic>& music, float delta)
{
	// Channel debugging
	if (p_debugging)
	{
		if (p_totalDelta >= 1000.0f)
		{
			p_totalDelta = 0.0f;
			system("cls");

			for (auto& element : p_channelMap)
			{
				Logger::getInst().throwDebug("Channel", std::to_string(element.first + 1), " : ", element.second);
			}
		}
		else
		{
			p_totalDelta += delta;
		}
	}

	// Update stopped playing
	for (auto& channelPair : p_channelMap)
	{
		if (!Mix_Playing(channelPair.first) && !Mix_Paused(channelPair.first)) // If audio stopped playing, but is not paused
		{
			channelPair.second = ""; // De-allocate channel
		}
	}

	// Update sound disable
	if (!p_soundEnabled)
	{
		Mix_HaltChannel(-1);
	}
	
	// Music
	if (p_musicEnabled)
	{
		if (!music.empty()) // Music added
		{
			if (!Mix_PlayingMusic()) // If music is not playing yet
			{
				// Select next song
				if (music.size() == 1)
				{
					p_musicIndex = 0;
				}
				else
				{
					srand((unsigned int)time(NULL));
					p_musicIndex = rand() % music.size();
				}

				// Play song
				Mix_PlayMusic(music[p_musicIndex].getMixMusic(), 0);
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
				Mix_SetPanning(p_getPair(chunk).first, leftStrength, rightStrength); // Apply stereo panning
			}
		}
	}
}

void AudioPlayer::setSoundEnabled(bool val)
{
	p_soundEnabled = val;
}

void AudioPlayer::setMusicEnabled(bool val)
{
	p_musicEnabled = val;
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
	if (p_soundEnabled)
	{
		if (p_isInMap(chunk)) // If already playing
		{
			if (!noRestart)
			{
				if (fadeMillis == 0)
				{
					Mix_PlayChannel(p_getPair(chunk).first, chunk.getMixChunk(), loops); // Play chunk again on same channel
				}
				else
				{
					Mix_FadeInChannel(p_getPair(chunk).first, chunk.getMixChunk(), loops, fadeMillis); // Fade in chunk again on same channel
				}
				setChunkVolume(chunk, initialVolume);
			}
		}
		else // If not playing yet
		{
			int channel = p_getFreeChannel(); // Allocate new channel

			if (fadeMillis == 0)
			{
				Mix_PlayChannel(channel, chunk.getMixChunk(), loops); // Play chunk
			}
			else
			{
				Mix_FadeInChannel(channel, chunk.getMixChunk(), loops, fadeMillis); // Fade in chunk
			}

			p_channelMap[channel] = chunk.getID(); // Assign to new channel
			setChunkVolume(chunk, initialVolume);
		}
	}
}

void AudioPlayer::pauseChunk(AudioChunk& chunk)
{
	if (p_isInMap(chunk))
	{
		Mix_Pause(p_getPair(chunk).first); // Pause chunk
	}
	else
	{
		Logger::getInst().throwWarning("Trying to pause audio chunk with ID \'", chunk.getID(), " \', but was not playing!"); // Warning
	}
}

void AudioPlayer::resumeChunk(AudioChunk& chunk)
{
	if (p_isInMap(chunk))
	{
		Mix_Resume(p_getPair(chunk).first); // Resume chunk
	}
	else
	{
		Logger::getInst().throwWarning("Trying to resume audio chunk with ID \'", chunk.getID(), " \', but was not paused!"); // Warning
	}
}

void AudioPlayer::stopChunk(AudioChunk& chunk, int fadeMillis)
{
	if (p_isInMap(chunk))
	{
		Mix_FadeOutChannel(p_getPair(chunk).first, fadeMillis); // Stop chunk
	}
	else
	{
		Logger::getInst().throwWarning("Trying to stop audio chunk with ID \'", chunk.getID(), " \', but was not playing!"); // Warning
	}
}

void AudioPlayer::setChunkVolume(AudioChunk& chunk, int volume)
{
	if (p_isInMap(chunk))
	{
		Mix_Volume(p_getPair(chunk).first, volume); // Set volume
	}
	else
	{
		Logger::getInst().throwWarning("Trying to set volume of audio chunk with ID \'", chunk.getID(), " \', but was not playing!"); // Warning
	}
}

void AudioPlayer::setMusicVolume(int volume)
{
	Mix_VolumeMusic(volume);
}

void AudioPlayer::setChannelDebugging(bool val)
{
	p_debugging = val;
}

bool AudioPlayer::isPlaying(AudioChunk& chunk)
{
	if (p_isInMap(chunk))
	{
		if (Mix_Playing(p_getPair(chunk).first))
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
	if (p_isInMap(chunk))
	{
		return Mix_Volume(p_getPair(chunk).first, -1); // Get volume
	}
	else
	{
		Logger::getInst().throwWarning("Trying to get volume of audio chunk with ID \'", chunk.getID(), " \', but was not playing!"); // Warning
	}
}

int AudioPlayer::getUsedChannelCount()
{
	int count = 0;

	for (auto& element : p_channelMap)
	{
		if (element.second != "")
		{
			count++; // Count amount of currently used channels
		}
	}

	return count;
}

std::pair<const int, string>& AudioPlayer::p_getPair(AudioChunk& chunk)
{
	for (auto& pair : p_channelMap)
	{
		if (pair.second == chunk.getID())
		{
			return pair; // If chunk found, return
		}
	}

	Logger::getInst().throwError("Trying to get audio chunk pair with ID \'", chunk.getID(), " \', but does not exist!"); // Error
}

bool AudioPlayer::p_isInMap(AudioChunk& chunk)
{
	for (auto& pair : p_channelMap)
	{
		if (pair.second == chunk.getID())
		{
			return true; // Chunk found
		}
	}

	return false; // Chunk not found
}

int AudioPlayer::p_getFreeChannel()
{
	for (auto& element : p_channelMap)
	{
		if (element.second == "")
		{
			return element.first; // Get first free channel
		}
	}

	Logger::getInst().throwError("Not enough audio channels availible!"); // Error
}