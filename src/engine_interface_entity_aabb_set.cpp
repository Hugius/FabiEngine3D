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