#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

using std::numeric_limits;

const pair<const string, float> FabiEngine3D::collision_checkCursorInAny()
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
				// Calculate box left bottom (LB) and right top (RT)
				Vec3 lb, rt;
				lb.x = (entity->getPosition().x - entity->getSize().x / 2.0f);
				lb.y = (entity->getPosition().y);
				lb.z = (entity->getPosition().z + entity->getSize().z / 2.0f);
				rt.x = (entity->getPosition().x + entity->getSize().x / 2.0f);
				rt.y = (entity->getPosition().y + entity->getSize().y);
				rt.z = (entity->getPosition().z - entity->getSize().z / 2.0f);

				// Check intersection
				float distance = _core->_rayCaster.checkCursorInBox(lb, rt, _core->_camera.getPosition());

				// Check if closest to camera
				if (distance != -1.0f && distance < closestDistance)
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

const pair<bool, float> FabiEngine3D::collision_checkCursorInEntity(const string& ID, bool canBeOccluded)
{
	// Check whether the AABB can be raycasted if it's occluded by another AABB
	if (canBeOccluded)
	{
		// Check if raycasting needs to be updated
		if (!_isRaycastUpdated)
		{
			collision_checkCursorInAny();
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
			// Prepare intersection box
			Vec3 lb, rt;
			lb.x = (entity->getPosition().x - entity->getSize().x / 2.0f);
			lb.y = (entity->getPosition().y);
			lb.z = (entity->getPosition().z + entity->getSize().z / 2.0f);
			rt.x = (entity->getPosition().x + entity->getSize().x / 2.0f);
			rt.y = (entity->getPosition().y + entity->getSize().y);
			rt.z = (entity->getPosition().z - entity->getSize().z / 2.0f);

			// Calculate intersection & distance
			float distance = _core->_rayCaster.checkCursorInBox(lb, rt, _core->_camera.getPosition());
			bool result = (distance != -1.0f);

			// Return
			return make_pair(result, distance);
		}
	}
}

const pair<const string, float> FabiEngine3D::collision_checkCursorInEntities(const string& ID, bool canBeOccluded, const string& exception)
{
	// Check whether the AABB can be raycasted if it's occluded by another AABB
	if (canBeOccluded)
	{
		// Check if raycasting needs to be updated
		if (!_isRaycastUpdated)
		{
			collision_checkCursorInAny();
		}

		// Check if hovered AABB is empty or non-existing
		if (_hoveredAabbID.empty() || !_core->_aabbEntityManager.isExisting(_hoveredAabbID))
		{
			return make_pair("", -1.0f);
		}

		// Check if ID matches (a part of) hovered AABB ID
		if (_hoveredAabbID.size() >= ID.size())
		{
			if (_hoveredAabbID.substr(0, ID.size()) == ID && _hoveredAabbID != exception)
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
					if (entity->getID().substr(0, ID.size()) == ID && entity->getID() != exception) // If entity matches ID
					{
						// Calculate box left bottom (LB) and right top (RT)
						Vec3 lb, rt;
						lb.x = (entity->getPosition().x - entity->getSize().x / 2.0f);
						lb.y = (entity->getPosition().y);
						lb.z = (entity->getPosition().z + entity->getSize().z / 2.0f);
						rt.x = (entity->getPosition().x + entity->getSize().x / 2.0f);
						rt.y = (entity->getPosition().y + entity->getSize().y);
						rt.z = (entity->getPosition().z - entity->getSize().z / 2.0f);

						// Check intersection
						float distance = _core->_rayCaster.checkCursorInBox(lb, rt, _core->_camera.getPosition());

						// Check if closest to camera
						if (distance != -1.0f && distance < closestDistance)
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