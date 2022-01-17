#include "animation2d_editor.hpp"
#include "logger.hpp"

void Animation2dEditor::startBillboardAnimation(const string& animationID, const string& billboardID, int playCount)
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!_fe3d->quad3d_isExisting(billboardID))
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

void Animation2dEditor::autopauseBillboardAnimation(const string& animationID, const string& billboardID)
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

	_startedBillboardAnimations.at(make_pair(animationID, billboardID)).setAutopaused(true);
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

void Animation2dEditor::autopauseBillboardAnimations()
{
	for(auto& [key, animation] : _startedBillboardAnimations)
	{
		animation.setAutopaused(true);
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

void Animation2dEditor::startQuad2dAnimation(const string& animationID, const string& quadID, int playCount)
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!_fe3d->quad2d_isExisting(quadID))
	{
		Logger::throwWarning("quad not existing!");
	}

	if(isQuad2dAnimationStarted(animationID, quadID))
	{
		Logger::throwWarning("animation already started!");
	}

	if((playCount < -1) || (playCount == 0))
	{
		Logger::throwWarning("play count is invalid!");
	}

	auto animation = *_getAnimation(animationID);
	animation.setPlayCount(playCount);

	_startedQuad2dAnimations.insert(make_pair(make_pair(animationID, quadID), animation));
}

void Animation2dEditor::pauseQuad2dAnimation(const string& animationID, const string& quadID)
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isQuad2dAnimationStarted(animationID, quadID))
	{
		Logger::throwWarning("animation not started!");

	}

	if(isQuad2dAnimationPaused(animationID, quadID))
	{
		Logger::throwWarning("animation not playing!");
	}

	_startedQuad2dAnimations.at(make_pair(animationID, quadID)).setPaused(true);
}

void Animation2dEditor::autopauseQuad2dAnimation(const string& animationID, const string& quadID)
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isQuad2dAnimationStarted(animationID, quadID))
	{
		Logger::throwWarning("animation not started!");

	}

	if(isQuad2dAnimationPaused(animationID, quadID))
	{
		Logger::throwWarning("animation not playing!");
	}

	_startedQuad2dAnimations.at(make_pair(animationID, quadID)).setAutopaused(true);
}

void Animation2dEditor::resumeQuad2dAnimation(const string& animationID, const string& quadID)
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isQuad2dAnimationStarted(animationID, quadID))
	{
		Logger::throwWarning("animation not started!");
	}

	if(!isQuad2dAnimationPaused(animationID, quadID))
	{
		Logger::throwWarning("animation not paused!");
	}

	_startedQuad2dAnimations.at(make_pair(animationID, quadID)).setPaused(false);
}

void Animation2dEditor::stopQuad2dAnimation(const string& animationID, const string& quadID)
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isQuad2dAnimationStarted(animationID, quadID))
	{
		Logger::throwWarning("animation not started!");
	}

	_startedQuad2dAnimations.erase(make_pair(animationID, quadID));
}

void Animation2dEditor::pauseQuad2dAnimations()
{
	for(auto& [key, animation] : _startedQuad2dAnimations)
	{
		animation.setPaused(true);
	}
}

void Animation2dEditor::autopauseQuad2dAnimations()
{
	for(auto& [key, animation] : _startedQuad2dAnimations)
	{
		animation.setAutopaused(true);
	}
}

void Animation2dEditor::resumeQuad2dAnimations()
{
	for(auto& [key, animation] : _startedQuad2dAnimations)
	{
		animation.setPaused(false);
	}
}

void Animation2dEditor::stopQuad2dAnimations()
{
	_startedQuad2dAnimations.clear();
}

void Animation2dEditor::setBillboardAnimationFramestep(const string& animationID, const string& billboardID, unsigned int value)
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isQuad2dAnimationStarted(animationID, billboardID))
	{
		Logger::throwWarning("animation not started!");
	}

	_startedBillboardAnimations.at(make_pair(animationID, billboardID)).setFramestep(value);
}

void Animation2dEditor::setQuad2dAnimationFramestep(const string& animationID, const string& quadID, unsigned int value)
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isQuad2dAnimationStarted(animationID, quadID))
	{
		Logger::throwWarning("animation not started!");
	}

	_startedQuad2dAnimations.at(make_pair(animationID, quadID)).setFramestep(value);
}