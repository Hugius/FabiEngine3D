#include "fe3d.hpp"
#include "core.hpp"

void FabiEngine3D::spotlight_create(const string& ID)
{
	if(_core->_spotlightEntityManager.getEntities().size() == SpotlightEntityManager::MAX_LIGHT_COUNT)
	{
		Logger::throwWarning("Tried to create spotlight entity: maximum reached!");
		return;
	}

	_core->_spotlightEntityManager.createEntity(ID);
}

void FabiEngine3D::spotlight_deleteAll()
{
	_core->_spotlightEntityManager.deleteEntities();
}

void FabiEngine3D::spotlight_delete(const string& ID)
{
	_core->_spotlightEntityManager.deleteEntity(ID);
}

void FabiEngine3D::spotlight_setVisible(const string& ID, bool value)
{
	_core->_spotlightEntityManager.getEntity(ID)->setVisible(value);
}

void FabiEngine3D::spotlight_setPosition(const string& ID, fvec3 value)
{
	_core->_spotlightEntityManager.getEntity(ID)->setPosition(value);
}

void FabiEngine3D::spotlight_move(const string& ID, fvec3 change)
{
	_core->_spotlightEntityManager.getEntity(ID)->move(change);
}

void FabiEngine3D::spotlight_moveTo(const string& ID, fvec3 target, float speed)
{
	_core->_spotlightEntityManager.getEntity(ID)->moveTo(target, speed);
}

void FabiEngine3D::spotlight_setColor(const string& ID, fvec3 value)
{
	_core->_spotlightEntityManager.getEntity(ID)->setColor(value);
}

void FabiEngine3D::spotlight_setYaw(const string& ID, float value)
{
	_core->_spotlightEntityManager.getEntity(ID)->setYaw(value);
}

void FabiEngine3D::spotlight_setPitch(const string& ID, float value)
{
	_core->_spotlightEntityManager.getEntity(ID)->setPitch(value);
}

void FabiEngine3D::spotlight_setIntensity(const string& ID, float value)
{
	_core->_spotlightEntityManager.getEntity(ID)->setIntensity(value);
}

void FabiEngine3D::spotlight_setAngle(const string& ID, float value)
{
	_core->_spotlightEntityManager.getEntity(ID)->setAngle(value);
}

void FabiEngine3D::spotlight_setDistance(const string& ID, float value)
{
	_core->_spotlightEntityManager.getEntity(ID)->setDistance(value);
}