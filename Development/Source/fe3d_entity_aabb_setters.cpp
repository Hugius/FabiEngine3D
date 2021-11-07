#include "fe3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::aabbEntity_create(const string& ID)
{
	_core->_aabbEntityManager.createEntity(ID);
}

void FabiEngine3D::aabbEntity_setParent(const string& ID, const string& parentID, AabbParentType parentType)
{
	_core->_aabbEntityManager.getEntity(ID)->setParent(parentID, parentType);
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

void FabiEngine3D::aabbEntity_setFollowParentTransformation(const string& ID, bool mustFollow)
{
	_core->_aabbEntityManager.getEntity(ID)->setFollowParentTransformation(mustFollow);
}

void FabiEngine3D::aabbEntity_setFollowParentVisibility(const string& ID, bool mustFollow)
{
	_core->_aabbEntityManager.getEntity(ID)->setFollowParentVisibility(mustFollow);
}

void FabiEngine3D::aabbEntity_setLocalPosition(const string& ID, Vec3 position)
{
	_core->_aabbEntityManager.getEntity(ID)->setLocalPosition(position);
}

void FabiEngine3D::aabbEntity_setLocalSize(const string& ID, Vec3 size)
{
	_core->_aabbEntityManager.getEntity(ID)->setLocalSize(size);
}

void FabiEngine3D::aabbEntity_setBasePosition(const string& ID, Vec3 position)
{
	_core->_aabbEntityManager.getEntity(ID)->setPosition(position);
}

void FabiEngine3D::aabbEntity_setBaseSize(const string& ID, Vec3 size)
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