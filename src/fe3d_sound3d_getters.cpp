#include "fe3d.hpp"
#include "core.hpp"

const vector<string> FabiEngine3D::sound3d_getAllIDs() const
{
	vector<string> result;

	for(const auto& chunk : _core->_sound3dManager.getSounds())
	{
		result.push_back(chunk.getID());
	}

	return result;
}

const string& FabiEngine3D::sound3d_getAudioPath(const string& ID) const
{
	return _core->_sound3dManager.getSound(ID).getAudioPath();
}

const bool FabiEngine3D::sound3d_isExisting(const string& ID) const
{
	return _core->_sound3dManager.isSoundExisting(ID);
}

const bool FabiEngine3D::sound3d_isStarted(const string& ID) const
{
	return _core->_sound3dPlayer.isSoundStarted(_core->_sound3dManager.getSound(ID));
}

const bool FabiEngine3D::sound3d_isPlaying(const string& ID) const
{
	return _core->_sound3dPlayer.isSoundPlaying(_core->_sound3dManager.getSound(ID));
}

const bool FabiEngine3D::sound3d_isPaused(const string& ID) const
{
	return _core->_sound3dPlayer.isSoundPaused(_core->_sound3dManager.getSound(ID));
}

const float FabiEngine3D::sound3d_getVolume(const string& ID) const
{
	return _core->_sound3dManager.getSound(ID).getVolume();
}

const float FabiEngine3D::sound3d_getMaxVolume(const string& ID) const
{
	return _core->_sound3dManager.getSound(ID).getMaxVolume();
}

const fvec3 FabiEngine3D::sound3d_getPosition(const string& ID) const
{
	return _core->_sound3dManager.getSound(ID).getPosition();
}

const float FabiEngine3D::sound3d_getMaxDistance(const string& ID) const
{
	return _core->_sound3dManager.getSound(ID).getMaxDistance();
}