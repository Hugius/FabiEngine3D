#include "animation3d_player.hpp"
#include "tools.hpp"

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

	for(const auto & [mergedId, animation] : _startedModelAnimations)
	{
		const auto splitKey = Tools::splitStringIntoTwo(mergedId, DELIMITER);

		ids.push_back(splitKey);
	}

	return ids;
}

const float Animation3dPlayer::getModelAnimationSpeedMultiplier(const string & animationId, const string & modelId) const
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

	return _startedModelAnimations.at(mergedId)->getSpeedMultiplier();
}

const int Animation3dPlayer::getModelAnimationPlayCount(const string & animationId, const string & modelId) const
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

	return _startedModelAnimations.at(mergedId)->getPlayCount();
}

const unsigned int Animation3dPlayer::getModelAnimationFrameIndex(const string & animationId, const string & modelId) const
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

	return _startedModelAnimations.at(mergedId)->getFrameIndex();
}

const bool Animation3dPlayer::isModelAnimationStarted(const string & animationId, const string & modelId) const
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

	return (_startedModelAnimations.find(mergedId) != _startedModelAnimations.end());
}

const bool Animation3dPlayer::isModelAnimationPaused(const string & animationId, const string & modelId) const
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

	return _startedModelAnimations.at(mergedId)->isPaused();
}

const bool Animation3dPlayer::isModelAnimationAutopaused(const string & animationId, const string & modelId) const
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

	return _startedModelAnimations.at(mergedId)->isAutopaused();
}

const bool Animation3dPlayer::_hasReachedTarget(float total, float target, float speed) const
{
	return (total >= (target - fabsf(speed))) && (total <= (target + fabsf(speed)));
}