#include "animation3d_manager.hpp"

using std::make_shared;

void Animation3dManager::createAnimation(const string & id)
{
	if(isAnimationExisting(id))
	{
		abort();
	}

	auto animation3d = make_shared<Animation3d>(id);

	_animations.insert({id, animation3d});
}

void Animation3dManager::deleteAnimation(const string & id)
{
	if(!isAnimationExisting(id))
	{
		abort();
	}

	_animations.erase(id);
}

void Animation3dManager::deleteAnimations()
{
	_animations.clear();
}

const bool Animation3dManager::isAnimationExisting(const string & id) const
{
	return (_animations.find(id) != _animations.end());
}

const bool Animation3dManager::isAnimationsExisting() const
{
	return !_animations.empty();
}

const shared_ptr<Animation3d> Animation3dManager::getAnimation(const string & id) const
{
	auto iterator = _animations.find(id);

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