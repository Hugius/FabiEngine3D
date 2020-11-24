#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

#include <algorithm>

void FabiEngine3D::audioEntity_deleteAll()
{
	audioEntity_stopAll();
	_core->_audioManager.deleteAllChunks();
}

void FabiEngine3D::audioEntity_stopAll()
{
	_core->_audioPlayer.stopAllChunks();
}

void FabiEngine3D::music_addToPlaylist(const std::string& fileName)
{
	_core->_audioManager.addMusic(fileName);
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

void FabiEngine3D::music_deleteAll()
{
	_core->_audioPlayer.stopMusic();
	_core->_audioManager.deleteMusic();
}

void FabiEngine3D::music_setVolume(float volume)
{
	volume = std::clamp(volume, 0.0f, 1.0f);
	_core->_audioPlayer.setMusicVolume(static_cast<int>(volume * 128.0f));
}

void FabiEngine3D::audioEntity_add2D(const std::string& ID, const std::string& fileName)
{
	_core->_audioManager.add2D(ID, fileName);
}

void FabiEngine3D::audioEntity_add3D(const std::string& ID, const std::string& fileName, Vec3 position, float maxVolume, float maxDistance)
{
	_core->_audioManager.add3D(ID, fileName, position, maxVolume, maxDistance);
}

void FabiEngine3D::audioEntity_delete(const std::string& ID)
{
	if (_core->_audioManager.isChunkExisting(ID)) // If chunk exists
	{
		if (_core->_audioPlayer.isChunkPlaying(_core->_audioManager.getChunk(ID))) // If chunk is playing
		{
			_core->_audioPlayer.stopChunk(_core->_audioManager.getChunk(ID), 0);
		}
	}

	_core->_audioManager.deleteChunk(ID);
}

void FabiEngine3D::audioEntity_play(const std::string& ID, int loops, float initialVolume, bool noRestart, int fadeMillis)
{
	initialVolume = std::clamp(initialVolume, 0.0f, 1.0f);
	_core->_audioPlayer.playChunk(_core->_audioManager.getChunk(ID), loops, static_cast<int>(initialVolume * 128.0f), noRestart, fadeMillis);
}

void FabiEngine3D::audioEntity_pause(const std::string& ID)
{
	_core->_audioPlayer.pauseChunk(_core->_audioManager.getChunk(ID));
}

void FabiEngine3D::audioEntity_resume(const std::string& ID)
{
	_core->_audioPlayer.resumeChunk(_core->_audioManager.getChunk(ID));
}

void FabiEngine3D::audioEntity_stop(const std::string& ID, int fadeMillis)
{
	_core->_audioPlayer.stopChunk(_core->_audioManager.getChunk(ID), fadeMillis);
}

void FabiEngine3D::audioEntity_setVolume(const std::string& ID, float volume)
{
	volume = std::clamp(volume, 0.0f, 1.0f);
	_core->_audioPlayer.setChunkVolume(_core->_audioManager.getChunk(ID), static_cast<int>(volume * 128.0f));
}

void FabiEngine3D::audioEntity_setPosition(const std::string& ID, Vec3 position)
{
	_core->_audioManager.getChunk(ID).setPosition(position);
}

void FabiEngine3D::audioEntity_setMaxDistance(const std::string& ID, float maxDistance)
{
	_core->_audioManager.getChunk(ID).setMaxDistance(maxDistance);
}

void FabiEngine3D::audioEntity_setMaxVolume(const string& ID, float volume)
{
	volume = std::clamp(volume, 0.0f, 1.0f);
	_core->_audioManager.getChunk(ID).setMaxVolume(volume);
}

vector<string> FabiEngine3D::audioEntity_getAllIDs()
{
	vector<string> IDs;

	for (auto chunk : _core->_audioManager.getChunks())
	{
		IDs.push_back(chunk.getID());
	}

	return IDs;
}

string FabiEngine3D::audioEntity_getFilePath(const std::string& ID)
{
	return _core->_audioManager.getChunk(ID).getFilePath();
}

Vec3 FabiEngine3D::audioEntity_getPosition(const string& ID)
{
	return _core->_audioManager.getChunk(ID).getPosition();
}

float FabiEngine3D::audioEntity_getMaxDistance(const string& ID)
{
	return _core->_audioManager.getChunk(ID).getMaxDistance();
}

bool FabiEngine3D::audioEntity_isExisting(const std::string& ID)
{
	return _core->_audioManager.isChunkExisting(ID);
}

bool FabiEngine3D::audioEntity_isPlaying(const std::string& ID)
{
	auto chunk = _core->_audioManager.getChunk(ID);

	return _core->_audioPlayer.isChunkPlaying(chunk) && !_core->_audioPlayer.isChunkPaused(chunk);
}

bool FabiEngine3D::audioEntity_isPaused(const std::string& ID)
{
	return _core->_audioPlayer.isChunkPaused(_core->_audioManager.getChunk(ID));;
}

float FabiEngine3D::audioEntity_getVolume(const std::string& ID)
{
	int volume = _core->_audioPlayer.getChunkVolume(_core->_audioManager.getChunk(ID));
	return static_cast<float>(volume) / 128.0f;
}

float FabiEngine3D::audioEntity_getMaxVolume(const string& ID)
{
	return _core->_audioManager.getChunk(ID).getMaxVolume();
}

int FabiEngine3D::audioEntity_getUsedChannelCount()
{
	return _core->_audioPlayer.getUsedChannelCount();
}

void FabiEngine3D::sound_setAudioEnabled(bool enabled)
{
	_core->_audioPlayer.setChunksEnabled(enabled);
}

void FabiEngine3D::sound_setMusicEnabled(bool enabled)
{
	_core->_audioPlayer.setMusicEnabled(enabled);
}

void FabiEngine3D::sound_setMaxChannels(int count)
{
	_core->_audioPlayer.allocateChannels(count);
}

int FabiEngine3D::sound_getMaxChannels()
{
	return _core->_audioPlayer.getAllocatedChannelCount();
}