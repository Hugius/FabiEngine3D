#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::lightEntity_deleteAll()
{
	_core->_lightEntityManager.deleteAllEntities();
}

void FabiEngine3D::lightEntity_add(const string& ID, Vec3 position, Vec3 color, float intensity, float distanceFactor, bool visible)
{
	_core->_lightEntityManager.addLightEntity(ID, position, color, intensity, distanceFactor);
	_core->_lightEntityManager.getEntity(ID)->setVisible(visible);
}

void FabiEngine3D::lightEntity_delete(const string& ID)
{
	_core->_lightEntityManager.deleteEntity(ID);
}

void FabiEngine3D::lightEntity_hide(const string& ID)
{
	_core->_lightEntityManager.getEntity(ID)->setVisible(false);
}

void FabiEngine3D::lightEntity_show(const string& ID)
{
	_core->_lightEntityManager.getEntity(ID)->setVisible(true);
}

bool FabiEngine3D::lightEntity_isExisting(const string& ID)
{
	return _core->_lightEntityManager.isExisting(ID);
}

bool FabiEngine3D::lightEntity_isVisible(const string& ID)
{
	return _core->_lightEntityManager.getEntity(ID)->isVisible();
}

void FabiEngine3D::lightEntity_setPosition(const string& ID, Vec3 position)
{
	_core->_lightEntityManager.getEntity(ID)->setPosition(position);
}

void FabiEngine3D::lightEntity_setColor(const string& ID, Vec3 color)
{
	_core->_lightEntityManager.getEntity(ID)->setColor(color);
}

void FabiEngine3D::lightEntity_setIntensity(const string& ID, float intensity)
{
	_core->_lightEntityManager.getEntity(ID)->setIntensity(intensity);
}

void FabiEngine3D::lightEntity_setDistanceFactor(const string& ID, float factor)
{
	_core->_lightEntityManager.getEntity(ID)->setDistanceFactor(factor);
}

Vec3 FabiEngine3D::lightEntity_getPosition(const string& ID)
{
	return _core->_lightEntityManager.getEntity(ID)->getPosition();
}

Vec3 FabiEngine3D::lightEntity_getColor(const string& ID)
{
	return _core->_lightEntityManager.getEntity(ID)->getColor();
}

float FabiEngine3D::lightEntity_getIntensity(const string& ID)
{
	return _core->_lightEntityManager.getEntity(ID)->getIntensity();
}

float FabiEngine3D::lightEntity_getDistanceFactor(const string& ID)
{
	return _core->_lightEntityManager.getEntity(ID)->getDistanceFactor();
}

vector<string> FabiEngine3D::lightEntity_getAllIDs()
{
	vector<string> IDs;

	for (auto [keyID, entity] : _core->_lightEntityManager.getEntities())
	{
		IDs.push_back(entity->getID());
	}

	return IDs;
}
