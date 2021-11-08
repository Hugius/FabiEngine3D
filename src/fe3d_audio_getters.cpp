#include "fe3d.hpp"
#include "core_engine.hpp"

#include <algorithm>

const vector<string> FabiEngine3D::sound_getAllIDs() const
{
	vector<string> IDs;

	for(const auto& chunk : _core->_audioManager.getSounds())
	{
		IDs.push_back(chunk.getID());
	}

	return IDs;
}

const string& FabiEngine3D::sound_getFilePath(const string& ID) const
{
	return _core->_audioManager.getSound(ID).getFilePath();
}

const Vec3 FabiEngine3D::sound_getPosition(const string& ID) const
{
	return _core->_audioManager.getSound(ID).getPosition();
}

const float FabiEngine3D::sound_getMaxDistance(const string& ID) const
{
	return _core->_audioManager.getSound(ID).getMaxDistance();
}

const bool FabiEngine3D::sound_isExisting(const string& ID) const
{
	return _core->_audioManager.isSoundExisting(ID);
}

const bool FabiEngine3D::sound_isStarted(const string& ID) const
{
	return _core->_audioPlayer.isSoundStarted(_core->_audioManager.getSound(ID));
}

const bool FabiEngine3D::sound_isPlaying(const string& ID) const
{
	return _core->_audioPlayer.isSoundPlaying(_core->_audioManager.getSound(ID));
}

const bool FabiEngine3D::sound_isPaused(const string& ID) const
{
	return _core->_audioPlayer.isSoundPaused(_core->_audioManager.getSound(ID));
}

const bool FabiEngine3D::sound_isLoaded(const string& ID) const
{
	return (_core->_audioManager.getSound(ID).getDataPointer() != nullptr);
}

const bool FabiEngine3D::sound_is3D(const string& ID) const
{
	return _core->_audioManager.getSound(ID).is3D();
}

const float FabiEngine3D::sound_getVolume(const string& ID) const
{
	return _core->_audioManager.getSound(ID).getVolume();
}

const float FabiEngine3D::sound_getMaxVolume(const string& ID) const
{
	return _core->_audioManager.getSound(ID).getMaxVolume();
}

const unsigned int FabiEngine3D::sound_getUsedChannelCount() const
{
	return _core->_audioPlayer.getUsedChannelCount();
}

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