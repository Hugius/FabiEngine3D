#include "animation3d_player.hpp"
#include "tools.hpp"

using std::make_shared;

void Animation3dPlayer::startModelAnimation(const string & animationId, const string & modelId, int playCount)
{
	const auto mergedId = Tools::mergeStrings(animationId, modelId, DELIMITER);

	if(!_animation3dManager->isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_modelEntityManager->isEntityExisting(modelId))
	{
		abort();
	}
	if(isModelAnimationStarted(animationId, modelId))
	{
		abort();
	}
	if((playCount == 0) || (playCount < -1))
	{
		abort();
	}

	const auto newAnimation = make_shared<StartedAnimation3d>();

	newAnimation->setPlayCount(playCount);
	newAnimation->setPartIds(_animation3dManager->getAnimation(animationId)->getPartIds());

	_startedModelAnimations.insert({mergedId, newAnimation});
}

void Animation3dPlayer::pauseModelAnimation(const string & animationId, const string & modelId)
{
	const auto mergedId = Tools::mergeStrings(animationId, modelId, DELIMITER);

	if(!_animation3dManager->isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_modelEntityManager->isEntityExisting(modelId))
	{
		abort();
	}
	if(!isModelAnimationStarted(animationId, modelId))
	{
		abort();

	}
	if(isModelAnimationPaused(animationId, modelId))
	{
		abort();
	}

	_startedModelAnimations.at(mergedId)->setPaused(true);
}

void Animation3dPlayer::autopauseModelAnimation(const string & animationId, const string & modelId)
{
	const auto mergedId = Tools::mergeStrings(animationId, modelId, DELIMITER);

	if(!_animation3dManager->isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_modelEntityManager->isEntityExisting(modelId))
	{
		abort();
	}
	if(!isModelAnimationStarted(animationId, modelId))
	{
		abort();

	}
	if(isModelAnimationPaused(animationId, modelId))
	{
		abort();
	}

	_startedModelAnimations.at(mergedId)->setAutopaused(true);
}

void Animation3dPlayer::resumeModelAnimation(const string & animationId, const string & modelId)
{
	const auto mergedId = Tools::mergeStrings(animationId, modelId, DELIMITER);

	if(!_animation3dManager->isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_modelEntityManager->isEntityExisting(modelId))
	{
		abort();
	}
	if(!isModelAnimationStarted(animationId, modelId))
	{
		abort();
	}
	if(!isModelAnimationPaused(animationId, modelId))
	{
		abort();
	}

	_startedModelAnimations.at(mergedId)->setPaused(false);
}

void Animation3dPlayer::stopModelAnimation(const string & animationId, const string & modelId)
{
	const auto mergedId = Tools::mergeStrings(animationId, modelId, DELIMITER);

	if(!_animation3dManager->isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_modelEntityManager->isEntityExisting(modelId))
	{
		abort();
	}
	if(!isModelAnimationStarted(animationId, modelId))
	{
		abort();
	}

	_startedModelAnimations.erase(mergedId);
}

void Animation3dPlayer::setModelAnimationSpeedMultiplier(const string & animationId, const string & modelId, float value)
{
	const auto mergedId = Tools::mergeStrings(animationId, modelId, DELIMITER);

	if(!_animation3dManager->isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_modelEntityManager->isEntityExisting(modelId))
	{
		abort();
	}
	if(!isModelAnimationStarted(animationId, modelId))
	{
		abort();
	}

	_startedModelAnimations.at(mergedId)->setSpeedMultiplier(value);
}

void Animation3dPlayer::setModelAnimationFrameIndex(const string & animationId, const string & modelId, int value)
{
	const auto mergedId = Tools::mergeStrings(animationId, modelId, DELIMITER);

	if(!_animation3dManager->isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_modelEntityManager->isEntityExisting(modelId))
	{
		abort();
	}
	if(!isModelAnimationStarted(animationId, modelId))
	{
		abort();
	}

	_startedModelAnimations.at(mergedId)->setFrameIndex(value);
}