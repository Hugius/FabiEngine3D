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

const vector<string> Animation2dPlayer::getStartedQuad3dAnimationIds(const string& quadId) const
{
	set<string> ids;

	for(const auto& [key, animation] : _startedQuad3dAnimations)
	{
		if(quadId == key.second)
		{
			ids.insert(key.first);
		}
	}

	return vector<string>(ids.begin(), ids.end());
}

const vector<string> Animation2dPlayer::getStartedQuad2dAnimationIds(const string& quadId) const
{
	set<string> ids;

	for(const auto& [key, animation] : _startedQuad2dAnimations)
	{
		if(quadId == key.second)
		{
			ids.insert(key.first);
		}
	}

	return vector<string>(ids.begin(), ids.end());
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