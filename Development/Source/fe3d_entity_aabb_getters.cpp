#include "fe3d.hpp"
#include "core_engine.hpp"

const Vec3 FabiEngine3D::aabbEntity_getPosition(const string& ID)
{
	if(_core->_aabbEntityManager.getEntity(ID)->hasParent())
	{
		return _core->_aabbEntityManager.getEntity(ID)->getLocalPosition();
	}
	else
	{
		return _core->_aabbEntityManager.getEntity(ID)->getPosition();
	}
}

const Vec3 FabiEngine3D::aabbEntity_getSize(const string& ID)
{
	if(_core->_aabbEntityManager.getEntity(ID)->hasParent())
	{
		return _core->_aabbEntityManager.getEntity(ID)->getLocalSize();
	}
	else
	{
		return _core->_aabbEntityManager.getEntity(ID)->getSize();
	}
}

const bool FabiEngine3D::aabbEntity_isRaycastResponsive(const string& ID)
{
	return _core->_aabbEntityManager.getEntity(ID)->isRaycastResponsive();
}

const bool FabiEngine3D::aabbEntity_isCollisionResponsive(const string& ID)
{
	return _core->_aabbEntityManager.getEntity(ID)->isCollisionResponsive();
}

const bool FabiEngine3D::aabbEntity_isExisting(const string& ID)
{
	return _core->_aabbEntityManager.isExisting(ID);
}

const bool FabiEngine3D::aabbEntity_isVisible(const string& ID)
{
	return _core->_aabbEntityManager.getEntity(ID)->isVisible();
}

const bool FabiEngine3D::aabbEntity_hasParent(const string& ID)
{
	return _core->_aabbEntityManager.getEntity(ID)->hasParent();
}

const vector<string> FabiEngine3D::aabbEntity_getChildIDs(const string& parentID, AabbParentType parentType)
{
	vector<string> IDs;

	// Iterate through AABB entities
	for(const auto& [keyID, entity] : _core->_aabbEntityManager.getEntities())
	{
		// Check if AABB has parent
		if(entity->hasParent())
		{
			// Check if parent matches
			if(parentID == entity->getParentID() && (
				(entity->getParentType() == AabbParentType::MODEL_ENTITY && (parentType == AabbParentType::MODEL_ENTITY)) ||
				(entity->getParentType() == AabbParentType::BILLBOARD_ENTITY && (parentType == AabbParentType::BILLBOARD_ENTITY))))
			{
				IDs.push_back(entity->getID());
			}
		}
	}

	return IDs;
}

const vector<string> FabiEngine3D::aabbEntity_getAllIDs()
{
	vector<string> IDs;

	for(const auto& [keyID, entity] : _core->_aabbEntityManager.getEntities())
	{
		IDs.push_back(entity->getID());
	}

	return IDs;
}

const string& FabiEngine3D::aabbEntity_getParentID(const string& ID)
{
	return _core->_aabbEntityManager.getEntity(ID)->getParentID();
}

const AabbParentType FabiEngine3D::aabbEntity_getParentType(const string& ID)
{
	return _core->_aabbEntityManager.getEntity(ID)->getParentType();
}