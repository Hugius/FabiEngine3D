#include "animation3d_editor.hpp"
#include "logger.hpp"

void Animation3dEditor::startModelAnimation(const string& animationId, const string& modelId, int playCount)
{
	if(!isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_fe3d->model_isExisting(modelId))
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

	auto animation = make_shared<Animation3d>(*_getAnimation(animationId));

	animation->setPlayCount(playCount);
	animation->setInitialSize(_fe3d->model_getBaseSize(modelId));

	bool hasAllParts = true;
	for(const auto& partId : animation->getPartIds())
	{
		if(!partId.empty())
		{
			if(!_fe3d->model_hasPart(modelId, partId))
			{
				abort();
			}
		}
	}

	_startedModelAnimations.insert(make_pair(make_pair(animationId, modelId), animation));
}

void Animation3dEditor::autopauseModelAnimation(const string& animationId, const string& modelId)
{
	if(!isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_fe3d->model_isExisting(modelId))
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

void Animation3dEditor::pauseModelAnimation(const string& animationId, const string& modelId)
{
	if(!isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_fe3d->model_isExisting(modelId))
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

void Animation3dEditor::resumeModelAnimation(const string& animationId, const string& modelId)
{
	if(!isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_fe3d->model_isExisting(modelId))
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

void Animation3dEditor::stopModelAnimation(const string& animationId, const string& modelId)
{
	if(!isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_fe3d->model_isExisting(modelId))
	{
		abort();
	}
	if(!isModelAnimationStarted(animationId, modelId))
	{
		abort();
	}

	_startedModelAnimations.erase(make_pair(animationId, modelId));
}

void Animation3dEditor::pauseModelAnimations()
{
	for(auto& [key, animation] : _startedModelAnimations)
	{
		animation->setPaused(true);
	}
}

void Animation3dEditor::autopauseModelAnimations()
{
	for(auto& [key, animation] : _startedModelAnimations)
	{
		animation->setAutopaused(true);
	}
}

void Animation3dEditor::resumeModelAnimations()
{
	for(auto& [key, animation] : _startedModelAnimations)
	{
		animation->setPaused(false);
	}
}

void Animation3dEditor::stopModelAnimations()
{
	_startedModelAnimations.clear();
}

void Animation3dEditor::setModelAnimationSpeed(const string& animationId, const string& modelId, float value)
{
	if(!isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_fe3d->model_isExisting(modelId))
	{
		abort();
	}
	if(!isModelAnimationStarted(animationId, modelId))
	{
		abort();
	}

	_startedModelAnimations.at(make_pair(animationId, modelId))->setSpeed(value);
}