#include "spotlight_manager.hpp"

using std::make_shared;

const shared_ptr<Spotlight> SpotlightManager::getSpotlight(const string & spotlightId) const
{
	const auto iterator = _spotlights.find(spotlightId);

	if(iterator == _spotlights.end())
	{
		abort();
	}

	return iterator->second;
}

const unordered_map<string, shared_ptr<Spotlight>> & SpotlightManager::getSpotlights() const
{
	return _spotlights;
}

void SpotlightManager::createSpotlight(const string & spotlightId)
{
	if(isSpotlightExisting(spotlightId))
	{
		abort();
	}

	if(getSpotlights().size() == MAX_COUNT)
	{
		abort();
	}

	const auto spotlight = make_shared<Spotlight>(spotlightId);

	_spotlights.insert({spotlightId, spotlight});
}

void SpotlightManager::update()
{
	for(const auto & [spotlightId, spotlight] : _spotlights)
	{
		spotlight->updateTarget();
	}
}

void SpotlightManager::deleteSpotlight(const string & spotlightId)
{
	if(!isSpotlightExisting(spotlightId))
	{
		abort();
	}

	_spotlights.erase(spotlightId);
}

void SpotlightManager::deleteSpotlights()
{
	_spotlights.clear();
}

const int SpotlightManager::getMaxCount() const
{
	return MAX_COUNT;
}

const bool SpotlightManager::isSpotlightExisting(const string & spotlightId) const
{
	return (_spotlights.find(spotlightId) != _spotlights.end());
}

const bool SpotlightManager::isSpotlightsExisting() const
{
	return !_spotlights.empty();
}