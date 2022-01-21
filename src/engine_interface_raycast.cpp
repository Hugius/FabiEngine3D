#include "engine_interface.hpp"
#include "engine_core.hpp"

using std::numeric_limits;

void EngineInterface::raycast_enableTerrainPointing(float distance, float precision)
{
	if(_core->getRaycaster()->isTerrainPointingEnabled())
	{
		Logger::throwWarning("Tried to enable terrain raycast pointing: already enabled!");
		return;
	}

	_core->getRaycaster()->setTerrainPointingEnabled(true);
	_core->getRaycaster()->setTerrainPointingDistance(distance);
	_core->getRaycaster()->setTerrainPointingPrecision(precision);
}

void EngineInterface::raycast_disableTerrainPointing()
{
	if(!_core->getRaycaster()->isTerrainPointingEnabled())
	{
		Logger::throwWarning("Tried to disable terrain raycast pointing: not enabled!");
		return;
	}

	_core->getRaycaster()->setTerrainPointingEnabled(false);
}

const pair<const string, float> EngineInterface::raycast_checkCursorInAny()
{
	float closestDistance = numeric_limits<float>::max();

	for(const auto& [key, entity] : _core->getAabbEntityManager()->getEntities())
	{
		if(entity->isRaycastResponsive() && entity->isVisible())
		{
			float distance;

			if(entity->isCentered())
			{
				const auto position = entity->getPosition();
				const auto left = (entity->getSize().x / 2.0f);
				const auto right = (entity->getSize().x / 2.0f);
				const auto bottom = (entity->getSize().y / 2.0f);
				const auto top = (entity->getSize().y / 2.0f);
				const auto back = (entity->getSize().z / 2.0f);
				const auto front = (entity->getSize().z / 2.0f);
				const auto box = Box(position, left, right, bottom, top, back, front);

				distance = _core->getRaycaster()->calculateRayBoxIntersectionDistance(_core->getRaycaster()->getCursorRay(), box);
			}
			else
			{
				const auto position = entity->getPosition();
				const auto left = (entity->getSize().x / 2.0f);
				const auto right = (entity->getSize().x / 2.0f);
				const auto bottom = 0.0f;
				const auto top = entity->getSize().y;
				const auto back = (entity->getSize().z / 2.0f);
				const auto front = (entity->getSize().z / 2.0f);
				const auto box = Box(position, left, right, bottom, top, back, front);

				distance = _core->getRaycaster()->calculateRayBoxIntersectionDistance(_core->getRaycaster()->getCursorRay(), box);
			}

			if((distance != -1.0f) && (distance < closestDistance))
			{
				closestDistance = distance;
				_hoveredAabbID = entity->getID();
				_hoveredAabbDistance = closestDistance;
			}
		}
	}

	if(!_core->getAabbEntityManager()->isEntityExisting(_hoveredAabbID) || _hoveredAabbID.empty())
	{
		_hoveredAabbID = "";
		_hoveredAabbDistance = -1.0f;
	}

	_isRaycastUpdated = true;
	return make_pair(_hoveredAabbID, _hoveredAabbDistance);
}

const pair<bool, float> EngineInterface::raycast_checkCursorInEntity(const string& ID, bool canBeOccluded)
{
	if(canBeOccluded)
	{
		if(!_isRaycastUpdated)
		{
			raycast_checkCursorInAny();
		}

		if(_core->getAabbEntityManager()->isEntityExisting(_hoveredAabbID))
		{
			return make_pair((ID == _hoveredAabbID), _hoveredAabbDistance);
		}
		else
		{
			return make_pair(false, -1.0f);
		}
	}
	else
	{
		auto entity = _core->getAabbEntityManager()->getEntity(ID);

		if(entity->isRaycastResponsive() && entity->isVisible())
		{
			float distance;
			if(entity->isCentered())
			{
				const auto position = entity->getPosition();
				const auto left = (entity->getSize().x / 2.0f);
				const auto right = (entity->getSize().x / 2.0f);
				const auto bottom = (entity->getSize().y / 2.0f);
				const auto top = (entity->getSize().y / 2.0f);
				const auto back = (entity->getSize().z / 2.0f);
				const auto front = (entity->getSize().z / 2.0f);
				const auto box = Box(position, left, right, bottom, top, back, front);

				distance = _core->getRaycaster()->calculateRayBoxIntersectionDistance(_core->getRaycaster()->getCursorRay(), box);
			}
			else
			{
				const auto position = entity->getPosition();
				const auto left = (entity->getSize().x / 2.0f);
				const auto right = (entity->getSize().x / 2.0f);
				const auto bottom = 0.0f;
				const auto top = entity->getSize().y;
				const auto back = (entity->getSize().z / 2.0f);
				const auto front = (entity->getSize().z / 2.0f);
				const auto box = Box(position, left, right, bottom, top, back, front);

				distance = _core->getRaycaster()->calculateRayBoxIntersectionDistance(_core->getRaycaster()->getCursorRay(), box);
			}

			return make_pair((distance != -1.0f), distance);
		}
	}
}

const pair<const string, float> EngineInterface::raycast_checkCursorInEntities(const string& ID, bool canBeOccluded)
{
	if(canBeOccluded)
	{
		if(!_isRaycastUpdated)
		{
			raycast_checkCursorInAny();
		}

		if(_hoveredAabbID.empty() || !_core->getAabbEntityManager()->isEntityExisting(_hoveredAabbID))
		{
			return make_pair("", -1.0f);
		}

		if(_hoveredAabbID.substr(0, ID.size()) == ID)
		{
			return make_pair(_hoveredAabbID, _hoveredAabbDistance);
		}

		return make_pair("", -1.0f);
	}
	else
	{
		float closestDistance = numeric_limits<float>::max();
		string closestBoxID = "";

		for(const auto& [key, entity] : _core->getAabbEntityManager()->getEntities())
		{
			if(entity->isRaycastResponsive() && entity->isVisible())
			{
				if(entity->getID().substr(0, ID.size()) == ID)
				{
					float distance;
					if(entity->isCentered())
					{
						const auto position = entity->getPosition();
						const auto left = (entity->getSize().x / 2.0f);
						const auto right = (entity->getSize().x / 2.0f);
						const auto bottom = (entity->getSize().y / 2.0f);
						const auto top = (entity->getSize().y / 2.0f);
						const auto back = (entity->getSize().z / 2.0f);
						const auto front = (entity->getSize().z / 2.0f);
						const auto box = Box(position, left, right, bottom, top, back, front);

						distance = _core->getRaycaster()->calculateRayBoxIntersectionDistance(_core->getRaycaster()->getCursorRay(), box);
					}
					else
					{
						const auto position = entity->getPosition();
						const auto left = (entity->getSize().x / 2.0f);
						const auto right = (entity->getSize().x / 2.0f);
						const auto bottom = 0.0f;
						const auto top = entity->getSize().y;
						const auto back = (entity->getSize().z / 2.0f);
						const auto front = (entity->getSize().z / 2.0f);
						const auto box = Box(position, left, right, bottom, top, back, front);

						distance = _core->getRaycaster()->calculateRayBoxIntersectionDistance(_core->getRaycaster()->getCursorRay(), box);
					}

					if((distance != -1.0f) && (distance < closestDistance))
					{
						closestDistance = distance;
						closestBoxID = entity->getID();
					}
				}
			}
		}

		if(closestBoxID.empty())
		{
			return make_pair("", -1.0f);
		}
		else
		{
			return make_pair(closestBoxID, closestDistance);
		}
	}
}

const Ray& EngineInterface::raycast_getCursorRay() const
{
	return _core->getRaycaster()->getCursorRay();
}

const fvec3& EngineInterface::raycast_getPointOnTerrain() const
{
	return _core->getRaycaster()->getTerrainPoint();
}

const bool EngineInterface::raycast_isPointOnTerrainValid() const
{
	return (_core->getRaycaster()->getTerrainPoint() != fvec3(-1.0f));
}

const bool EngineInterface::raycast_isTerrainPointingEnabled() const
{
	return _core->getRaycaster()->isTerrainPointingEnabled();
}