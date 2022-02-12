#include "animation2d_player.hpp"

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

	for(const auto& [key, animation] : _startedQuad3dAnimations)
	{
		ids.push_back(key);
	}

	return ids;
}

const vector<pair<string, string>> Animation2dPlayer::getStartedQuad2dAnimationIds() const
{
	vector<pair<string, string>> ids;

	for(const auto& [key, animation] : _startedQuad2dAnimations)
	{
		ids.push_back(key);
	}

	return ids;
}

const int Animation2dPlayer::getQuad3dAnimationPlayCount(const string& animationId, const string& quadId) const
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

	return _startedQuad3dAnimations.at(make_pair(animationId, quadId))->getPlayCount();
}

const int Animation2dPlayer::getQuad2dAnimationPlayCount(const string& animationId, const string& quadId) const
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

	return _startedQuad2dAnimations.at(make_pair(animationId, quadId))->getPlayCount();
}

const unsigned int Animation2dPlayer::getQuad3dAnimationRowIndex(const string& animationId, const string& quadId) const
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

	return _startedQuad3dAnimations.at(make_pair(animationId, quadId))->getRowIndex();
}

const unsigned int Animation2dPlayer::getQuad2dAnimationRowIndex(const string& animationId, const string& quadId) const
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

	return _startedQuad2dAnimations.at(make_pair(animationId, quadId))->getRowIndex();
}

const unsigned int Animation2dPlayer::getQuad3dAnimationColumnIndex(const string& animationId, const string& quadId) const
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

	return _startedQuad3dAnimations.at(make_pair(animationId, quadId))->getColumnIndex();
}

const unsigned int Animation2dPlayer::getQuad2dAnimationColumnIndex(const string& animationId, const string& quadId) const
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

	return _startedQuad2dAnimations.at(make_pair(animationId, quadId))->getColumnIndex();
}

const unsigned int Animation2dPlayer::getQuad3dAnimationIntervalMultiplier(const string& animationId, const string& quadId) const
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

	return _startedQuad2dAnimations.at(make_pair(animationId, quadId))->getIntervalMultiplier();
}

const unsigned int Animation2dPlayer::getQuad2dAnimationIntervalMultiplier(const string& animationId, const string& quadId) const
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

	return _startedQuad2dAnimations.at(make_pair(animationId, quadId))->getIntervalMultiplier();
}

const unsigned int Animation2dPlayer::getQuad3dAnimationIntervalDivider(const string& animationId, const string& quadId) const
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

	return _startedQuad2dAnimations.at(make_pair(animationId, quadId))->getIntervalDivider();
}

const unsigned int Animation2dPlayer::getQuad2dAnimationIntervalDivider(const string& animationId, const string& quadId) const
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

	return _startedQuad2dAnimations.at(make_pair(animationId, quadId))->getIntervalDivider();
}

const bool Animation2dPlayer::isQuad3dAnimationStarted(const string& animationId, const string& quadId) const
{
	if(!_animation2dManager->isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_quad3dEntityManager->isEntityExisting(quadId))
	{
		abort();
	}

	return (_startedQuad3dAnimations.find(make_pair(animationId, quadId)) != _startedQuad3dAnimations.end());
}

const bool Animation2dPlayer::isQuad3dAnimationPlaying(const string& animationId, const string& quadId) const
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

	return !isQuad3dAnimationPaused(animationId, quadId);
}

const bool Animation2dPlayer::isQuad3dAnimationPaused(const string& animationId, const string& quadId) const
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

	return _startedQuad3dAnimations.at(make_pair(animationId, quadId))->isPaused();
}

const bool Animation2dPlayer::isQuad3dAnimationAutopaused(const string& animationId, const string& quadId) const
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

	return _startedQuad3dAnimations.at(make_pair(animationId, quadId))->isAutopaused();
}

const bool Animation2dPlayer::isQuad2dAnimationStarted(const string& animationId, const string& quadId) const
{
	if(!_animation2dManager->isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_quad2dEntityManager->isEntityExisting(quadId))
	{
		abort();
	}

	return (_startedQuad2dAnimations.find(make_pair(animationId, quadId)) != _startedQuad2dAnimations.end());
}

const bool Animation2dPlayer::isQuad2dAnimationPlaying(const string& animationId, const string& quadId) const
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

	return !isQuad2dAnimationPaused(animationId, quadId);
}

const bool Animation2dPlayer::isQuad2dAnimationPaused(const string& animationId, const string& quadId) const
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

	return _startedQuad2dAnimations.at(make_pair(animationId, quadId))->isPaused();
}

const bool Animation2dPlayer::isQuad2dAnimationAutopaused(const string& animationId, const string& quadId) const
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

	return _startedQuad2dAnimations.at(make_pair(animationId, quadId))->isAutopaused();
}