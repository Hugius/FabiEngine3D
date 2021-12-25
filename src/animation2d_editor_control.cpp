#include "animation2d_editor.hpp"
#include "logger.hpp"

void Animation2dEditor::startBillboardAnimation(const string& animationID, const string& billboardID, int playCount)
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!_fe3d.billboard_isExisting(billboardID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(isBillboardAnimationStarted(animationID, billboardID))
	{
		Logger::throwWarning("animation already started!");
	}

	if((playCount < -1) || (playCount == 0))
	{
		Logger::throwWarning("invalid play count!");
	}

	auto animation = *_getAnimation(animationID);
	animation.setPlayCount(playCount);

	_startedBillboardAnimations.insert(make_pair(make_pair(animationID, billboardID), animation));
}

void Animation2dEditor::pauseBillboardAnimation(const string& animationID, const string& billboardID)
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isBillboardAnimationStarted(animationID, billboardID))
	{
		Logger::throwWarning("animation not started!");

	}

	if(isBillboardAnimationPaused(animationID, billboardID))
	{
		Logger::throwWarning("animation not playing!");
	}

	_startedBillboardAnimations.at(make_pair(animationID, billboardID)).setPaused(true);
}

void Animation2dEditor::resumeBillboardAnimation(const string& animationID, const string& billboardID)
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isBillboardAnimationStarted(animationID, billboardID))
	{
		Logger::throwWarning("animation not started!");
	}

	if(!isBillboardAnimationPaused(animationID, billboardID))
	{
		Logger::throwWarning("animation not paused!");
	}

	_startedBillboardAnimations.at(make_pair(animationID, billboardID)).setPaused(false);
}

void Animation2dEditor::stopBillboardAnimation(const string& animationID, const string& billboardID)
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isBillboardAnimationStarted(animationID, billboardID))
	{
		Logger::throwWarning("animation not started!");
	}

	_startedBillboardAnimations.erase(make_pair(animationID, billboardID));
}

void Animation2dEditor::pauseBillboardAnimations()
{
	for(auto& [idPair, animation] : _startedBillboardAnimations)
	{
		animation.setPaused(true);
	}
}

void Animation2dEditor::resumeBillboardAnimations()
{
	for(auto& [idPair, animation] : _startedBillboardAnimations)
	{
		animation.setPaused(false);
	}
}

void Animation2dEditor::stopBillboardAnimations()
{
	_startedBillboardAnimations.clear();
}

void Animation2dEditor::startImageAnimation(const string& animationID, const string& imageID, int playCount)
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!_fe3d.image_isExisting(imageID))
	{
		Logger::throwWarning("image not existing!");
	}

	if(isImageAnimationStarted(animationID, imageID))
	{
		Logger::throwWarning("animation already started!");
	}

	if((playCount < -1) || (playCount == 0))
	{
		Logger::throwWarning("play count is invalid!");
	}

	auto animation = *_getAnimation(animationID);
	animation.setPlayCount(playCount);

	_startedImageAnimations.insert(make_pair(make_pair(animationID, imageID), animation));
}

void Animation2dEditor::pauseImageAnimation(const string& animationID, const string& imageID)
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isImageAnimationStarted(animationID, imageID))
	{
		Logger::throwWarning("animation not started!");

	}

	if(isImageAnimationPaused(animationID, imageID))
	{
		Logger::throwWarning("animation not playing!");
	}

	_startedImageAnimations.at(make_pair(animationID, imageID)).setPaused(true);
}

void Animation2dEditor::resumeImageAnimation(const string& animationID, const string& imageID)
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isImageAnimationStarted(animationID, imageID))
	{
		Logger::throwWarning("animation not started!");
	}

	if(!isImageAnimationPaused(animationID, imageID))
	{
		Logger::throwWarning("animation not paused!");
	}

	_startedImageAnimations.at(make_pair(animationID, imageID)).setPaused(false);
}

void Animation2dEditor::stopImageAnimation(const string& animationID, const string& imageID)
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isImageAnimationStarted(animationID, imageID))
	{
		Logger::throwWarning("animation not started!");
	}

	_startedImageAnimations.erase(make_pair(animationID, imageID));
}

void Animation2dEditor::pauseImageAnimations()
{
	for(auto& [idPair, animation] : _startedImageAnimations)
	{
		animation.setPaused(true);
	}
}

void Animation2dEditor::resumeImageAnimations()
{
	for(auto& [idPair, animation] : _startedImageAnimations)
	{
		animation.setPaused(false);
	}
}

void Animation2dEditor::stopImageAnimations()
{
	_startedImageAnimations.clear();
}

void Animation2dEditor::setBillboardAnimationFramestep(const string& animationID, const string& billboardID, unsigned int value)
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isImageAnimationStarted(animationID, billboardID))
	{
		Logger::throwWarning("animation not started!");
	}

	_startedBillboardAnimations.at(make_pair(animationID, billboardID)).setFramestep(value);
}

void Animation2dEditor::setImageAnimationFramestep(const string& animationID, const string& imageID, unsigned int value)
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isImageAnimationStarted(animationID, imageID))
	{
		Logger::throwWarning("animation not started!");
	}

	_startedImageAnimations.at(make_pair(animationID, imageID)).setFramestep(value);
}