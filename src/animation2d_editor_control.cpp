#include "animation2d_editor.hpp"
#include "logger.hpp"

void Animation2dEditor::startBillboardAnimation(const string& animationID, const string& billboardID, int playCount)
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!_fe3d->billboard_isExisting(billboardID))
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
	for(auto& [key, animation] : _startedBillboardAnimations)
	{
		animation.setPaused(true);
	}
}

void Animation2dEditor::resumeBillboardAnimations()
{
	for(auto& [key, animation] : _startedBillboardAnimations)
	{
		animation.setPaused(false);
	}
}

void Animation2dEditor::stopBillboardAnimations()
{
	_startedBillboardAnimations.clear();
}

void Animation2dEditor::startQuadAnimation(const string& animationID, const string& quadID, int playCount)
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!_fe3d->quad_isExisting(quadID))
	{
		Logger::throwWarning("quad not existing!");
	}

	if(isQuadAnimationStarted(animationID, quadID))
	{
		Logger::throwWarning("animation already started!");
	}

	if((playCount < -1) || (playCount == 0))
	{
		Logger::throwWarning("play count is invalid!");
	}

	auto animation = *_getAnimation(animationID);
	animation.setPlayCount(playCount);

	_startedQuadAnimations.insert(make_pair(make_pair(animationID, quadID), animation));
}

void Animation2dEditor::pauseQuadAnimation(const string& animationID, const string& quadID)
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isQuadAnimationStarted(animationID, quadID))
	{
		Logger::throwWarning("animation not started!");

	}

	if(isQuadAnimationPaused(animationID, quadID))
	{
		Logger::throwWarning("animation not playing!");
	}

	_startedQuadAnimations.at(make_pair(animationID, quadID)).setPaused(true);
}

void Animation2dEditor::resumeQuadAnimation(const string& animationID, const string& quadID)
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isQuadAnimationStarted(animationID, quadID))
	{
		Logger::throwWarning("animation not started!");
	}

	if(!isQuadAnimationPaused(animationID, quadID))
	{
		Logger::throwWarning("animation not paused!");
	}

	_startedQuadAnimations.at(make_pair(animationID, quadID)).setPaused(false);
}

void Animation2dEditor::stopQuadAnimation(const string& animationID, const string& quadID)
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isQuadAnimationStarted(animationID, quadID))
	{
		Logger::throwWarning("animation not started!");
	}

	_startedQuadAnimations.erase(make_pair(animationID, quadID));
}

void Animation2dEditor::pauseQuadAnimations()
{
	for(auto& [key, animation] : _startedQuadAnimations)
	{
		animation.setPaused(true);
	}
}

void Animation2dEditor::resumeQuadAnimations()
{
	for(auto& [key, animation] : _startedQuadAnimations)
	{
		animation.setPaused(false);
	}
}

void Animation2dEditor::stopQuadAnimations()
{
	_startedQuadAnimations.clear();
}

void Animation2dEditor::setBillboardAnimationFramestep(const string& animationID, const string& billboardID, unsigned int value)
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isQuadAnimationStarted(animationID, billboardID))
	{
		Logger::throwWarning("animation not started!");
	}

	_startedBillboardAnimations.at(make_pair(animationID, billboardID)).setFramestep(value);
}

void Animation2dEditor::setQuadAnimationFramestep(const string& animationID, const string& quadID, unsigned int value)
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isQuadAnimationStarted(animationID, quadID))
	{
		Logger::throwWarning("animation not started!");
	}

	_startedQuadAnimations.at(make_pair(animationID, quadID)).setFramestep(value);
}