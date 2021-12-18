#include "animation2d_editor.hpp"
#include "logger.hpp"

void Animation2dEditor::startBillboardAnimation(const string& animationID, const string& billboardID, int timesToPlay)
{
	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	// Check if billboard not existing
	if(!_fe3d.billboard_isExisting(billboardID))
	{
		Logger::throwWarning("animation not existing!");
	}

	// Check if animation already started
	if(isBillboardAnimationStarted(animationID, billboardID))
	{
		Logger::throwWarning("animation already started!");
	}

	// Check if play count invalid
	if((timesToPlay < -1) || (timesToPlay == 0))
	{
		Logger::throwWarning("invalid play count!");
	}

	// Copy animation
	auto animation = *_getAnimation(animationID);
	animation.setTimesToPlay(timesToPlay);

	// Start animation
	_startedBillboardAnimations.insert(make_pair(make_pair(animationID, billboardID), animation));
}

void Animation2dEditor::pauseBillboardAnimation(const string& animationID, const string& billboardID)
{
	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	// Check if animation not started
	if(!isBillboardAnimationStarted(animationID, billboardID))
	{
		Logger::throwWarning("animation not started!");

	}

	// Check if animation paused
	if(isBillboardAnimationPaused(animationID, billboardID))
	{
		Logger::throwWarning("animation not playing!");
	}

	// Pause animation
	_startedBillboardAnimations.at(make_pair(animationID, billboardID)).setPaused(true);
}

void Animation2dEditor::resumeBillboardAnimation(const string& animationID, const string& billboardID)
{
	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	// Check if animation not started
	if(!isBillboardAnimationStarted(animationID, billboardID))
	{
		Logger::throwWarning("animation not started!");
	}

	// Check if animation not paused
	if(!isBillboardAnimationPaused(animationID, billboardID))
	{
		Logger::throwWarning("animation not paused!");
	}

	// Resume animation
	_startedBillboardAnimations.at(make_pair(animationID, billboardID)).setPaused(false);
}

void Animation2dEditor::stopBillboardAnimation(const string& animationID, const string& billboardID)
{
	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	// Check if animation not started
	if(!isBillboardAnimationStarted(animationID, billboardID))
	{
		Logger::throwWarning("animation not started!");
	}

	// Stop animation
	_startedBillboardAnimations.erase(make_pair(animationID, billboardID));
}

void Animation2dEditor::stopBillboardAnimations()
{
	_startedBillboardAnimations.clear();
}

void Animation2dEditor::startImageAnimation(const string& animationID, const string& imageID, int timesToPlay)
{
	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	// Check if image not existing
	if(!_fe3d.image_isExisting(imageID))
	{
		Logger::throwWarning("image not existing!");
	}

	// Check if animation already started
	if(isImageAnimationStarted(animationID, imageID))
	{
		Logger::throwWarning("animation already started!");
	}

	// Check if play count invalid
	if((timesToPlay < -1) || (timesToPlay == 0))
	{
		Logger::throwWarning("play count is invalid!");
	}

	// Copy animation
	auto animation = *_getAnimation(animationID);
	animation.setTimesToPlay(timesToPlay);

	// Start animation
	_startedImageAnimations.insert(make_pair(make_pair(animationID, imageID), animation));
}

void Animation2dEditor::pauseImageAnimation(const string& animationID, const string& imageID)
{
	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	// Check if animation not started
	if(!isImageAnimationStarted(animationID, imageID))
	{
		Logger::throwWarning("animation not started!");

	}

	// Check if animation paused
	if(isImageAnimationPaused(animationID, imageID))
	{
		Logger::throwWarning("animation not playing!");
	}

	// Pause animation
	_startedImageAnimations.at(make_pair(animationID, imageID)).setPaused(true);
}

void Animation2dEditor::resumeImageAnimation(const string& animationID, const string& imageID)
{
	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	// Check if animation not started
	if(!isImageAnimationStarted(animationID, imageID))
	{
		Logger::throwWarning("animation not started!");
	}

	// Check if animation not paused
	if(!isImageAnimationPaused(animationID, imageID))
	{
		Logger::throwWarning("animation not paused!");
	}

	// Resume animation
	_startedImageAnimations.at(make_pair(animationID, imageID)).setPaused(false);
}

void Animation2dEditor::stopImageAnimation(const string& animationID, const string& imageID)
{
	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	// Check if animation not started
	if(!isImageAnimationStarted(animationID, imageID))
	{
		Logger::throwWarning("animation not started!");
	}

	// Stop animation
	_startedImageAnimations.erase(make_pair(animationID, imageID));
}

void Animation2dEditor::stopImageAnimations()
{
	_startedImageAnimations.clear();
}

void Animation2dEditor::setBillboardAnimationFramestep(const string& animationID, const string& billboardID, unsigned int framestep)
{
	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	// Check if animation not started
	if(!isImageAnimationStarted(animationID, billboardID))
	{
		Logger::throwWarning("animation not started!");
	}

	// Set framestep
	_startedBillboardAnimations.at(make_pair(animationID, billboardID)).setFramestep(framestep);
}

void Animation2dEditor::setImageAnimationFramestep(const string& animationID, const string& imageID, unsigned int framestep)
{
	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	// Check if animation not started
	if(!isImageAnimationStarted(animationID, imageID))
	{
		Logger::throwWarning("animation not started!");
	}

	// Set framestep
	_startedImageAnimations.at(make_pair(animationID, imageID)).setFramestep(framestep);
}