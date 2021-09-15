#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"
#include "logger.hpp"

void FabiEngine3D::aabbEntity_create(const string& ID)
{
	_core->_aabbEntityManager.createEntity(ID);
}

void FabiEngine3D::aabbEntity_bindToModelEntity(const string& ID, const string& parentID)
{
	_core->_aabbEntityManager.getEntity(ID)->setParent(parentID, AabbParentType::MODEL_ENTITY);
}

void FabiEngine3D::aabbEntity_bindToBillboardEntity(const string& ID, const string& parentID)
{
	_core->_aabbEntityManager.getEntity(ID)->setParent(parentID, AabbParentType::BILLBOARD_ENTITY);
}

void FabiEngine3D::aabbEntity_deleteAll()
{
	_core->_aabbEntityManager.deleteAllEntities();
}

void FabiEngine3D::aabbEntity_delete(const string& ID)
{
	_core->_aabbEntityManager.deleteEntity(ID);
}

void FabiEngine3D::aabbEntity_setVisible(const string& ID, bool isVisible)
{
	_core->_aabbEntityManager.getEntity(ID)->setVisible(isVisible);
}

void FabiEngine3D::aabbEntity_setRaycastResponsive(const string& ID, bool responsive)
{
	_core->_aabbEntityManager.getEntity(ID)->setRaycastResponsive(responsive);
}

void FabiEngine3D::aabbEntity_setCollisionResponsive(const string& ID, bool responsive)
{
	_core->_aabbEntityManager.getEntity(ID)->setCollisionResponsive(responsive);
}

void FabiEngine3D::aabbEntity_setLocalPosition(const string& ID, Vec3 position)
{
	_core->_aabbEntityManager.getEntity(ID)->setLocalPosition(position);
}

void FabiEngine3D::aabbEntity_setLocalSize(const string& ID, Vec3 size)
{
	_core->_aabbEntityManager.getEntity(ID)->setLocalSize(size);
}

void FabiEngine3D::aabbEntity_setPosition(const string& ID, Vec3 position)
{
	_core->_aabbEntityManager.getEntity(ID)->setPosition(position);
}

void FabiEngine3D::aabbEntity_setSize(const string& ID, Vec3 size)
{
	_core->_aabbEntityManager.getEntity(ID)->setSize(size);
}

void FabiEngine3D::aabbEntity_move(const string& ID, Vec3 change)
{
	_core->_aabbEntityManager.getEntity(ID)->move(change);
}

void FabiEngine3D::aabbEntity_scale(const string& ID, Vec3 change)
{
	_core->_aabbEntityManager.getEntity(ID)->scale(change);
}

void FabiEngine3D::aabbEntity_moveTo(const string& ID, Vec3 target, float speed)
{
	_core->_aabbEntityManager.getEntity(ID)->moveTo(target, speed);
}

void FabiEngine3D::aabbEntity_scaleTo(const string& ID, Vec3 target, float speed)
{
	_core->_aabbEntityManager.getEntity(ID)->scaleTo(target, speed);
}

const Vec3 FabiEngine3D::aabbEntity_getPosition(const string& ID)
{
	if (_core->_aabbEntityManager.getEntity(ID)->hasParent())
	{
		return _core->_aabbEntityManager.getEntity(ID)->getLocalPosition();
	}
	else
	{
		return _core->_aabbEntityManager.getEntity(ID)->getPosition();
	}
}

const Vec3 FabiEngine3D::aabbEntity_getSize(const string& ID)
{
	if (_core->_aabbEntityManager.getEntity(ID)->hasParent())
	{
		return _core->_aabbEntityManager.getEntity(ID)->getLocalSize();
	}
	else
	{
		return _core->_aabbEntityManager.getEntity(ID)->getSize();
	}
}

const bool FabiEngine3D::aabbEntity_isRaycastResponsive(const string& ID)
{
	return _core->_aabbEntityManager.getEntity(ID)->isRaycastResponsive();
}

const bool FabiEngine3D::aabbEntity_isCollisionResponsive(const string& ID)
{
	return _core->_aabbEntityManager.getEntity(ID)->isCollisionResponsive();
}

const bool FabiEngine3D::aabbEntity_isExisting(const string& ID)
{
	return _core->_aabbEntityManager.isExisting(ID);
}

const bool FabiEngine3D::aabbEntity_isVisible(const string& ID)
{
	return _core->_aabbEntityManager.getEntity(ID)->isVisible();
}

const bool FabiEngine3D::aabbEntity_hasParent(const string& ID)
{
	return _core->_aabbEntityManager.getEntity(ID)->hasParent();
}

const vector<string> FabiEngine3D::aabbEntity_getBoundIDs(const string& parentID, bool modelEntity, bool billboardEntity)
{
	vector<string> IDs;

	// Iterate through AABB entities
	for (const auto& [keyID, entity] : _core->_aabbEntityManager.getEntities())
	{
		// Check if AABB has parent
		if (entity->hasParent())
		{
			// Check if parent matches
			if (parentID == entity->getParentID() && (
				(entity->getParentType() == AabbParentType::MODEL_ENTITY && modelEntity) ||
				(entity->getParentType() == AabbParentType::BILLBOARD_ENTITY && billboardEntity)))
			{
				IDs.push_back(entity->getID());
			}
		}
	}

	return IDs;
}

const vector<string> FabiEngine3D::aabbEntity_getAllIDs()
{
	vector<string> IDs;

	for (const auto& [keyID, entity] : _core->_aabbEntityManager.getEntities())
	{
		IDs.push_back(entity->getID());
	}

	return IDs;
}

const string& FabiEngine3D::aabbEntity_getParentID(const string& ID)
{
	return _core->_aabbEntityManager.getEntity(ID)->getParentID();
}

const AabbParentType FabiEngine3D::aabbEntity_getParentType(const string& ID)
{
	return _core->_aabbEntityManager.getEntity(ID)->getParentType();
}