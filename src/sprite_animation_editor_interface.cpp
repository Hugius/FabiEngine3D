#include "sprite_animation_editor.hpp"
#include "logger.hpp"

void SpriteAnimationEditor::startAnimation(const string& animationID, const string& billboardID, int loops)
{
	// Temporary values
	string errorMessage = "Tried to start animation with ID \"" + animationID + "\" on billboard with ID \"" + billboardID + "\": ";

	// Check if animation exists
	if(isAnimationExisting(animationID))
	{
		// Check if billboard trying to animate exists
		if(_fe3d.billboard_isExisting(billboardID))
		{
			// Check if animation has not already started
			if(!isAnimationStarted(animationID, billboardID))
			{
				// Check if animation count is valid
				if(loops >= -1)
				{
					// Retrieve animation
					auto animation = *_getAnimation(animationID);
					animation.setTimesToPlay((loops == -1) ? -1 : (loops + 1));

					// Start animation
					_startedAnimations.insert(make_pair(make_pair(animationID, billboardID), animation));
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
			Logger::throwWarning(errorMessage + "billboard not existing!");
		}
	}
	else
	{
		Logger::throwWarning(errorMessage + "animation not existing!");
	}
}

const bool SpriteAnimationEditor::isAnimationExisting(const string& ID) const
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

const bool SpriteAnimationEditor::isAnimationStarted(const string& animationID, const string& billboardID) const
{
	// Temporary values
	string errorMessage = "Tried to retrieve animation started status with ID \"" + animationID + "\" on billboard with ID \"" + billboardID + "\": ";

	// Check if animation does not exist
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning(errorMessage + "animation not existing!");
	}
	else
	{
		return _startedAnimations.find(make_pair(animationID, billboardID)) != _startedAnimations.end();
	}

	return false;
}

const bool SpriteAnimationEditor::isAnimationPlaying(const string& animationID, const string& billboardID) const
{
	// Temporary values
	string errorMessage = "Tried to retrieve animation playing status with ID \"" + animationID + "\" on billboard with ID \"" + billboardID + "\": ";

	// Check if animation is able to be retrieved
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning(errorMessage + "animation not existing!");
	}
	else if(!isAnimationStarted(animationID, billboardID))
	{
		Logger::throwWarning(errorMessage + "animation not started!");
	}
	else
	{
		return !_startedAnimations.at(make_pair(animationID, billboardID)).isPaused();
	}

	return false;
}

const bool SpriteAnimationEditor::isAnimationPaused(const string& animationID, const string& billboardID) const
{
	// Temporary values
	string errorMessage = "Tried to retrieve animation pausing status with ID \"" + animationID + "\" on billboard with ID \"" + billboardID + "\": ";

	// Check if animation is able to be retrieved
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning(errorMessage + "animation not existing!");
	}
	else if(!isAnimationStarted(animationID, billboardID))
	{
		Logger::throwWarning(errorMessage + "animation not started!");
	}
	else
	{
		return _startedAnimations.at(make_pair(animationID, billboardID)).isPaused();
	}

	return false;
}

void SpriteAnimationEditor::pauseAnimation(const string& animationID, const string& billboardID)
{
	// Temporary values
	string errorMessage = "Tried to pause animation with ID \"" + animationID + "\" on billboard with ID \"" + billboardID + "\": ";

	// Check if animation is existing
	if(isAnimationExisting(animationID))
	{
		// Check if animation is started
		if(isAnimationStarted(animationID, billboardID))
		{
			// Check if animation is paused
			if(isAnimationPaused(animationID, billboardID))
			{
				Logger::throwWarning(errorMessage + "animation already paused!");
			}
			else
			{
				_startedAnimations.at(make_pair(animationID, billboardID)).setPaused(true);
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

void SpriteAnimationEditor::resumeAnimation(const string& animationID, const string& billboardID)
{
	// Temporary values
	string errorMessage = "Tried to resume animation with ID \"" + animationID + "\" on billboard with ID \"" + billboardID + "\": ";

	// Check if animation is existing
	if(isAnimationExisting(animationID))
	{
		// Check if animation is started
		if(isAnimationStarted(animationID, billboardID))
		{
			// Check if animation is paused
			if(isAnimationPaused(animationID, billboardID))
			{
				_startedAnimations.at(make_pair(animationID, billboardID)).setPaused(false);
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

void SpriteAnimationEditor::stopAnimation(const string& animationID, const string& billboardID)
{
	// Temporary values
	string errorMessage = "Tried to stop animation with ID \"" + animationID + "\" on billboard with ID \"" + billboardID + "\": ";

	// Check if animation is existing
	if(isAnimationExisting(animationID))
	{
		// Check if animation is started
		if(isAnimationStarted(animationID, billboardID))
		{
			_startedAnimations.erase(make_pair(animationID, billboardID));
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

void SpriteAnimationEditor::stopAllAnimations()
{
	_startedAnimations.clear();
}