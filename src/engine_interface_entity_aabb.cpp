#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::aabb_create(const string& id, bool isCentered)
{
	_core->getAabbEntityManager()->createEntity(id, isCentered);
}

void EngineInterface::aabb_setParentEntityId(const string& id, const string& value)
{
	_core->getAabbEntityManager()->getEntity(id)->setParentEntityId(value);
}

void EngineInterface::aabb_setParentEntityType(const string& id, AabbParentEntityType value)
{
	_core->getAabbEntityManager()->getEntity(id)->setParentEntityType(value);
}

void EngineInterface::aabb_deleteAll()
{
	_core->getAabbEntityManager()->deleteEntities();
}

void EngineInterface::aabb_delete(const string& id)
{
	_core->getAabbEntityManager()->deleteEntity(id);
}

void EngineInterface::aabb_setVisible(const string& id, bool value)
{
	_core->getAabbEntityManager()->getEntity(id)->setVisible(value);
}

void EngineInterface::aabb_setColor(const string& id, const fvec3& value)
{
	_core->getAabbEntityManager()->getEntity(id)->setColor(value);
}

void EngineInterface::aabb_setRaycastResponsive(const string& id, bool value)
{
	_core->getAabbEntityManager()->getEntity(id)->setRaycastResponsive(value);
}

void EngineInterface::aabb_setCollisionResponsive(const string& id, bool value)
{
	_core->getAabbEntityManager()->getEntity(id)->setCollisionResponsive(value);
}

void EngineInterface::aabb_setLocalPosition(const string& id, const fvec3& value)
{
	_core->getAabbEntityManager()->getEntity(id)->setLocalPosition(value);
}

void EngineInterface::aabb_setLocalSize(const string& id, const fvec3& value)
{
	_core->getAabbEntityManager()->getEntity(id)->setLocalSize(value);
}

void EngineInterface::aabb_setBasePosition(const string& id, const fvec3& value)
{
	_core->getAabbEntityManager()->getEntity(id)->setPosition(value);
}

void EngineInterface::aabb_setBaseSize(const string& id, const fvec3& value)
{
	_core->getAabbEntityManager()->getEntity(id)->setSize(value);
}

void EngineInterface::aabb_move(const string& id, const fvec3& change)
{
	_core->getAabbEntityManager()->getEntity(id)->move(change);
}

void EngineInterface::aabb_scale(const string& id, const fvec3& change)
{
	_core->getAabbEntityManager()->getEntity(id)->scale(change);
}

void EngineInterface::aabb_moveTo(const string& id, const fvec3& target, float speed)
{
	_core->getAabbEntityManager()->getEntity(id)->moveTo(target, speed);
}

void EngineInterface::aabb_scaleTo(const string& id, const fvec3& target, float speed)
{
	_core->getAabbEntityManager()->getEntity(id)->scaleTo(target, speed);
}

const fvec3& EngineInterface::aabb_getPosition(const string& id) const
{
	if(_core->getAabbEntityManager()->getEntity(id)->hasParent())
	{
		return _core->getAabbEntityManager()->getEntity(id)->getLocalPosition();
	}
	else
	{
		return _core->getAabbEntityManager()->getEntity(id)->getPosition();
	}
}

const fvec3& EngineInterface::aabb_getSize(const string& id) const
{
	if(_core->getAabbEntityManager()->getEntity(id)->hasParent())
	{
		return _core->getAabbEntityManager()->getEntity(id)->getLocalSize();
	}
	else
	{
		return _core->getAabbEntityManager()->getEntity(id)->getSize();
	}
}

const fvec3& EngineInterface::aabb_getColor(const string& id) const
{
	return _core->getAabbEntityManager()->getEntity(id)->getColor();
}

const bool EngineInterface::aabb_isRaycastResponsive(const string& id) const
{
	return _core->getAabbEntityManager()->getEntity(id)->isRaycastResponsive();
}

const bool EngineInterface::aabb_isCollisionResponsive(const string& id) const
{
	return _core->getAabbEntityManager()->getEntity(id)->isCollisionResponsive();
}

const bool EngineInterface::aabb_isExisting(const string& id) const
{
	return _core->getAabbEntityManager()->isEntityExisting(id);
}

const bool EngineInterface::aabb_isVisible(const string& id) const
{
	return _core->getAabbEntityManager()->getEntity(id)->isVisible();
}

const bool EngineInterface::aabb_hasParent(const string& id) const
{
	return _core->getAabbEntityManager()->getEntity(id)->hasParent();
}

const vector<string> EngineInterface::aabb_getIds() const
{
	vector<string> result;

	for(const auto& [key, entity] : _core->getAabbEntityManager()->getEntities())
	{
		result.push_back(entity->getId());
	}

	return result;
}

const string& EngineInterface::aabb_getParentEntityId(const string& id) const
{
	return _core->getAabbEntityManager()->getEntity(id)->getParentEntityId();
}

const AabbParentEntityType EngineInterface::aabb_getParentEntityType(const string& id) const
{
	return _core->getAabbEntityManager()->getEntity(id)->getParentEntityType();
}