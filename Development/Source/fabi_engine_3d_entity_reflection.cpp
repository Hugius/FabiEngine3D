#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::reflectionEntity_create(const string& ID)
{
	_core->_reflectionEntityManager.createEntity(ID);
}

void FabiEngine3D::reflectionEntity_deleteAll()
{
	_core->_reflectionEntityManager.deleteAllEntities();
}

void FabiEngine3D::reflectionEntity_delete(const string& ID)
{
	_core->_reflectionEntityManager.deleteEntity(ID);
}

void FabiEngine3D::reflectionEntity_setPosition(const string& ID, Vec3 position)
{
	_core->_reflectionEntityManager.getEntity(ID)->setPosition(position);
}

void FabiEngine3D::reflectionEntity_move(const string& ID, Vec3 factor)
{
	_core->_reflectionEntityManager.getEntity(ID)->move(factor);
}

const vector<string> FabiEngine3D::reflectionEntity_getAllIDs()
{
	vector<string> IDs;

	for (const auto& [keyID, entity] : _core->_reflectionEntityManager.getEntities())
	{
		IDs.push_back(entity->getID());
	}

	return IDs;
}

const Vec3 FabiEngine3D::reflectionEntity_getPosition(const string& ID)
{
	return _core->_reflectionEntityManager.getEntity(ID)->getPosition();
}

const bool FabiEngine3D::reflectionEntity_isExisting(const string& ID)
{
	return _core->_reflectionEntityManager.isExisting(ID);
}