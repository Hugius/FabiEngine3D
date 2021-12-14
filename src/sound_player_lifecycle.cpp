#include "sound_player.hpp"
#include "logger.hpp"

using std::clamp;
using std::max;

SoundPlayer::SoundPlayer()
{
	Mix_AllocateChannels(0);
}

void SoundPlayer::update(Camera& camera, vector<Sound2d>& sound2ds, vector<Sound3d>& sound3ds)
{
	// Update 2D sounds
	for(auto& sound : sound2ds)
	{
		// Update sound volume
		_updateSound2dVolume(sound);
	}

	// Update 3D sounds
	for(auto& sound : sound3ds)
	{
		// Check if sound is started
		if(isSound3dStarted(sound))
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
		_updateSound3dVolume(sound);
	}

	// Update channels
	for (size_t i = 0; i < _channels.size(); i++)
	{
		// Check if sound stopped playing
		if (!Mix_Playing(static_cast<int>(i)) && !Mix_Paused(static_cast<int>(i)))
		{
			// De-allocate channel
			_channels[i] = "";
		}
	}
}