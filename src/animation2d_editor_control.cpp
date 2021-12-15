#include "animation2d_editor.hpp"
#include "logger.hpp"

void Animation2dEditor::startBillboardAnimation(const string& animationID, const string& billboardID, int timesToPlay)
{
	// Temporary values
	string errorMessage = "Tried to start animation with ID \"" + animationID + "\" on billboard with ID \"" + billboardID + "\": ";

	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning(errorMessage + "animation not existing!");
	}

	// Check if billboard not existing
	if(!_fe3d.billboard_isExisting(billboardID))
	{
		Logger::throwWarning(errorMessage + "billboard not existing!");
	}

	// Check if animation already started
	if(isBillboardAnimationStarted(animationID, billboardID))
	{
		Logger::throwWarning(errorMessage + "animation already started!");
	}

	// Check if play count invalid
	if((timesToPlay < -1) || (timesToPlay == 0))
	{
		Logger::throwWarning(errorMessage + "play count is invalid!");
	}

	// Copy animation
	auto animation = *_getAnimation(animationID);
	animation.setTimesToPlay(timesToPlay);

	// Start animation
	_startedBillboardAnimations.insert(make_pair(make_pair(animationID, billboardID), animation));
}

void Animation2dEditor::pauseBillboardAnimation(const string& animationID, const string& billboardID)
{
	// Temporary values
	string errorMessage = "Tried to pause animation with ID \"" + animationID + "\" on billboard with ID \"" + billboardID + "\": ";

	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning(errorMessage + "animation not existing!");
	}

	// Check if animation not started
	if(!isBillboardAnimationStarted(animationID, billboardID))
	{
		Logger::throwWarning(errorMessage + "animation not started!");

	}

	// Check if animation is paused
	if(isBillboardAnimationPaused(animationID, billboardID))
	{
		Logger::throwWarning(errorMessage + "animation already paused!");
	}

	// Pause animation
	_startedBillboardAnimations.at(make_pair(animationID, billboardID)).setPaused(true);
}

void Animation2dEditor::resumeBillboardAnimation(const string& animationID, const string& billboardID)
{
	// Temporary values
	string errorMessage = "Tried to resume animation with ID \"" + animationID + "\" on billboard with ID \"" + billboardID + "\": ";

	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning(errorMessage + "animation not existing!");
	}

	// Check if animation not started
	if(!isBillboardAnimationStarted(animationID, billboardID))
	{
		Logger::throwWarning(errorMessage + "animation not started!");
	}

	// Check if animation not paused
	if(!isBillboardAnimationPaused(animationID, billboardID))
	{
		Logger::throwWarning(errorMessage + "animation already playing!");
	}

	// Resume animation
	_startedBillboardAnimations.at(make_pair(animationID, billboardID)).setPaused(false);
}

void Animation2dEditor::stopBillboardAnimation(const string& animationID, const string& billboardID)
{
	// Temporary values
	string errorMessage = "Tried to stop animation with ID \"" + animationID + "\" on billboard with ID \"" + billboardID + "\": ";

	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning(errorMessage + "animation not existing!");
	}

	// Check if animation not started
	if(!isBillboardAnimationStarted(animationID, billboardID))
	{
		Logger::throwWarning(errorMessage + "animation not started!");
	}

	// Reset UV properties
	_fe3d.billboard_setMultiplierUV(billboardID, fvec2(1.0f));
	_fe3d.billboard_setAdderUV(billboardID, fvec2(0.0f));

	// Stop animation
	_startedBillboardAnimations.erase(make_pair(animationID, billboardID));
}

void Animation2dEditor::stopBillboardAnimations()
{
	_startedBillboardAnimations.clear();
}

void Animation2dEditor::startImageAnimation(const string& animationID, const string& imageID, int timesToPlay)
{
	// Temporary values
	string errorMessage = "Tried to start animation with ID \"" + animationID + "\" on image with ID \"" + imageID + "\": ";

	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning(errorMessage + "animation not existing!");
	}

	// Check if image not existing
	if(!_fe3d.image_isExisting(imageID))
	{
		Logger::throwWarning(errorMessage + "image not existing!");
	}

	// Check if animation already started
	if(isImageAnimationStarted(animationID, imageID))
	{
		Logger::throwWarning(errorMessage + "animation already started!");
	}

	// Check if play count invalid
	if((timesToPlay < -1) || (timesToPlay == 0))
	{
		Logger::throwWarning(errorMessage + "play count is invalid!");
	}

	// Copy animation
	auto animation = *_getAnimation(animationID);
	animation.setTimesToPlay(timesToPlay);

	// Start animation
	_startedImageAnimations.insert(make_pair(make_pair(animationID, imageID), animation));
}

void Animation2dEditor::pauseImageAnimation(const string& animationID, const string& imageID)
{
	// Temporary values
	string errorMessage = "Tried to pause animation with ID \"" + animationID + "\" on image with ID \"" + imageID + "\": ";

	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning(errorMessage + "animation not existing!");
	}

	// Check if animation not started
	if(!isImageAnimationStarted(animationID, imageID))
	{
		Logger::throwWarning(errorMessage + "animation not started!");

	}

	// Check if animation is paused
	if(isImageAnimationPaused(animationID, imageID))
	{
		Logger::throwWarning(errorMessage + "animation already paused!");
	}

	// Pause animation
	_startedImageAnimations.at(make_pair(animationID, imageID)).setPaused(true);
}

void Animation2dEditor::resumeImageAnimation(const string& animationID, const string& imageID)
{
	// Temporary values
	string errorMessage = "Tried to resume animation with ID \"" + animationID + "\" on image with ID \"" + imageID + "\": ";

	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning(errorMessage + "animation not existing!");
	}

	// Check if animation not started
	if(!isImageAnimationStarted(animationID, imageID))
	{
		Logger::throwWarning(errorMessage + "animation not started!");
	}

	// Check if animation not paused
	if(!isImageAnimationPaused(animationID, imageID))
	{
		Logger::throwWarning(errorMessage + "animation already playing!");
	}

	// Resume animation
	_startedImageAnimations.at(make_pair(animationID, imageID)).setPaused(false);
}

void Animation2dEditor::stopImageAnimation(const string& animationID, const string& imageID)
{
	// Temporary values
	string errorMessage = "Tried to stop animation with ID \"" + animationID + "\" on image with ID \"" + imageID + "\": ";

	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning(errorMessage + "animation not existing!");
	}

	// Check if animation not started
	if(!isImageAnimationStarted(animationID, imageID))
	{
		Logger::throwWarning(errorMessage + "animation not started!");
	}

	// Reset UV properties
	_fe3d.image_setMultiplierUV(imageID, fvec2(1.0f));
	_fe3d.image_setAdderUV(imageID, fvec2(0.0f));

	// Stop animation
	_startedImageAnimations.erase(make_pair(animationID, imageID));
}

void Animation2dEditor::stopImageAnimations()
{
	_startedImageAnimations.clear();
}