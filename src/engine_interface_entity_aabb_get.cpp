#include "engine_interface.hpp"
#include "engine_core.hpp"

const fvec3 EngineInterface::aabb_getPosition(const string& ID) const
{
	if(_core->getAabbEntityManager()->getEntity(ID)->hasParent())
	{
		return _core->getAabbEntityManager()->getEntity(ID)->getLocalPosition();
	}
	else
	{
		return _core->getAabbEntityManager()->getEntity(ID)->getPosition();
	}
}

const fvec3 EngineInterface::aabb_getSize(const string& ID) const
{
	if(_core->getAabbEntityManager()->getEntity(ID)->hasParent())
	{
		return _core->getAabbEntityManager()->getEntity(ID)->getLocalSize();
	}
	else
	{
		return _core->getAabbEntityManager()->getEntity(ID)->getSize();
	}
}

const fvec3 EngineInterface::aabb_getColor(const string& ID) const
{
	return _core->getAabbEntityManager()->getEntity(ID)->getColor();
}

const bool EngineInterface::aabb_isRaycastResponsive(const string& ID) const
{
	return _core->getAabbEntityManager()->getEntity(ID)->isRaycastResponsive();
}

const bool EngineInterface::aabb_isCollisionResponsive(const string& ID) const
{
	return _core->getAabbEntityManager()->getEntity(ID)->isCollisionResponsive();
}

const bool EngineInterface::aabb_isExisting(const string& ID) const
{
	return _core->getAabbEntityManager()->isEntityExisting(ID);
}

const bool EngineInterface::aabb_isVisible(const string& ID) const
{
	return _core->getAabbEntityManager()->getEntity(ID)->isVisible();
}

const bool EngineInterface::aabb_hasParent(const string& ID) const
{
	return _core->getAabbEntityManager()->getEntity(ID)->hasParent();
}

const vector<string> EngineInterface::aabb_getChildIDs(const string& parentID, AabbParentEntityType parentEntityType) const
{
	vector<string> result;

	for(const auto& [key, entity] : _core->getAabbEntityManager()->getEntities())
	{
		if(entity->hasParent())
		{
			if(parentID == entity->getParentEntityID() && (
				(entity->getParentEntityType() == AabbParentEntityType::MODEL && (parentEntityType == AabbParentEntityType::MODEL)) ||
				(entity->getParentEntityType() == AabbParentEntityType::QUAD3D && (parentEntityType == AabbParentEntityType::QUAD3D))))
			{
				result.push_back(entity->getID());
			}
		}
	}

	return result;
}

const vector<string> EngineInterface::aabb_getIDs() const
{
	vector<string> result;

	for(const auto& [key, entity] : _core->getAabbEntityManager()->getEntities())
	{
		result.push_back(entity->getID());
	}

	return result;
}

const string& EngineInterface::aabb_getParentEntityID(const string& ID) const
{
	return _core->getAabbEntityManager()->getEntity(ID)->getParentEntityID();
}

const AabbParentEntityType EngineInterface::aabb_getParentEntityType(const string& ID) const
{
	return _core->getAabbEntityManager()->getEntity(ID)->getParentEntityType();
}