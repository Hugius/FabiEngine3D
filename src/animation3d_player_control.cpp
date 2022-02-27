#include "animation3d_player.hpp"
#include "tools.hpp"

using std::make_shared;

void Animation3dPlayer::startModelAnimation(const string& animationId, const string& modelId, int playCount)
{
	const auto key = Tools::mergeStrings(animationId, modelId, DELIMITER);

	if(playCount == 0)
	{
		return;
	}
	if(playCount < -1)
	{
		abort();
	}
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

	const auto newAnimation = make_shared<StartedAnimation3d>();

	newAnimation->setPlayCount(playCount);
	newAnimation->setPartIds(_animation3dManager->getAnimation(animationId)->getPartIds());

	_startedModelAnimations.insert(make_pair(key, newAnimation));
}

void Animation3dPlayer::pauseModelAnimation(const string& animationId, const string& modelId)
{
	const auto key = Tools::mergeStrings(animationId, modelId, DELIMITER);

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

	_startedModelAnimations.at(key)->setPaused(true);
}

void Animation3dPlayer::autopauseModelAnimation(const string& animationId, const string& modelId)
{
	const auto key = Tools::mergeStrings(animationId, modelId, DELIMITER);

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

	_startedModelAnimations.at(key)->setAutopaused(true);
}

void Animation3dPlayer::resumeModelAnimation(const string& animationId, const string& modelId)
{
	const auto key = Tools::mergeStrings(animationId, modelId, DELIMITER);

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

	_startedModelAnimations.at(key)->setPaused(false);
}

void Animation3dPlayer::stopModelAnimation(const string& animationId, const string& modelId)
{
	const auto key = Tools::mergeStrings(animationId, modelId, DELIMITER);

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

	_startedModelAnimations.erase(key);
}

void Animation3dPlayer::setModelAnimationSpeedMultiplier(const string& animationId, const string& modelId, float value)
{
	const auto key = Tools::mergeStrings(animationId, modelId, DELIMITER);

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

	_startedModelAnimations.at(key)->setSpeedMultiplier(value);
}

void Animation3dPlayer::setModelAnimationFrameIndex(const string& animationId, const string& modelId, unsigned int value)
{
	const auto key = Tools::mergeStrings(animationId, modelId, DELIMITER);

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

	_startedModelAnimations.at(key)->setFrameIndex(value);
}