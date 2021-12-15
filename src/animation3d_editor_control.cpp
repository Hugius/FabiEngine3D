#include "animation3d_editor.hpp"
#include "logger.hpp"

void Animation3dEditor::startAnimation(const string& animationID, const string& modelID, int timesToPlay)
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
				if(timesToPlay == -1 || timesToPlay > 0)
				{
					// Copy animation
					auto animation = *_getAnimation(animationID);
					animation.setTimesToPlay(timesToPlay);
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
					Logger::throwWarning(errorMessage + "play count is invalid!");
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

void Animation3dEditor::pauseAnimation(const string& animationID, const string& modelID)
{
	// Temporary values
	string errorMessage = "Tried to pause animation with ID \"" + animationID + "\" on model with ID \"" + modelID + "\": ";

	// Check if animation existing
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

void Animation3dEditor::resumeAnimation(const string& animationID, const string& modelID)
{
	// Temporary values
	string errorMessage = "Tried to resume animation with ID \"" + animationID + "\" on model with ID \"" + modelID + "\": ";

	// Check if animation existing
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

void Animation3dEditor::stopAnimation(const string& animationID, const string& modelID)
{
	// Temporary values
	string errorMessage = "Tried to stop animation with ID \"" + animationID + "\" on model with ID \"" + modelID + "\": ";

	// Check if animation existing
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

void Animation3dEditor::stopAllAnimations()
{
	_startedAnimations.clear();
}

void Animation3dEditor::fadeAnimation(const string& animationID, const string& modelID, unsigned int framestep)
{
	// Temporary values
	string errorMessage = "Tried to fade animation with ID \"" + animationID + "\" on model with ID \"" + modelID + "\": ";

	// Check if animation existing
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
					_startedAnimations.at(make_pair(animationID, modelID)).setFadeFramestep(framestep);
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