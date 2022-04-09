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

	for(const auto & [key, animation] : _startedQuad3dAnimations)
	{
		const auto splitKey = Tools::splitStringIntoTwo(key, DELIMITER);

		ids.push_back(splitKey);
	}

	return ids;
}

const vector<pair<string, string>> Animation2dPlayer::getStartedQuad2dAnimationIds() const
{
	vector<pair<string, string>> ids;

	for(const auto & [key, animation] : _startedQuad2dAnimations)
	{
		const auto splitKey = Tools::splitStringIntoTwo(key, DELIMITER);

		ids.push_back(splitKey);
	}

	return ids;
}

const int Animation2dPlayer::getQuad3dAnimationPlayCount(const string & animationId, const string & quadId) const
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

	return _startedQuad3dAnimations.at(key)->getPlayCount();
}

const int Animation2dPlayer::getQuad2dAnimationPlayCount(const string & animationId, const string & quadId) const
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

	return _startedQuad2dAnimations.at(key)->getPlayCount();
}

const unsigned int Animation2dPlayer::getQuad3dAnimationRowIndex(const string & animationId, const string & quadId) const
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

	return _startedQuad3dAnimations.at(key)->getRowIndex();
}

const unsigned int Animation2dPlayer::getQuad2dAnimationRowIndex(const string & animationId, const string & quadId) const
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

	return _startedQuad2dAnimations.at(key)->getRowIndex();
}

const unsigned int Animation2dPlayer::getQuad3dAnimationColumnIndex(const string & animationId, const string & quadId) const
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

	return _startedQuad3dAnimations.at(key)->getColumnIndex();
}

const unsigned int Animation2dPlayer::getQuad2dAnimationColumnIndex(const string & animationId, const string & quadId) const
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

	return _startedQuad2dAnimations.at(key)->getColumnIndex();
}

const unsigned int Animation2dPlayer::getQuad3dAnimationIntervalMultiplier(const string & animationId, const string & quadId) const
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

	return _startedQuad2dAnimations.at(key)->getIntervalMultiplier();
}

const unsigned int Animation2dPlayer::getQuad2dAnimationIntervalMultiplier(const string & animationId, const string & quadId) const
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

	return _startedQuad2dAnimations.at(key)->getIntervalMultiplier();
}

const unsigned int Animation2dPlayer::getQuad3dAnimationIntervalDivider(const string & animationId, const string & quadId) const
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

	return _startedQuad2dAnimations.at(key)->getIntervalDivider();
}

const unsigned int Animation2dPlayer::getQuad2dAnimationIntervalDivider(const string & animationId, const string & quadId) const
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

	return _startedQuad2dAnimations.at(key)->getIntervalDivider();
}

const bool Animation2dPlayer::isQuad3dAnimationStarted(const string & animationId, const string & quadId) const
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

	return (_startedQuad3dAnimations.find(key) != _startedQuad3dAnimations.end());
}

const bool Animation2dPlayer::isQuad3dAnimationPaused(const string & animationId, const string & quadId) const
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

	return _startedQuad3dAnimations.at(key)->isPaused();
}

const bool Animation2dPlayer::isQuad3dAnimationAutopaused(const string & animationId, const string & quadId) const
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

	return _startedQuad3dAnimations.at(key)->isAutopaused();
}

const bool Animation2dPlayer::isQuad2dAnimationStarted(const string & animationId, const string & quadId) const
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

	return (_startedQuad2dAnimations.find(key) != _startedQuad2dAnimations.end());
}

const bool Animation2dPlayer::isQuad2dAnimationPaused(const string & animationId, const string & quadId) const
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

	return _startedQuad2dAnimations.at(key)->isPaused();
}

const bool Animation2dPlayer::isQuad2dAnimationAutopaused(const string & animationId, const string & quadId) const
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

	return _startedQuad2dAnimations.at(key)->isAutopaused();
}