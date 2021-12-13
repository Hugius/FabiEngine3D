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

const vector<string> FabiEngine3D::music_getAudioPaths() const
{
	vector<string> result;

	for (const auto& music : _core->_audioManager.getAllMusic())
	{
		result.push_back(music.getAudioPath());
	}

	return result;
}

const float FabiEngine3D::music_getVolume() const
{
	return _core->_audioPlayer.getMusicVolume();
}

const vector<string> FabiEngine3D::sound2d_getAllIDs() const
{
	vector<string> result;

	for(const auto& chunk : _core->_audioManager.getAllSound2d())
	{
		result.push_back(chunk.getID());
	}

	return result;
}

const string& FabiEngine3D::sound2d_getAudioPath(const string& ID) const
{
	return _core->_audioManager.getSound2d(ID).getAudioPath();
}

const bool FabiEngine3D::sound2d_isExisting(const string& ID) const
{
	return _core->_audioManager.isSound2dExisting(ID);
}

const bool FabiEngine3D::sound2d_isStarted(const string& ID) const
{
	return _core->_audioPlayer.isSound2dStarted(_core->_audioManager.getSound2d(ID));
}

const bool FabiEngine3D::sound2d_isPlaying(const string& ID) const
{
	return _core->_audioPlayer.isSound2dPlaying(_core->_audioManager.getSound2d(ID));
}

const bool FabiEngine3D::sound2d_isPaused(const string& ID) const
{
	return _core->_audioPlayer.isSound2dPaused(_core->_audioManager.getSound2d(ID));
}

const float FabiEngine3D::sound2d_getVolume(const string& ID) const
{
	return _core->_audioManager.getSound2d(ID).getVolume();
}

const vector<string> FabiEngine3D::sound3d_getAllIDs() const
{
	vector<string> result;

	for (const auto& chunk : _core->_audioManager.getAllSound3d())
	{
		result.push_back(chunk.getID());
	}

	return result;
}

const string& FabiEngine3D::sound3d_getAudioPath(const string& ID) const
{
	return _core->_audioManager.getSound3d(ID).getAudioPath();
}

const bool FabiEngine3D::sound3d_isExisting(const string& ID) const
{
	return _core->_audioManager.isSound3dExisting(ID);
}

const bool FabiEngine3D::sound3d_isStarted(const string& ID) const
{
	return _core->_audioPlayer.isSound3dStarted(_core->_audioManager.getSound3d(ID));
}

const bool FabiEngine3D::sound3d_isPlaying(const string& ID) const
{
	return _core->_audioPlayer.isSound3dPlaying(_core->_audioManager.getSound3d(ID));
}

const bool FabiEngine3D::sound3d_isPaused(const string& ID) const
{
	return _core->_audioPlayer.isSound3dPaused(_core->_audioManager.getSound3d(ID));
}

const float FabiEngine3D::sound3d_getVolume(const string& ID) const
{
	return _core->_audioManager.getSound3d(ID).getVolume();
}

const float FabiEngine3D::sound3d_getMaxVolume(const string& ID) const
{
	return _core->_audioManager.getSound3d(ID).getMaxVolume();
}

const fvec3 FabiEngine3D::sound3d_getPosition(const string& ID) const
{
	return _core->_audioManager.getSound3d(ID).getPosition();
}

const float FabiEngine3D::sound3d_getMaxDistance(const string& ID) const
{
	return _core->_audioManager.getSound3d(ID).getMaxDistance();
}