#include "animation2d_player.hpp"
#include "tools.hpp"

using std::make_shared;

void Animation2dPlayer::startQuad3dAnimation(const string & animationId, const string & quad3dId, int playCount)
{
	const auto mergedId = Tools::mergeStrings(animationId, quad3dId, DELIMITER);

	if(!_animation2dManager->isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_quad3dEntityManager->isEntityExisting(quad3dId))
	{
		abort();
	}
	if(isQuad3dAnimationStarted(animationId, quad3dId))
	{
		abort();
	}
	if((playCount == 0) || (playCount < -1))
	{
		abort();
	}

	const auto newAnimation = make_shared<StartedAnimation2d>();

	newAnimation->setPlayCount(playCount);

	_startedQuad3dAnimations.insert({mergedId, newAnimation});
}

void Animation2dPlayer::pauseQuad3dAnimation(const string & animationId, const string & quad3dId)
{
	const auto mergedId = Tools::mergeStrings(animationId, quad3dId, DELIMITER);

	if(!_animation2dManager->isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_quad3dEntityManager->isEntityExisting(quad3dId))
	{
		abort();
	}
	if(!isQuad3dAnimationStarted(animationId, quad3dId))
	{
		abort();

	}
	if(isQuad3dAnimationPaused(animationId, quad3dId))
	{
		abort();
	}

	_startedQuad3dAnimations.at(mergedId)->setPaused(true);
}

void Animation2dPlayer::autopauseQuad3dAnimation(const string & animationId, const string & quad3dId)
{
	const auto mergedId = Tools::mergeStrings(animationId, quad3dId, DELIMITER);

	if(!_animation2dManager->isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_quad3dEntityManager->isEntityExisting(quad3dId))
	{
		abort();
	}
	if(!isQuad3dAnimationStarted(animationId, quad3dId))
	{
		abort();

	}
	if(isQuad3dAnimationPaused(animationId, quad3dId))
	{
		abort();
	}

	_startedQuad3dAnimations.at(mergedId)->setAutopaused(true);
}

void Animation2dPlayer::resumeQuad3dAnimation(const string & animationId, const string & quad3dId)
{
	const auto mergedId = Tools::mergeStrings(animationId, quad3dId, DELIMITER);

	if(!_animation2dManager->isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_quad3dEntityManager->isEntityExisting(quad3dId))
	{
		abort();
	}
	if(!isQuad3dAnimationStarted(animationId, quad3dId))
	{
		abort();
	}
	if(!isQuad3dAnimationPaused(animationId, quad3dId))
	{
		abort();
	}

	_startedQuad3dAnimations.at(mergedId)->setPaused(false);
}

void Animation2dPlayer::stopQuad3dAnimation(const string & animationId, const string & quad3dId)
{
	const auto mergedId = Tools::mergeStrings(animationId, quad3dId, DELIMITER);

	if(!_animation2dManager->isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_quad3dEntityManager->isEntityExisting(quad3dId))
	{
		abort();
	}
	if(!isQuad3dAnimationStarted(animationId, quad3dId))
	{
		abort();
	}

	_startedQuad3dAnimations.erase(mergedId);
}

void Animation2dPlayer::setQuad3dAnimationRowIndex(const string & animationId, const string & quad3dId, int value)
{
	const auto mergedId = Tools::mergeStrings(animationId, quad3dId, DELIMITER);

	if(!_animation2dManager->isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_quad3dEntityManager->isEntityExisting(quad3dId))
	{
		abort();
	}
	if(!isQuad3dAnimationStarted(animationId, quad3dId))
	{
		abort();
	}

	_startedQuad3dAnimations.at(mergedId)->setRowIndex(value);
}

void Animation2dPlayer::setQuad3dAnimationColumnIndex(const string & animationId, const string & quad3dId, int value)
{
	const auto mergedId = Tools::mergeStrings(animationId, quad3dId, DELIMITER);

	if(!_animation2dManager->isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_quad3dEntityManager->isEntityExisting(quad3dId))
	{
		abort();
	}
	if(!isQuad3dAnimationStarted(animationId, quad3dId))
	{
		abort();
	}

	_startedQuad3dAnimations.at(mergedId)->setColumnIndex(value);
}

void Animation2dPlayer::setQuad3dAnimationIntervalMultiplier(const string & animationId, const string & quad3dId, int value)
{
	const auto mergedId = Tools::mergeStrings(animationId, quad3dId, DELIMITER);

	if(!_animation2dManager->isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_quad3dEntityManager->isEntityExisting(quad3dId))
	{
		abort();
	}
	if(!isQuad3dAnimationStarted(animationId, quad3dId))
	{
		abort();
	}

	_startedQuad3dAnimations.at(mergedId)->setIntervalMultiplier(value);
}

void Animation2dPlayer::setQuad3dAnimationIntervalDivider(const string & animationId, const string & quad3dId, int value)
{
	const auto mergedId = Tools::mergeStrings(animationId, quad3dId, DELIMITER);

	if(!_animation2dManager->isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_quad3dEntityManager->isEntityExisting(quad3dId))
	{
		abort();
	}
	if(!isQuad3dAnimationStarted(animationId, quad3dId))
	{
		abort();
	}

	_startedQuad3dAnimations.at(mergedId)->setIntervalDivider(value);
}

void Animation2dPlayer::startQuad2dAnimation(const string & animationId, const string & quad2dId, int playCount)
{
	const auto mergedId = Tools::mergeStrings(animationId, quad2dId, DELIMITER);

	if(!_animation2dManager->isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_quad2dEntityManager->isEntityExisting(quad2dId))
	{
		abort();
	}
	if(isQuad2dAnimationStarted(animationId, quad2dId))
	{
		abort();
	}
	if((playCount == 0) || (playCount < -1))
	{
		abort();
	}

	const auto newAnimation = make_shared<StartedAnimation2d>();

	newAnimation->setPlayCount(playCount);

	_startedQuad2dAnimations.insert({mergedId, newAnimation});
}

void Animation2dPlayer::pauseQuad2dAnimation(const string & animationId, const string & quad2dId)
{
	const auto mergedId = Tools::mergeStrings(animationId, quad2dId, DELIMITER);

	if(!_animation2dManager->isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_quad2dEntityManager->isEntityExisting(quad2dId))
	{
		abort();
	}
	if(!isQuad2dAnimationStarted(animationId, quad2dId))
	{
		abort();

	}
	if(isQuad2dAnimationPaused(animationId, quad2dId))
	{
		abort();
	}

	_startedQuad2dAnimations.at(mergedId)->setPaused(true);
}

void Animation2dPlayer::autopauseQuad2dAnimation(const string & animationId, const string & quad2dId)
{
	const auto mergedId = Tools::mergeStrings(animationId, quad2dId, DELIMITER);

	if(!_animation2dManager->isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_quad2dEntityManager->isEntityExisting(quad2dId))
	{
		abort();
	}
	if(!isQuad2dAnimationStarted(animationId, quad2dId))
	{
		abort();

	}
	if(isQuad2dAnimationPaused(animationId, quad2dId))
	{
		abort();
	}

	_startedQuad2dAnimations.at(mergedId)->setAutopaused(true);
}

void Animation2dPlayer::resumeQuad2dAnimation(const string & animationId, const string & quad2dId)
{
	const auto mergedId = Tools::mergeStrings(animationId, quad2dId, DELIMITER);

	if(!_animation2dManager->isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_quad2dEntityManager->isEntityExisting(quad2dId))
	{
		abort();
	}
	if(!isQuad2dAnimationStarted(animationId, quad2dId))
	{
		abort();
	}
	if(!isQuad2dAnimationPaused(animationId, quad2dId))
	{
		abort();
	}

	_startedQuad2dAnimations.at(mergedId)->setPaused(false);
}

void Animation2dPlayer::stopQuad2dAnimation(const string & animationId, const string & quad2dId)
{
	const auto mergedId = Tools::mergeStrings(animationId, quad2dId, DELIMITER);

	if(!_animation2dManager->isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_quad2dEntityManager->isEntityExisting(quad2dId))
	{
		abort();
	}
	if(!isQuad2dAnimationStarted(animationId, quad2dId))
	{
		abort();
	}

	_startedQuad2dAnimations.erase(mergedId);
}

void Animation2dPlayer::setQuad2dAnimationRowIndex(const string & animationId, const string & quad2dId, int value)
{
	const auto mergedId = Tools::mergeStrings(animationId, quad2dId, DELIMITER);

	if(!_animation2dManager->isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_quad2dEntityManager->isEntityExisting(quad2dId))
	{
		abort();
	}
	if(!isQuad2dAnimationStarted(animationId, quad2dId))
	{
		abort();
	}

	_startedQuad2dAnimations.at(mergedId)->setRowIndex(value);
}

void Animation2dPlayer::setQuad2dAnimationColumnIndex(const string & animationId, const string & quad2dId, int value)
{
	const auto mergedId = Tools::mergeStrings(animationId, quad2dId, DELIMITER);

	if(!_animation2dManager->isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_quad2dEntityManager->isEntityExisting(quad2dId))
	{
		abort();
	}
	if(!isQuad2dAnimationStarted(animationId, quad2dId))
	{
		abort();
	}

	_startedQuad2dAnimations.at(mergedId)->setColumnIndex(value);
}

void Animation2dPlayer::setQuad2dAnimationIntervalMultiplier(const string & animationId, const string & quad2dId, int value)
{
	const auto mergedId = Tools::mergeStrings(animationId, quad2dId, DELIMITER);

	if(!_animation2dManager->isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_quad2dEntityManager->isEntityExisting(quad2dId))
	{
		abort();
	}
	if(!isQuad2dAnimationStarted(animationId, quad2dId))
	{
		abort();
	}

	_startedQuad2dAnimations.at(mergedId)->setIntervalMultiplier(value);
}

void Animation2dPlayer::setQuad2dAnimationIntervalDivider(const string & animationId, const string & quad2dId, int value)
{
	const auto mergedId = Tools::mergeStrings(animationId, quad2dId, DELIMITER);

	if(!_animation2dManager->isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_quad2dEntityManager->isEntityExisting(quad2dId))
	{
		abort();
	}
	if(!isQuad2dAnimationStarted(animationId, quad2dId))
	{
		abort();
	}

	_startedQuad2dAnimations.at(mergedId)->setIntervalDivider(value);
}