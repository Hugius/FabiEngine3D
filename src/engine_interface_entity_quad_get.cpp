#include "engine_interface.hpp"
#include "engine_core.hpp"

const bool EngineInterface::quad_isExisting(const string& ID) const
{
	return _core->getQuadEntityManager()->isEntityExisting(ID);
}

const fvec2 EngineInterface::quad_getPosition(const string& ID) const
{
	return _core->getQuadEntityManager()->getEntity(ID)->getPosition();
}

const float EngineInterface::quad_getRotation(const string& ID) const
{
	return _core->getQuadEntityManager()->getEntity(ID)->getRotation();
}

const float EngineInterface::quad_getTransparency(const string& ID) const
{
	return _core->getQuadEntityManager()->getEntity(ID)->getTransparency();
}

const vector<string> EngineInterface::quad_getIDs() const
{
	vector<string> result;

	for(const auto& [key, entity] : _core->getQuadEntityManager()->getEntities())
	{
		result.push_back(entity->getID());
	}

	return result;
}

const string& EngineInterface::quad_getDiffuseMapPath(const string& ID) const
{
	return _core->getQuadEntityManager()->getEntity(ID)->getDiffuseMapPath();
}

const fvec3 EngineInterface::quad_getWireframeColor(const string& ID) const
{
	return _core->getQuadEntityManager()->getEntity(ID)->getWireframeColor();
}

const fvec2 EngineInterface::quad_getSize(const string& ID) const
{
	return _core->getQuadEntityManager()->getEntity(ID)->getSize();
}

const fvec2 EngineInterface::quad_getMinPosition(const string& ID) const
{
	return _core->getQuadEntityManager()->getEntity(ID)->getMinPosition();
}

const fvec2 EngineInterface::quad_getMaxPosition(const string& ID) const
{
	return _core->getQuadEntityManager()->getEntity(ID)->getMaxPosition();
}

const fvec2 EngineInterface::quad_getUvMultiplier(const string& ID) const
{
	return _core->getQuadEntityManager()->getEntity(ID)->getUvMultiplier();
}

const fvec2 EngineInterface::quad_getUvOffset(const string& ID) const
{
	return _core->getQuadEntityManager()->getEntity(ID)->getUvOffset();
}

const fvec3 EngineInterface::quad_getColor(const string& ID) const
{
	return _core->getQuadEntityManager()->getEntity(ID)->getColor();
}

const bool EngineInterface::quad_isVisible(const string& ID) const
{
	return _core->getQuadEntityManager()->getEntity(ID)->isVisible();
}

const bool EngineInterface::quad_isCentered(const string& ID) const
{
	return _core->getQuadEntityManager()->getEntity(ID)->isCentered();
}

const bool EngineInterface::quad_hasDiffuseMap(const string& ID) const
{
	return _core->getQuadEntityManager()->getEntity(ID)->hasDiffuseMap();
}

const bool EngineInterface::quad_isWireframed(const string& ID) const
{
	return _core->getQuadEntityManager()->getEntity(ID)->isWireframed();
}

const bool EngineInterface::quad_isMirroredHorizontally(const string& ID) const
{
	return _core->getQuadEntityManager()->getEntity(ID)->isMirroredHorizonally();
}

const bool EngineInterface::quad_isMirroredVertically(const string& ID) const
{
	return _core->getQuadEntityManager()->getEntity(ID)->isMirroredVertically();
}