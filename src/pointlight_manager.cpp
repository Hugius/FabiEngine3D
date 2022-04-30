#include "pointlight_manager.hpp"

using std::make_shared;

const shared_ptr<Pointlight> PointlightManager::getPointlight(const string & pointlightId) const
{
	auto iterator = _pointlights.find(pointlightId);

	if(iterator == _pointlights.end())
	{
		abort();
	}

	return iterator->second;
}

const unordered_map<string, shared_ptr<Pointlight>> & PointlightManager::getPointlights() const
{
	return _pointlights;
}

void PointlightManager::createPointlight(const string & pointlightId)
{
	if(isPointlightExisting(pointlightId))
	{
		abort();
	}

	if(getPointlights().size() == MAX_COUNT)
	{
		abort();
	}

	auto pointlight = make_shared<Pointlight>(pointlightId);

	_pointlights.insert({pointlightId, pointlight});
}

void PointlightManager::deletePointlight(const string & pointlightId)
{
	if(!isPointlightExisting(pointlightId))
	{
		abort();
	}

	_pointlights.erase(pointlightId);
}

void PointlightManager::deletePointlights()
{
	_pointlights.clear();
}

const int PointlightManager::getMaxCount() const
{
	return MAX_COUNT;
}

const bool PointlightManager::isPointlightExisting(const string & pointlightId) const
{
	return (_pointlights.find(pointlightId) != _pointlights.end());
}

const bool PointlightManager::isPointlightsExisting() const
{
	return !_pointlights.empty();
}

void PointlightManager::update()
{
	for(const auto & [pointlightId, pointlight] : _pointlights)
	{
		pointlight->updateTarget();
	}
}