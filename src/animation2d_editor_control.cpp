#include "animation2d_editor.hpp"
#include "logger.hpp"

void Animation2dEditor::startQuad3dAnimation(const string& animationId, const string& quadId, int playCount)
{
	if(!isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_fe3d->quad3d_isExisting(quadId))
	{
		abort();
	}
	if(isQuad3dAnimationStarted(animationId, quadId))
	{
		abort();
	}
	if((playCount < -1) || (playCount == 0))
	{
		abort();
	}

	auto animation = *_getAnimation(animationId);
	animation.setPlayCount(playCount);

	_startedQuad3dAnimations.insert(make_pair(make_pair(animationId, quadId), animation));
}

void Animation2dEditor::pauseQuad3dAnimation(const string& animationId, const string& quadId)
{
	if(!isAnimationExisting(animationId))
	{
		abort();
	}
	if(!isQuad3dAnimationStarted(animationId, quadId))
	{
		abort();

	}
	if(isQuad3dAnimationPaused(animationId, quadId))
	{
		abort();
	}

	_startedQuad3dAnimations.at(make_pair(animationId, quadId)).setPaused(true);
}

void Animation2dEditor::autopauseQuad3dAnimation(const string& animationId, const string& quadId)
{
	if(!isAnimationExisting(animationId))
	{
		abort();
	}
	if(!isQuad3dAnimationStarted(animationId, quadId))
	{
		abort();

	}
	if(isQuad3dAnimationPaused(animationId, quadId))
	{
		abort();
	}

	_startedQuad3dAnimations.at(make_pair(animationId, quadId)).setAutopaused(true);
}

void Animation2dEditor::resumeQuad3dAnimation(const string& animationId, const string& quadId)
{
	if(!isAnimationExisting(animationId))
	{
		abort();
	}
	if(!isQuad3dAnimationStarted(animationId, quadId))
	{
		abort();
	}
	if(!isQuad3dAnimationPaused(animationId, quadId))
	{
		abort();
	}

	_startedQuad3dAnimations.at(make_pair(animationId, quadId)).setPaused(false);
}

void Animation2dEditor::stopQuad3dAnimation(const string& animationId, const string& quadId)
{
	if(!isAnimationExisting(animationId))
	{
		abort();
	}
	if(!isQuad3dAnimationStarted(animationId, quadId))
	{
		abort();
	}

	_startedQuad3dAnimations.erase(make_pair(animationId, quadId));
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

void Animation2dEditor::setQuad3dAnimationInterval(const string& animationId, const string& quadId, unsigned int value)
{
	if(!isAnimationExisting(animationId))
	{
		abort();
	}
	if(!isQuad3dAnimationStarted(animationId, quadId))
	{
		abort();
	}

	_startedQuad3dAnimations.at(make_pair(animationId, quadId)).setInterval(value);
}

void Animation2dEditor::startQuad2dAnimation(const string& animationId, const string& quadId, int playCount)
{
	if(!isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_fe3d->quad2d_isExisting(quadId))
	{
		abort();
	}
	if(isQuad2dAnimationStarted(animationId, quadId))
	{
		abort();
	}
	if((playCount < -1) || (playCount == 0))
	{
		abort();
	}

	auto animation = *_getAnimation(animationId);
	animation.setPlayCount(playCount);

	_startedQuad2dAnimations.insert(make_pair(make_pair(animationId, quadId), animation));
}

void Animation2dEditor::pauseQuad2dAnimation(const string& animationId, const string& quadId)
{
	if(!isAnimationExisting(animationId))
	{
		abort();
	}
	if(!isQuad2dAnimationStarted(animationId, quadId))
	{
		abort();

	}
	if(isQuad2dAnimationPaused(animationId, quadId))
	{
		abort();
	}

	_startedQuad2dAnimations.at(make_pair(animationId, quadId)).setPaused(true);
}

void Animation2dEditor::autopauseQuad2dAnimation(const string& animationId, const string& quadId)
{
	if(!isAnimationExisting(animationId))
	{
		abort();
	}
	if(!isQuad2dAnimationStarted(animationId, quadId))
	{
		abort();

	}
	if(isQuad2dAnimationPaused(animationId, quadId))
	{
		abort();
	}

	_startedQuad2dAnimations.at(make_pair(animationId, quadId)).setAutopaused(true);
}

void Animation2dEditor::resumeQuad2dAnimation(const string& animationId, const string& quadId)
{
	if(!isAnimationExisting(animationId))
	{
		abort();
	}
	if(!isQuad2dAnimationStarted(animationId, quadId))
	{
		abort();
	}
	if(!isQuad2dAnimationPaused(animationId, quadId))
	{
		abort();
	}

	_startedQuad2dAnimations.at(make_pair(animationId, quadId)).setPaused(false);
}

void Animation2dEditor::stopQuad2dAnimation(const string& animationId, const string& quadId)
{
	if(!isAnimationExisting(animationId))
	{
		abort();
	}
	if(!isQuad2dAnimationStarted(animationId, quadId))
	{
		abort();
	}

	_startedQuad2dAnimations.erase(make_pair(animationId, quadId));
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

void Animation2dEditor::setQuad2dAnimationInterval(const string& animationId, const string& quadId, unsigned int value)
{
	if(!isAnimationExisting(animationId))
	{
		abort();
	}
	if(!isQuad2dAnimationStarted(animationId, quadId))
	{
		abort();
	}

	_startedQuad2dAnimations.at(make_pair(animationId, quadId)).setInterval(value);
}