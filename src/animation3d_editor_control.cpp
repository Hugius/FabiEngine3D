#include "animation3d_editor.hpp"
#include "logger.hpp"

void Animation3dEditor::startModelAnimation(const string& animationID, const string& modelID, int timesToPlay)
{
	// Temporary values
	string errorMessage = "Tried to start animation with ID \"" + animationID + "\" on model with ID \"" + modelID + "\": ";

	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning(errorMessage + "animation not existing!");
	}

	// Check if model not existing
	if(!_fe3d.model_isExisting(modelID))
	{
		Logger::throwWarning(errorMessage + "model not existing!");
	}

	// Check if animation already started
	if(isModelAnimationStarted(animationID, modelID))
	{
		Logger::throwWarning(errorMessage + "animation already started!");
	}

	// Check if count invalid
	if((timesToPlay < -1) || (timesToPlay == 0))
	{
		Logger::throwWarning(errorMessage + "play count is invalid!");
	}

	// Copy animation
	auto animation = *_getAnimation(animationID);
	animation.setTimesToPlay(timesToPlay);
	animation.setInitialSize(_fe3d.model_getBaseSize(modelID));

	// Check if model invalid
	bool hasAllParts = true;
	for(const auto& partID : animation.getPartIDs())
	{
		// Part cannot be empty
		if(!partID.empty())
		{
			if(!_fe3d.model_hasPart(modelID, partID))
			{
				Logger::throwWarning(errorMessage + "model does not have required animation parts!");
			}
		}
	}

	// Start animation
	_startedModelAnimations.insert(make_pair(make_pair(animationID, modelID), animation));
}

void Animation3dEditor::pauseModelAnimation(const string& animationID, const string& modelID)
{
	// Temporary values
	string errorMessage = "Tried to pause animation with ID \"" + animationID + "\" on model with ID \"" + modelID + "\": ";

	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning(errorMessage + "animation not existing!");
	}

	// Check if animation not started
	if(!isModelAnimationStarted(animationID, modelID))
	{
		Logger::throwWarning(errorMessage + "animation not started!");
	}

	// Check if animation paused
	if(isModelAnimationPaused(animationID, modelID))
	{
		Logger::throwWarning(errorMessage + "animation not playing!");
	}

	// Pause animation
	_startedModelAnimations.at(make_pair(animationID, modelID)).setPaused(true);
}

void Animation3dEditor::resumeModelAnimation(const string& animationID, const string& modelID)
{
	// Temporary values
	string errorMessage = "Tried to resume animation with ID \"" + animationID + "\" on model with ID \"" + modelID + "\": ";

	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning(errorMessage + "animation not existing!");
	}

	// Check if animation not started
	if(!isModelAnimationStarted(animationID, modelID))
	{
		Logger::throwWarning(errorMessage + "animation not started!");
	}

	// Check if animation not paused
	if(!isModelAnimationPaused(animationID, modelID))
	{
		Logger::throwWarning(errorMessage + "animation not paused!");
	}

	// Resume animation
	_startedModelAnimations.at(make_pair(animationID, modelID)).setPaused(false);
}

void Animation3dEditor::fadeModelAnimation(const string& animationID, const string& modelID, unsigned int framestep)
{
	// Temporary values
	string errorMessage = "Tried to fade animation with ID \"" + animationID + "\" on model with ID \"" + modelID + "\": ";

	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning(errorMessage + "animation not existing!");
	}

	// Check if animation not started
	if(!isModelAnimationStarted(animationID, modelID))
	{
		Logger::throwWarning(errorMessage + "animation not started!");
	}

	// Check if animation not playing
	if(!isModelAnimationPlaying(animationID, modelID))
	{
		Logger::throwWarning(errorMessage + "animation not playing!");
	}

	// Check if animation is fading
	if(isModelAnimationFading(animationID, modelID))
	{
		Logger::throwWarning(errorMessage + "animation already fading!");
	}

	// Fade animation
	_startedModelAnimations.at(make_pair(animationID, modelID)).setFadeFramestep(framestep);
}

void Animation3dEditor::stopModelAnimation(const string& animationID, const string& modelID)
{
	// Temporary values
	string errorMessage = "Tried to stop animation with ID \"" + animationID + "\" on model with ID \"" + modelID + "\": ";

	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning(errorMessage + "animation not existing!");
	}

	// Check if animation not started
	if(!isModelAnimationStarted(animationID, modelID))
	{
		Logger::throwWarning(errorMessage + "animation not started!");
	}

	// Stop animation
	_startedModelAnimations.erase(make_pair(animationID, modelID));
}

void Animation3dEditor::stopModelAnimations()
{
	_startedModelAnimations.clear();
}