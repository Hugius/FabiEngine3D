#include "engine_interface.hpp"
#include "engine_core.hpp"

const bool EngineInterface::quad2d_isExisting(const string& ID) const
{
	return _core->getQuad2dEntityManager()->isEntityExisting(ID);
}

const fvec2 EngineInterface::quad2d_getPosition(const string& ID) const
{
	return _core->getQuad2dEntityManager()->getEntity(ID)->getPosition();
}

const float EngineInterface::quad2d_getRotation(const string& ID) const
{
	return _core->getQuad2dEntityManager()->getEntity(ID)->getRotation();
}

const float EngineInterface::quad2d_getTransparency(const string& ID) const
{
	return _core->getQuad2dEntityManager()->getEntity(ID)->getTransparency();
}

const vector<string> EngineInterface::quad2d_getIDs() const
{
	vector<string> result;

	for(const auto& [key, entity] : _core->getQuad2dEntityManager()->getEntities())
	{
		result.push_back(entity->getID());
	}

	return result;
}

const string& EngineInterface::quad2d_getDiffuseMapPath(const string& ID) const
{
	return _core->getQuad2dEntityManager()->getEntity(ID)->getDiffuseMapPath();
}

const fvec3 EngineInterface::quad2d_getWireframeColor(const string& ID) const
{
	return _core->getQuad2dEntityManager()->getEntity(ID)->getWireframeColor();
}

const fvec2 EngineInterface::quad2d_getSize(const string& ID) const
{
	return _core->getQuad2dEntityManager()->getEntity(ID)->getSize();
}

const fvec2 EngineInterface::quad2d_getMinPosition(const string& ID) const
{
	return _core->getQuad2dEntityManager()->getEntity(ID)->getMinPosition();
}

const fvec2 EngineInterface::quad2d_getMaxPosition(const string& ID) const
{
	return _core->getQuad2dEntityManager()->getEntity(ID)->getMaxPosition();
}

const fvec2 EngineInterface::quad2d_getUvMultiplier(const string& ID) const
{
	return _core->getQuad2dEntityManager()->getEntity(ID)->getUvMultiplier();
}

const fvec2 EngineInterface::quad2d_getUvOffset(const string& ID) const
{
	return _core->getQuad2dEntityManager()->getEntity(ID)->getUvOffset();
}

const fvec3 EngineInterface::quad2d_getColor(const string& ID) const
{
	return _core->getQuad2dEntityManager()->getEntity(ID)->getColor();
}

const bool EngineInterface::quad2d_isVisible(const string& ID) const
{
	return _core->getQuad2dEntityManager()->getEntity(ID)->isVisible();
}

const bool EngineInterface::quad2d_isCentered(const string& ID) const
{
	return _core->getQuad2dEntityManager()->getEntity(ID)->isCentered();
}

const bool EngineInterface::quad2d_hasDiffuseMap(const string& ID) const
{
	return _core->getQuad2dEntityManager()->getEntity(ID)->hasDiffuseMap();
}

const bool EngineInterface::quad2d_isWireframed(const string& ID) const
{
	return _core->getQuad2dEntityManager()->getEntity(ID)->isWireframed();
}

const bool EngineInterface::quad2d_isHorizontallyMirrored(const string& ID) const
{
	return _core->getQuad2dEntityManager()->getEntity(ID)->isMirroredHorizonally();
}

const bool EngineInterface::quad2d_isVerticallyMirrored(const string& ID) const
{
	return _core->getQuad2dEntityManager()->getEntity(ID)->isVerticallyMirrored();
}