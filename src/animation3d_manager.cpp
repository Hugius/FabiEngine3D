#include "animation3d_manager.hpp"

using std::make_shared;

void Animation3dManager::createAnimation3d(const string & animation3dId)
{
	if(isAnimation3dExisting(animation3dId))
	{
		abort();
	}

	auto animation3d = make_shared<Animation3d>(animation3dId);

	_animation3ds.insert({animation3dId, animation3d});
}

void Animation3dManager::deleteAnimation3d(const string & animation3dId)
{
	if(!isAnimation3dExisting(animation3dId))
	{
		abort();
	}

	_animation3ds.erase(animation3dId);
}

void Animation3dManager::deleteAnimation3ds()
{
	_animation3ds.clear();
}

const bool Animation3dManager::isAnimation3dExisting(const string & animation3dId) const
{
	return (_animation3ds.find(animation3dId) != _animation3ds.end());
}

const bool Animation3dManager::isAnimation3dsExisting() const
{
	return !_animation3ds.empty();
}

const shared_ptr<Animation3d> Animation3dManager::getAnimation3d(const string & animation3dId) const
{
	auto iterator = _animation3ds.find(animation3dId);

	if(iterator == _animation3ds.end())
	{
		abort();
	}

	return iterator->second;
}

const unordered_map<string, shared_ptr<Animation3d>> & Animation3dManager::getAnimation3ds() const
{
	return _animation3ds;
}