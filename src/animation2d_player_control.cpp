#include "animation2d_player.hpp"
#include "tools.hpp"

using std::make_shared;

void Animation2dPlayer::startQuad3dAnimation(const string & animation2dId, const string & quad3dId, int playCount)
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad3dId, DELIMITER);

	if(!_animation2dManager->isAnimationExisting(animation2dId))
	{
		abort();
	}
	if(!_quad3dManager->isEntityExisting(quad3dId))
	{
		abort();
	}
	if(isQuad3dAnimationStarted(animation2dId, quad3dId))
	{
		abort();
	}
	if((playCount == 0) || (playCount < -1))
	{
		abort();
	}

	const auto newAnimation2d = make_shared<StartedAnimation2d>();

	newAnimation2d->setPlayCount(playCount);

	_startedQuad3dAnimations.insert({mergedId, newAnimation2d});
}

void Animation2dPlayer::pauseQuad3dAnimation(const string & animation2dId, const string & quad3dId)
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad3dId, DELIMITER);

	if(!_animation2dManager->isAnimationExisting(animation2dId))
	{
		abort();
	}
	if(!_quad3dManager->isEntityExisting(quad3dId))
	{
		abort();
	}
	if(!isQuad3dAnimationStarted(animation2dId, quad3dId))
	{
		abort();

	}
	if(isQuad3dAnimationPaused(animation2dId, quad3dId))
	{
		abort();
	}

	_startedQuad3dAnimations.at(mergedId)->setPaused(true);
}

void Animation2dPlayer::autopauseQuad3dAnimation(const string & animation2dId, const string & quad3dId)
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad3dId, DELIMITER);

	if(!_animation2dManager->isAnimationExisting(animation2dId))
	{
		abort();
	}
	if(!_quad3dManager->isEntityExisting(quad3dId))
	{
		abort();
	}
	if(!isQuad3dAnimationStarted(animation2dId, quad3dId))
	{
		abort();

	}
	if(isQuad3dAnimationPaused(animation2dId, quad3dId))
	{
		abort();
	}

	_startedQuad3dAnimations.at(mergedId)->setAutopaused(true);
}

void Animation2dPlayer::resumeQuad3dAnimation(const string & animation2dId, const string & quad3dId)
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad3dId, DELIMITER);

	if(!_animation2dManager->isAnimationExisting(animation2dId))
	{
		abort();
	}
	if(!_quad3dManager->isEntityExisting(quad3dId))
	{
		abort();
	}
	if(!isQuad3dAnimationStarted(animation2dId, quad3dId))
	{
		abort();
	}
	if(!isQuad3dAnimationPaused(animation2dId, quad3dId))
	{
		abort();
	}

	_startedQuad3dAnimations.at(mergedId)->setPaused(false);
}

void Animation2dPlayer::stopQuad3dAnimation(const string & animation2dId, const string & quad3dId)
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad3dId, DELIMITER);

	if(!_animation2dManager->isAnimationExisting(animation2dId))
	{
		abort();
	}
	if(!_quad3dManager->isEntityExisting(quad3dId))
	{
		abort();
	}
	if(!isQuad3dAnimationStarted(animation2dId, quad3dId))
	{
		abort();
	}

	_startedQuad3dAnimations.erase(mergedId);
}

void Animation2dPlayer::setQuad3dAnimationRowIndex(const string & animation2dId, const string & quad3dId, int value)
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad3dId, DELIMITER);

	if(!_animation2dManager->isAnimationExisting(animation2dId))
	{
		abort();
	}
	if(!_quad3dManager->isEntityExisting(quad3dId))
	{
		abort();
	}
	if(!isQuad3dAnimationStarted(animation2dId, quad3dId))
	{
		abort();
	}

	_startedQuad3dAnimations.at(mergedId)->setRowIndex(value);
}

void Animation2dPlayer::setQuad3dAnimationColumnIndex(const string & animation2dId, const string & quad3dId, int value)
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad3dId, DELIMITER);

	if(!_animation2dManager->isAnimationExisting(animation2dId))
	{
		abort();
	}
	if(!_quad3dManager->isEntityExisting(quad3dId))
	{
		abort();
	}
	if(!isQuad3dAnimationStarted(animation2dId, quad3dId))
	{
		abort();
	}

	_startedQuad3dAnimations.at(mergedId)->setColumnIndex(value);
}

void Animation2dPlayer::setQuad3dAnimationIntervalMultiplier(const string & animation2dId, const string & quad3dId, int value)
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad3dId, DELIMITER);

	if(!_animation2dManager->isAnimationExisting(animation2dId))
	{
		abort();
	}
	if(!_quad3dManager->isEntityExisting(quad3dId))
	{
		abort();
	}
	if(!isQuad3dAnimationStarted(animation2dId, quad3dId))
	{
		abort();
	}

	_startedQuad3dAnimations.at(mergedId)->setIntervalMultiplier(value);
}

void Animation2dPlayer::setQuad3dAnimationIntervalDivider(const string & animation2dId, const string & quad3dId, int value)
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad3dId, DELIMITER);

	if(!_animation2dManager->isAnimationExisting(animation2dId))
	{
		abort();
	}
	if(!_quad3dManager->isEntityExisting(quad3dId))
	{
		abort();
	}
	if(!isQuad3dAnimationStarted(animation2dId, quad3dId))
	{
		abort();
	}

	_startedQuad3dAnimations.at(mergedId)->setIntervalDivider(value);
}

void Animation2dPlayer::startQuad2dAnimation(const string & animation2dId, const string & quad2dId, int playCount)
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad2dId, DELIMITER);

	if(!_animation2dManager->isAnimationExisting(animation2dId))
	{
		abort();
	}
	if(!_quad2dManager->isEntityExisting(quad2dId))
	{
		abort();
	}
	if(isQuad2dAnimationStarted(animation2dId, quad2dId))
	{
		abort();
	}
	if((playCount == 0) || (playCount < -1))
	{
		abort();
	}

	const auto newAnimation2d = make_shared<StartedAnimation2d>();

	newAnimation2d->setPlayCount(playCount);

	_startedQuad2dAnimations.insert({mergedId, newAnimation2d});
}

void Animation2dPlayer::pauseQuad2dAnimation(const string & animation2dId, const string & quad2dId)
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad2dId, DELIMITER);

	if(!_animation2dManager->isAnimationExisting(animation2dId))
	{
		abort();
	}
	if(!_quad2dManager->isEntityExisting(quad2dId))
	{
		abort();
	}
	if(!isQuad2dAnimationStarted(animation2dId, quad2dId))
	{
		abort();

	}
	if(isQuad2dAnimationPaused(animation2dId, quad2dId))
	{
		abort();
	}

	_startedQuad2dAnimations.at(mergedId)->setPaused(true);
}

void Animation2dPlayer::autopauseQuad2dAnimation(const string & animation2dId, const string & quad2dId)
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad2dId, DELIMITER);

	if(!_animation2dManager->isAnimationExisting(animation2dId))
	{
		abort();
	}
	if(!_quad2dManager->isEntityExisting(quad2dId))
	{
		abort();
	}
	if(!isQuad2dAnimationStarted(animation2dId, quad2dId))
	{
		abort();

	}
	if(isQuad2dAnimationPaused(animation2dId, quad2dId))
	{
		abort();
	}

	_startedQuad2dAnimations.at(mergedId)->setAutopaused(true);
}

void Animation2dPlayer::resumeQuad2dAnimation(const string & animation2dId, const string & quad2dId)
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad2dId, DELIMITER);

	if(!_animation2dManager->isAnimationExisting(animation2dId))
	{
		abort();
	}
	if(!_quad2dManager->isEntityExisting(quad2dId))
	{
		abort();
	}
	if(!isQuad2dAnimationStarted(animation2dId, quad2dId))
	{
		abort();
	}
	if(!isQuad2dAnimationPaused(animation2dId, quad2dId))
	{
		abort();
	}

	_startedQuad2dAnimations.at(mergedId)->setPaused(false);
}

void Animation2dPlayer::stopQuad2dAnimation(const string & animation2dId, const string & quad2dId)
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad2dId, DELIMITER);

	if(!_animation2dManager->isAnimationExisting(animation2dId))
	{
		abort();
	}
	if(!_quad2dManager->isEntityExisting(quad2dId))
	{
		abort();
	}
	if(!isQuad2dAnimationStarted(animation2dId, quad2dId))
	{
		abort();
	}

	_startedQuad2dAnimations.erase(mergedId);
}

void Animation2dPlayer::setQuad2dAnimationRowIndex(const string & animation2dId, const string & quad2dId, int value)
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad2dId, DELIMITER);

	if(!_animation2dManager->isAnimationExisting(animation2dId))
	{
		abort();
	}
	if(!_quad2dManager->isEntityExisting(quad2dId))
	{
		abort();
	}
	if(!isQuad2dAnimationStarted(animation2dId, quad2dId))
	{
		abort();
	}

	_startedQuad2dAnimations.at(mergedId)->setRowIndex(value);
}

void Animation2dPlayer::setQuad2dAnimationColumnIndex(const string & animation2dId, const string & quad2dId, int value)
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad2dId, DELIMITER);

	if(!_animation2dManager->isAnimationExisting(animation2dId))
	{
		abort();
	}
	if(!_quad2dManager->isEntityExisting(quad2dId))
	{
		abort();
	}
	if(!isQuad2dAnimationStarted(animation2dId, quad2dId))
	{
		abort();
	}

	_startedQuad2dAnimations.at(mergedId)->setColumnIndex(value);
}

void Animation2dPlayer::setQuad2dAnimationIntervalMultiplier(const string & animation2dId, const string & quad2dId, int value)
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad2dId, DELIMITER);

	if(!_animation2dManager->isAnimationExisting(animation2dId))
	{
		abort();
	}
	if(!_quad2dManager->isEntityExisting(quad2dId))
	{
		abort();
	}
	if(!isQuad2dAnimationStarted(animation2dId, quad2dId))
	{
		abort();
	}

	_startedQuad2dAnimations.at(mergedId)->setIntervalMultiplier(value);
}

void Animation2dPlayer::setQuad2dAnimationIntervalDivider(const string & animation2dId, const string & quad2dId, int value)
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad2dId, DELIMITER);

	if(!_animation2dManager->isAnimationExisting(animation2dId))
	{
		abort();
	}
	if(!_quad2dManager->isEntityExisting(quad2dId))
	{
		abort();
	}
	if(!isQuad2dAnimationStarted(animation2dId, quad2dId))
	{
		abort();
	}

	_startedQuad2dAnimations.at(mergedId)->setIntervalDivider(value);
}