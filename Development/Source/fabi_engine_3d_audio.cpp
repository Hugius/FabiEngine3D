#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

#include <algorithm>

void FabiEngine3D::soundEntity_deleteAll()
{
	soundEntity_stopAll();
	_core->_audioManager.deleteAllChunks();
}

void FabiEngine3D::soundEntity_stopAll()
{
	soundEntity_resumeAll();
	_core->_audioPlayer.stopAllChunks();
}

void FabiEngine3D::music_addToPlaylist(const std::string& fileName)
{
	_core->_audioManager.addMusic(fileName);
	_core->_audioPlayer.playMusic(_core->_audioManager.getMusic(), true);
}

void FabiEngine3D::music_pause()
{
	_core->_audioPlayer.pauseMusic();
}

void FabiEngine3D::music_resume()
{
	_core->_audioPlayer.resumeMusic();
}

bool FabiEngine3D::music_isPlaying()
{
	return _core->_audioPlayer.isMusicPlaying() && !_core->_audioPlayer.isMusicPaused();
}

bool FabiEngine3D::music_isPaused()
{
	return _core->_audioPlayer.isMusicPaused();
}

float FabiEngine3D::music_getVolume()
{
	return static_cast<float>(_core->_audioPlayer.getMusicVolume()) / 128.0f;
}

void FabiEngine3D::music_clearPlaylist()
{
	// Resume before stopping
	if (music_isPaused())
	{
		music_resume();
	}

	_core->_audioPlayer.stopMusic();
	_core->_audioManager.deleteMusic();
}

void FabiEngine3D::music_setVolume(float volume)
{
	volume = std::clamp(volume, 0.0f, 1.0f);
	_core->_audioPlayer.setMusicVolume(static_cast<int>(volume * 128.0f));
}

void FabiEngine3D::soundEntity_add2D(const std::string& ID, const std::string& fileName)
{
	_core->_audioManager.add2D(ID, fileName);
}

void FabiEngine3D::soundEntity_add3D(const std::string& ID, const std::string& fileName, Vec3 position, float maxVolume, float maxDistance)
{
	_core->_audioManager.add3D(ID, fileName, position, maxVolume, maxDistance);
}

void FabiEngine3D::soundEntity_delete(const std::string& ID)
{
	// Check if chunk exists
	if (_core->_audioManager.isChunkExisting(ID))
	{
		// Check if chunk is playing
		if (_core->_audioPlayer.isChunkPlaying(_core->_audioManager.getChunk(ID)))
		{
			// Resume playback if paused
			if (_core->_audioPlayer.isChunkPaused(_core->_audioManager.getChunk(ID)))
			{
				_core->_audioPlayer.resumeChunk(_core->_audioManager.getChunk(ID));
			}

			// Stop playback
			_core->_audioPlayer.stopChunk(_core->_audioManager.getChunk(ID), 0);
		}
	}

	// Delete audio chunk
	_core->_audioManager.deleteChunk(ID);
}

void FabiEngine3D::soundEntity_play(const std::string& ID, int loops, float initialVolume)
{
	// Retrieve values
	auto chunk = _core->_audioManager.getChunk(ID);
	initialVolume = std::clamp(initialVolume, 0.0f, 1.0f);
	auto volume = static_cast<int>(initialVolume * 128.0f);

	// Play chunk
	_core->_audioPlayer.playChunk(chunk, loops);

	// Set initial or maximum volume
	if (chunk.is3D())
	{
		chunk.setMaxVolume(volume);
	}
	else
	{
		_core->_audioPlayer.setChunkVolume(chunk, volume);
	}
}

void FabiEngine3D::soundEntity_pause(const std::string& ID)
{
	_core->_audioPlayer.pauseChunk(_core->_audioManager.getChunk(ID));
}

void FabiEngine3D::soundEntity_pauseAll()
{
	_core->_audioPlayer.pauseAllChunks();
}

void FabiEngine3D::soundEntity_resume(const std::string& ID)
{
	_core->_audioPlayer.resumeChunk(_core->_audioManager.getChunk(ID));
}

void FabiEngine3D::soundEntity_resumeAll()
{
	_core->_audioPlayer.resumeAllChunks();
}

void FabiEngine3D::soundEntity_stop(const std::string& ID, int fadeMillis)
{
	// Resume playback if paused
	if (_core->_audioPlayer.isChunkPaused(_core->_audioManager.getChunk(ID)))
	{
		_core->_audioPlayer.resumeChunk(_core->_audioManager.getChunk(ID));
	}

	// Stop playback
	_core->_audioPlayer.stopChunk(_core->_audioManager.getChunk(ID), fadeMillis);
}

void FabiEngine3D::soundEntity_setVolume(const std::string& ID, float volume)
{
	volume = std::clamp(volume, 0.0f, 1.0f);
	_core->_audioPlayer.setChunkVolume(_core->_audioManager.getChunk(ID), static_cast<int>(volume * 128.0f));
}

void FabiEngine3D::soundEntity_setPosition(const std::string& ID, Vec3 position)
{
	_core->_audioManager.getChunk(ID).setPosition(position);
}

void FabiEngine3D::soundEntity_move(const string& ID, Vec3 factor)
{
	_core->_audioManager.getChunk(ID).translate(factor);
}

void FabiEngine3D::soundEntity_setMaxDistance(const std::string& ID, float maxDistance)
{
	_core->_audioManager.getChunk(ID).setMaxDistance(maxDistance);
}

void FabiEngine3D::soundEntity_setMaxVolume(const string& ID, float volume)
{
	volume = std::clamp(volume, 0.0f, 1.0f);
	_core->_audioManager.getChunk(ID).setMaxVolume(volume);
}

vector<string> FabiEngine3D::soundEntity_getAllIDs()
{
	vector<string> IDs;

	for (auto chunk : _core->_audioManager.getChunks())
	{
		IDs.push_back(chunk.getID());
	}

	return IDs;
}

string FabiEngine3D::soundEntity_getFilePath(const std::string& ID)
{
	return _core->_audioManager.getChunk(ID).getFilePath();
}

Vec3 FabiEngine3D::soundEntity_getPosition(const string& ID)
{
	return _core->_audioManager.getChunk(ID).getPosition();
}

float FabiEngine3D::soundEntity_getMaxDistance(const string& ID)
{
	return _core->_audioManager.getChunk(ID).getMaxDistance();
}

bool FabiEngine3D::soundEntity_isExisting(const std::string& ID)
{
	return _core->_audioManager.isChunkExisting(ID);
}

bool FabiEngine3D::soundEntity_isPlaying(const std::string& ID)
{
	auto chunk = _core->_audioManager.getChunk(ID);

	return _core->_audioPlayer.isChunkPlaying(chunk) && !_core->_audioPlayer.isChunkPaused(chunk);
}

bool FabiEngine3D::soundEntity_isPaused(const std::string& ID)
{
	return _core->_audioPlayer.isChunkPaused(_core->_audioManager.getChunk(ID));;
}

bool FabiEngine3D::soundEntity_isLoaded(const string& ID)
{
	return (_core->_audioManager.getChunk(ID).getMixChunk() != nullptr);
}

bool FabiEngine3D::soundEntity_is3D(const string& ID)
{
	return _core->_audioManager.getChunk(ID).is3D();
}

float FabiEngine3D::soundEntity_getVolume(const std::string& ID)
{
	int volume = _core->_audioPlayer.getChunkVolume(_core->_audioManager.getChunk(ID));
	return static_cast<float>(volume) / 128.0f;
}

float FabiEngine3D::soundEntity_getMaxVolume(const string& ID)
{
	return _core->_audioManager.getChunk(ID).getMaxVolume();
}

int FabiEngine3D::soundEntity_getUsedChannelCount()
{
	return _core->_audioPlayer.getUsedChannelCount();
}