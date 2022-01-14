#include "animation3d_editor.hpp"
#include "logger.hpp"

void Animation3dEditor::startModelAnimation(const string& animationID, const string& modelID, int playCount)
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!_fe3d->model_isExisting(modelID))
	{
		Logger::throwWarning("model not existing!");
	}

	if(isModelAnimationStarted(animationID, modelID))
	{
		Logger::throwWarning("animation already started!");
	}

	if((playCount < -1) || (playCount == 0))
	{
		Logger::throwWarning("play count is invalid!");
	}

	auto animation = *_getAnimation(animationID);
	animation.setPlayCount(playCount);
	animation.setInitialSize(_fe3d->model_getBaseSize(modelID));

	bool hasAllParts = true;
	for(const auto& partID : animation.getPartIDs())
	{
		if(!partID.empty())
		{
			if(!_fe3d->model_hasPart(modelID, partID))
			{
				Logger::throwWarning("model does not have required animation parts!");
			}
		}
	}

	_startedModelAnimations.insert(make_pair(make_pair(animationID, modelID), animation));
}

void Animation3dEditor::autopauseModelAnimation(const string& animationID, const string& modelID)
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isModelAnimationStarted(animationID, modelID))
	{
		Logger::throwWarning("animation not started!");
	}

	if(isModelAnimationPaused(animationID, modelID))
	{
		Logger::throwWarning("animation not playing!");
	}

	_startedModelAnimations.at(make_pair(animationID, modelID)).setAutopaused(true);
}

void Animation3dEditor::pauseModelAnimation(const string& animationID, const string& modelID)
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isModelAnimationStarted(animationID, modelID))
	{
		Logger::throwWarning("animation not started!");
	}

	if(isModelAnimationPaused(animationID, modelID))
	{
		Logger::throwWarning("animation not playing!");
	}

	_startedModelAnimations.at(make_pair(animationID, modelID)).setPaused(true);
}

void Animation3dEditor::resumeModelAnimation(const string& animationID, const string& modelID)
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isModelAnimationStarted(animationID, modelID))
	{
		Logger::throwWarning("animation not started!");
	}

	if(!isModelAnimationPaused(animationID, modelID))
	{
		Logger::throwWarning("animation not paused!");
	}

	_startedModelAnimations.at(make_pair(animationID, modelID)).setPaused(false);
}

void Animation3dEditor::stopModelAnimation(const string& animationID, const string& modelID)
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isModelAnimationStarted(animationID, modelID))
	{
		Logger::throwWarning("animation not started!");
	}

	_startedModelAnimations.erase(make_pair(animationID, modelID));
}

void Animation3dEditor::pauseModelAnimations()
{
	for(auto& [key, animation] : _startedModelAnimations)
	{
		animation.setPaused(true);
	}
}

void Animation3dEditor::resumeModelAnimations()
{
	for(auto& [key, animation] : _startedModelAnimations)
	{
		animation.setPaused(false);
	}
}

void Animation3dEditor::stopModelAnimations()
{
	_startedModelAnimations.clear();
}

void Animation3dEditor::setModelAnimationSpeed(const string& animationID, const string& modelID, float value)
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isModelAnimationStarted(animationID, modelID))
	{
		Logger::throwWarning("animation not started!");
	}

	_startedModelAnimations.at(make_pair(animationID, modelID)).setSpeed(value);
}