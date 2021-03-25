#include "animation_editor.hpp"

void AnimationEditor::startAnimation(const string& animationID, const string& modelID, int timesToPlay)
{
	// Temporary values
	string errorMessage = "Trying to start animation with ID \"" + animationID + "\" on model with ID \"" + modelID + "\": ";

	// Check if animation exists
	if (_isAnimationExisting(animationID))
	{
		// Check if model trying to animate exists
		if (_fe3d.modelEntity_isExisting(modelID))
		{
			// Check if animation has not already started
			if (!isAnimationStarted(animationID, modelID))
			{
				// Check if animation count is valid
				if (timesToPlay >= -1)
				{
					// Retrieve animation
					auto animation = _getAnimation(animationID);
					animation->animatedModelID = modelID;
					animation->timesToPlay = timesToPlay;
					animation->initialScaling = _fe3d.modelEntity_getSize(modelID);

					// Check if model has all the parts
					bool hasAllParts = true;
					for (auto& partName : animation->partNames)
					{
						// Part cannot be empty
						if (!partName.empty())
						{
							hasAllParts = hasAllParts && _fe3d.modelEntity_hasPart(modelID, partName);
						}
					}

					// Play animation
					if (hasAllParts)
					{
						_playingAnimations.insert(make_pair(make_pair(animationID, modelID), *animation));
					}
					else
					{
						_fe3d.logger_throwWarning(errorMessage + "model does not have required animation parts!");
					}
				}
				else
				{
					_fe3d.logger_throwWarning(errorMessage + "play count is invalid!");
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

bool AnimationEditor::isAnimationStarted(const string& animationID, const string& modelID)
{
	// Temporary values
	string errorMessage = "Trying to retrieve animation started status with ID \"" + animationID + "\" on model with ID \"" + modelID + "\": ";

	// Check if animation does not exist
	if (!_isAnimationExisting(animationID))
	{
		_fe3d.logger_throwWarning(errorMessage + "animation not existing!");
	}
	else
	{
		return _playingAnimations.find(make_pair(animationID, modelID)) != _playingAnimations.end();
	}

	return false;
}

bool AnimationEditor::isAnimationPlaying(const string& animationID, const string& modelID)
{
	// Temporary values
	string errorMessage = "Trying to retrieve animation playing status with ID \"" + animationID + "\" on model with ID \"" + modelID + "\": ";

	// Check if animation does not exist
	if (!_isAnimationExisting(animationID))
	{
		_fe3d.logger_throwWarning(errorMessage + "animation not existing!");
	}
	else if (!isAnimationStarted(animationID, modelID))
	{
		_fe3d.logger_throwWarning(errorMessage + "animation not started!");
	}
	else
	{
		return !_playingAnimations.at(make_pair(animationID, modelID)).isPaused;
	}

	return false;
}

bool AnimationEditor::isAnimationPaused(const string& animationID, const string& modelID)
{
	// Temporary values
	string errorMessage = "Trying to retrieve animation pausing status with ID \"" + animationID + "\" on model with ID \"" + modelID + "\": ";

	// Check if animation does not exist
	if (!_isAnimationExisting(animationID))
	{
		_fe3d.logger_throwWarning(errorMessage + "animation not existing!");
	}
	else if (!isAnimationStarted(animationID, modelID))
	{
		_fe3d.logger_throwWarning(errorMessage + "animation not started!");
	}
	else
	{
		return _playingAnimations.at(make_pair(animationID, modelID)).isPaused;
	}

	return false;
}

void AnimationEditor::pauseAnimation(const string& animationID, const string& modelID)
{
	// Temporary values
	string errorMessage = "Trying to pause animation with ID \"" + animationID + "\" on model with ID \"" + modelID + "\": ";

	// Check if animation exists
	if (_isAnimationExisting(animationID))
	{
		// Check if animation has already started
		if (isAnimationStarted(animationID, modelID))
		{
			// Check if animation is playing
			if (isAnimationPlaying(animationID, modelID))
			{
				_playingAnimations.at(make_pair(animationID, modelID)).isPaused = true;
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

void AnimationEditor::resumeAnimation(const string& animationID, const string& modelID)
{
	// Temporary values
	string errorMessage = "Trying to resume animation with ID \"" + animationID + "\" on model with ID \"" + modelID + "\": ";

	// Check if animation exists
	if (_isAnimationExisting(animationID))
	{
		// Check if animation has already started
		if (isAnimationStarted(animationID, modelID))
		{
			// Check if animation is paused
			if (isAnimationPaused(animationID, modelID))
			{
				_playingAnimations.at(make_pair(animationID, modelID)).isPaused = false;
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

	// Check if animation exists
	if (_isAnimationExisting(animationID))
	{
		// Check if animation has already started
		if (isAnimationStarted(animationID, modelID))
		{
			_playingAnimations.erase(make_pair(animationID, modelID));
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

void AnimationEditor::fadeAnimation(const string& animationID, const string& modelID, int framestep)
{
	// Temporary values
	string errorMessage = "Trying to fade animation with ID \"" + animationID + "\" on model with ID \"" + modelID + "\": ";

	// Check if animation exists
	if (_isAnimationExisting(animationID))
	{
		// Check if animation has already started
		if (isAnimationStarted(animationID, modelID))
		{
			// Check if animation is playing
			if (isAnimationPlaying(animationID, modelID))
			{
				_playingAnimations.at(make_pair(animationID, modelID)).fadeFramestep = framestep;
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

void AnimationEditor::setAnimationSpeedMultiplier(const string animationID, const string& modelID, float speed)
{
	// Temporary values
	string errorMessage = "Trying to set animation speed with ID \"" + animationID + "\" on model with ID \"" + modelID + "\": ";

	// Check if animation exists
	if (_isAnimationExisting(animationID))
	{
		// Check if animation has already started
		if (isAnimationStarted(animationID, modelID))
		{
			_playingAnimations.at(make_pair(animationID, modelID)).speedMultiplier = speed;
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

unsigned int AnimationEditor::getAnimationFrameIndex(const string& animationID, const string& modelID)
{
	// Temporary values
	string errorMessage = "Trying to retrieve animation frame index with ID \"" + animationID + "\" on model with ID \"" + modelID + "\": ";

	// Check if animation does not exist
	if (!_isAnimationExisting(animationID))
	{
		_fe3d.logger_throwWarning(errorMessage + "animation not existing!");
	}
	else if (!isAnimationStarted(animationID, modelID))
	{
		_fe3d.logger_throwWarning(errorMessage + "animation not started!");
	}
	else
	{
		return _playingAnimations.at(make_pair(animationID, modelID)).frameIndex;
	}

	return false;
}

void AnimationEditor::stopAllAnimations()
{
	_playingAnimations.clear();
}