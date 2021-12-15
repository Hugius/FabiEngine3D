#include "animation2d_editor.hpp"
#include "logger.hpp"

void Animation2dEditor::startAnimation(const string& animationID, const string& billboardID, int timesToPlay)
{
	// Temporary values
	string errorMessage = "Tried to start animation with ID \"" + animationID + "\" on billboard with ID \"" + billboardID + "\": ";

	// Check if animation exists
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning(errorMessage + "animation not existing!");
	}

	// Check if billboard trying to animate exists
	if(!_fe3d.billboard_isExisting(billboardID))
	{
		Logger::throwWarning(errorMessage + "billboard not existing!");
	}

	// Check if animation has not already started
	if(isAnimationStarted(animationID, billboardID))
	{
		Logger::throwWarning(errorMessage + "animation already playing!");
	}

	// Check if animation play count is valid
	if((timesToPlay < -1) || (timesToPlay == 0))
	{
		Logger::throwWarning(errorMessage + "play count is invalid!");
	}

	// Copy animation
	auto animation = *_getAnimation(animationID);
	animation.setTimesToPlay(timesToPlay);

	// Start animation
	_startedAnimations.insert(make_pair(make_pair(animationID, billboardID), animation));
}

void Animation2dEditor::pauseAnimation(const string& animationID, const string& billboardID)
{
	// Temporary values
	string errorMessage = "Tried to pause animation with ID \"" + animationID + "\" on billboard with ID \"" + billboardID + "\": ";

	// Check if animation existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning(errorMessage + "animation not existing!");
	}

	// Check if animation not started
	if(!isAnimationStarted(animationID, billboardID))
	{
		Logger::throwWarning(errorMessage + "animation not started!");

	}

	// Check if animation is paused
	if(isAnimationPaused(animationID, billboardID))
	{
		Logger::throwWarning(errorMessage + "animation already paused!");
	}
		
	_startedAnimations.at(make_pair(animationID, billboardID)).setPaused(true);
}

void Animation2dEditor::resumeAnimation(const string& animationID, const string& billboardID)
{
	// Temporary values
	string errorMessage = "Tried to resume animation with ID \"" + animationID + "\" on billboard with ID \"" + billboardID + "\": ";

	// Check if animation existing
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

void Animation2dEditor::stopAnimation(const string& animationID, const string& billboardID)
{
	// Temporary values
	string errorMessage = "Tried to stop animation with ID \"" + animationID + "\" on billboard with ID \"" + billboardID + "\": ";

	// Check if animation existing
	if(isAnimationExisting(animationID))
	{
		// Check if animation is started
		if(isAnimationStarted(animationID, billboardID))
		{
			// Reset UV properties
			_fe3d.billboard_setMultiplierUV(billboardID, fvec2(1.0f));
			_fe3d.billboard_setAdderUV(billboardID, fvec2(0.0f));

			// Stop animation
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

void Animation2dEditor::stopAllAnimations()
{
	_startedAnimations.clear();
}