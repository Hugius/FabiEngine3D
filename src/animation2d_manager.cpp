#include "animation2d_manager.hpp"

using std::make_shared;

void Animation2dManager::createAnimation(const string & animation2dId)
{
	if(isAnimationExisting(animation2dId))
	{
		abort();
	}

	auto animation = make_shared<Animation2d>(animation2dId);

	_animations.insert({animation2dId, animation});
}

void Animation2dManager::deleteAnimation(const string & animation2dId)
{
	if(!isAnimationExisting(animation2dId))
	{
		abort();
	}

	_animations.erase(animation2dId);
}

void Animation2dManager::deleteAnimations()
{
	_animations.clear();
}

const bool Animation2dManager::isAnimationExisting(const string & animation2dId) const
{
	return (_animations.find(animation2dId) != _animations.end());
}

const bool Animation2dManager::isAnimationsExisting() const
{
	return !_animations.empty();
}

const shared_ptr<Animation2d> Animation2dManager::getAnimation(const string & animation2dId) const
{
	auto iterator = _animations.find(animation2dId);

	if(iterator == _animations.end())
	{
		abort();
	}

	return iterator->second;
}

const unordered_map<string, shared_ptr<Animation2d>> & Animation2dManager::getAnimations() const
{
	return _animations;
}