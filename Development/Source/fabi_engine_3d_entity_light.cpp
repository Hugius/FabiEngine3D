#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::lightEntity_deleteAll()
{
	_core->_lightEntityManager.deleteEntities();
}

void FabiEngine3D::lightEntity_add(const string& ID, vec3 position, vec3 color, float strength)
{
	_core->_lightEntityManager.addLightEntity(ID, position, color, strength);
}

void FabiEngine3D::lightEntity_delete(const string& ID)
{
	_core->_lightEntityManager.deleteEntity(ID, EntityType::LIGHT);
}

void FabiEngine3D::lightEntity_hide(const string& ID)
{
	_core->_lightEntityManager.getEntity(ID)->setEnabled(false);
}

void FabiEngine3D::lightEntity_show(const string& ID)
{
	_core->_lightEntityManager.getEntity(ID)->setEnabled(true);
}

bool FabiEngine3D::lightEntity_isExisting(const string& ID)
{
	return _core->_lightEntityManager.isExisting(ID);
}

void FabiEngine3D::lightEntity_setPosition(const string& ID, vec3 position)
{
	_core->_lightEntityManager.getEntity(ID)->setPosition(position);
}

void FabiEngine3D::lightEntity_setColor(const string& ID, vec3 color)
{
	_core->_lightEntityManager.getEntity(ID)->setColor(color);
}

void FabiEngine3D::lightEntity_setStrength(const string& ID, float strength)
{
	_core->_lightEntityManager.getEntity(ID)->setStrength(strength);
}