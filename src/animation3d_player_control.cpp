#include "animation3d_player.hpp"
#include "tools.hpp"

using std::make_shared;

void Animation3dPlayer::startModelAnimation3d(const string & animation3dId, const string & modelId, int playCount)
{
	const auto mergedId = Tools::mergeStrings(animation3dId, modelId, DELIMITER);

	if(!_animation3dManager->isAnimation3dExisting(animation3dId))
	{
		abort();
	}

	if(!_modelManager->isModelExisting(modelId))
	{
		abort();
	}

	if(isModelAnimation3dStarted(animation3dId, modelId))
	{
		abort();
	}

	if((playCount == 0) || (playCount < -1))
	{
		abort();
	}

	const auto newAnimation3d = make_shared<StartedAnimation3d>();

	newAnimation3d->setPlayCount(playCount);
	newAnimation3d->setPartIds(_animation3dManager->getAnimation3d(animation3dId)->getPartIds());

	_startedModelAnimation3ds.insert({mergedId, newAnimation3d});
}

void Animation3dPlayer::pauseModelAnimation3d(const string & animation3dId, const string & modelId)
{
	const auto mergedId = Tools::mergeStrings(animation3dId, modelId, DELIMITER);

	if(!_animation3dManager->isAnimation3dExisting(animation3dId))
	{
		abort();
	}

	if(!_modelManager->isModelExisting(modelId))
	{
		abort();
	}

	if(!isModelAnimation3dStarted(animation3dId, modelId))
	{
		abort();

	}

	if(isModelAnimation3dPaused(animation3dId, modelId))
	{
		abort();
	}

	_startedModelAnimation3ds.at(mergedId)->setPaused(true);
}

void Animation3dPlayer::autopauseModelAnimation3d(const string & animation3dId, const string & modelId)
{
	const auto mergedId = Tools::mergeStrings(animation3dId, modelId, DELIMITER);

	if(!_animation3dManager->isAnimation3dExisting(animation3dId))
	{
		abort();
	}

	if(!_modelManager->isModelExisting(modelId))
	{
		abort();
	}

	if(!isModelAnimation3dStarted(animation3dId, modelId))
	{
		abort();

	}

	if(isModelAnimation3dPaused(animation3dId, modelId))
	{
		abort();
	}

	_startedModelAnimation3ds.at(mergedId)->setAutopaused(true);
}

void Animation3dPlayer::resumeModelAnimation3d(const string & animation3dId, const string & modelId)
{
	const auto mergedId = Tools::mergeStrings(animation3dId, modelId, DELIMITER);

	if(!_animation3dManager->isAnimation3dExisting(animation3dId))
	{
		abort();
	}

	if(!_modelManager->isModelExisting(modelId))
	{
		abort();
	}

	if(!isModelAnimation3dStarted(animation3dId, modelId))
	{
		abort();
	}

	if(!isModelAnimation3dPaused(animation3dId, modelId))
	{
		abort();
	}

	_startedModelAnimation3ds.at(mergedId)->setPaused(false);
}

void Animation3dPlayer::stopModelAnimation3d(const string & animation3dId, const string & modelId)
{
	const auto mergedId = Tools::mergeStrings(animation3dId, modelId, DELIMITER);

	if(!_animation3dManager->isAnimation3dExisting(animation3dId))
	{
		abort();
	}

	if(!_modelManager->isModelExisting(modelId))
	{
		abort();
	}

	if(!isModelAnimation3dStarted(animation3dId, modelId))
	{
		abort();
	}

	_startedModelAnimation3ds.erase(mergedId);
}

void Animation3dPlayer::setModelAnimation3dSpeedMultiplier(const string & animation3dId, const string & modelId, float value)
{
	const auto mergedId = Tools::mergeStrings(animation3dId, modelId, DELIMITER);

	if(!_animation3dManager->isAnimation3dExisting(animation3dId))
	{
		abort();
	}

	if(!_modelManager->isModelExisting(modelId))
	{
		abort();
	}

	if(!isModelAnimation3dStarted(animation3dId, modelId))
	{
		abort();
	}

	_startedModelAnimation3ds.at(mergedId)->setSpeedMultiplier(value);
}

void Animation3dPlayer::setModelAnimation3dFrameIndex(const string & animation3dId, const string & modelId, int value)
{
	const auto mergedId = Tools::mergeStrings(animation3dId, modelId, DELIMITER);

	if(!_animation3dManager->isAnimation3dExisting(animation3dId))
	{
		abort();
	}

	if(!_modelManager->isModelExisting(modelId))
	{
		abort();
	}

	if(!isModelAnimation3dStarted(animation3dId, modelId))
	{
		abort();
	}

	_startedModelAnimation3ds.at(mergedId)->setFrameIndex(value);
}

void Animation3dPlayer::setModelAnimation3dTotalMovement(const string & animation3dId, const string & modelId, const string & partId, const fvec3 & value)
{
	const auto mergedId = Tools::mergeStrings(animation3dId, modelId, DELIMITER);

	if(!_animation3dManager->isAnimation3dExisting(animation3dId))
	{
		abort();
	}

	if(!_modelManager->isModelExisting(modelId))
	{
		abort();
	}

	if(!isModelAnimation3dStarted(animation3dId, modelId))
	{
		abort();
	}

	_startedModelAnimation3ds.at(mergedId)->setTotalMovement(partId, value);
}

void Animation3dPlayer::setModelAnimation3dTotalRotation(const string & animation3dId, const string & modelId, const string & partId, const fvec3 & value)
{
	const auto mergedId = Tools::mergeStrings(animation3dId, modelId, DELIMITER);

	if(!_animation3dManager->isAnimation3dExisting(animation3dId))
	{
		abort();
	}

	if(!_modelManager->isModelExisting(modelId))
	{
		abort();
	}

	if(!isModelAnimation3dStarted(animation3dId, modelId))
	{
		abort();
	}

	_startedModelAnimation3ds.at(mergedId)->setTotalRotation(partId, value);
}

void Animation3dPlayer::setModelAnimation3dTotalScaling(const string & animation3dId, const string & modelId, const string & partId, const fvec3 & value)
{
	const auto mergedId = Tools::mergeStrings(animation3dId, modelId, DELIMITER);

	if(!_animation3dManager->isAnimation3dExisting(animation3dId))
	{
		abort();
	}

	if(!_modelManager->isModelExisting(modelId))
	{
		abort();
	}

	if(!isModelAnimation3dStarted(animation3dId, modelId))
	{
		abort();
	}

	_startedModelAnimation3ds.at(mergedId)->setTotalScaling(partId, value);
}

void Animation3dPlayer::setModelAnimation3dTotalSpeed(const string & animation3dId, const string & modelId, const string & partId, const fvec3 & value)
{
	const auto mergedId = Tools::mergeStrings(animation3dId, modelId, DELIMITER);

	if(!_animation3dManager->isAnimation3dExisting(animation3dId))
	{
		abort();
	}

	if(!_modelManager->isModelExisting(modelId))
	{
		abort();
	}

	if(!isModelAnimation3dStarted(animation3dId, modelId))
	{
		abort();
	}

	_startedModelAnimation3ds.at(mergedId)->setTotalSpeed(partId, value);
}