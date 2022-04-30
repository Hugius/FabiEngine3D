#include "animation2d_player.hpp"
#include "tools.hpp"

void Animation2dPlayer::inject(shared_ptr<Animation2dManager> animation2dManager)
{
	_animation2dManager = animation2dManager;
}

void Animation2dPlayer::inject(shared_ptr<Quad3dManager> quad3dManager)
{
	_quad3dManager = quad3dManager;
}

void Animation2dPlayer::inject(shared_ptr<Quad2dManager> quad2dManager)
{
	_quad2dManager = quad2dManager;
}

const vector<pair<string, string>> Animation2dPlayer::getStartedQuad3dAnimation2dIds() const
{
	vector<pair<string, string>> result;

	for(const auto & [mergedId, startedAnimation2d] : _startedQuad3dAnimation2ds)
	{
		const auto splitKey = Tools::splitStringIntoTwo(mergedId, DELIMITER);

		result.push_back(splitKey);
	}

	return result;
}

const vector<pair<string, string>> Animation2dPlayer::getStartedQuad2dAnimation2dIds() const
{
	vector<pair<string, string>> result;

	for(const auto & [mergedId, startedAnimation2d] : _startedQuad2dAnimation2ds)
	{
		const auto splitKey = Tools::splitStringIntoTwo(mergedId, DELIMITER);

		result.push_back(splitKey);
	}

	return result;
}

const int Animation2dPlayer::getQuad3dAnimation2dPlayCount(const string & animation2dId, const string & quad3dId) const
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

	return _startedQuad3dAnimation2ds.at(mergedId)->getPlayCount();
}

const int Animation2dPlayer::getQuad2dAnimation2dPlayCount(const string & animation2dId, const string & quad2dId) const
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

	return _startedQuad2dAnimation2ds.at(mergedId)->getPlayCount();
}

const int Animation2dPlayer::getQuad3dAnimation2dRowIndex(const string & animation2dId, const string & quad3dId) const
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

	return _startedQuad3dAnimation2ds.at(mergedId)->getRowIndex();
}

const int Animation2dPlayer::getQuad2dAnimation2dRowIndex(const string & animation2dId, const string & quad2dId) const
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

	return _startedQuad2dAnimation2ds.at(mergedId)->getRowIndex();
}

const int Animation2dPlayer::getQuad3dAnimation2dColumnIndex(const string & animation2dId, const string & quad3dId) const
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

	return _startedQuad3dAnimation2ds.at(mergedId)->getColumnIndex();
}

const int Animation2dPlayer::getQuad2dAnimation2dColumnIndex(const string & animation2dId, const string & quad2dId) const
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

	return _startedQuad2dAnimation2ds.at(mergedId)->getColumnIndex();
}

const int Animation2dPlayer::getQuad3dAnimation2dIntervalMultiplier(const string & animation2dId, const string & quad3dId) const
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

	return _startedQuad2dAnimation2ds.at(mergedId)->getIntervalMultiplier();
}

const int Animation2dPlayer::getQuad2dAnimation2dIntervalMultiplier(const string & animation2dId, const string & quad2dId) const
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

	return _startedQuad2dAnimation2ds.at(mergedId)->getIntervalMultiplier();
}

const int Animation2dPlayer::getQuad3dAnimation2dIntervalDivider(const string & animation2dId, const string & quad3dId) const
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

	return _startedQuad2dAnimation2ds.at(mergedId)->getIntervalDivider();
}

const int Animation2dPlayer::getQuad2dAnimation2dIntervalDivider(const string & animation2dId, const string & quad2dId) const
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

	return _startedQuad2dAnimation2ds.at(mergedId)->getIntervalDivider();
}

const bool Animation2dPlayer::isQuad3dAnimation2dStarted(const string & animation2dId, const string & quad3dId) const
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

	return (_startedQuad3dAnimation2ds.find(mergedId) != _startedQuad3dAnimation2ds.end());
}

const bool Animation2dPlayer::isQuad3dAnimation2dPaused(const string & animation2dId, const string & quad3dId) const
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

	return _startedQuad3dAnimation2ds.at(mergedId)->isPaused();
}

const bool Animation2dPlayer::isQuad3dAnimation2dAutopaused(const string & animation2dId, const string & quad3dId) const
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

	return _startedQuad3dAnimation2ds.at(mergedId)->isAutopaused();
}

const bool Animation2dPlayer::isQuad2dAnimation2dStarted(const string & animation2dId, const string & quad2dId) const
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

	return (_startedQuad2dAnimation2ds.find(mergedId) != _startedQuad2dAnimation2ds.end());
}

const bool Animation2dPlayer::isQuad2dAnimation2dPaused(const string & animation2dId, const string & quad2dId) const
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

	return _startedQuad2dAnimation2ds.at(mergedId)->isPaused();
}

const bool Animation2dPlayer::isQuad2dAnimation2dAutopaused(const string & animation2dId, const string & quad2dId) const
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

	return _startedQuad2dAnimation2ds.at(mergedId)->isAutopaused();
}