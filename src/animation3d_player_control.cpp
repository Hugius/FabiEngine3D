#include "animation3d_player.hpp"

using std::make_shared;

void Animation3dPlayer::startModelAnimation(const string& animationId, const string& modelId, int playCount)
{
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
	if((playCount < -1) || (playCount == 0))
	{
		abort();
	}

	const auto newAnimation = make_shared<StartedAnimation3d>(animationId, modelId);

	newAnimation->setPlayCount(playCount);
	newAnimation->setPartIds(_animation3dManager->getAnimation(animationId)->getPartIds());

	_startedModelAnimations.insert(make_pair(make_pair(animationId, modelId), newAnimation));
}

void Animation3dPlayer::pauseModelAnimation(const string& animationId, const string& modelId)
{
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

	_startedModelAnimations.at(make_pair(animationId, modelId))->setPaused(true);
}

void Animation3dPlayer::autopauseModelAnimation(const string& animationId, const string& modelId)
{
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

	_startedModelAnimations.at(make_pair(animationId, modelId))->setAutopaused(true);
}

void Animation3dPlayer::resumeModelAnimation(const string& animationId, const string& modelId)
{
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

	_startedModelAnimations.at(make_pair(animationId, modelId))->setPaused(false);
}

void Animation3dPlayer::stopModelAnimation(const string& animationId, const string& modelId)
{
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

	_startedModelAnimations.erase(make_pair(animationId, modelId));
}

void Animation3dPlayer::setModelAnimationSpeedMultiplier(const string& animationId, const string& modelId, float value)
{
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

	_startedModelAnimations.at(make_pair(animationId, modelId))->setFrameIndex(value);
}

void Animation3dPlayer::setModelAnimationFrameIndex(const string& animationId, const string& modelId, unsigned int value)
{
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

	_startedModelAnimations.at(make_pair(animationId, modelId))->setFrameIndex(value);
}