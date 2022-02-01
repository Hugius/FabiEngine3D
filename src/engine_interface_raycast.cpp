#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::raycast_setTerrainPointingEnabled(bool value)
{
	_core->getRaycaster()->setTerrainPointingEnabled(value);
}

void EngineInterface::raycast_setTerrainPointingDistance(float value)
{
	_core->getRaycaster()->setTerrainPointingDistance(value);
}

void EngineInterface::raycast_setTerrainPointingPrecision(float value)
{
	_core->getRaycaster()->setTerrainPointingPrecision(value);
}

const pair<const string, float> EngineInterface::raycast_checkCursorInAny()
{
	float closestDistance = FLT_MAX;

	for(const auto& [key, entity] : _core->getAabbEntityManager()->getEntities())
	{
		if(entity->isRaycastResponsive())
		{
			float distance;

			if(entity->isCentered())
			{
				const auto position = entity->getPosition();
				const auto left = (entity->getSize().x * 0.5f);
				const auto right = (entity->getSize().x * 0.5f);
				const auto bottom = (entity->getSize().y * 0.5f);
				const auto top = (entity->getSize().y * 0.5f);
				const auto back = (entity->getSize().z * 0.5f);
				const auto front = (entity->getSize().z * 0.5f);
				const auto box = Box(position, left, right, bottom, top, back, front);

				distance = _core->getRaycaster()->calculateRayBoxIntersectionDistance(_core->getRaycaster()->getCursorRay(), box);
			}
			else
			{
				const auto position = entity->getPosition();
				const auto left = (entity->getSize().x * 0.5f);
				const auto right = (entity->getSize().x * 0.5f);
				const auto bottom = 0.0f;
				const auto top = entity->getSize().y;
				const auto back = (entity->getSize().z * 0.5f);
				const auto front = (entity->getSize().z * 0.5f);
				const auto box = Box(position, left, right, bottom, top, back, front);

				distance = _core->getRaycaster()->calculateRayBoxIntersectionDistance(_core->getRaycaster()->getCursorRay(), box);
			}

			if((distance != -1.0f) && (distance < closestDistance))
			{
				closestDistance = distance;
				_hoveredAabbId = entity->getId();
				_hoveredAabbDistance = closestDistance;
			}
		}
	}

	if(!_core->getAabbEntityManager()->isEntityExisting(_hoveredAabbId) || _hoveredAabbId.empty())
	{
		_hoveredAabbId = "";
		_hoveredAabbDistance = -1.0f;
	}

	_isRaycastUpdated = true;
	return make_pair(_hoveredAabbId, _hoveredAabbDistance);
}

const pair<bool, float> EngineInterface::raycast_checkCursorInEntity(const string& id, bool canBeOccluded)
{
	if(canBeOccluded)
	{
		if(!_isRaycastUpdated)
		{
			raycast_checkCursorInAny();
		}

		if(_core->getAabbEntityManager()->isEntityExisting(_hoveredAabbId))
		{
			return make_pair((id == _hoveredAabbId), _hoveredAabbDistance);
		}
		else
		{
			return make_pair(false, -1.0f);
		}
	}
	else
	{
		auto entity = _core->getAabbEntityManager()->getEntity(id);

		if(entity->isRaycastResponsive())
		{
			float distance;
			if(entity->isCentered())
			{
				const auto position = entity->getPosition();
				const auto left = (entity->getSize().x * 0.5f);
				const auto right = (entity->getSize().x * 0.5f);
				const auto bottom = (entity->getSize().y * 0.5f);
				const auto top = (entity->getSize().y * 0.5f);
				const auto back = (entity->getSize().z * 0.5f);
				const auto front = (entity->getSize().z * 0.5f);
				const auto box = Box(position, left, right, bottom, top, back, front);

				distance = _core->getRaycaster()->calculateRayBoxIntersectionDistance(_core->getRaycaster()->getCursorRay(), box);
			}
			else
			{
				const auto position = entity->getPosition();
				const auto left = (entity->getSize().x * 0.5f);
				const auto right = (entity->getSize().x * 0.5f);
				const auto bottom = 0.0f;
				const auto top = entity->getSize().y;
				const auto back = (entity->getSize().z * 0.5f);
				const auto front = (entity->getSize().z * 0.5f);
				const auto box = Box(position, left, right, bottom, top, back, front);

				distance = _core->getRaycaster()->calculateRayBoxIntersectionDistance(_core->getRaycaster()->getCursorRay(), box);
			}

			return make_pair((distance != -1.0f), distance);
		}
	}
}

const pair<const string, float> EngineInterface::raycast_checkCursorInEntities(const string& id, bool canBeOccluded)
{
	if(canBeOccluded)
	{
		if(!_isRaycastUpdated)
		{
			raycast_checkCursorInAny();
		}

		if(_hoveredAabbId.empty() || !_core->getAabbEntityManager()->isEntityExisting(_hoveredAabbId))
		{
			return make_pair("", -1.0f);
		}

		if(_hoveredAabbId.substr(0, id.size()) == id)
		{
			return make_pair(_hoveredAabbId, _hoveredAabbDistance);
		}

		return make_pair("", -1.0f);
	}
	else
	{
		float closestDistance = FLT_MAX;
		string closestBoxId = "";

		for(const auto& [key, entity] : _core->getAabbEntityManager()->getEntities())
		{
			if(entity->isRaycastResponsive())
			{
				if(entity->getId().substr(0, id.size()) == id)
				{
					float distance;
					if(entity->isCentered())
					{
						const auto position = entity->getPosition();
						const auto left = (entity->getSize().x * 0.5f);
						const auto right = (entity->getSize().x * 0.5f);
						const auto bottom = (entity->getSize().y * 0.5f);
						const auto top = (entity->getSize().y * 0.5f);
						const auto back = (entity->getSize().z * 0.5f);
						const auto front = (entity->getSize().z * 0.5f);
						const auto box = Box(position, left, right, bottom, top, back, front);

						distance = _core->getRaycaster()->calculateRayBoxIntersectionDistance(_core->getRaycaster()->getCursorRay(), box);
					}
					else
					{
						const auto position = entity->getPosition();
						const auto left = (entity->getSize().x * 0.5f);
						const auto right = (entity->getSize().x * 0.5f);
						const auto bottom = 0.0f;
						const auto top = entity->getSize().y;
						const auto back = (entity->getSize().z * 0.5f);
						const auto front = (entity->getSize().z * 0.5f);
						const auto box = Box(position, left, right, bottom, top, back, front);

						distance = _core->getRaycaster()->calculateRayBoxIntersectionDistance(_core->getRaycaster()->getCursorRay(), box);
					}

					if((distance != -1.0f) && (distance < closestDistance))
					{
						closestDistance = distance;
						closestBoxId = entity->getId();
					}
				}
			}
		}

		if(closestBoxId.empty())
		{
			return make_pair("", -1.0f);
		}
		else
		{
			return make_pair(closestBoxId, closestDistance);
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

const float EngineInterface::raycast_getTerrainPointingDistance() const
{
	return _core->getRaycaster()->getTerrainPointingDistance();
}

const float EngineInterface::raycast_getTerrainPointingPrecision() const
{
	return _core->getRaycaster()->getTerrainPointingPrecision();
}

const bool EngineInterface::raycast_isPointOnTerrainValid() const
{
	return (_core->getRaycaster()->getTerrainPoint() != fvec3(-1.0f));
}

const bool EngineInterface::raycast_isTerrainPointingEnabled() const
{
	return _core->getRaycaster()->isTerrainPointingEnabled();
}