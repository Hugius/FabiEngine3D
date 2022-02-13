#include "animation3d_player.hpp"

void Animation3dPlayer::inject(shared_ptr<Animation3dManager> animation3dManager)
{
	_animation3dManager = animation3dManager;
}

void Animation3dPlayer::inject(shared_ptr<ModelEntityManager> modelEntityManager)
{
	_modelEntityManager = modelEntityManager;
}

const vector<pair<string, string>> Animation3dPlayer::getStartedModelAnimationIds() const
{
	vector<pair<string, string>> ids;

	for(const auto& [key, animation] : _startedModelAnimations)
	{
		ids.push_back(key);
	}

	return ids;
}

const float Animation3dPlayer::getModelAnimationSpeedMultiplier(const string& animationId, const string& modelId) const
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

	return _startedModelAnimations.at(make_pair(animationId, modelId))->getSpeedMultiplier();
}

const int Animation3dPlayer::getModelAnimationPlayCount(const string& animationId, const string& modelId) const
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

	return _startedModelAnimations.at(make_pair(animationId, modelId))->getPlayCount();
}

const unsigned int Animation3dPlayer::getModelAnimationFrameIndex(const string& animationId, const string& modelId) const
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

	return _startedModelAnimations.at(make_pair(animationId, modelId))->getFrameIndex();
}

const bool Animation3dPlayer::isModelAnimationStarted(const string& animationId, const string& modelId) const
{
	if(!_animation3dManager->isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_modelEntityManager->isEntityExisting(modelId))
	{
		abort();
	}

	return (_startedModelAnimations.find(make_pair(animationId, modelId)) != _startedModelAnimations.end());
}

const bool Animation3dPlayer::isModelAnimationPlaying(const string& animationId, const string& modelId) const
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

	return !isModelAnimationPaused(animationId, modelId);
}

const bool Animation3dPlayer::isModelAnimationPaused(const string& animationId, const string& modelId) const
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

	return _startedModelAnimations.at(make_pair(animationId, modelId))->isPaused();
}

const bool Animation3dPlayer::isModelAnimationAutopaused(const string& animationId, const string& modelId) const
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

	return _startedModelAnimations.at(make_pair(animationId, modelId))->isAutopaused();
}

const bool Animation3dPlayer::_hasReachedTarget(float total, float target, float speed) const
{
	return (total >= (target - fabsf(speed))) && (total <= (target + fabsf(speed)));
}