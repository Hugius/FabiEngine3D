#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::lightEntity_create(const string& ID)
{
	if (_core->_pointlightEntityManager.getEntities().size() == PointlightEntityManager::MAX_LIGHT_COUNT)
	{
		Logger::throwWarning("Tried to create light entity: maximum reached!");
		return;
	}

	_core->_pointlightEntityManager.createEntity(ID);
}

void FabiEngine3D::lightEntity_deleteAll()
{
	_core->_pointlightEntityManager.deleteAllEntities();
}

void FabiEngine3D::lightEntity_delete(const string& ID)
{
	_core->_pointlightEntityManager.deleteEntity(ID);
}

void FabiEngine3D::lightEntity_setVisible(const string& ID, bool isVisible)
{
	_core->_pointlightEntityManager.getEntity(ID)->setVisible(isVisible);
}

const bool FabiEngine3D::lightEntity_isExisting(const string& ID)
{
	return _core->_pointlightEntityManager.isExisting(ID);
}

const  bool FabiEngine3D::lightEntity_isVisible(const string& ID)
{
	return _core->_pointlightEntityManager.getEntity(ID)->isVisible();
}

const LightShape FabiEngine3D::lightEntity_getShape(const string& ID)
{
	return _core->_pointlightEntityManager.getEntity(ID)->getShape();
}

void FabiEngine3D::lightEntity_setPosition(const string& ID, Vec3 position)
{
	_core->_pointlightEntityManager.getEntity(ID)->setPosition(position);
}

void FabiEngine3D::lightEntity_move(const string& ID, Vec3 change)
{
	_core->_pointlightEntityManager.getEntity(ID)->move(change);
}

void FabiEngine3D::lightEntity_moveTo(const string& ID, Vec3 target, float speed)
{
	_core->_pointlightEntityManager.getEntity(ID)->moveTo(target, speed);
}

void FabiEngine3D::lightEntity_setRadius(const string& ID, Vec3 radius)
{
	_core->_pointlightEntityManager.getEntity(ID)->setRadius(radius);
}

void FabiEngine3D::lightEntity_setColor(const string& ID, Vec3 color)
{
	_core->_pointlightEntityManager.getEntity(ID)->setColor(color);
}

void FabiEngine3D::lightEntity_setIntensity(const string& ID, float intensity)
{
	_core->_pointlightEntityManager.getEntity(ID)->setIntensity(intensity);
}

void FabiEngine3D::lightEntity_setShape(const string& ID, LightShape shape)
{
	return _core->_pointlightEntityManager.getEntity(ID)->setShape(shape);
}

const Vec3 FabiEngine3D::lightEntity_getPosition(const string& ID)
{
	return _core->_pointlightEntityManager.getEntity(ID)->getPosition();
}

const Vec3 FabiEngine3D::lightEntity_getRadius(const string& ID)
{
	return _core->_pointlightEntityManager.getEntity(ID)->getRadius();
}

const Vec3 FabiEngine3D::lightEntity_getColor(const string& ID)
{
	return _core->_pointlightEntityManager.getEntity(ID)->getColor();
}

const float FabiEngine3D::lightEntity_getIntensity(const string& ID)
{
	return _core->_pointlightEntityManager.getEntity(ID)->getIntensity();
}

const vector<string> FabiEngine3D::lightEntity_getAllIDs()
{
	vector<string> IDs;

	for (const auto& [keyID, entity] : _core->_pointlightEntityManager.getEntities())
	{
		IDs.push_back(entity->getID());
	}

	return IDs;
}