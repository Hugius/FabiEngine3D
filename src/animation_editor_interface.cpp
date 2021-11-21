#include "animation_editor.hpp"
#include "logger.hpp"

using std::max;

void AnimationEditor::startAnimation(const string& animationID, const string& modelID, int loops)
{
	// Temporary values
	string errorMessage = "Tried to start animation with ID \"" + animationID + "\" on model with ID \"" + modelID + "\": ";

	// Check if animation exists
	if(isAnimationExisting(animationID))
	{
		// Check if model trying to animate exists
		if(_fe3d.model_isExisting(modelID))
		{
			// Check if animation has not already started
			if(!isAnimationStarted(animationID, modelID))
			{
				// Check if animation count is valid
				if(loops >= -1)
				{
					// Retrieve animation
					auto animation = *_getAnimation(animationID);
					animation.setAnimatedModelID(modelID);
					animation.setTimesToPlay((loops == -1) ? -1 : (loops + 1));
					animation.setInitialSize(_fe3d.model_getBaseSize(modelID));

					// Check if model has all the parts
					bool hasAllParts = true;
					for(const auto& partID : animation.getPartIDs())
					{
						// Part cannot be empty
						if(!partID.empty())
						{
							hasAllParts = (hasAllParts && _fe3d.model_hasPart(modelID, partID));
						}
					}

					// Start animation
					if(hasAllParts)
					{
						_startedAnimations.insert(make_pair(make_pair(animationID, modelID), animation));
					}
					else
					{
						Logger::throwWarning(errorMessage + "model does not have required animation parts!");
					}
				}
				else
				{
					Logger::throwWarning(errorMessage + "loop count is invalid!");
				}
			}
			else
			{
				Logger::throwWarning(errorMessage + "animation already playing!");
			}
		}
		else
		{
			Logger::throwWarning(errorMessage + "model not existing!");
		}
	}
	else
	{
		Logger::throwWarning(errorMessage + "animation not existing!");
	}
}

const bool AnimationEditor::isAnimationExisting(const string& ID) const
{
	for(const auto& animation : _animations)
	{
		if(animation->getID() == ID)
		{
			return true;
		}
	}

	return false;
}

const bool AnimationEditor::isAnimationStarted(const string& animationID, const string& modelID) const
{
	// Temporary values
	string errorMessage = "Tried to retrieve animation started status with ID \"" + animationID + "\" on model with ID \"" + modelID + "\": ";

	// Check if animation does not exist
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning(errorMessage + "animation not existing!");
	}
	else
	{
		return _startedAnimations.find(make_pair(animationID, modelID)) != _startedAnimations.end();
	}

	return false;
}

const bool AnimationEditor::isAnimationPlaying(const string& animationID, const string& modelID) const
{
	// Temporary values
	string errorMessage = "Tried to retrieve animation playing status with ID \"" + animationID + "\" on model with ID \"" + modelID + "\": ";

	// Check if animation is able to be retrieved
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning(errorMessage + "animation not existing!");
	}
	else if(!isAnimationStarted(animationID, modelID))
	{
		Logger::throwWarning(errorMessage + "animation not started!");
	}
	else
	{
		return !_startedAnimations.at(make_pair(animationID, modelID)).isPaused();
	}

	return false;
}

const bool AnimationEditor::isAnimationPaused(const string& animationID, const string& modelID) const
{
	// Temporary values
	string errorMessage = "Tried to retrieve animation pausing status with ID \"" + animationID + "\" on model with ID \"" + modelID + "\": ";

	// Check if animation is able to be retrieved
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning(errorMessage + "animation not existing!");
	}
	else if(!isAnimationStarted(animationID, modelID))
	{
		Logger::throwWarning(errorMessage + "animation not started!");
	}
	else
	{
		return _startedAnimations.at(make_pair(animationID, modelID)).isPaused();
	}

	return false;
}

const bool AnimationEditor::isAnimationFading(const string& animationID, const string& modelID) const
{
	// Temporary values
	string errorMessage = "Tried to retrieve animation fading status with ID \"" + animationID + "\" on model with ID \"" + modelID + "\": ";

	// Check if animation is able to be retrieved
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning(errorMessage + "animation not existing!");
	}
	else if(!isAnimationStarted(animationID, modelID))
	{
		Logger::throwWarning(errorMessage + "animation not started!");
	}
	else
	{
		return (_startedAnimations.at(make_pair(animationID, modelID)).getFadeFramestep() != -1);
	}

	return false;
}

void AnimationEditor::pauseAnimation(const string& animationID, const string& modelID)
{
	// Temporary values
	string errorMessage = "Tried to pause animation with ID \"" + animationID + "\" on model with ID \"" + modelID + "\": ";

	// Check if animation is existing
	if(isAnimationExisting(animationID))
	{
		// Check if animation is started
		if(isAnimationStarted(animationID, modelID))
		{
			// Check if animation is paused
			if(isAnimationPaused(animationID, modelID))
			{
				Logger::throwWarning(errorMessage + "animation already paused!");
			}
			else
			{
				_startedAnimations.at(make_pair(animationID, modelID)).setPaused(true);
			}
		}
		else
		{
			Logger::throwWarning(errorMessage + "animation not started!");
		}
	}
	else
	{
		Logger::throwWarning(errorMessage + "animation not existing!");
	}
}

void AnimationEditor::resumeAnimation(const string& animationID, const string& modelID)
{
	// Temporary values
	string errorMessage = "Tried to resume animation with ID \"" + animationID + "\" on model with ID \"" + modelID + "\": ";

	// Check if animation is existing
	if(isAnimationExisting(animationID))
	{
		// Check if animation is started
		if(isAnimationStarted(animationID, modelID))
		{
			// Check if animation is paused
			if(isAnimationPaused(animationID, modelID))
			{
				_startedAnimations.at(make_pair(animationID, modelID)).setPaused(false);
			}
			else
			{
				Logger::throwWarning(errorMessage + "animation already playing!");
			}
		}
		else
		{
			Logger::throwWarning(errorMessage + "animation not started!");
		}
	}
	else
	{
		Logger::throwWarning(errorMessage + "animation not existing!");
	}
}

void AnimationEditor::stopAnimation(const string& animationID, const string& modelID)
{
	// Temporary values
	string errorMessage = "Tried to stop animation with ID \"" + animationID + "\" on model with ID \"" + modelID + "\": ";

	// Check if animation is existing
	if(isAnimationExisting(animationID))
	{
		// Check if animation is started
		if(isAnimationStarted(animationID, modelID))
		{
			_startedAnimations.erase(make_pair(animationID, modelID));
		}
		else
		{
			Logger::throwWarning(errorMessage + "animation not started!");
		}
	}
	else
	{
		Logger::throwWarning(errorMessage + "animation not existing!");
	}
}

void AnimationEditor::stopAllAnimations()
{
	_startedAnimations.clear();
}

void AnimationEditor::fadeAnimation(const string& animationID, const string& modelID, int framestep)
{
	// Temporary values
	string errorMessage = "Tried to fade animation with ID \"" + animationID + "\" on model with ID \"" + modelID + "\": ";

	// Check if animation is existing
	if(isAnimationExisting(animationID))
	{
		// Check if animation is started
		if(isAnimationStarted(animationID, modelID))
		{
			// Check if animation is playing
			if(isAnimationPlaying(animationID, modelID))
			{
				// Check if animation is fading
				if(isAnimationFading(animationID, modelID))
				{
					Logger::throwWarning(errorMessage + "animation already fading!");
				}
				else
				{
					_startedAnimations.at(make_pair(animationID, modelID)).setFadeFramestep(max(0, framestep));
				}
			}
			else
			{
				Logger::throwWarning(errorMessage + "animation not playing!");
			}
		}
		else
		{
			Logger::throwWarning(errorMessage + "animation not started!");
		}
	}
	else
	{
		Logger::throwWarning(errorMessage + "animation not existing!");
	}
}

Animation* AnimationEditor::getAnimationData(const string& animationID, const string& modelID, string baseErrorMessage)
{
	// Check if animation is able to be retrieved
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning(baseErrorMessage + "animation not existing!");
	}
	else if(!isAnimationStarted(animationID, modelID))
	{
		Logger::throwWarning(baseErrorMessage + "animation not started!");
	}
	else
	{
		return &_startedAnimations.at(make_pair(animationID, modelID));
	}

	return nullptr;
}