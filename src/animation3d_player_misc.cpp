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

const vector<pair<string, string>> Animation3dPlayer::getStartedModelAnimation3dIds() const
{
	vector<pair<string, string>> result = {};

	for(const auto & [mergedId, startedAnimation3d] : _startedModelAnimation3ds)
	{
		const auto splitKey = Tools::splitStringIntoTwo(mergedId, DELIMITER);

		result.push_back(splitKey);
	}

	return result;
}

const float Animation3dPlayer::getModelAnimation3dSpeedMultiplier(const string & animation3dId, const string & modelId) const
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

	return _startedModelAnimation3ds.at(mergedId)->getSpeedMultiplier();
}

const int Animation3dPlayer::getModelAnimation3dPlayCount(const string & animation3dId, const string & modelId) const
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

	return _startedModelAnimation3ds.at(mergedId)->getPlayCount();
}

const int Animation3dPlayer::getModelAnimation3dFrameIndex(const string & animation3dId, const string & modelId) const
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

	return _startedModelAnimation3ds.at(mergedId)->getFrameIndex();
}

const bool Animation3dPlayer::isModelAnimation3dStarted(const string & animation3dId, const string & modelId) const
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

	return (_startedModelAnimation3ds.find(mergedId) != _startedModelAnimation3ds.end());
}

const bool Animation3dPlayer::isModelAnimation3dPaused(const string & animation3dId, const string & modelId) const
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

	return _startedModelAnimation3ds.at(mergedId)->isPaused();
}

const bool Animation3dPlayer::isModelAnimation3dAutopaused(const string & animation3dId, const string & modelId) const
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

	return _startedModelAnimation3ds.at(mergedId)->isAutopaused();
}

const bool Animation3dPlayer::_hasReachedTarget(float total, float target, float speed) const
{
	return (total >= (target - fabsf(speed))) && (total <= (target + fabsf(speed)));
}