#include "animation2d_player.hpp"
#include "tools.hpp"

using std::make_shared;

void Animation2dPlayer::startQuad3dAnimation2d(const string & animation2dId, const string & quad3dId, int playCount)
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad3dId, DELIMITER);

	if(!_animation2dManager->isAnimation2dExisting(animation2dId))
	{
		abort();
	}

	if(!_quad3dManager->isQuad3dExisting(quad3dId))
	{
		abort();
	}

	for(const auto & [startedAnimation2dId, startedQuad3dId] : getStartedQuad3dAnimation2dIds())
	{
		if(quad3dId == startedQuad3dId)
		{
			abort();
		}
	}

	if((playCount == 0) || (playCount < -1))
	{
		abort();
	}

	const auto newAnimation2d = make_shared<StartedAnimation2d>();

	newAnimation2d->setPlayCount(playCount);

	_startedQuad3dAnimation2ds.insert({mergedId, newAnimation2d});
}

void Animation2dPlayer::pauseQuad3dAnimation2d(const string & animation2dId, const string & quad3dId)
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad3dId, DELIMITER);

	if(!_animation2dManager->isAnimation2dExisting(animation2dId))
	{
		abort();
	}

	if(!_quad3dManager->isQuad3dExisting(quad3dId))
	{
		abort();
	}

	if(!isQuad3dAnimation2dStarted(animation2dId, quad3dId))
	{
		abort();

	}

	if(isQuad3dAnimation2dPaused(animation2dId, quad3dId))
	{
		abort();
	}

	_startedQuad3dAnimation2ds.at(mergedId)->setPaused(true);
}

void Animation2dPlayer::autopauseQuad3dAnimation2d(const string & animation2dId, const string & quad3dId)
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad3dId, DELIMITER);

	if(!_animation2dManager->isAnimation2dExisting(animation2dId))
	{
		abort();
	}

	if(!_quad3dManager->isQuad3dExisting(quad3dId))
	{
		abort();
	}

	if(!isQuad3dAnimation2dStarted(animation2dId, quad3dId))
	{
		abort();

	}

	if(isQuad3dAnimation2dPaused(animation2dId, quad3dId))
	{
		abort();
	}

	_startedQuad3dAnimation2ds.at(mergedId)->setAutopaused(true);
}

void Animation2dPlayer::resumeQuad3dAnimation2d(const string & animation2dId, const string & quad3dId)
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad3dId, DELIMITER);

	if(!_animation2dManager->isAnimation2dExisting(animation2dId))
	{
		abort();
	}

	if(!_quad3dManager->isQuad3dExisting(quad3dId))
	{
		abort();
	}

	if(!isQuad3dAnimation2dStarted(animation2dId, quad3dId))
	{
		abort();
	}

	if(!isQuad3dAnimation2dPaused(animation2dId, quad3dId))
	{
		abort();
	}

	_startedQuad3dAnimation2ds.at(mergedId)->setPaused(false);
}

void Animation2dPlayer::stopQuad3dAnimation2d(const string & animation2dId, const string & quad3dId)
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad3dId, DELIMITER);

	if(!_animation2dManager->isAnimation2dExisting(animation2dId))
	{
		abort();
	}

	if(!_quad3dManager->isQuad3dExisting(quad3dId))
	{
		abort();
	}

	if(!isQuad3dAnimation2dStarted(animation2dId, quad3dId))
	{
		abort();
	}

	_startedQuad3dAnimation2ds.erase(mergedId);
}

void Animation2dPlayer::setQuad3dAnimation2dRowIndex(const string & animation2dId, const string & quad3dId, int value)
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad3dId, DELIMITER);

	if(!_animation2dManager->isAnimation2dExisting(animation2dId))
	{
		abort();
	}

	if(!_quad3dManager->isQuad3dExisting(quad3dId))
	{
		abort();
	}

	if(!isQuad3dAnimation2dStarted(animation2dId, quad3dId))
	{
		abort();
	}

	_startedQuad3dAnimation2ds.at(mergedId)->setRowIndex(value);
}

void Animation2dPlayer::setQuad3dAnimation2dColumnIndex(const string & animation2dId, const string & quad3dId, int value)
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad3dId, DELIMITER);

	if(!_animation2dManager->isAnimation2dExisting(animation2dId))
	{
		abort();
	}

	if(!_quad3dManager->isQuad3dExisting(quad3dId))
	{
		abort();
	}

	if(!isQuad3dAnimation2dStarted(animation2dId, quad3dId))
	{
		abort();
	}

	_startedQuad3dAnimation2ds.at(mergedId)->setColumnIndex(value);
}

void Animation2dPlayer::setQuad3dAnimation2dIntervalMultiplier(const string & animation2dId, const string & quad3dId, int value)
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad3dId, DELIMITER);

	if(!_animation2dManager->isAnimation2dExisting(animation2dId))
	{
		abort();
	}

	if(!_quad3dManager->isQuad3dExisting(quad3dId))
	{
		abort();
	}

	if(!isQuad3dAnimation2dStarted(animation2dId, quad3dId))
	{
		abort();
	}

	_startedQuad3dAnimation2ds.at(mergedId)->setIntervalMultiplier(value);
}

void Animation2dPlayer::setQuad3dAnimation2dIntervalDivider(const string & animation2dId, const string & quad3dId, int value)
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad3dId, DELIMITER);

	if(!_animation2dManager->isAnimation2dExisting(animation2dId))
	{
		abort();
	}

	if(!_quad3dManager->isQuad3dExisting(quad3dId))
	{
		abort();
	}

	if(!isQuad3dAnimation2dStarted(animation2dId, quad3dId))
	{
		abort();
	}

	_startedQuad3dAnimation2ds.at(mergedId)->setIntervalDivider(value);
}

void Animation2dPlayer::setQuad3dAnimation2dUpdateCount(const string & animation2dId, const string & quad3dId, int value)
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad3dId, DELIMITER);

	if(!_animation2dManager->isAnimation2dExisting(animation2dId))
	{
		abort();
	}

	if(!_quad3dManager->isQuad3dExisting(quad3dId))
	{
		abort();
	}

	if(!isQuad3dAnimation2dStarted(animation2dId, quad3dId))
	{
		abort();
	}

	_startedQuad3dAnimation2ds.at(mergedId)->setUpdateCount(value);
}

void Animation2dPlayer::startQuad2dAnimation2d(const string & animation2dId, const string & quad2dId, int playCount)
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad2dId, DELIMITER);

	if(!_animation2dManager->isAnimation2dExisting(animation2dId))
	{
		abort();
	}

	if(!_quad2dManager->isQuad2dExisting(quad2dId))
	{
		abort();
	}

	for(const auto & [startedAnimation2dId, startedQuad2dId] : getStartedQuad2dAnimation2dIds())
	{
		if(quad2dId == startedQuad2dId)
		{
			abort();
		}
	}

	if((playCount == 0) || (playCount < -1))
	{
		abort();
	}

	const auto newAnimation2d = make_shared<StartedAnimation2d>();

	newAnimation2d->setPlayCount(playCount);

	_startedQuad2dAnimation2ds.insert({mergedId, newAnimation2d});
}

void Animation2dPlayer::pauseQuad2dAnimation2d(const string & animation2dId, const string & quad2dId)
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad2dId, DELIMITER);

	if(!_animation2dManager->isAnimation2dExisting(animation2dId))
	{
		abort();
	}

	if(!_quad2dManager->isQuad2dExisting(quad2dId))
	{
		abort();
	}

	if(!isQuad2dAnimation2dStarted(animation2dId, quad2dId))
	{
		abort();

	}

	if(isQuad2dAnimation2dPaused(animation2dId, quad2dId))
	{
		abort();
	}

	_startedQuad2dAnimation2ds.at(mergedId)->setPaused(true);
}

void Animation2dPlayer::autopauseQuad2dAnimation2d(const string & animation2dId, const string & quad2dId)
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad2dId, DELIMITER);

	if(!_animation2dManager->isAnimation2dExisting(animation2dId))
	{
		abort();
	}

	if(!_quad2dManager->isQuad2dExisting(quad2dId))
	{
		abort();
	}

	if(!isQuad2dAnimation2dStarted(animation2dId, quad2dId))
	{
		abort();

	}

	if(isQuad2dAnimation2dPaused(animation2dId, quad2dId))
	{
		abort();
	}

	_startedQuad2dAnimation2ds.at(mergedId)->setAutopaused(true);
}

void Animation2dPlayer::resumeQuad2dAnimation2d(const string & animation2dId, const string & quad2dId)
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad2dId, DELIMITER);

	if(!_animation2dManager->isAnimation2dExisting(animation2dId))
	{
		abort();
	}

	if(!_quad2dManager->isQuad2dExisting(quad2dId))
	{
		abort();
	}

	if(!isQuad2dAnimation2dStarted(animation2dId, quad2dId))
	{
		abort();
	}

	if(!isQuad2dAnimation2dPaused(animation2dId, quad2dId))
	{
		abort();
	}

	_startedQuad2dAnimation2ds.at(mergedId)->setPaused(false);
}

void Animation2dPlayer::stopQuad2dAnimation2d(const string & animation2dId, const string & quad2dId)
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad2dId, DELIMITER);

	if(!_animation2dManager->isAnimation2dExisting(animation2dId))
	{
		abort();
	}

	if(!_quad2dManager->isQuad2dExisting(quad2dId))
	{
		abort();
	}

	if(!isQuad2dAnimation2dStarted(animation2dId, quad2dId))
	{
		abort();
	}

	_startedQuad2dAnimation2ds.erase(mergedId);
}

void Animation2dPlayer::setQuad2dAnimation2dRowIndex(const string & animation2dId, const string & quad2dId, int value)
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad2dId, DELIMITER);

	if(!_animation2dManager->isAnimation2dExisting(animation2dId))
	{
		abort();
	}

	if(!_quad2dManager->isQuad2dExisting(quad2dId))
	{
		abort();
	}

	if(!isQuad2dAnimation2dStarted(animation2dId, quad2dId))
	{
		abort();
	}

	_startedQuad2dAnimation2ds.at(mergedId)->setRowIndex(value);
}

void Animation2dPlayer::setQuad2dAnimation2dColumnIndex(const string & animation2dId, const string & quad2dId, int value)
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad2dId, DELIMITER);

	if(!_animation2dManager->isAnimation2dExisting(animation2dId))
	{
		abort();
	}

	if(!_quad2dManager->isQuad2dExisting(quad2dId))
	{
		abort();
	}

	if(!isQuad2dAnimation2dStarted(animation2dId, quad2dId))
	{
		abort();
	}

	_startedQuad2dAnimation2ds.at(mergedId)->setColumnIndex(value);
}

void Animation2dPlayer::setQuad2dAnimation2dIntervalMultiplier(const string & animation2dId, const string & quad2dId, int value)
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad2dId, DELIMITER);

	if(!_animation2dManager->isAnimation2dExisting(animation2dId))
	{
		abort();
	}

	if(!_quad2dManager->isQuad2dExisting(quad2dId))
	{
		abort();
	}

	if(!isQuad2dAnimation2dStarted(animation2dId, quad2dId))
	{
		abort();
	}

	_startedQuad2dAnimation2ds.at(mergedId)->setIntervalMultiplier(value);
}

void Animation2dPlayer::setQuad2dAnimation2dIntervalDivider(const string & animation2dId, const string & quad2dId, int value)
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad2dId, DELIMITER);

	if(!_animation2dManager->isAnimation2dExisting(animation2dId))
	{
		abort();
	}

	if(!_quad2dManager->isQuad2dExisting(quad2dId))
	{
		abort();
	}

	if(!isQuad2dAnimation2dStarted(animation2dId, quad2dId))
	{
		abort();
	}

	_startedQuad2dAnimation2ds.at(mergedId)->setIntervalDivider(value);
}

void Animation2dPlayer::setQuad2dAnimation2dUpdateCount(const string & animation2dId, const string & quad2dId, int value)
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad2dId, DELIMITER);

	if(!_animation2dManager->isAnimation2dExisting(animation2dId))
	{
		abort();
	}

	if(!_quad2dManager->isQuad2dExisting(quad2dId))
	{
		abort();
	}

	if(!isQuad2dAnimation2dStarted(animation2dId, quad2dId))
	{
		abort();
	}

	_startedQuad2dAnimation2ds.at(mergedId)->setUpdateCount(value);
}