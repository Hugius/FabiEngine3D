#include "spotlight_entity_manager.hpp"

using std::make_shared;

const shared_ptr<SpotlightEntity> SpotlightManager::getSpotlight(const string & spotlightId) const
{
	auto iterator = _spotlights.find(spotlightId);

	if(iterator == _spotlights.end())
	{
		abort();
	}

	return iterator->second;
}

const unordered_map<string, shared_ptr<SpotlightEntity>> & SpotlightManager::getSpotlights() const
{
	return _spotlights;
}

void SpotlightManager::createSpotlight(const string & spotlightId)
{
	if(isSpotlightExisting(spotlightId))
	{
		abort();
	}

	if(getSpotlights().size() == MAX_SPOTLIGHT_COUNT)
	{
		abort();
	}

	auto entity = make_shared<SpotlightEntity>(spotlightId);

	_spotlights.insert({spotlightId, entity});
}

void SpotlightManager::update()
{
	for(const auto & [entityId, entity] : _spotlights)
	{
		entity->updateTarget();

		if(entity->isVisible())
		{
			entity->updateFront();
		}
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

const int SpotlightManager::getMaxSpotlightCount() const
{
	return MAX_SPOTLIGHT_COUNT;
}

const bool SpotlightManager::isSpotlightExisting(const string & spotlightId) const
{
	return (_spotlights.find(spotlightId) != _spotlights.end());
}

const bool SpotlightManager::isSpotlightsExisting() const
{
	return !_spotlights.empty();
}