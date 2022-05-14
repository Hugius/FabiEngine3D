#include "animation2d_manager.hpp"

using std::make_shared;

void Animation2dManager::createAnimation2d(const string & animation2dId)
{
	if(isAnimation2dExisting(animation2dId))
	{
		abort();
	}

	const auto animation2d = make_shared<Animation2d>(animation2dId);

	_animation2ds.insert({animation2dId, animation2d});
}

void Animation2dManager::deleteAnimation2d(const string & animation2dId)
{
	if(!isAnimation2dExisting(animation2dId))
	{
		abort();
	}

	_animation2ds.erase(animation2dId);
}

void Animation2dManager::deleteAnimation2ds()
{
	_animation2ds.clear();
}

const bool Animation2dManager::isAnimation2dExisting(const string & animation2dId) const
{
	return (_animation2ds.find(animation2dId) != _animation2ds.end());
}

const bool Animation2dManager::isAnimation2dsExisting() const
{
	return !_animation2ds.empty();
}

const shared_ptr<Animation2d> Animation2dManager::getAnimation2d(const string & animation2dId) const
{
	const auto iterator = _animation2ds.find(animation2dId);

	if(iterator == _animation2ds.end())
	{
		abort();
	}

	return iterator->second;
}

const unordered_map<string, shared_ptr<Animation2d>> & Animation2dManager::getAnimation2ds() const
{
	return _animation2ds;
}