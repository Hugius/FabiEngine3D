#include "animation3d_manager.hpp"

using std::make_shared;

void Animation3dManager::createAnimation(const string & animation3dId)
{
	if(isAnimationExisting(animation3dId))
	{
		abort();
	}

	auto animation3d = make_shared<Animation3d>(animation3dId);

	_animations.insert({animation3dId, animation3d});
}

void Animation3dManager::deleteAnimation(const string & animation3dId)
{
	if(!isAnimationExisting(animation3dId))
	{
		abort();
	}

	_animations.erase(animation3dId);
}

void Animation3dManager::deleteAnimations()
{
	_animations.clear();
}

const bool Animation3dManager::isAnimationExisting(const string & animation3dId) const
{
	return (_animations.find(animation3dId) != _animations.end());
}

const bool Animation3dManager::isAnimationsExisting() const
{
	return !_animations.empty();
}

const shared_ptr<Animation3d> Animation3dManager::getAnimation(const string & animation3dId) const
{
	auto iterator = _animations.find(animation3dId);

	if(iterator == _animations.end())
	{
		abort();
	}

	return iterator->second;
}

const unordered_map<string, shared_ptr<Animation3d>> & Animation3dManager::getAnimations() const
{
	return _animations;
}