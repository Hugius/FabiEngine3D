#include "animation2d_player.hpp"
#include "tools.hpp"

void Animation2dPlayer::inject(shared_ptr<Animation2dManager> animation2dManager)
{
	_animation2dManager = animation2dManager;
}

void Animation2dPlayer::inject(shared_ptr<Quad3dEntityManager> quad3dEntityManager)
{
	_quad3dEntityManager = quad3dEntityManager;
}

void Animation2dPlayer::inject(shared_ptr<Quad2dEntityManager> quad2dEntityManager)
{
	_quad2dEntityManager = quad2dEntityManager;
}

const vector<pair<string, string>> Animation2dPlayer::getStartedQuad3dAnimationIds() const
{
	vector<pair<string, string>> ids;

	for(const auto & [mergedId, animation] : _startedQuad3dAnimations)
	{
		const auto splitKey = Tools::splitStringIntoTwo(mergedId, DELIMITER);

		ids.push_back(splitKey);
	}

	return ids;
}

const vector<pair<string, string>> Animation2dPlayer::getStartedQuad2dAnimationIds() const
{
	vector<pair<string, string>> ids;

	for(const auto & [mergedId, animation] : _startedQuad2dAnimations)
	{
		const auto splitKey = Tools::splitStringIntoTwo(mergedId, DELIMITER);

		ids.push_back(splitKey);
	}

	return ids;
}

const int Animation2dPlayer::getQuad3dAnimationPlayCount(const string & animation2dId, const string & quad3dId) const
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad3dId, DELIMITER);

	if(!_animation2dManager->isAnimationExisting(animation2dId))
	{
		abort();
	}
	if(!_quad3dEntityManager->isEntityExisting(quad3dId))
	{
		abort();
	}
	if(!isQuad3dAnimationStarted(animation2dId, quad3dId))
	{
		abort();
	}

	return _startedQuad3dAnimations.at(mergedId)->getPlayCount();
}

const int Animation2dPlayer::getQuad2dAnimationPlayCount(const string & animation2dId, const string & quad2dId) const
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad2dId, DELIMITER);

	if(!_animation2dManager->isAnimationExisting(animation2dId))
	{
		abort();
	}
	if(!_quad2dEntityManager->isEntityExisting(quad2dId))
	{
		abort();
	}
	if(!isQuad2dAnimationStarted(animation2dId, quad2dId))
	{
		abort();
	}

	return _startedQuad2dAnimations.at(mergedId)->getPlayCount();
}

const int Animation2dPlayer::getQuad3dAnimationRowIndex(const string & animation2dId, const string & quad3dId) const
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad3dId, DELIMITER);

	if(!_animation2dManager->isAnimationExisting(animation2dId))
	{
		abort();
	}
	if(!_quad3dEntityManager->isEntityExisting(quad3dId))
	{
		abort();
	}
	if(!isQuad3dAnimationStarted(animation2dId, quad3dId))
	{
		abort();
	}

	return _startedQuad3dAnimations.at(mergedId)->getRowIndex();
}

const int Animation2dPlayer::getQuad2dAnimationRowIndex(const string & animation2dId, const string & quad2dId) const
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad2dId, DELIMITER);

	if(!_animation2dManager->isAnimationExisting(animation2dId))
	{
		abort();
	}
	if(!_quad2dEntityManager->isEntityExisting(quad2dId))
	{
		abort();
	}
	if(!isQuad2dAnimationStarted(animation2dId, quad2dId))
	{
		abort();
	}

	return _startedQuad2dAnimations.at(mergedId)->getRowIndex();
}

const int Animation2dPlayer::getQuad3dAnimationColumnIndex(const string & animation2dId, const string & quad3dId) const
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad3dId, DELIMITER);

	if(!_animation2dManager->isAnimationExisting(animation2dId))
	{
		abort();
	}
	if(!_quad3dEntityManager->isEntityExisting(quad3dId))
	{
		abort();
	}
	if(!isQuad3dAnimationStarted(animation2dId, quad3dId))
	{
		abort();
	}

	return _startedQuad3dAnimations.at(mergedId)->getColumnIndex();
}

const int Animation2dPlayer::getQuad2dAnimationColumnIndex(const string & animation2dId, const string & quad2dId) const
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad2dId, DELIMITER);

	if(!_animation2dManager->isAnimationExisting(animation2dId))
	{
		abort();
	}
	if(!_quad2dEntityManager->isEntityExisting(quad2dId))
	{
		abort();
	}
	if(!isQuad2dAnimationStarted(animation2dId, quad2dId))
	{
		abort();
	}

	return _startedQuad2dAnimations.at(mergedId)->getColumnIndex();
}

const int Animation2dPlayer::getQuad3dAnimationIntervalMultiplier(const string & animation2dId, const string & quad3dId) const
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad3dId, DELIMITER);

	if(!_animation2dManager->isAnimationExisting(animation2dId))
	{
		abort();
	}
	if(!_quad3dEntityManager->isEntityExisting(quad3dId))
	{
		abort();
	}
	if(!isQuad3dAnimationStarted(animation2dId, quad3dId))
	{
		abort();
	}

	return _startedQuad2dAnimations.at(mergedId)->getIntervalMultiplier();
}

const int Animation2dPlayer::getQuad2dAnimationIntervalMultiplier(const string & animation2dId, const string & quad2dId) const
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad2dId, DELIMITER);

	if(!_animation2dManager->isAnimationExisting(animation2dId))
	{
		abort();
	}
	if(!_quad2dEntityManager->isEntityExisting(quad2dId))
	{
		abort();
	}
	if(!isQuad2dAnimationStarted(animation2dId, quad2dId))
	{
		abort();
	}

	return _startedQuad2dAnimations.at(mergedId)->getIntervalMultiplier();
}

const int Animation2dPlayer::getQuad3dAnimationIntervalDivider(const string & animation2dId, const string & quad3dId) const
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad3dId, DELIMITER);

	if(!_animation2dManager->isAnimationExisting(animation2dId))
	{
		abort();
	}
	if(!_quad3dEntityManager->isEntityExisting(quad3dId))
	{
		abort();
	}
	if(!isQuad3dAnimationStarted(animation2dId, quad3dId))
	{
		abort();
	}

	return _startedQuad2dAnimations.at(mergedId)->getIntervalDivider();
}

const int Animation2dPlayer::getQuad2dAnimationIntervalDivider(const string & animation2dId, const string & quad2dId) const
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad2dId, DELIMITER);

	if(!_animation2dManager->isAnimationExisting(animation2dId))
	{
		abort();
	}
	if(!_quad2dEntityManager->isEntityExisting(quad2dId))
	{
		abort();
	}
	if(!isQuad2dAnimationStarted(animation2dId, quad2dId))
	{
		abort();
	}

	return _startedQuad2dAnimations.at(mergedId)->getIntervalDivider();
}

const bool Animation2dPlayer::isQuad3dAnimationStarted(const string & animation2dId, const string & quad3dId) const
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad3dId, DELIMITER);

	if(!_animation2dManager->isAnimationExisting(animation2dId))
	{
		abort();
	}
	if(!_quad3dEntityManager->isEntityExisting(quad3dId))
	{
		abort();
	}

	return (_startedQuad3dAnimations.find(mergedId) != _startedQuad3dAnimations.end());
}

const bool Animation2dPlayer::isQuad3dAnimationPaused(const string & animation2dId, const string & quad3dId) const
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad3dId, DELIMITER);

	if(!_animation2dManager->isAnimationExisting(animation2dId))
	{
		abort();
	}
	if(!_quad3dEntityManager->isEntityExisting(quad3dId))
	{
		abort();
	}
	if(!isQuad3dAnimationStarted(animation2dId, quad3dId))
	{
		abort();
	}

	return _startedQuad3dAnimations.at(mergedId)->isPaused();
}

const bool Animation2dPlayer::isQuad3dAnimationAutopaused(const string & animation2dId, const string & quad3dId) const
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad3dId, DELIMITER);

	if(!_animation2dManager->isAnimationExisting(animation2dId))
	{
		abort();
	}
	if(!_quad3dEntityManager->isEntityExisting(quad3dId))
	{
		abort();
	}
	if(!isQuad3dAnimationStarted(animation2dId, quad3dId))
	{
		abort();
	}

	return _startedQuad3dAnimations.at(mergedId)->isAutopaused();
}

const bool Animation2dPlayer::isQuad2dAnimationStarted(const string & animation2dId, const string & quad2dId) const
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad2dId, DELIMITER);

	if(!_animation2dManager->isAnimationExisting(animation2dId))
	{
		abort();
	}
	if(!_quad2dEntityManager->isEntityExisting(quad2dId))
	{
		abort();
	}

	return (_startedQuad2dAnimations.find(mergedId) != _startedQuad2dAnimations.end());
}

const bool Animation2dPlayer::isQuad2dAnimationPaused(const string & animation2dId, const string & quad2dId) const
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad2dId, DELIMITER);

	if(!_animation2dManager->isAnimationExisting(animation2dId))
	{
		abort();
	}
	if(!_quad2dEntityManager->isEntityExisting(quad2dId))
	{
		abort();
	}
	if(!isQuad2dAnimationStarted(animation2dId, quad2dId))
	{
		abort();
	}

	return _startedQuad2dAnimations.at(mergedId)->isPaused();
}

const bool Animation2dPlayer::isQuad2dAnimationAutopaused(const string & animation2dId, const string & quad2dId) const
{
	const auto mergedId = Tools::mergeStrings(animation2dId, quad2dId, DELIMITER);

	if(!_animation2dManager->isAnimationExisting(animation2dId))
	{
		abort();
	}
	if(!_quad2dEntityManager->isEntityExisting(quad2dId))
	{
		abort();
	}
	if(!isQuad2dAnimationStarted(animation2dId, quad2dId))
	{
		abort();
	}

	return _startedQuad2dAnimations.at(mergedId)->isAutopaused();
}