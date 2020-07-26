#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::aabbEntity_deleteAll()
{
	_core->_aabbEntityManager.deleteEntities();
}

void FabiEngine3D::aabbEntity_add(const string& ID, vec3 T, vec3 S, bool responsive)
{
	_core->_aabbEntityManager.addAabbEntity(ID, T, vec3(0.0f), S, responsive);
}

void FabiEngine3D::aabbEntity_bindToGameEntity(const string& parentID, vec3 S, bool responsive)
{
	if (_core->_gameEntityManager.isExisting(parentID))
	{
		_core->_aabbEntityManager.bindAabbEntity(parentID, parentID, vec3(0.0f), S, responsive);
		_core->_aabbEntityManager.getEntity(parentID)->setTranslation(_core->_gameEntityManager.getEntity(parentID)->getTranslation());
	}
	else
	{
		logger_throwError("Tried to bind AABB entity to non-existing GAME entity \"" + parentID + "\"!");
	}
}

void FabiEngine3D::aabbEntity_bindToGameEntityGroup(const string& parentID, vec3 S, bool responsive)
{
	bool found = false;

	for (auto entity : _core->_gameEntityManager.getEntities()) // Loop over game entities
	{
		if (entity->getID().size() >= parentID.size()) // Check if entity ID is at least the size of group ID
		{
			if (entity->getID().substr(0, parentID.size()) == parentID) // If entity matches ID
			{
				found = true;
				_core->_aabbEntityManager.bindAabbEntity(entity->getID(), entity->getID(), vec3(0.0f), S, responsive); // Add new box
			}
		}
	}

	if (!found)
	{
		logger_throwError("Tried to bind AABB entities to non-existing GAME entity group \"" + parentID + "\"!");
	}
}

void FabiEngine3D::aabbEntity_delete(const string& ID)
{
	_core->_aabbEntityManager.deleteEntity(ID, EntityType::AABB);
}

void FabiEngine3D::aabbEntity_hide(const string& ID)
{
	_core->_aabbEntityManager.getEntity(ID)->setVisible(false);
}

void FabiEngine3D::aabbEntity_show(const string& ID)
{
	_core->_aabbEntityManager.getEntity(ID)->setVisible(true);
}

void FabiEngine3D::aabbEntity_setResponsiveness(const string& ID, bool responsive)
{
	_core->_aabbEntityManager.getEntity(ID)->setResponsiveness(responsive);
}

void FabiEngine3D::aabbEntity_setGroupResponsiveness(const string& ID, bool responsive)
{
	for (auto entity : _core->_aabbEntityManager.getEntities()) // Loop over aabb entities
	{
		if (entity->getID().size() >= ID.size()) // Check if entity ID is at least the size of group ID
		{
			auto subString = entity->getID().substr(0, ID.size());
			if (subString == ID) // If entity matches ID
			{
				_core->_aabbEntityManager.getEntity(entity->getID())->setResponsiveness(responsive);
			}
		}
	}
}

void FabiEngine3D::aabbEntity_setPosition(const string& ID, vec3 position)
{
	_core->_aabbEntityManager.getEntity(ID)->setTranslation(position);
}

void FabiEngine3D::aabbEntity_setSize(const string& ID, vec3 size)
{
	_core->_aabbEntityManager.getEntity(ID)->setScaling(size);
}

vec3 FabiEngine3D::aabbEntity_getPosition(const string& ID)
{
	return _core->_aabbEntityManager.getEntity(ID)->getTranslation();
}

vec3 FabiEngine3D::aabbEntity_getSize(const string& ID)
{
	return _core->_aabbEntityManager.getEntity(ID)->getScaling();
}

bool FabiEngine3D::aabbEntity_isExisting(const string& ID)
{
	return _core->_aabbEntityManager.isExisting(ID);
}

void FabiEngine3D::collision_enableCameraResponse()
{
	_core->_collisionResolver.enableAabbResponse();
}

void FabiEngine3D::collision_disableCameraResponse()
{
	_core->_collisionResolver.disableAabbResponse();
}

void FabiEngine3D::collision_enableCameraTerrainResponse(float cameraHeight, float cameraSpeed)
{
	_core->_collisionResolver.enableTerrainResponse(cameraHeight, cameraSpeed);
}

void FabiEngine3D::collision_disableCameraTerrainResponse()
{
	_core->_collisionResolver.disableTerrainResponse();
}

void FabiEngine3D::collision_enableFrameRendering()
{
	_core->_shaderBus.setAabbFrameEnabled(true);
}

void FabiEngine3D::collision_disableFrameRendering()
{
	_core->_shaderBus.setAabbFrameEnabled(false);
}

bool FabiEngine3D::collision_checkAnyWithCamera()
{
	for (auto entity : _core->_aabbEntityManager.getEntities()) // Loop over aabb entities
	{
		if (entity->getCollisionDirection() != CollisionDir::NONE)
		{
			return true;
		}
	}

	return false;
}

bool FabiEngine3D::collision_checkEntityCamera(const string& ID)
{
	return _core->_aabbEntityManager.getEntity(ID)->getCollisionDirection() != CollisionDir::NONE;
}

bool FabiEngine3D::collision_isCameraUnderGround()
{
	return _core->_collisionResolver.isCameraUnderGround();
}

bool FabiEngine3D::collision_isCameraAboveGround()
{
	return _core->_collisionResolver.isCameraAboveGround();
}

string FabiEngine3D::collision_checkEntityOthers(const string ID)
{
	for (auto other : _core->_aabbEntityManager.getEntities()) // Loop over aabb entities
	{
		if (other->getID() != ID && other->isResponsive()) // Don't check own entity & must be responsive
		{
			auto self = _core->_aabbEntityManager.getEntity(ID);
			vec3 selfPos = self->getTranslation();
			vec3 selfSize = self->getScaling();
			vec3 otherPos = other->getTranslation();
			vec3 otherSize = other->getScaling();

			// Check XYZ collision between 2 entities
			if
				(
					// Check both all X collision situations
					((selfPos.z > otherPos.z - otherSize.z && selfPos.z < otherPos.z + otherSize.z) || // Middle coordinate within
						(selfPos.z - selfSize.z > otherPos.z - otherSize.z && selfPos.z - selfSize.z < otherPos.z + otherSize.z) || // Lower corner within
						(selfPos.z + selfSize.z > otherPos.z - otherSize.z && selfPos.z + selfSize.z < otherPos.z + otherSize.z) || // Upper corner within 
						(selfPos.z - selfSize.z < otherPos.z - otherSize.z && selfPos.z + selfSize.z > otherPos.z + otherSize.z))   // AABB too big but overlapping 

					&&

					// Check both all Y collision situations
					((selfPos.y > otherPos.y - otherSize.y && selfPos.y < otherPos.y + otherSize.y) || // Middle coordinate within
						(selfPos.y - selfSize.y > otherPos.y - otherSize.y && selfPos.y - selfSize.y < otherPos.y + otherSize.y) || // Lower corner within
						(selfPos.y + selfSize.y > otherPos.y - otherSize.y && selfPos.y + selfSize.y < otherPos.y + otherSize.y) || // Upper corner within 
						(selfPos.y - selfSize.y < otherPos.y - otherSize.y && selfPos.y + selfSize.y > otherPos.y + otherSize.y))   // AABB too big but overlapping 

					&&

					// Check both all Z collision situations
					((selfPos.x > otherPos.x - otherSize.x && selfPos.x < otherPos.x + otherSize.x) || // Middle coordinate within
						(selfPos.x - selfSize.x > otherPos.x - otherSize.x && selfPos.x - selfSize.x < otherPos.x + otherSize.x) || // Lower corner within
						(selfPos.x + selfSize.x > otherPos.x - otherSize.x && selfPos.x + selfSize.x < otherPos.x + otherSize.x) || // Upper corner within 
						(selfPos.x - selfSize.x < otherPos.x - otherSize.x && selfPos.x + selfSize.x > otherPos.x + otherSize.x))   // AABB too big but overlapping 
					)
			{
				return other->getID();
			}
		}
	}

	return "";
}

string FabiEngine3D::collision_checkEntityGroupCamera(const string& ID)
{
	for (auto entity : _core->_aabbEntityManager.getEntities()) // Loop over aabb entities
	{
		if (entity->getID().size() >= ID.size()) // Check if entity ID is at least the size of group ID
		{
			auto subString = entity->getID().substr(0, ID.size());
			if (subString == ID) // If entity matches ID
			{
				auto direction = entity->getCollisionDirection(); // Calculate direction

				// True if collides
				if (direction != CollisionDir::NONE)
				{
					return entity->getID();
				}
			}
		}
	}

	// No collision
	return "";
}

bool FabiEngine3D::collision_checkCursorInEntity(const string& ID)
{
	auto entity = _core->_aabbEntityManager.getEntity(ID);

	vec3 lb, rt;
	lb.x = (entity->getTranslation().x - entity->getScaling().x / 2.0f);
	lb.y = (entity->getTranslation().y);
	lb.z = (entity->getTranslation().z + entity->getScaling().z / 2.0f);
	rt.x = (entity->getTranslation().x + entity->getScaling().x / 2.0f);
	rt.y = (entity->getTranslation().y + entity->getScaling().y);
	rt.z = (entity->getTranslation().z - entity->getScaling().z / 2.0f);

	return _core->_mousePicker.checkCursorInBox(lb, rt, _core->_cameraManager.getPosition()) != -1.0f;
}

string FabiEngine3D::collision_checkCursorInEntityGroup(const string& ID, const string exception)
{
	float closestDistance = (std::numeric_limits<float>::max)();
	string closestBox = "";

	for (auto entity : _core->_aabbEntityManager.getEntities()) // Loop over aabb entities
	{
		if (entity->getID().size() >= ID.size()) // Check if entity ID is at least the size of group ID
		{
			auto subString = entity->getID().substr(0, ID.size());
			if (subString == ID && entity->getID() != exception) // If entity matches ID
			{
				// Calculate box left bottom (LB) and right top (RT)
				vec3 lb, rt;
				lb.x = (entity->getTranslation().x - entity->getScaling().x / 2.0f);
				lb.y = (entity->getTranslation().y);
				lb.z = (entity->getTranslation().z + entity->getScaling().z / 2.0f);
				rt.x = (entity->getTranslation().x + entity->getScaling().x / 2.0f);
				rt.y = (entity->getTranslation().y + entity->getScaling().y);
				rt.z = (entity->getTranslation().z - entity->getScaling().z / 2.0f);

				// Check intersection
				float distance = _core->_mousePicker.checkCursorInBox(lb, rt, _core->_cameraManager.getPosition());

				// Check if closest to camera
				if (distance != -1.0f && distance < closestDistance)
				{
					closestDistance = distance;
					closestBox = entity->getID();
				}
			}
		}
	}

	// No intersection
	return closestBox;
}

ivec3 FabiEngine3D::collision_checkEntityCameraDir(const string& ID)
{
	// Calculate direction
	auto state = _core->_aabbEntityManager.getEntity(ID)->getCollisionDirection();

	// Return collision
	return ivec3(state == CollisionDir::X, state == CollisionDir::Y, state == CollisionDir::Z);
}

ivec3 FabiEngine3D::collision_checkEntityGroupCameraDir(const string& ID)
{
	for (auto entity : _core->_aabbEntityManager.getEntities()) // Loop over aabb entities
	{
		if (entity->getID().size() >= ID.size()) // Check if entity ID is at least the size of group ID
		{
			auto subString = entity->getID().substr(0, ID.size());
			if (subString == ID) // If entity matches ID
			{
				auto direction = entity->getCollisionDirection(); // Calculate direction

				// Return direction if collides
				if (direction != CollisionDir::NONE)
				{
					return ivec3(direction == CollisionDir::X, direction == CollisionDir::Y, direction == CollisionDir::Z);
				}
			}
		}
	}

	// No collision
	return ivec3(0);
}