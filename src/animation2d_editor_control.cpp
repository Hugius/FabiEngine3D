#include "animation2d_editor.hpp"
#include "logger.hpp"

void Animation2dEditor::startQuad3dAnimation(const string& animationID, const string& quad3dID, int playCount)
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!_fe3d->quad3d_isExisting(quad3dID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(isQuad3dAnimationStarted(animationID, quad3dID))
	{
		Logger::throwWarning("animation already started!");
	}

	if((playCount < -1) || (playCount == 0))
	{
		Logger::throwWarning("invalid play count!");
	}

	auto animation = *_getAnimation(animationID);
	animation.setPlayCount(playCount);

	_startedQuad3dAnimations.insert(make_pair(make_pair(animationID, quad3dID), animation));
}

void Animation2dEditor::pauseQuad3dAnimation(const string& animationID, const string& quad3dID)
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isQuad3dAnimationStarted(animationID, quad3dID))
	{
		Logger::throwWarning("animation not started!");

	}

	if(isQuad3dAnimationPaused(animationID, quad3dID))
	{
		Logger::throwWarning("animation not playing!");
	}

	_startedQuad3dAnimations.at(make_pair(animationID, quad3dID)).setPaused(true);
}

void Animation2dEditor::autopauseQuad3dAnimation(const string& animationID, const string& quad3dID)
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isQuad3dAnimationStarted(animationID, quad3dID))
	{
		Logger::throwWarning("animation not started!");

	}

	if(isQuad3dAnimationPaused(animationID, quad3dID))
	{
		Logger::throwWarning("animation not playing!");
	}

	_startedQuad3dAnimations.at(make_pair(animationID, quad3dID)).setAutopaused(true);
}

void Animation2dEditor::resumeQuad3dAnimation(const string& animationID, const string& quad3dID)
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isQuad3dAnimationStarted(animationID, quad3dID))
	{
		Logger::throwWarning("animation not started!");
	}

	if(!isQuad3dAnimationPaused(animationID, quad3dID))
	{
		Logger::throwWarning("animation not paused!");
	}

	_startedQuad3dAnimations.at(make_pair(animationID, quad3dID)).setPaused(false);
}

void Animation2dEditor::stopQuad3dAnimation(const string& animationID, const string& quad3dID)
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isQuad3dAnimationStarted(animationID, quad3dID))
	{
		Logger::throwWarning("animation not started!");
	}

	_startedQuad3dAnimations.erase(make_pair(animationID, quad3dID));
}

void Animation2dEditor::pauseQuad3dAnimations()
{
	for(auto& [key, animation] : _startedQuad3dAnimations)
	{
		animation.setPaused(true);
	}
}

void Animation2dEditor::autopauseQuad3dAnimations()
{
	for(auto& [key, animation] : _startedQuad3dAnimations)
	{
		animation.setAutopaused(true);
	}
}

void Animation2dEditor::resumeQuad3dAnimations()
{
	for(auto& [key, animation] : _startedQuad3dAnimations)
	{
		animation.setPaused(false);
	}
}

void Animation2dEditor::stopQuad3dAnimations()
{
	_startedQuad3dAnimations.clear();
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

void Animation2dEditor::setQuad3dAnimationFramestep(const string& animationID, const string& quad3dID, unsigned int value)
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isQuad2dAnimationStarted(animationID, quad3dID))
	{
		Logger::throwWarning("animation not started!");
	}

	_startedQuad3dAnimations.at(make_pair(animationID, quad3dID)).setFramestep(value);
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