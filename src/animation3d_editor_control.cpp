#include "animation3d_editor.hpp"
#include "logger.hpp"

void Animation3dEditor::startModelAnimation(const string& animationID, const string& modelID, int playCount)
{
	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	// Check if model not existing
	if(!_fe3d.model_isExisting(modelID))
	{
		Logger::throwWarning("model not existing!");
	}

	// Check if animation already started
	if(isModelAnimationStarted(animationID, modelID))
	{
		Logger::throwWarning("animation already started!");
	}

	// Check if count invalid
	if((playCount < -1) || (playCount == 0))
	{
		Logger::throwWarning("play count is invalid!");
	}

	// Copy animation
	auto animation = *_getAnimation(animationID);
	animation.setPlayCount(playCount);
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
				Logger::throwWarning("model does not have required animation parts!");
			}
		}
	}

	// Start animation
	_startedModelAnimations.insert(make_pair(make_pair(animationID, modelID), animation));
}

void Animation3dEditor::autopauseModelAnimation(const string& animationID, const string& modelID)
{
	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	// Check if animation not started
	if(!isModelAnimationStarted(animationID, modelID))
	{
		Logger::throwWarning("animation not started!");
	}

	// Check if animation paused
	if(isModelAnimationPaused(animationID, modelID))
	{
		Logger::throwWarning("animation not playing!");
	}

	// Autopause animation
	_startedModelAnimations.at(make_pair(animationID, modelID)).setAutopaused(true);
}

void Animation3dEditor::pauseModelAnimation(const string& animationID, const string& modelID)
{
	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	// Check if animation not started
	if(!isModelAnimationStarted(animationID, modelID))
	{
		Logger::throwWarning("animation not started!");
	}

	// Check if animation paused
	if(isModelAnimationPaused(animationID, modelID))
	{
		Logger::throwWarning("animation not playing!");
	}

	// Pause animation
	_startedModelAnimations.at(make_pair(animationID, modelID)).setPaused(true);
}

void Animation3dEditor::resumeModelAnimation(const string& animationID, const string& modelID)
{
	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	// Check if animation not started
	if(!isModelAnimationStarted(animationID, modelID))
	{
		Logger::throwWarning("animation not started!");
	}

	// Check if animation not paused
	if(!isModelAnimationPaused(animationID, modelID))
	{
		Logger::throwWarning("animation not paused!");
	}

	// Resume animation
	_startedModelAnimations.at(make_pair(animationID, modelID)).setPaused(false);
}

void Animation3dEditor::fadeModelAnimation(const string& animationID, const string& modelID, unsigned int framestep)
{
	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	// Check if animation not started
	if(!isModelAnimationStarted(animationID, modelID))
	{
		Logger::throwWarning("animation not started!");
	}

	// Check if animation not playing
	if(!isModelAnimationPlaying(animationID, modelID))
	{
		Logger::throwWarning("animation not playing!");
	}

	// Check if animation is fading
	if(isModelAnimationFading(animationID, modelID))
	{
		Logger::throwWarning("animation already fading!");
	}

	// Fade animation
	_startedModelAnimations.at(make_pair(animationID, modelID)).setFadeFramestep(framestep);
}

void Animation3dEditor::stopModelAnimation(const string& animationID, const string& modelID)
{
	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	// Check if animation not started
	if(!isModelAnimationStarted(animationID, modelID))
	{
		Logger::throwWarning("animation not started!");
	}

	// Stop animation
	_startedModelAnimations.erase(make_pair(animationID, modelID));
}

void Animation3dEditor::stopModelAnimations()
{
	_startedModelAnimations.clear();
}

void Animation3dEditor::setModelAnimationSpeed(const string& animationID, const string& modelID, float value)
{
	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	// Check if animation not started
	if(!isModelAnimationStarted(animationID, modelID))
	{
		Logger::throwWarning("animation not started!");
	}

	// Set speed
	_startedModelAnimations.at(make_pair(animationID, modelID)).setSpeed(value);
}