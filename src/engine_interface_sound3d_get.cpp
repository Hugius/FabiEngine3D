#include "engine_interface.hpp"
#include "engine_core.hpp"

const vector<string> EngineInterface::sound3d_getIDs() const
{
	vector<string> result;

	for(const auto& chunk : _core->getSound3dManager()->getSounds())
	{
		result.push_back(chunk.getID());
	}

	return result;
}

const string& EngineInterface::sound3d_getAudioPath(const string& ID) const
{
	return _core->getSound3dManager()->getSound(ID).getAudioPath();
}

const bool EngineInterface::sound3d_isExisting(const string& ID) const
{
	return _core->getSound3dManager()->isSoundExisting(ID);
}

const bool EngineInterface::sound3d_isStarted(const string& ID) const
{
	return _core->getSound3dPlayer()->isSoundStarted(_core->getSound3dManager()->getSound(ID));
}

const bool EngineInterface::sound3d_isPlaying(const string& ID) const
{
	return _core->getSound3dPlayer()->isSoundPlaying(_core->getSound3dManager()->getSound(ID));
}

const bool EngineInterface::sound3d_isPaused(const string& ID) const
{
	return _core->getSound3dPlayer()->isSoundPaused(_core->getSound3dManager()->getSound(ID));
}

const float EngineInterface::sound3d_getVolume(const string& ID) const
{
	return _core->getSound3dManager()->getSound(ID).getVolume();
}

const float EngineInterface::sound3d_getMaxVolume(const string& ID) const
{
	return _core->getSound3dManager()->getSound(ID).getMaxVolume();
}

const fvec3 EngineInterface::sound3d_getPosition(const string& ID) const
{
	return _core->getSound3dManager()->getSound(ID).getPosition();
}

const float EngineInterface::sound3d_getMaxDistance(const string& ID) const
{
	return _core->getSound3dManager()->getSound(ID).getMaxDistance();
}