#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::aabb_create(const string& ID, bool isCentered)
{
	_core->getAabbEntityManager()->createEntity(ID, isCentered);
}

void EngineInterface::aabb_setParentEntityID(const string& ID, const string& value)
{
	_core->getAabbEntityManager()->getEntity(ID)->setParentEntityID(value);
}

void EngineInterface::aabb_setParentEntityType(const string& ID, AabbParentEntityType value)
{
	_core->getAabbEntityManager()->getEntity(ID)->setParentEntityType(value);
}

void EngineInterface::aabb_deleteAll()
{
	_core->getAabbEntityManager()->deleteEntities();
}

void EngineInterface::aabb_delete(const string& ID)
{
	_core->getAabbEntityManager()->deleteEntity(ID);
}

void EngineInterface::aabb_setVisible(const string& ID, bool value)
{
	_core->getAabbEntityManager()->getEntity(ID)->setVisible(value);
}

void EngineInterface::aabb_setColor(const string& ID, fvec3 value)
{
	_core->getAabbEntityManager()->getEntity(ID)->setColor(value);
}

void EngineInterface::aabb_setRaycastResponsive(const string& ID, bool value)
{
	_core->getAabbEntityManager()->getEntity(ID)->setRaycastResponsive(value);
}

void EngineInterface::aabb_setCollisionResponsive(const string& ID, bool value)
{
	_core->getAabbEntityManager()->getEntity(ID)->setCollisionResponsive(value);
}

void EngineInterface::aabb_setFollowParentTransformation(const string& ID, bool value)
{
	_core->getAabbEntityManager()->getEntity(ID)->setFollowParentEntityTransformation(value);
}

void EngineInterface::aabb_setFollowParentVisibility(const string& ID, bool value)
{
	_core->getAabbEntityManager()->getEntity(ID)->setFollowParentEntityVisibility(value);
}

void EngineInterface::aabb_setLocalPosition(const string& ID, fvec3 value)
{
	_core->getAabbEntityManager()->getEntity(ID)->setLocalPosition(value);
}

void EngineInterface::aabb_setLocalSize(const string& ID, fvec3 value)
{
	_core->getAabbEntityManager()->getEntity(ID)->setLocalSize(value);
}

void EngineInterface::aabb_setBasePosition(const string& ID, fvec3 value)
{
	_core->getAabbEntityManager()->getEntity(ID)->setPosition(value);
}

void EngineInterface::aabb_setBaseSize(const string& ID, fvec3 value)
{
	_core->getAabbEntityManager()->getEntity(ID)->setSize(value);
}

void EngineInterface::aabb_move(const string& ID, fvec3 change)
{
	_core->getAabbEntityManager()->getEntity(ID)->move(change);
}

void EngineInterface::aabb_scale(const string& ID, fvec3 change)
{
	_core->getAabbEntityManager()->getEntity(ID)->scale(change);
}

void EngineInterface::aabb_moveTo(const string& ID, fvec3 target, float speed)
{
	_core->getAabbEntityManager()->getEntity(ID)->moveTo(target, speed);
}

void EngineInterface::aabb_scaleTo(const string& ID, fvec3 target, float speed)
{
	_core->getAabbEntityManager()->getEntity(ID)->scaleTo(target, speed);
}

const fvec3 EngineInterface::aabb_getPosition(const string& ID) const
{
	if(_core->getAabbEntityManager()->getEntity(ID)->hasParent())
	{
		return _core->getAabbEntityManager()->getEntity(ID)->getLocalPosition();
	}
	else
	{
		return _core->getAabbEntityManager()->getEntity(ID)->getPosition();
	}
}

const fvec3 EngineInterface::aabb_getSize(const string& ID) const
{
	if(_core->getAabbEntityManager()->getEntity(ID)->hasParent())
	{
		return _core->getAabbEntityManager()->getEntity(ID)->getLocalSize();
	}
	else
	{
		return _core->getAabbEntityManager()->getEntity(ID)->getSize();
	}
}

const fvec3 EngineInterface::aabb_getColor(const string& ID) const
{
	return _core->getAabbEntityManager()->getEntity(ID)->getColor();
}

const bool EngineInterface::aabb_isRaycastResponsive(const string& ID) const
{
	return _core->getAabbEntityManager()->getEntity(ID)->isRaycastResponsive();
}

const bool EngineInterface::aabb_isCollisionResponsive(const string& ID) const
{
	return _core->getAabbEntityManager()->getEntity(ID)->isCollisionResponsive();
}

const bool EngineInterface::aabb_isExisting(const string& ID) const
{
	return _core->getAabbEntityManager()->isEntityExisting(ID);
}

const bool EngineInterface::aabb_isVisible(const string& ID) const
{
	return _core->getAabbEntityManager()->getEntity(ID)->isVisible();
}

const bool EngineInterface::aabb_hasParent(const string& ID) const
{
	return _core->getAabbEntityManager()->getEntity(ID)->hasParent();
}

const vector<string> EngineInterface::aabb_getChildIDs(const string& parentID, AabbParentEntityType parentEntityType) const
{
	vector<string> result;

	for(const auto& [key, entity] : _core->getAabbEntityManager()->getEntities())
	{
		if(entity->hasParent())
		{
			if(parentID == entity->getParentEntityID() && (
				(entity->getParentEntityType() == AabbParentEntityType::MODEL && (parentEntityType == AabbParentEntityType::MODEL)) ||
				(entity->getParentEntityType() == AabbParentEntityType::QUAD3D && (parentEntityType == AabbParentEntityType::QUAD3D))))
			{
				result.push_back(entity->getID());
			}
		}
	}

	return result;
}

const vector<string> EngineInterface::aabb_getIDs() const
{
	vector<string> result;

	for(const auto& [key, entity] : _core->getAabbEntityManager()->getEntities())
	{
		result.push_back(entity->getID());
	}

	return result;
}

const string& EngineInterface::aabb_getParentEntityID(const string& ID) const
{
	return _core->getAabbEntityManager()->getEntity(ID)->getParentEntityID();
}

const AabbParentEntityType EngineInterface::aabb_getParentEntityType(const string& ID) const
{
	return _core->getAabbEntityManager()->getEntity(ID)->getParentEntityType();
}