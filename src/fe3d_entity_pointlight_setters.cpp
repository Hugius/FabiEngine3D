#include "fe3d.hpp"
#include "core_engine.hpp"

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

void FabiEngine3D::pointlight_setVisible(const string& ID, bool isVisible)
{
	_core->_pointlightEntityManager.getEntity(ID)->setVisible(isVisible);
}

void FabiEngine3D::pointlight_setPosition(const string& ID, fvec3 position)
{
	_core->_pointlightEntityManager.getEntity(ID)->setPosition(position);
}

void FabiEngine3D::pointlight_move(const string& ID, fvec3 change)
{
	_core->_pointlightEntityManager.getEntity(ID)->move(change);
}

void FabiEngine3D::pointlight_moveTo(const string& ID, fvec3 target, float speed)
{
	_core->_pointlightEntityManager.getEntity(ID)->moveTo(target, speed);
}

void FabiEngine3D::pointlight_setRadius(const string& ID, fvec3 radius)
{
	_core->_pointlightEntityManager.getEntity(ID)->setRadius(radius);
}

void FabiEngine3D::pointlight_setColor(const string& ID, fvec3 color)
{
	_core->_pointlightEntityManager.getEntity(ID)->setColor(color);
}

void FabiEngine3D::pointlight_setIntensity(const string& ID, float intensity)
{
	_core->_pointlightEntityManager.getEntity(ID)->setIntensity(intensity);
}

void FabiEngine3D::pointlight_setShape(const string& ID, PointlightShape shape)
{
	return _core->_pointlightEntityManager.getEntity(ID)->setShape(shape);
}