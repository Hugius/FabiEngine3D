#include "animation2d_player.hpp"
#include "tools.hpp"

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

	_startedQuad3dAnimations.insert(make_pair(Tools::mergeStrings(animationId, quadId, DELIMITER), newAnimation));
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

	_startedQuad3dAnimations.at(Tools::mergeStrings(animationId, quadId, DELIMITER))->setPaused(true);
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

	_startedQuad3dAnimations.at(Tools::mergeStrings(animationId, quadId, DELIMITER))->setAutopaused(true);
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

	_startedQuad3dAnimations.at(Tools::mergeStrings(animationId, quadId, DELIMITER))->setPaused(false);
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

	_startedQuad3dAnimations.erase(Tools::mergeStrings(animationId, quadId, DELIMITER));
}

void Animation2dPlayer::setQuad3dAnimationRowIndex(const string& animationId, const string& quadId, unsigned int value)
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

	_startedQuad3dAnimations.at(Tools::mergeStrings(animationId, quadId, DELIMITER))->setRowIndex(value);
}

void Animation2dPlayer::setQuad3dAnimationColumnIndex(const string& animationId, const string& quadId, unsigned int value)
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

	_startedQuad3dAnimations.at(Tools::mergeStrings(animationId, quadId, DELIMITER))->setColumnIndex(value);
}

void Animation2dPlayer::setQuad3dAnimationIntervalMultiplier(const string& animationId, const string& quadId, unsigned int value)
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

	_startedQuad3dAnimations.at(Tools::mergeStrings(animationId, quadId, DELIMITER))->setIntervalMultiplier(value);
}

void Animation2dPlayer::setQuad3dAnimationIntervalDivider(const string& animationId, const string& quadId, unsigned int value)
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

	_startedQuad3dAnimations.at(Tools::mergeStrings(animationId, quadId, DELIMITER))->setIntervalDivider(value);
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

	_startedQuad2dAnimations.insert(make_pair(Tools::mergeStrings(animationId, quadId, DELIMITER), newAnimation));
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

	_startedQuad2dAnimations.at(Tools::mergeStrings(animationId, quadId, DELIMITER))->setPaused(true);
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

	_startedQuad2dAnimations.at(Tools::mergeStrings(animationId, quadId, DELIMITER))->setAutopaused(true);
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

	_startedQuad2dAnimations.at(Tools::mergeStrings(animationId, quadId, DELIMITER))->setPaused(false);
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

	_startedQuad2dAnimations.erase(Tools::mergeStrings(animationId, quadId, DELIMITER));
}

void Animation2dPlayer::setQuad2dAnimationRowIndex(const string& animationId, const string& quadId, unsigned int value)
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

	_startedQuad2dAnimations.at(Tools::mergeStrings(animationId, quadId, DELIMITER))->setRowIndex(value);
}

void Animation2dPlayer::setQuad2dAnimationColumnIndex(const string& animationId, const string& quadId, unsigned int value)
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

	_startedQuad2dAnimations.at(Tools::mergeStrings(animationId, quadId, DELIMITER))->setColumnIndex(value);
}

void Animation2dPlayer::setQuad2dAnimationIntervalMultiplier(const string& animationId, const string& quadId, unsigned int value)
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

	_startedQuad2dAnimations.at(Tools::mergeStrings(animationId, quadId, DELIMITER))->setIntervalMultiplier(value);
}

void Animation2dPlayer::setQuad2dAnimationIntervalDivider(const string& animationId, const string& quadId, unsigned int value)
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

	_startedQuad2dAnimations.at(Tools::mergeStrings(animationId, quadId, DELIMITER))->setIntervalDivider(value);
}