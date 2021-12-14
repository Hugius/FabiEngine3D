#include "fe3d.hpp"
#include "core.hpp"

void FabiEngine3D::pointlight_create(const string& ID)
{
	if(_core->_pointlightEntityManager.getEntities().size() == PointlightEntityManager::MAX_LIGHT_COUNT)
	{
		Logger::throwWarning("Tried to create pointlight entity: maximum reached!");
		return;
	}

	_core->_pointlightEntityManager.createEntity(ID);
}

void FabiEngine3D::pointlight_deleteAll()
{
	_core->_pointlightEntityManager.deleteAllEntities();
}

void FabiEngine3D::pointlight_delete(const string& ID)
{
	_core->_pointlightEntityManager.deleteEntity(ID);
}

void FabiEngine3D::pointlight_setVisible(const string& ID, bool value)
{
	_core->_pointlightEntityManager.getEntity(ID)->setVisible(value);
}

void FabiEngine3D::pointlight_setPosition(const string& ID, fvec3 value)
{
	_core->_pointlightEntityManager.getEntity(ID)->setPosition(value);
}

void FabiEngine3D::pointlight_move(const string& ID, fvec3 change)
{
	_core->_pointlightEntityManager.getEntity(ID)->move(change);
}

void FabiEngine3D::pointlight_moveTo(const string& ID, fvec3 target, float speed)
{
	_core->_pointlightEntityManager.getEntity(ID)->moveTo(target, speed);
}

void FabiEngine3D::pointlight_setRadius(const string& ID, fvec3 value)
{
	_core->_pointlightEntityManager.getEntity(ID)->setRadius(value);
}

void FabiEngine3D::pointlight_setColor(const string& ID, fvec3 value)
{
	_core->_pointlightEntityManager.getEntity(ID)->setColor(value);
}

void FabiEngine3D::pointlight_setIntensity(const string& ID, float value)
{
	_core->_pointlightEntityManager.getEntity(ID)->setIntensity(value);
}

void FabiEngine3D::pointlight_setShape(const string& ID, PointlightShape value)
{
	return _core->_pointlightEntityManager.getEntity(ID)->setShape(value);
}