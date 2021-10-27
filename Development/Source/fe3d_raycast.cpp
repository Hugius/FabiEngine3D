#include "fe3d.hpp"
#include "core_engine.hpp"

using std::numeric_limits;

void FabiEngine3D::raycast_enableTerrainPointing(float distance, float precision)
{
	if (_core->_raycaster.isTerrainPointingEnabled())
	{
		Logger::throwWarning("Tried to enable terrain raycast pointing: already enabled!");
		return;
	}

	_core->_raycaster.setTerrainPointingEnabled(true);
	_core->_raycaster.setTerrainPointingDistance(distance);
	_core->_raycaster.setTerrainPointingPrecision(precision);
}

void FabiEngine3D::raycast_disableTerrainPointing()
{
	if (!_core->_raycaster.isTerrainPointingEnabled())
	{
		Logger::throwWarning("Tried to disable terrain raycast pointing: not enabled!");
		return;
	}

	_core->_raycaster.setTerrainPointingEnabled(false);
}

const pair<const string, float> FabiEngine3D::raycast_checkCursorInAny()
{
	// Temporary values
	float closestDistance = (numeric_limits<float>::max)();

	// Iterate through AABB entities
	for (const auto& [keyID, entity] : _core->_aabbEntityManager.getEntities())
	{
		// Check if parent entity does not have LOD
		if (!(entity->hasParent() && entity->getParentType() == AabbParentType::MODEL_ENTITY &&
			_core->_modelEntityManager.getEntity(entity->getParentID())->isLevelOfDetailed()))
		{
			// Check if AABB is responsive
			if (entity->isRaycastResponsive() && entity->isVisible())
			{
				// Compose AABB dimensions
				auto position = entity->getPosition();
				float left = (entity->getSize().x / 2.0f);
				float right = (entity->getSize().x / 2.0f);
				float bottom = 0.0f;
				float top = entity->getSize().y;
				float back = (entity->getSize().z / 2.0f);
				float front = (entity->getSize().z / 2.0f);

				// Check intersection
				float distance = _core->_raycaster.calculateRayBoxIntersectionDistance(_core->_raycaster.getCursorRay(), Box(position, left, right, bottom, top, back, front));

				// Check if closest to camera
				if ((distance != -1.0f) && (distance < closestDistance))
				{
					closestDistance = distance;
					_hoveredAabbID = entity->getID();
					_hoveredAabbDistance = closestDistance;
				}
			}
		}
	}

	// Update hovered AABB status
	if (!_core->_aabbEntityManager.isExisting(_hoveredAabbID) || _hoveredAabbID.empty())
	{
		_hoveredAabbID = "";
		_hoveredAabbDistance = -1.0f;
	}

	// Return
	_isRaycastUpdated = true;
	return make_pair(_hoveredAabbID, _hoveredAabbDistance);
}

const pair<bool, float> FabiEngine3D::raycast_checkCursorInEntity(const string& ID, bool canBeOccluded)
{
	// Check whether the AABB can be raycasted if it's occluded by another AABB
	if (canBeOccluded)
	{
		// Check if raycasting needs to be updated
		if (!_isRaycastUpdated)
		{
			raycast_checkCursorInAny();
		}

		// Check if hovered AABB still exists
		if (_core->_aabbEntityManager.isExisting(_hoveredAabbID))
		{
			auto result = (ID == _hoveredAabbID);
			return make_pair(result, _hoveredAabbDistance);
		}
		else
		{
			return make_pair(false, -1.0f);
		}
	}
	else
	{
		auto entity = _core->_aabbEntityManager.getEntity(ID);

		if (entity->isRaycastResponsive() && entity->isVisible())
		{
			// Compose AABB dimensions
			auto position = entity->getPosition();
			float left = (entity->getSize().x / 2.0f);
			float right = (entity->getSize().x / 2.0f);
			float bottom = 0.0f;
			float top = entity->getSize().y;
			float back = (entity->getSize().z / 2.0f);
			float front = (entity->getSize().z / 2.0f);

			// Calculate intersection & distance
			float distance = _core->_raycaster.calculateRayBoxIntersectionDistance(_core->_raycaster.getCursorRay(), Box(position, left, right, bottom, top, back, front));
			bool result = (distance != -1.0f);

			// Return
			return make_pair(result, distance);
		}
	}
}

const pair<const string, float> FabiEngine3D::raycast_checkCursorInEntities(const string& ID, bool canBeOccluded)
{
	// Check whether the AABB can be raycasted if it's occluded by another AABB
	if (canBeOccluded)
	{
		// Check if raycasting needs to be updated
		if (!_isRaycastUpdated)
		{
			raycast_checkCursorInAny();
		}

		// Check if hovered AABB is empty or non-existing
		if (_hoveredAabbID.empty() || !_core->_aabbEntityManager.isExisting(_hoveredAabbID))
		{
			return make_pair("", -1.0f);
		}

		// Check if ID matches (a part of) hovered AABB ID
		if (_hoveredAabbID.size() >= ID.size())
		{
			if (_hoveredAabbID.substr(0, ID.size()) == ID)
			{
				return make_pair(_hoveredAabbID, _hoveredAabbDistance);
			}
		}

		// ID not found
		return make_pair("", -1.0f);
	}
	else
	{
		// Temporary values
		float closestDistance = (numeric_limits<float>::max)();
		string closestBoxID = "";

		// Iterate through AABB entities
		for (const auto& [keyID, entity] : _core->_aabbEntityManager.getEntities())
		{
			if (entity->isRaycastResponsive() && entity->isVisible())
			{
				if (entity->getID().size() >= ID.size()) // Check if entity ID is at least the size of group ID
				{
					if (entity->getID().substr(0, ID.size()) == ID) // If entity matches ID
					{
						// Compose AABB dimensions
						auto position = entity->getPosition();
						float left = (entity->getSize().x / 2.0f);
						float right = (entity->getSize().x / 2.0f);
						float bottom = 0.0f;
						float top = entity->getSize().y;
						float back = (entity->getSize().z / 2.0f);
						float front = (entity->getSize().z / 2.0f);

						// Check intersection
						float distance = _core->_raycaster.calculateRayBoxIntersectionDistance(_core->_raycaster.getCursorRay(), Box(position, left, right, bottom, top, back, front));

						// Check if closest to camera
						if ((distance != -1.0f) && (distance < closestDistance))
						{
							closestDistance = distance;
							closestBoxID = entity->getID();
						}
					}
				}
			}
		}

		// Return
		if (closestBoxID.empty())
		{
			return make_pair("", -1.0f);
		}
		else
		{
			return make_pair(closestBoxID, closestDistance);
		}
	}
}

const Ray FabiEngine3D::raycast_getCursorRay()
{
	return _core->_raycaster.getCursorRay();
}

const Vec3 FabiEngine3D::raycast_getPointOnTerrain()
{
	return _core->_raycaster.getTerrainPoint();
}

const bool FabiEngine3D::raycast_isPointOnTerrainValid()
{
	return (_core->_raycaster.getTerrainPoint() != Vec3(-1.0f));
}

const bool FabiEngine3D::raycast_isTerrainPointingEnabled()
{
	return _core->_raycaster.isTerrainPointingEnabled();
}