#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::lightEntity_deleteAll()
{
	_core->_lightEntityManager.deleteAllEntities();
}

void FabiEngine3D::lightEntity_create(const string& ID)
{
	_core->_lightEntityManager.createEntity(ID);
}

void FabiEngine3D::lightEntity_delete(const string& ID)
{
	_core->_lightEntityManager.deleteEntity(ID);
}

void FabiEngine3D::lightEntity_setVisible(const string& ID, bool isVisible)
{
	_core->_lightEntityManager.getEntity(ID)->setVisible(isVisible);
}

const bool FabiEngine3D::lightEntity_isExisting(const string& ID)
{
	return _core->_lightEntityManager.isExisting(ID);
}

const  bool FabiEngine3D::lightEntity_isVisible(const string& ID)
{
	return _core->_lightEntityManager.getEntity(ID)->isVisible();
}

const LightShape FabiEngine3D::lightEntity_getShape(const string& ID)
{
	return _core->_lightEntityManager.getEntity(ID)->getShape();
}

void FabiEngine3D::lightEntity_setPosition(const string& ID, Vec3 position)
{
	_core->_lightEntityManager.getEntity(ID)->setPosition(position);
}

void FabiEngine3D::lightEntity_move(const string& ID, Vec3 factor)
{
	_core->_lightEntityManager.getEntity(ID)->move(factor);
}

void FabiEngine3D::lightEntity_setRadius(const string& ID, Vec3 radius)
{
	_core->_lightEntityManager.getEntity(ID)->setRadius(radius);
}

void FabiEngine3D::lightEntity_setColor(const string& ID, Vec3 color)
{
	_core->_lightEntityManager.getEntity(ID)->setColor(color);
}

void FabiEngine3D::lightEntity_setIntensity(const string& ID, float intensity)
{
	_core->_lightEntityManager.getEntity(ID)->setIntensity(intensity);
}

void FabiEngine3D::lightEntity_setShape(const string& ID, LightShape shape)
{
	return _core->_lightEntityManager.getEntity(ID)->setShape(shape);
}

const Vec3 FabiEngine3D::lightEntity_getPosition(const string& ID)
{
	return _core->_lightEntityManager.getEntity(ID)->getPosition();
}

const Vec3 FabiEngine3D::lightEntity_getRadius(const string& ID)
{
	return _core->_lightEntityManager.getEntity(ID)->getRadius();
}

const Vec3 FabiEngine3D::lightEntity_getColor(const string& ID)
{
	return _core->_lightEntityManager.getEntity(ID)->getColor();
}

const float FabiEngine3D::lightEntity_getIntensity(const string& ID)
{
	return _core->_lightEntityManager.getEntity(ID)->getIntensity();
}

const vector<string> FabiEngine3D::lightEntity_getAllIDs()
{
	vector<string> IDs;

	for (const auto& [keyID, entity] : _core->_lightEntityManager.getEntities())
	{
		IDs.push_back(entity->getID());
	}

	return IDs;
}
