#include "animation3d_player.hpp"
#include "tools.hpp"

void Animation3dPlayer::inject(shared_ptr<Animation3dManager> animation3dManager)
{
	_animation3dManager = animation3dManager;
}

void Animation3dPlayer::inject(shared_ptr<ModelManager> modelManager)
{
	_modelManager = modelManager;
}

const vector<pair<string, string>> Animation3dPlayer::getStartedModelAnimationIds() const
{
	vector<pair<string, string>> result;

	for(const auto & [mergedId, animation] : _startedModelAnimations)
	{
		const auto splitKey = Tools::splitStringIntoTwo(mergedId, DELIMITER);

		result.push_back(splitKey);
	}

	return result;
}

const float Animation3dPlayer::getModelAnimationSpeedMultiplier(const string & animation3dId, const string & modelId) const
{
	const auto mergedId = Tools::mergeStrings(animation3dId, modelId, DELIMITER);

	if(!_animation3dManager->isAnimationExisting(animation3dId))
	{
		abort();
	}
	if(!_modelManager->isEntityExisting(modelId))
	{
		abort();
	}
	if(!isModelAnimationStarted(animation3dId, modelId))
	{
		abort();
	}

	return _startedModelAnimations.at(mergedId)->getSpeedMultiplier();
}

const int Animation3dPlayer::getModelAnimationPlayCount(const string & animation3dId, const string & modelId) const
{
	const auto mergedId = Tools::mergeStrings(animation3dId, modelId, DELIMITER);

	if(!_animation3dManager->isAnimationExisting(animation3dId))
	{
		abort();
	}
	if(!_modelManager->isEntityExisting(modelId))
	{
		abort();
	}
	if(!isModelAnimationStarted(animation3dId, modelId))
	{
		abort();
	}

	return _startedModelAnimations.at(mergedId)->getPlayCount();
}

const int Animation3dPlayer::getModelAnimationFrameIndex(const string & animation3dId, const string & modelId) const
{
	const auto mergedId = Tools::mergeStrings(animation3dId, modelId, DELIMITER);

	if(!_animation3dManager->isAnimationExisting(animation3dId))
	{
		abort();
	}
	if(!_modelManager->isEntityExisting(modelId))
	{
		abort();
	}
	if(!isModelAnimationStarted(animation3dId, modelId))
	{
		abort();
	}

	return _startedModelAnimations.at(mergedId)->getFrameIndex();
}

const bool Animation3dPlayer::isModelAnimationStarted(const string & animation3dId, const string & modelId) const
{
	const auto mergedId = Tools::mergeStrings(animation3dId, modelId, DELIMITER);

	if(!_animation3dManager->isAnimationExisting(animation3dId))
	{
		abort();
	}
	if(!_modelManager->isEntityExisting(modelId))
	{
		abort();
	}

	return (_startedModelAnimations.find(mergedId) != _startedModelAnimations.end());
}

const bool Animation3dPlayer::isModelAnimationPaused(const string & animation3dId, const string & modelId) const
{
	const auto mergedId = Tools::mergeStrings(animation3dId, modelId, DELIMITER);

	if(!_animation3dManager->isAnimationExisting(animation3dId))
	{
		abort();
	}
	if(!_modelManager->isEntityExisting(modelId))
	{
		abort();
	}
	if(!isModelAnimationStarted(animation3dId, modelId))
	{
		abort();
	}

	return _startedModelAnimations.at(mergedId)->isPaused();
}

const bool Animation3dPlayer::isModelAnimationAutopaused(const string & animation3dId, const string & modelId) const
{
	const auto mergedId = Tools::mergeStrings(animation3dId, modelId, DELIMITER);

	if(!_animation3dManager->isAnimationExisting(animation3dId))
	{
		abort();
	}
	if(!_modelManager->isEntityExisting(modelId))
	{
		abort();
	}
	if(!isModelAnimationStarted(animation3dId, modelId))
	{
		abort();
	}

	return _startedModelAnimations.at(mergedId)->isAutopaused();
}

const bool Animation3dPlayer::_hasReachedTarget(float total, float target, float speed) const
{
	return (total >= (target - fabsf(speed))) && (total <= (target + fabsf(speed)));
}