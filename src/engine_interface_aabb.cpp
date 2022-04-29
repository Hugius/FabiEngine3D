#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::aabb_create(const string & aabbId, bool isCentered)
{
	_core->getAabbManager()->createAabb(aabbId, isCentered);
}

void EngineInterface::aabb_setParentId(const string & aabbId, const string & value)
{
	_core->getAabbManager()->getAabb(aabbId)->setParentId(value);
}

void EngineInterface::aabb_setParentType(const string & aabbId, AabbParentType value)
{
	_core->getAabbManager()->getAabb(aabbId)->setParentType(value);
}

void EngineInterface::aabb_delete(const string & aabbId)
{
	_core->getAabbManager()->deleteAabb(aabbId);

	_core->getRaycastIntersector()->resetAabbStatus(aabbId);
}

void EngineInterface::aabb_setVisible(const string & aabbId, bool value)
{
	_core->getAabbManager()->getAabb(aabbId)->setVisible(value);
}

void EngineInterface::aabb_setColor(const string & aabbId, const fvec3 & value)
{
	_core->getAabbManager()->getAabb(aabbId)->setColor(value);
}

void EngineInterface::aabb_setRaycastResponsive(const string & aabbId, bool value)
{
	_core->getAabbManager()->getAabb(aabbId)->setRaycastResponsive(value);

	if(!value)
	{
		_core->getRaycastIntersector()->resetAabbStatus(aabbId);
	}
}

void EngineInterface::aabb_setCollisionResponsive(const string & aabbId, bool value)
{
	_core->getAabbManager()->getAabb(aabbId)->setCollisionResponsive(value);
}

void EngineInterface::aabb_setLocalPosition(const string & aabbId, const fvec3 & value)
{
	_core->getAabbManager()->getAabb(aabbId)->setLocalPosition(value);
}

void EngineInterface::aabb_setLocalSize(const string & aabbId, const fvec3 & value)
{
	_core->getAabbManager()->getAabb(aabbId)->setLocalSize(value);
}

void EngineInterface::aabb_setBasePosition(const string & aabbId, const fvec3 & value)
{
	_core->getAabbManager()->getAabb(aabbId)->setBasePosition(value);
}

void EngineInterface::aabb_setBaseSize(const string & aabbId, const fvec3 & value)
{
	_core->getAabbManager()->getAabb(aabbId)->setBaseSize(value);
}

void EngineInterface::aabb_moveBase(const string & aabbId, const fvec3 & change)
{
	_core->getAabbManager()->getAabb(aabbId)->moveBase(change);
}

void EngineInterface::aabb_scaleBase(const string & aabbId, const fvec3 & change)
{
	_core->getAabbManager()->getAabb(aabbId)->scaleBase(change);
}

void EngineInterface::aabb_moveBaseTo(const string & aabbId, const fvec3 & target, float speed)
{
	_core->getAabbManager()->getAabb(aabbId)->moveBaseTo(target, speed);
}

void EngineInterface::aabb_scaleBaseTo(const string & aabbId, const fvec3 & target, float speed)
{
	_core->getAabbManager()->getAabb(aabbId)->scaleBaseTo(target, speed);
}

void EngineInterface::aabb_moveLocal(const string & aabbId, const fvec3 & change)
{
	_core->getAabbManager()->getAabb(aabbId)->moveLocal(change);
}

void EngineInterface::aabb_scaleLocal(const string & aabbId, const fvec3 & change)
{
	_core->getAabbManager()->getAabb(aabbId)->scaleLocal(change);
}

void EngineInterface::aabb_moveLocalTo(const string & aabbId, const fvec3 & target, float speed)
{
	_core->getAabbManager()->getAabb(aabbId)->moveLocalTo(target, speed);
}

void EngineInterface::aabb_scaleLocalTo(const string & aabbId, const fvec3 & target, float speed)
{
	_core->getAabbManager()->getAabb(aabbId)->scaleLocalTo(target, speed);
}

void EngineInterface::aabb_setMinClipPosition(const string & aabbId, const fvec3 & value)
{
	_core->getAabbManager()->getAabb(aabbId)->setMinClipPosition(value);
}

void EngineInterface::aabb_setMaxClipPosition(const string & aabbId, const fvec3 & value)
{
	_core->getAabbManager()->getAabb(aabbId)->setMaxClipPosition(value);
}

const fvec3 & EngineInterface::aabb_getBasePosition(const string & aabbId) const
{
	return _core->getAabbManager()->getAabb(aabbId)->getBasePosition();
}

const fvec3 & EngineInterface::aabb_getBaseSize(const string & aabbId) const
{
	return _core->getAabbManager()->getAabb(aabbId)->getBaseSize();
}

const fvec3 & EngineInterface::aabb_getLocalPosition(const string & aabbId) const
{
	return _core->getAabbManager()->getAabb(aabbId)->getLocalPosition();
}

const fvec3 & EngineInterface::aabb_getLocalSize(const string & aabbId) const
{
	return _core->getAabbManager()->getAabb(aabbId)->getLocalSize();
}

const fvec3 & EngineInterface::aabb_getColor(const string & aabbId) const
{
	return _core->getAabbManager()->getAabb(aabbId)->getColor();
}

const fvec3 & EngineInterface::aabb_getMinClipPosition(const string & aabbId) const
{
	return _core->getAabbManager()->getAabb(aabbId)->getMinClipPosition();
}

const fvec3 & EngineInterface::aabb_getMaxClipPosition(const string & aabbId) const
{
	return _core->getAabbManager()->getAabb(aabbId)->getMaxClipPosition();
}

const bool EngineInterface::aabb_isRaycastResponsive(const string & aabbId) const
{
	return _core->getAabbManager()->getAabb(aabbId)->isRaycastResponsive();
}

const bool EngineInterface::aabb_isCollisionResponsive(const string & aabbId) const
{
	return _core->getAabbManager()->getAabb(aabbId)->isCollisionResponsive();
}

const bool EngineInterface::aabb_isExisting(const string & aabbId) const
{
	return _core->getAabbManager()->isAabbExisting(aabbId);
}

const bool EngineInterface::aabb_isVisible(const string & aabbId) const
{
	return _core->getAabbManager()->getAabb(aabbId)->isVisible();
}

const bool EngineInterface::aabb_hasParent(const string & aabbId) const
{
	return _core->getAabbManager()->getAabb(aabbId)->hasParent();
}

const vector<string> EngineInterface::aabb_getIds() const
{
	vector<string> result;

	for(const auto & [aabbId, aabb] : _core->getAabbManager()->getAabbs())
	{
		result.push_back(aabb->getId());
	}

	return result;
}

const string & EngineInterface::aabb_getParentId(const string & aabbId) const
{
	return _core->getAabbManager()->getAabb(aabbId)->getParentId();
}

const AabbParentType EngineInterface::aabb_getParentType(const string & aabbId) const
{
	return _core->getAabbManager()->getAabb(aabbId)->getParentType();
}