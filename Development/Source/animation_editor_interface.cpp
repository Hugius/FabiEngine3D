#include "animation_editor.hpp"

void AnimationEditor::startAnimation(const string& animationID, const string& modelID, int loops)
{
	// Temporary values
	string errorMessage = "Trying to start animation with ID \"" + animationID + "\" on model with ID \"" + modelID + "\": ";

	// Check if animation exists
	if (isAnimationExisting(animationID))
	{
		// Check if model trying to animate exists
		if (_fe3d.modelEntity_isExisting(modelID))
		{
			// Check if animation has not already started
			if (!isAnimationStarted(animationID, modelID))
			{
				// Check if animation count is valid
				if (loops >= -1)
				{
					// Retrieve animation
					auto animation = _getAnimation(animationID);
					animation->animatedModelID = modelID;
					animation->timesToPlay = (loops == -1) ? -1 : (loops + 1);
					animation->initialScaling = _fe3d.modelEntity_getSize(modelID);

					// Check if model has all the parts
					bool hasAllParts = true;
					for (const auto& partID : animation->partIDs)
					{
						// Part cannot be empty
						if (!partID.empty())
						{
							hasAllParts = hasAllParts && _fe3d.modelEntity_hasPart(modelID, partID);
						}
					}

					// Start animation
					if (hasAllParts)
					{
						_startedAnimations.insert(make_pair(make_pair(animationID, modelID), *animation));
					}
					else
					{
						_fe3d.logger_throwWarning(errorMessage + "model does not have required animation parts!");
					}
				}
				else
				{
					_fe3d.logger_throwWarning(errorMessage + "loop count is invalid!");
				}
			}
			else
			{
				_fe3d.logger_throwWarning(errorMessage + "animation already playing!");
			}
		}
		else
		{
			_fe3d.logger_throwWarning(errorMessage + "model not existing!");
		}
	}
	else
	{
		_fe3d.logger_throwWarning(errorMessage + "animation not existing!");
	}
}

bool AnimationEditor::isAnimationExisting(const string& ID)
{
	for (const auto& animation : _animations)
	{
		if (animation->ID == ID)
		{
			return true;
		}
	}

	return false;
}

bool AnimationEditor::isAnimationStarted(const string& animationID, const string& modelID)
{
	// Temporary values
	string errorMessage = "Trying to retrieve animation started status with ID \"" + animationID + "\" on model with ID \"" + modelID + "\": ";

	// Check if animation does not exist
	if (!isAnimationExisting(animationID))
	{
		_fe3d.logger_throwWarning(errorMessage + "animation not existing!");
	}
	else
	{
		return _startedAnimations.find(make_pair(animationID, modelID)) != _startedAnimations.end();
	}

	return false;
}

bool AnimationEditor::isAnimationPlaying(const string& animationID, const string& modelID)
{
	// Temporary values
	string errorMessage = "Trying to retrieve animation playing status with ID \"" + animationID + "\" on model with ID \"" + modelID + "\": ";

	// Check if animation is able to be retrieved
	if (!isAnimationExisting(animationID))
	{
		_fe3d.logger_throwWarning(errorMessage + "animation not existing!");
	}
	else if (!isAnimationStarted(animationID, modelID))
	{
		_fe3d.logger_throwWarning(errorMessage + "animation not started!");
	}
	else
	{
		return !_startedAnimations.at(make_pair(animationID, modelID)).isPaused;
	}

	return false;
}

bool AnimationEditor::isAnimationPaused(const string& animationID, const string& modelID)
{
	// Temporary values
	string errorMessage = "Trying to retrieve animation pausing status with ID \"" + animationID + "\" on model with ID \"" + modelID + "\": ";

	// Check if animation is able to be retrieved
	if (!isAnimationExisting(animationID))
	{
		_fe3d.logger_throwWarning(errorMessage + "animation not existing!");
	}
	else if (!isAnimationStarted(animationID, modelID))
	{
		_fe3d.logger_throwWarning(errorMessage + "animation not started!");
	}
	else
	{
		return _startedAnimations.at(make_pair(animationID, modelID)).isPaused;
	}

	return false;
}

bool AnimationEditor::isAnimationFading(const string& animationID, const string& modelID)
{
	// Temporary values
	string errorMessage = "Trying to retrieve animation fading status with ID \"" + animationID + "\" on model with ID \"" + modelID + "\": ";

	// Check if animation is able to be retrieved
	if (!isAnimationExisting(animationID))
	{
		_fe3d.logger_throwWarning(errorMessage + "animation not existing!");
	}
	else if (!isAnimationStarted(animationID, modelID))
	{
		_fe3d.logger_throwWarning(errorMessage + "animation not started!");
	}
	else
	{
		return (_startedAnimations.at(make_pair(animationID, modelID)).fadeFramestep != -1);
	}

	return false;
}

void AnimationEditor::pauseAnimation(const string& animationID, const string& modelID)
{
	// Temporary values
	string errorMessage = "Trying to pause animation with ID \"" + animationID + "\" on model with ID \"" + modelID + "\": ";

	// Check if animation is existing
	if (isAnimationExisting(animationID))
	{
		// Check if animation is started
		if (isAnimationStarted(animationID, modelID))
		{
			// Check if animation is paused
			if (isAnimationPaused(animationID, modelID))
			{
				_fe3d.logger_throwWarning(errorMessage + "animation already paused!");
			}
			else
			{
				_startedAnimations.at(make_pair(animationID, modelID)).isPaused = true;
			}
		}
		else
		{
			_fe3d.logger_throwWarning(errorMessage + "animation not started!");
		}
	}
	else
	{
		_fe3d.logger_throwWarning(errorMessage + "animation not existing!");
	}
}

void AnimationEditor::resumeAnimation(const string& animationID, const string& modelID)
{
	// Temporary values
	string errorMessage = "Trying to resume animation with ID \"" + animationID + "\" on model with ID \"" + modelID + "\": ";

	// Check if animation is existing
	if (isAnimationExisting(animationID))
	{
		// Check if animation is started
		if (isAnimationStarted(animationID, modelID))
		{
			// Check if animation is paused
			if (isAnimationPaused(animationID, modelID))
			{
				_startedAnimations.at(make_pair(animationID, modelID)).isPaused = false;
			}
			else
			{
				_fe3d.logger_throwWarning(errorMessage + "animation already playing!");
			}
		}
		else
		{
			_fe3d.logger_throwWarning(errorMessage + "animation not started!");
		}
	}
	else
	{
		_fe3d.logger_throwWarning(errorMessage + "animation not existing!");
	}
}

void AnimationEditor::stopAnimation(const string& animationID, const string& modelID)
{
	// Temporary values
	string errorMessage = "Trying to stop animation with ID \"" + animationID + "\" on model with ID \"" + modelID + "\": ";

	// Check if animation is existing
	if (isAnimationExisting(animationID))
	{
		// Check if animation is started
		if (isAnimationStarted(animationID, modelID))
		{
			_startedAnimations.erase(make_pair(animationID, modelID));
		}
		else
		{
			_fe3d.logger_throwWarning(errorMessage + "animation not started!");
		}
	}
	else
	{
		_fe3d.logger_throwWarning(errorMessage + "animation not existing!");
	}
}

void AnimationEditor::stopAllAnimations()
{
	_startedAnimations.clear();
}

void AnimationEditor::fadeAnimation(const string& animationID, const string& modelID, int framestep)
{
	// Temporary values
	string errorMessage = "Trying to fade animation with ID \"" + animationID + "\" on model with ID \"" + modelID + "\": ";

	// Check if animation is existing
	if (isAnimationExisting(animationID))
	{
		// Check if animation is started
		if (isAnimationStarted(animationID, modelID))
		{
			// Check if animation is playing
			if (isAnimationPlaying(animationID, modelID))
			{
				// Check if animation is fading
				if (isAnimationFading(animationID, modelID))
				{
					_fe3d.logger_throwWarning(errorMessage + "animation already fading!");
				}
				else
				{
					_startedAnimations.at(make_pair(animationID, modelID)).fadeFramestep = std::max(0, framestep);
				}
			}
			else
			{
				_fe3d.logger_throwWarning(errorMessage + "animation not playing!");
			}
		}
		else
		{
			_fe3d.logger_throwWarning(errorMessage + "animation not started!");
		}
	}
	else
	{
		_fe3d.logger_throwWarning(errorMessage + "animation not existing!");
	}
}

Animation* AnimationEditor::getAnimationData(const string& animationID, const string& modelID, string baseErrorMessage)
{
	// Check if animation is able to be retrieved
	if (!isAnimationExisting(animationID))
	{
		_fe3d.logger_throwWarning(baseErrorMessage + "animation not existing!");
	}
	else if (!isAnimationStarted(animationID, modelID))
	{
		_fe3d.logger_throwWarning(baseErrorMessage + "animation not started!");
	}
	else
	{
		return &_startedAnimations.at(make_pair(animationID, modelID));
	}

	return nullptr;
}