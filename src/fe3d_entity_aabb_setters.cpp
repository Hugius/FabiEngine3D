#include "fe3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::aabb_create(const string& ID)
{
	_core->_aabbEntityManager.createEntity(ID);
}

void FabiEngine3D::aabb_setParentEntityID(const string& ID, const string& value)
{
	_core->_aabbEntityManager.getEntity(ID)->setParentEntityID(value);
}

void FabiEngine3D::aabb_setParentEntityType(const string& ID, AabbParentEntityType value)
{
	_core->_aabbEntityManager.getEntity(ID)->setParentEntityType(value);
}

void FabiEngine3D::aabb_deleteAll()
{
	_core->_aabbEntityManager.deleteAllEntities();
}

void FabiEngine3D::aabb_delete(const string& ID)
{
	_core->_aabbEntityManager.deleteEntity(ID);
}

void FabiEngine3D::aabb_setVisible(const string& ID, bool value)
{
	_core->_aabbEntityManager.getEntity(ID)->setVisible(value);
}

void FabiEngine3D::aabb_setColor(const string& ID, fvec3 value)
{
	_core->_aabbEntityManager.getEntity(ID)->setColor(value);
}

void FabiEngine3D::aabb_setRaycastResponsive(const string& ID, bool value)
{
	_core->_aabbEntityManager.getEntity(ID)->setRaycastResponsive(value);
}

void FabiEngine3D::aabb_setCollisionResponsive(const string& ID, bool value)
{
	_core->_aabbEntityManager.getEntity(ID)->setCollisionResponsive(value);
}

void FabiEngine3D::aabb_setFollowParentTransformation(const string& ID, bool value)
{
	_core->_aabbEntityManager.getEntity(ID)->setFollowParentEntityTransformation(value);
}

void FabiEngine3D::aabb_setFollowParentVisibility(const string& ID, bool value)
{
	_core->_aabbEntityManager.getEntity(ID)->setFollowParentEntityVisibility(value);
}

void FabiEngine3D::aabb_setLocalPosition(const string& ID, fvec3 value)
{
	_core->_aabbEntityManager.getEntity(ID)->setLocalPosition(value);
}

void FabiEngine3D::aabb_setLocalSize(const string& ID, fvec3 value)
{
	_core->_aabbEntityManager.getEntity(ID)->setLocalSize(value);
}

void FabiEngine3D::aabb_setBasePosition(const string& ID, fvec3 value)
{
	_core->_aabbEntityManager.getEntity(ID)->setPosition(value);
}

void FabiEngine3D::aabb_setBaseSize(const string& ID, fvec3 value)
{
	_core->_aabbEntityManager.getEntity(ID)->setSize(value);
}

void FabiEngine3D::aabb_move(const string& ID, fvec3 change)
{
	_core->_aabbEntityManager.getEntity(ID)->move(change);
}

void FabiEngine3D::aabb_scale(const string& ID, fvec3 change)
{
	_core->_aabbEntityManager.getEntity(ID)->scale(change);
}

void FabiEngine3D::aabb_moveTo(const string& ID, fvec3 target, float speed)
{
	_core->_aabbEntityManager.getEntity(ID)->moveTo(target, speed);
}

void FabiEngine3D::aabb_scaleTo(const string& ID, fvec3 target, float speed)
{
	_core->_aabbEntityManager.getEntity(ID)->scaleTo(target, speed);
}