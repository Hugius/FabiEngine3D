#include "animation3d_player.hpp"
#include "tools.hpp"

using std::make_shared;

void Animation3dPlayer::startModelAnimation(const string & animation3dId, const string & modelId, int playCount)
{
	const auto mergedId = Tools::mergeStrings(animation3dId, modelId, DELIMITER);

	if(!_animation3dManager->isAnimationExisting(animation3dId))
	{
		abort();
	}
	if(!_modelEntityManager->isEntityExisting(modelId))
	{
		abort();
	}
	if(isModelAnimationStarted(animation3dId, modelId))
	{
		abort();
	}
	if((playCount == 0) || (playCount < -1))
	{
		abort();
	}

	const auto newAnimation3d = make_shared<StartedAnimation3d>();

	newAnimation3d->setPlayCount(playCount);
	newAnimation3d->setPartIds(_animation3dManager->getAnimation(animation3dId)->getPartIds());

	_startedModelAnimations.insert({mergedId, newAnimation3d});
}

void Animation3dPlayer::pauseModelAnimation(const string & animation3dId, const string & modelId)
{
	const auto mergedId = Tools::mergeStrings(animation3dId, modelId, DELIMITER);

	if(!_animation3dManager->isAnimationExisting(animation3dId))
	{
		abort();
	}
	if(!_modelEntityManager->isEntityExisting(modelId))
	{
		abort();
	}
	if(!isModelAnimationStarted(animation3dId, modelId))
	{
		abort();

	}
	if(isModelAnimationPaused(animation3dId, modelId))
	{
		abort();
	}

	_startedModelAnimations.at(mergedId)->setPaused(true);
}

void Animation3dPlayer::autopauseModelAnimation(const string & animation3dId, const string & modelId)
{
	const auto mergedId = Tools::mergeStrings(animation3dId, modelId, DELIMITER);

	if(!_animation3dManager->isAnimationExisting(animation3dId))
	{
		abort();
	}
	if(!_modelEntityManager->isEntityExisting(modelId))
	{
		abort();
	}
	if(!isModelAnimationStarted(animation3dId, modelId))
	{
		abort();

	}
	if(isModelAnimationPaused(animation3dId, modelId))
	{
		abort();
	}

	_startedModelAnimations.at(mergedId)->setAutopaused(true);
}

void Animation3dPlayer::resumeModelAnimation(const string & animation3dId, const string & modelId)
{
	const auto mergedId = Tools::mergeStrings(animation3dId, modelId, DELIMITER);

	if(!_animation3dManager->isAnimationExisting(animation3dId))
	{
		abort();
	}
	if(!_modelEntityManager->isEntityExisting(modelId))
	{
		abort();
	}
	if(!isModelAnimationStarted(animation3dId, modelId))
	{
		abort();
	}
	if(!isModelAnimationPaused(animation3dId, modelId))
	{
		abort();
	}

	_startedModelAnimations.at(mergedId)->setPaused(false);
}

void Animation3dPlayer::stopModelAnimation(const string & animation3dId, const string & modelId)
{
	const auto mergedId = Tools::mergeStrings(animation3dId, modelId, DELIMITER);

	if(!_animation3dManager->isAnimationExisting(animation3dId))
	{
		abort();
	}
	if(!_modelEntityManager->isEntityExisting(modelId))
	{
		abort();
	}
	if(!isModelAnimationStarted(animation3dId, modelId))
	{
		abort();
	}

	_startedModelAnimations.erase(mergedId);
}

void Animation3dPlayer::setModelAnimationSpeedMultiplier(const string & animation3dId, const string & modelId, float value)
{
	const auto mergedId = Tools::mergeStrings(animation3dId, modelId, DELIMITER);

	if(!_animation3dManager->isAnimationExisting(animation3dId))
	{
		abort();
	}
	if(!_modelEntityManager->isEntityExisting(modelId))
	{
		abort();
	}
	if(!isModelAnimationStarted(animation3dId, modelId))
	{
		abort();
	}

	_startedModelAnimations.at(mergedId)->setSpeedMultiplier(value);
}

void Animation3dPlayer::setModelAnimationFrameIndex(const string & animation3dId, const string & modelId, int value)
{
	const auto mergedId = Tools::mergeStrings(animation3dId, modelId, DELIMITER);

	if(!_animation3dManager->isAnimationExisting(animation3dId))
	{
		abort();
	}
	if(!_modelEntityManager->isEntityExisting(modelId))
	{
		abort();
	}
	if(!isModelAnimationStarted(animation3dId, modelId))
	{
		abort();
	}

	_startedModelAnimations.at(mergedId)->setFrameIndex(value);
}