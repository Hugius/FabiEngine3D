#include "fe3d.hpp"
#include "core_engine.hpp"

#include <algorithm>

const bool FabiEngine3D::music_isStarted() const
{
	return _core->_audioPlayer.isMusicStarted();
}

const bool FabiEngine3D::music_isPlaying() const
{
	return _core->_audioPlayer.isMusicPlaying();
}

const bool FabiEngine3D::music_isPaused() const
{
	return _core->_audioPlayer.isMusicPaused();
}

const float FabiEngine3D::music_getVolume() const
{
	return _core->_audioPlayer.getMusicVolume();
}

const vector<string> FabiEngine3D::sound2D_getAllIDs() const
{
	vector<string> IDs;

	for(const auto& chunk : _core->_audioManager.getSounds2D())
	{
		IDs.push_back(chunk.getID());
	}

	return IDs;
}

const string& FabiEngine3D::sound2D_getFilePath(const string& ID) const
{
	return _core->_audioManager.getSound2D(ID).getAudioPath();
}

const bool FabiEngine3D::sound2D_isExisting(const string& ID) const
{
	return _core->_audioManager.isSoundExisting2D(ID);
}

const bool FabiEngine3D::sound2D_isStarted(const string& ID) const
{
	return _core->_audioPlayer.isSoundStarted2D(_core->_audioManager.getSound2D(ID));
}

const bool FabiEngine3D::sound2D_isPlaying(const string& ID) const
{
	return _core->_audioPlayer.isSoundPlaying2D(_core->_audioManager.getSound2D(ID));
}

const bool FabiEngine3D::sound2D_isPaused(const string& ID) const
{
	return _core->_audioPlayer.isSoundPaused2D(_core->_audioManager.getSound2D(ID));
}

const float FabiEngine3D::sound2D_getVolume(const string& ID) const
{
	return _core->_audioManager.getSound2D(ID).getVolume();
}

const vector<string> FabiEngine3D::sound3D_getAllIDs() const
{
	vector<string> IDs;

	for (const auto& chunk : _core->_audioManager.getSounds3D())
	{
		IDs.push_back(chunk.getID());
	}

	return IDs;
}

const string& FabiEngine3D::sound3D_getFilePath(const string& ID) const
{
	return _core->_audioManager.getSound3D(ID).getAudioPath();
}

const bool FabiEngine3D::sound3D_isExisting(const string& ID) const
{
	return _core->_audioManager.isSoundExisting3D(ID);
}

const bool FabiEngine3D::sound3D_isStarted(const string& ID) const
{
	return _core->_audioPlayer.isSoundStarted3D(_core->_audioManager.getSound3D(ID));
}

const bool FabiEngine3D::sound3D_isPlaying(const string& ID) const
{
	return _core->_audioPlayer.isSoundPlaying3D(_core->_audioManager.getSound3D(ID));
}

const bool FabiEngine3D::sound3D_isPaused(const string& ID) const
{
	return _core->_audioPlayer.isSoundPaused3D(_core->_audioManager.getSound3D(ID));
}

const float FabiEngine3D::sound3D_getVolume(const string& ID) const
{
	return _core->_audioManager.getSound3D(ID).getVolume();
}

const float FabiEngine3D::sound3D_getMaxVolume(const string& ID) const
{
	return _core->_audioManager.getSound3D(ID).getMaxVolume();
}

const fvec3 FabiEngine3D::sound3D_getPosition(const string& ID) const
{
	return _core->_audioManager.getSound3D(ID).getPosition();
}

const float FabiEngine3D::sound3D_getMaxDistance(const string& ID) const
{
	return _core->_audioManager.getSound3D(ID).getMaxDistance();
}