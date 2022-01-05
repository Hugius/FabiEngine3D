#include "fe3d.hpp"
#include "core.hpp"

void FabiEngine3D::reflection_create(const string& ID)
{
	_core->_reflectionEntityManager->createEntity(ID);
}

void FabiEngine3D::reflection_deleteAll()
{
	_core->_reflectionEntityManager->deleteEntities();
}

void FabiEngine3D::reflection_delete(const string& ID)
{
	_core->_reflectionEntityManager->deleteEntity(ID);
}

void FabiEngine3D::reflection_setVisible(const string& ID, bool value)
{
	_core->_reflectionEntityManager->getEntity(ID)->setVisible(value);
}

void FabiEngine3D::reflection_setPosition(const string& ID, fvec3 value)
{
	_core->_reflectionEntityManager->getEntity(ID)->setPosition(value);
}

void FabiEngine3D::reflection_move(const string& ID, fvec3 change)
{
	_core->_reflectionEntityManager->getEntity(ID)->move(change);
}

void FabiEngine3D::reflection_moveTo(const string& ID, fvec3 target, float speed)
{
	_core->_reflectionEntityManager->getEntity(ID)->moveTo(target, speed);
}

void FabiEngine3D::reflection_capture(const string& ID)
{
	_core->_reflectionEntityManager->getEntity(ID)->capture();
}