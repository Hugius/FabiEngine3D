#include "animation2d_player.hpp"

using std::make_shared;

void Animation2dPlayer::startQuad3dAnimation(const string& animationId, const string& quadId, int playCount)
{
	if(!_animation2dManager->isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_quad3dEntityManager->isEntityExisting(quadId))
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

	const auto newAnimation = make_shared<StartedAnimation2d>(animationId, quadId);

	newAnimation->setPlayCount(playCount);

	_startedQuad3dAnimations.insert(make_pair(make_pair(animationId, quadId), newAnimation));
}

void Animation2dPlayer::pauseQuad3dAnimation(const string& animationId, const string& quadId)
{
	if(!_animation2dManager->isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_quad3dEntityManager->isEntityExisting(quadId))
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

	_startedQuad3dAnimations.at(make_pair(animationId, quadId))->setPaused(true);
}

void Animation2dPlayer::autopauseQuad3dAnimation(const string& animationId, const string& quadId)
{
	if(!_animation2dManager->isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_quad3dEntityManager->isEntityExisting(quadId))
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

	_startedQuad3dAnimations.at(make_pair(animationId, quadId))->setAutopaused(true);
}

void Animation2dPlayer::resumeQuad3dAnimation(const string& animationId, const string& quadId)
{
	if(!_animation2dManager->isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_quad3dEntityManager->isEntityExisting(quadId))
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

	_startedQuad3dAnimations.at(make_pair(animationId, quadId))->setPaused(false);
}

void Animation2dPlayer::stopQuad3dAnimation(const string& animationId, const string& quadId)
{
	if(!_animation2dManager->isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_quad3dEntityManager->isEntityExisting(quadId))
	{
		abort();
	}
	if(!isQuad3dAnimationStarted(animationId, quadId))
	{
		abort();
	}

	_startedQuad3dAnimations.erase(make_pair(animationId, quadId));
}

void Animation2dPlayer::startQuad2dAnimation(const string& animationId, const string& quadId, int playCount)
{
	if(!_animation2dManager->isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_quad2dEntityManager->isEntityExisting(quadId))
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

	const auto newAnimation = make_shared<StartedAnimation2d>(animationId, quadId);

	newAnimation->setPlayCount(playCount);

	_startedQuad2dAnimations.insert(make_pair(make_pair(animationId, quadId), newAnimation));
}

void Animation2dPlayer::pauseQuad2dAnimation(const string& animationId, const string& quadId)
{
	if(!_animation2dManager->isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_quad2dEntityManager->isEntityExisting(quadId))
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

	_startedQuad2dAnimations.at(make_pair(animationId, quadId))->setPaused(true);
}

void Animation2dPlayer::autopauseQuad2dAnimation(const string& animationId, const string& quadId)
{
	if(!_animation2dManager->isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_quad2dEntityManager->isEntityExisting(quadId))
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

	_startedQuad2dAnimations.at(make_pair(animationId, quadId))->setAutopaused(true);
}

void Animation2dPlayer::resumeQuad2dAnimation(const string& animationId, const string& quadId)
{
	if(!_animation2dManager->isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_quad2dEntityManager->isEntityExisting(quadId))
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

	_startedQuad2dAnimations.at(make_pair(animationId, quadId))->setPaused(false);
}

void Animation2dPlayer::stopQuad2dAnimation(const string& animationId, const string& quadId)
{
	if(!_animation2dManager->isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_quad2dEntityManager->isEntityExisting(quadId))
	{
		abort();
	}
	if(!isQuad2dAnimationStarted(animationId, quadId))
	{
		abort();
	}

	_startedQuad2dAnimations.erase(make_pair(animationId, quadId));
}