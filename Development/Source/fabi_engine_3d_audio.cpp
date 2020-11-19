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

int FabiEngine3D::music_getVolume()
{
	return _core->_audioPlayer.getMusicVolume();
}

void FabiEngine3D::music_deleteAll()
{
	_core->_audioPlayer.stopMusic();
	_core->_audioManager.deleteMusic();
}

void FabiEngine3D::music_setVolume(int volume)
{
	volume = std::clamp(volume, 0, 100);
	_core->_audioPlayer.setMusicVolume(int((float(volume) / 100.0f) * 128.0f));
}

void FabiEngine3D::audioEntity_addGlobal(const std::string& ID, const std::string& fileName)
{
	_core->_audioManager.addGlobalChunk(ID, fileName);
}

void FabiEngine3D::audioEntity_addPoint(const std::string& ID, const std::string& fileName, vec3 position, float maxDistance)
{
	_core->_audioManager.addPointChunk(ID, fileName, position, maxDistance);
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

void FabiEngine3D::audioEntity_play(const std::string& ID, int loops, int initialVolume, bool noRestart, int fadeMillis)
{
	initialVolume = std::clamp(initialVolume, 0, 100);
	_core->_audioPlayer.playChunk(_core->_audioManager.getChunk(ID), loops, int((float(initialVolume) / 100.0f) * 128.0f), noRestart, fadeMillis);
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

void FabiEngine3D::audioEntity_setVolume(const std::string& ID, int volume)
{
	volume = std::clamp(volume, 0, 100);
	_core->_audioPlayer.setChunkVolume(_core->_audioManager.getChunk(ID), int((float(volume) / 100.0f) * 128.0f));
}

void FabiEngine3D::audioEntity_changePoint(const std::string& ID, vec3 position)
{
	_core->_audioManager.getChunk(ID).setPosition(position);
}

string FabiEngine3D::audioEntity_getFilePath(const std::string& ID)
{
	return _core->_audioManager.getChunk(ID).getFilePath();
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

int FabiEngine3D::audioEntity_getVolume(const std::string& ID)
{
	return _core->_audioPlayer.getChunkVolume(_core->_audioManager.getChunk(ID));
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