#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

#include <algorithm>

void FabiEngine3D::audioEntity_setSoundEnabled(bool val)
{
	_core->_audioPlayer.setSoundEnabled(val);
}

void FabiEngine3D::audioEntity_setMusicEnabled(bool val)
{
	_core->_audioPlayer.setMusicEnabled(val);
}

void FabiEngine3D::audioEntity_deleteAllSounds()
{
	audioEntity_stopAllSounds();
	_core->_audioManager.deleteAllChunks();
}

void FabiEngine3D::audioEntity_deleteAllMusic()
{
	audioEntity_stopAllMusic();
	_core->_audioManager.deleteAllMusic();
}

void FabiEngine3D::audioEntity_stopAllSounds()
{
	_core->_audioPlayer.stopAllSounds();
}

void FabiEngine3D::audioEntity_stopAllMusic()
{
	_core->_audioPlayer.stopAllMusic();
}

void FabiEngine3D::audioEntity_addMusic(const std::string& fileName)
{
	_core->_audioManager.addMusic(fileName);
}

void FabiEngine3D::audioEntity_deleteMusic()
{
	_core->_audioManager.removeMusic();
}

void FabiEngine3D::audioEntity_setMusicVolume(int volume)
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
		if (_core->_audioPlayer.isPlaying(_core->_audioManager.getChunk(ID))) // If chunk is playing
		{
			_core->_audioPlayer.stopChunk(_core->_audioManager.getChunk(ID), 0);
		}
	}

	_core->_audioManager.removeChunk(ID);
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

bool FabiEngine3D::audioEntity_isPlaying(const std::string& ID)
{
	return _core->_audioPlayer.isPlaying(_core->_audioManager.getChunk(ID));
}

int FabiEngine3D::audioEntity_getVolume(const std::string& ID)
{
	return _core->_audioPlayer.getVolume(_core->_audioManager.getChunk(ID));
}

int FabiEngine3D::audioEntity_getUsedChannelCount()
{
	return _core->_audioPlayer.getUsedChannelCount();
}