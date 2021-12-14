#include "fe3d.hpp"
#include "core_engine.hpp"

const vector<string> FabiEngine3D::sound2d_getAllIDs() const
{
	vector<string> result;

	for(const auto& chunk : _core->_soundManager.getAllSound2ds())
	{
		result.push_back(chunk.getID());
	}

	return result;
}

const string& FabiEngine3D::sound2d_getAudioPath(const string& ID) const
{
	return _core->_soundManager.getSound2d(ID).getAudioPath();
}

const bool FabiEngine3D::sound2d_isExisting(const string& ID) const
{
	return _core->_soundManager.isSound2dExisting(ID);
}

const bool FabiEngine3D::sound2d_isStarted(const string& ID) const
{
	return _core->_soundPlayer.isSound2dStarted(_core->_soundManager.getSound2d(ID));
}

const bool FabiEngine3D::sound2d_isPlaying(const string& ID) const
{
	return _core->_soundPlayer.isSound2dPlaying(_core->_soundManager.getSound2d(ID));
}

const bool FabiEngine3D::sound2d_isPaused(const string& ID) const
{
	return _core->_soundPlayer.isSound2dPaused(_core->_soundManager.getSound2d(ID));
}

const float FabiEngine3D::sound2d_getVolume(const string& ID) const
{
	return _core->_soundManager.getSound2d(ID).getVolume();
}

const vector<string> FabiEngine3D::sound3d_getAllIDs() const
{
	vector<string> result;

	for (const auto& chunk : _core->_soundManager.getAllSound3ds())
	{
		result.push_back(chunk.getID());
	}

	return result;
}

const string& FabiEngine3D::sound3d_getAudioPath(const string& ID) const
{
	return _core->_soundManager.getSound3d(ID).getAudioPath();
}

const bool FabiEngine3D::sound3d_isExisting(const string& ID) const
{
	return _core->_soundManager.isSound3dExisting(ID);
}

const bool FabiEngine3D::sound3d_isStarted(const string& ID) const
{
	return _core->_soundPlayer.isSound3dStarted(_core->_soundManager.getSound3d(ID));
}

const bool FabiEngine3D::sound3d_isPlaying(const string& ID) const
{
	return _core->_soundPlayer.isSound3dPlaying(_core->_soundManager.getSound3d(ID));
}

const bool FabiEngine3D::sound3d_isPaused(const string& ID) const
{
	return _core->_soundPlayer.isSound3dPaused(_core->_soundManager.getSound3d(ID));
}

const float FabiEngine3D::sound3d_getVolume(const string& ID) const
{
	return _core->_soundManager.getSound3d(ID).getVolume();
}

const float FabiEngine3D::sound3d_getMaxVolume(const string& ID) const
{
	return _core->_soundManager.getSound3d(ID).getMaxVolume();
}

const fvec3 FabiEngine3D::sound3d_getPosition(const string& ID) const
{
	return _core->_soundManager.getSound3d(ID).getPosition();
}

const float FabiEngine3D::sound3d_getMaxDistance(const string& ID) const
{
	return _core->_soundManager.getSound3d(ID).getMaxDistance();
}