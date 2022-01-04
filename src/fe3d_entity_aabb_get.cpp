#include "fe3d.hpp"
#include "core.hpp"

const fvec3 FabiEngine3D::aabb_getPosition(const string& ID) const
{
	if (_core->_aabbEntityManager.getEntity(ID)->hasParent())
	{
		return _core->_aabbEntityManager.getEntity(ID)->getLocalPosition();
	}
	else
	{
		return _core->_aabbEntityManager.getEntity(ID)->getPosition();
	}
}

const fvec3 FabiEngine3D::aabb_getSize(const string& ID) const
{
	if (_core->_aabbEntityManager.getEntity(ID)->hasParent())
	{
		return _core->_aabbEntityManager.getEntity(ID)->getLocalSize();
	}
	else
	{
		return _core->_aabbEntityManager.getEntity(ID)->getSize();
	}
}

const fvec3 FabiEngine3D::aabb_getColor(const string& ID) const
{
	return _core->_aabbEntityManager.getEntity(ID)->getColor();
}

const bool FabiEngine3D::aabb_isRaycastResponsive(const string& ID) const
{
	return _core->_aabbEntityManager.getEntity(ID)->isRaycastResponsive();
}

const bool FabiEngine3D::aabb_isCollisionResponsive(const string& ID) const
{
	return _core->_aabbEntityManager.getEntity(ID)->isCollisionResponsive();
}

const bool FabiEngine3D::aabb_isExisting(const string& ID) const
{
	return _core->_aabbEntityManager.isEntityExisting(ID);
}

const bool FabiEngine3D::aabb_isVisible(const string& ID) const
{
	return _core->_aabbEntityManager.getEntity(ID)->isVisible();
}

const bool FabiEngine3D::aabb_hasParent(const string& ID) const
{
	return _core->_aabbEntityManager.getEntity(ID)->hasParent();
}

const vector<string> FabiEngine3D::aabb_getChildIDs(const string& parentID, AabbParentEntityType parentEntityType) const
{
	vector<string> result;

	for (const auto& [key, entity] : _core->_aabbEntityManager.getEntities())
	{
		if (entity->hasParent())
		{
			if (parentID == entity->getParentEntityID() && (
				(entity->getParentEntityType() == AabbParentEntityType::MODEL && (parentEntityType == AabbParentEntityType::MODEL)) ||
				(entity->getParentEntityType() == AabbParentEntityType::BILLBOARD && (parentEntityType == AabbParentEntityType::BILLBOARD))))
			{
				result.push_back(entity->getID());
			}
		}
	}

	return result;
}

const vector<string> FabiEngine3D::aabb_getIDs() const
{
	vector<string> result;

	for (const auto& [key, entity] : _core->_aabbEntityManager.getEntities())
	{
		result.push_back(entity->getID());
	}

	return result;
}

const string& FabiEngine3D::aabb_getParentEntityID(const string& ID) const
{
	return _core->_aabbEntityManager.getEntity(ID)->getParentEntityID();
}

const AabbParentEntityType FabiEngine3D::aabb_getParentEntityType(const string& ID) const
{
	return _core->_aabbEntityManager.getEntity(ID)->getParentEntityType();
}