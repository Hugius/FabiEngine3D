#include "engine_interface.hpp"
#include "engine_core.hpp"

const vector<string> EngineInterface::sound2d_getIDs() const
{
	vector<string> result;

	for(const auto& chunk : _core->getSound2dManager()->getSounds())
	{
		result.push_back(chunk.getID());
	}

	return result;
}

const string& EngineInterface::sound2d_getAudioPath(const string& ID) const
{
	return _core->getSound2dManager()->getSound(ID).getAudioPath();
}

const bool EngineInterface::sound2d_isExisting(const string& ID) const
{
	return _core->getSound2dManager()->isSoundExisting(ID);
}

const bool EngineInterface::sound2d_isStarted(const string& ID) const
{
	return _core->getSound2dPlayer()->isSoundStarted(_core->getSound2dManager()->getSound(ID));
}

const bool EngineInterface::sound2d_isPlaying(const string& ID) const
{
	return _core->getSound2dPlayer()->isSoundPlaying(_core->getSound2dManager()->getSound(ID));
}

const bool EngineInterface::sound2d_isPaused(const string& ID) const
{
	return _core->getSound2dPlayer()->isSoundPaused(_core->getSound2dManager()->getSound(ID));
}

const float EngineInterface::sound2d_getVolume(const string& ID) const
{
	return _core->getSound2dManager()->getSound(ID).getVolume();
}