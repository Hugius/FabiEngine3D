#include "animation2d_player.hpp"
#include "tools.hpp"

using std::make_shared;

void Animation2dPlayer::startQuad3dAnimation(const string& animationId, const string& quadId, int playCount)
{
	const auto key = Tools::mergeStrings(animationId, quadId, DELIMITER);

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
	if((playCount == 0) || (playCount < -1))
	{
		abort();
	}

	const auto newAnimation = make_shared<StartedAnimation2d>();

	newAnimation->setPlayCount(playCount);

	_startedQuad3dAnimations.insert({key, newAnimation});
}

void Animation2dPlayer::pauseQuad3dAnimation(const string& animationId, const string& quadId)
{
	const auto key = Tools::mergeStrings(animationId, quadId, DELIMITER);

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

	_startedQuad3dAnimations.at(key)->setPaused(true);
}

void Animation2dPlayer::autopauseQuad3dAnimation(const string& animationId, const string& quadId)
{
	const auto key = Tools::mergeStrings(animationId, quadId, DELIMITER);

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

	_startedQuad3dAnimations.at(key)->setAutopaused(true);
}

void Animation2dPlayer::resumeQuad3dAnimation(const string& animationId, const string& quadId)
{
	const auto key = Tools::mergeStrings(animationId, quadId, DELIMITER);

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

	_startedQuad3dAnimations.at(key)->setPaused(false);
}

void Animation2dPlayer::stopQuad3dAnimation(const string& animationId, const string& quadId)
{
	const auto key = Tools::mergeStrings(animationId, quadId, DELIMITER);

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

	_startedQuad3dAnimations.erase(key);
}

void Animation2dPlayer::setQuad3dAnimationRowIndex(const string& animationId, const string& quadId, unsigned int value)
{
	const auto key = Tools::mergeStrings(animationId, quadId, DELIMITER);

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

	_startedQuad3dAnimations.at(key)->setRowIndex(value);
}

void Animation2dPlayer::setQuad3dAnimationColumnIndex(const string& animationId, const string& quadId, unsigned int value)
{
	const auto key = Tools::mergeStrings(animationId, quadId, DELIMITER);

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

	_startedQuad3dAnimations.at(key)->setColumnIndex(value);
}

void Animation2dPlayer::setQuad3dAnimationIntervalMultiplier(const string& animationId, const string& quadId, unsigned int value)
{
	const auto key = Tools::mergeStrings(animationId, quadId, DELIMITER);

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

	_startedQuad3dAnimations.at(key)->setIntervalMultiplier(value);
}

void Animation2dPlayer::setQuad3dAnimationIntervalDivider(const string& animationId, const string& quadId, unsigned int value)
{
	const auto key = Tools::mergeStrings(animationId, quadId, DELIMITER);

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

	_startedQuad3dAnimations.at(key)->setIntervalDivider(value);
}

void Animation2dPlayer::startQuad2dAnimation(const string& animationId, const string& quadId, int playCount)
{
	const auto key = Tools::mergeStrings(animationId, quadId, DELIMITER);

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
	if((playCount == 0) || (playCount < -1))
	{
		abort();
	}

	const auto newAnimation = make_shared<StartedAnimation2d>();

	newAnimation->setPlayCount(playCount);

	_startedQuad2dAnimations.insert({key, newAnimation});
}

void Animation2dPlayer::pauseQuad2dAnimation(const string& animationId, const string& quadId)
{
	const auto key = Tools::mergeStrings(animationId, quadId, DELIMITER);

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

	_startedQuad2dAnimations.at(key)->setPaused(true);
}

void Animation2dPlayer::autopauseQuad2dAnimation(const string& animationId, const string& quadId)
{
	const auto key = Tools::mergeStrings(animationId, quadId, DELIMITER);

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

	_startedQuad2dAnimations.at(key)->setAutopaused(true);
}

void Animation2dPlayer::resumeQuad2dAnimation(const string& animationId, const string& quadId)
{
	const auto key = Tools::mergeStrings(animationId, quadId, DELIMITER);

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

	_startedQuad2dAnimations.at(key)->setPaused(false);
}

void Animation2dPlayer::stopQuad2dAnimation(const string& animationId, const string& quadId)
{
	const auto key = Tools::mergeStrings(animationId, quadId, DELIMITER);

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

	_startedQuad2dAnimations.erase(key);
}

void Animation2dPlayer::setQuad2dAnimationRowIndex(const string& animationId, const string& quadId, unsigned int value)
{
	const auto key = Tools::mergeStrings(animationId, quadId, DELIMITER);

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

	_startedQuad2dAnimations.at(key)->setRowIndex(value);
}

void Animation2dPlayer::setQuad2dAnimationColumnIndex(const string& animationId, const string& quadId, unsigned int value)
{
	const auto key = Tools::mergeStrings(animationId, quadId, DELIMITER);

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

	_startedQuad2dAnimations.at(key)->setColumnIndex(value);
}

void Animation2dPlayer::setQuad2dAnimationIntervalMultiplier(const string& animationId, const string& quadId, unsigned int value)
{
	const auto key = Tools::mergeStrings(animationId, quadId, DELIMITER);

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

	_startedQuad2dAnimations.at(key)->setIntervalMultiplier(value);
}

void Animation2dPlayer::setQuad2dAnimationIntervalDivider(const string& animationId, const string& quadId, unsigned int value)
{
	const auto key = Tools::mergeStrings(animationId, quadId, DELIMITER);

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

	_startedQuad2dAnimations.at(key)->setIntervalDivider(value);
}