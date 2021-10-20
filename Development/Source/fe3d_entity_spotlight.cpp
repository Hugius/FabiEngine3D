#include "fe3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::spotlightEntity_create(const string& ID)
{
	if (_core->_spotlightEntityManager.getEntities().size() == SpotlightEntityManager::MAX_LIGHT_COUNT)
	{
		Logger::throwWarning("Tried to create spotlight entity: maximum reached!");
		return;
	}

	_core->_spotlightEntityManager.createEntity(ID);
}

void FabiEngine3D::spotlightEntity_deleteAll()
{
	_core->_spotlightEntityManager.deleteAllEntities();
}

void FabiEngine3D::spotlightEntity_delete(const string& ID)
{
	_core->_spotlightEntityManager.deleteEntity(ID);
}

void FabiEngine3D::spotlightEntity_setVisible(const string& ID, bool isVisible)
{
	_core->_spotlightEntityManager.getEntity(ID)->setVisible(isVisible);
}

void FabiEngine3D::spotlightEntity_setPosition(const string& ID, Vec3 position)
{
	_core->_spotlightEntityManager.getEntity(ID)->setPosition(position);
}

void FabiEngine3D::spotlightEntity_move(const string& ID, Vec3 change)
{
	_core->_spotlightEntityManager.getEntity(ID)->move(change);
}

void FabiEngine3D::spotlightEntity_moveTo(const string& ID, Vec3 target, float speed)
{
	_core->_spotlightEntityManager.getEntity(ID)->moveTo(target, speed);
}

void FabiEngine3D::spotlightEntity_setFront(const string& ID, Vec3 front)
{
	_core->_spotlightEntityManager.getEntity(ID)->setFront(front);
}

void FabiEngine3D::spotlightEntity_setColor(const string& ID, Vec3 color)
{
	_core->_spotlightEntityManager.getEntity(ID)->setColor(color);
}

void FabiEngine3D::spotlightEntity_setIntensity(const string& ID, float intensity)
{
	_core->_spotlightEntityManager.getEntity(ID)->setIntensity(intensity);
}

void FabiEngine3D::spotlightEntity_setAngle(const string& ID, float angle)
{
	_core->_spotlightEntityManager.getEntity(ID)->setAngle(angle);
}

void FabiEngine3D::spotlightEntity_setDistance(const string& ID, float distance)
{
	_core->_spotlightEntityManager.getEntity(ID)->setDistance(distance);
}

const vector<string> FabiEngine3D::spotlightEntity_getAllIDs()
{
	vector<string> IDs;

	for (const auto& [keyID, entity] : _core->_spotlightEntityManager.getEntities())
	{
		IDs.push_back(entity->getID());
	}

	return IDs;
}

const Vec3 FabiEngine3D::spotlightEntity_getPosition(const string& ID)
{
	return _core->_spotlightEntityManager.getEntity(ID)->getPosition();
}

const Vec3 FabiEngine3D::spotlightEntity_getFront(const string& ID)
{
	return _core->_spotlightEntityManager.getEntity(ID)->getFront();
}

const Vec3 FabiEngine3D::spotlightEntity_getColor(const string& ID)
{
	return _core->_spotlightEntityManager.getEntity(ID)->getColor();
}

const float FabiEngine3D::spotlightEntity_getIntensity(const string& ID)
{
	return _core->_spotlightEntityManager.getEntity(ID)->getIntensity();
}

const float FabiEngine3D::spotlightEntity_getAngle(const string& ID)
{
	return _core->_spotlightEntityManager.getEntity(ID)->getAngle();
}

const float FabiEngine3D::spotlightEntity_getDistance(const string& ID)
{
	return _core->_spotlightEntityManager.getEntity(ID)->getDistance();
}

const bool FabiEngine3D::spotlightEntity_isExisting(const string& ID)
{
	return _core->_spotlightEntityManager.isExisting(ID);
}

const bool FabiEngine3D::spotlightEntity_isVisible(const string& ID)
{
	return _core->_spotlightEntityManager.getEntity(ID)->isVisible();
}