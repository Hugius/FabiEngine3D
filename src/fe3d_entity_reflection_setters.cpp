#include "fe3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::reflection_create(const string& ID)
{
	_core->_reflectionEntityManager.createEntity(ID);
}

void FabiEngine3D::reflection_deleteAll()
{
	_core->_reflectionEntityManager.deleteAllEntities();
}

void FabiEngine3D::reflection_delete(const string& ID)
{
	_core->_reflectionEntityManager.deleteEntity(ID);
}

void FabiEngine3D::reflection_setVisible(const string& ID, bool isVisible)
{
	_core->_reflectionEntityManager.getEntity(ID)->setVisible(isVisible);
}

void FabiEngine3D::reflection_setPosition(const string& ID, Vec3 position)
{
	_core->_reflectionEntityManager.getEntity(ID)->setPosition(position);
}

void FabiEngine3D::reflection_move(const string& ID, Vec3 change)
{
	_core->_reflectionEntityManager.getEntity(ID)->move(change);
}

void FabiEngine3D::reflection_moveTo(const string& ID, Vec3 target, float speed)
{
	_core->_reflectionEntityManager.getEntity(ID)->moveTo(target, speed);
}

void FabiEngine3D::reflection_capture(const string& ID)
{
	_core->_reflectionEntityManager.getEntity(ID)->capture();
}