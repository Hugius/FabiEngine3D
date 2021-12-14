#include "fe3d.hpp"
#include "core.hpp"

const vector<string> FabiEngine3D::sound2d_getAllIDs() const
{
	vector<string> result;

	for(const auto& chunk : _core->_sound2dManager.getSounds())
	{
		result.push_back(chunk.getID());
	}

	return result;
}

const string& FabiEngine3D::sound2d_getAudioPath(const string& ID) const
{
	return _core->_sound2dManager.getSound(ID).getAudioPath();
}

const bool FabiEngine3D::sound2d_isExisting(const string& ID) const
{
	return _core->_sound2dManager.isSoundExisting(ID);
}

const bool FabiEngine3D::sound2d_isStarted(const string& ID) const
{
	return _core->_sound2dPlayer.isSoundStarted(_core->_sound2dManager.getSound(ID));
}

const bool FabiEngine3D::sound2d_isPlaying(const string& ID) const
{
	return _core->_sound2dPlayer.isSoundPlaying(_core->_sound2dManager.getSound(ID));
}

const bool FabiEngine3D::sound2d_isPaused(const string& ID) const
{
	return _core->_sound2dPlayer.isSoundPaused(_core->_sound2dManager.getSound(ID));
}

const float FabiEngine3D::sound2d_getVolume(const string& ID) const
{
	return _core->_sound2dManager.getSound(ID).getVolume();
}