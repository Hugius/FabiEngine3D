#include "fe3d.hpp"
#include "core_engine.hpp"

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
	_core->_spotlightEntityManager.deleteAllEntities();
}

void FabiEngine3D::spotlight_delete(const string& ID)
{
	_core->_spotlightEntityManager.deleteEntity(ID);
}

void FabiEngine3D::spotlight_setVisible(const string& ID, bool isVisible)
{
	_core->_spotlightEntityManager.getEntity(ID)->setVisible(isVisible);
}

void FabiEngine3D::spotlight_setPosition(const string& ID, fvec3 position)
{
	_core->_spotlightEntityManager.getEntity(ID)->setPosition(position);
}

void FabiEngine3D::spotlight_move(const string& ID, fvec3 change)
{
	_core->_spotlightEntityManager.getEntity(ID)->move(change);
}

void FabiEngine3D::spotlight_moveTo(const string& ID, fvec3 target, float speed)
{
	_core->_spotlightEntityManager.getEntity(ID)->moveTo(target, speed);
}

void FabiEngine3D::spotlight_setColor(const string& ID, fvec3 color)
{
	_core->_spotlightEntityManager.getEntity(ID)->setColor(color);
}

void FabiEngine3D::spotlight_setYaw(const string& ID, float yaw)
{
	_core->_spotlightEntityManager.getEntity(ID)->setYaw(yaw);
}

void FabiEngine3D::spotlight_setPitch(const string& ID, float pitch)
{
	_core->_spotlightEntityManager.getEntity(ID)->setPitch(pitch);
}

void FabiEngine3D::spotlight_setIntensity(const string& ID, float intensity)
{
	_core->_spotlightEntityManager.getEntity(ID)->setIntensity(intensity);
}

void FabiEngine3D::spotlight_setAngle(const string& ID, float angle)
{
	_core->_spotlightEntityManager.getEntity(ID)->setAngle(angle);
}

void FabiEngine3D::spotlight_setDistance(const string& ID, float distance)
{
	_core->_spotlightEntityManager.getEntity(ID)->setDistance(distance);
}