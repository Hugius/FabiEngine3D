#include "engine_interface.hpp"
#include "engine_core.hpp"

const float EngineInterface::text3d_getLightness(const string& ID) const
{
	return _core->getText3dEntityManager()->getEntity(ID)->getLightness();
}

const float EngineInterface::text3d_getMinHeight(const string& ID) const
{
	return _core->getText3dEntityManager()->getEntity(ID)->getMinHeight();
}

const float EngineInterface::text3d_getMaxHeight(const string& ID) const
{
	return _core->getText3dEntityManager()->getEntity(ID)->getMaxHeight();
}

const float EngineInterface::text3d_getTransparency(const string& ID) const
{
	return _core->getText3dEntityManager()->getEntity(ID)->getTransparency();
}

const bool EngineInterface::text3d_isExisting(const string& ID) const
{
	return _core->getText3dEntityManager()->isEntityExisting(ID);
}

const bool EngineInterface::text3d_isVisible(const string& ID) const
{
	return _core->getText3dEntityManager()->getEntity(ID)->isVisible();
}

const fvec3 EngineInterface::text3d_getPosition(const string& ID) const
{
	return _core->getText3dEntityManager()->getEntity(ID)->getPosition();
}

const fvec3 EngineInterface::text3d_getRotation(const string& ID) const
{
	return _core->getText3dEntityManager()->getEntity(ID)->getRotation();
}

const fvec2 EngineInterface::text3d_getSize(const string& ID) const
{
	return _core->getText3dEntityManager()->getEntity(ID)->getSize().x;
}

const fvec2 EngineInterface::text3d_getUvMultiplier(const string& ID) const
{
	return _core->getText3dEntityManager()->getEntity(ID)->getUvMultiplier();
}

const fvec2 EngineInterface::text3d_getUvOffset(const string& ID) const
{
	return _core->getText3dEntityManager()->getEntity(ID)->getUvOffset();
}

const fvec3 EngineInterface::text3d_getColor(const string& ID) const
{
	return _core->getText3dEntityManager()->getEntity(ID)->getColor();
}

const fvec3 EngineInterface::text3d_getWireframeColor(const string& ID) const
{
	return _core->getText3dEntityManager()->getEntity(ID)->getWireframeColor();
}

const vector<string> EngineInterface::text3d_getIDs() const
{
	vector<string> result;

	for(const auto& [key, entity] : _core->getText3dEntityManager()->getEntities())
	{
		result.push_back(entity->getID());
	}

	return result;
}

const string& EngineInterface::text3d_getFontMapPath(const string& ID) const
{
	return _core->getText3dEntityManager()->getEntity(ID)->getFontMapPath();
}

const string& EngineInterface::text3d_getContent(const string& ID) const
{
	return _core->getText3dEntityManager()->getEntity(ID)->getContent();
}

const bool EngineInterface::text3d_isFacingCameraX(const string& ID) const
{
	return _core->getText3dEntityManager()->getEntity(ID)->isFacingCameraX();
}

const bool EngineInterface::text3d_isFacingCameraY(const string& ID) const
{
	return _core->getText3dEntityManager()->getEntity(ID)->isFacingCameraY();
}

const bool EngineInterface::text3d_isDepthMapIncluded(const string& ID) const
{
	return _core->getText3dEntityManager()->getEntity(ID)->isDepthMapIncluded();
}

const bool EngineInterface::text3d_isShadowed(const string& ID) const
{
	return _core->getText3dEntityManager()->getEntity(ID)->isShadowed();
}

const bool EngineInterface::text3d_isReflected(const string& ID) const
{
	return _core->getText3dEntityManager()->getEntity(ID)->isReflected();
}

const bool EngineInterface::text3d_isBright(const string& ID) const
{
	return _core->getText3dEntityManager()->getEntity(ID)->isBright();
}

const bool EngineInterface::text3d_isFrozen(const string& ID) const
{
	return _core->getText3dEntityManager()->getEntity(ID)->isFrozen();
}

const bool EngineInterface::text3d_hasFontMap(const string& ID) const
{
	return (_core->getText3dEntityManager()->getEntity(ID)->getFontMap() != nullptr);
}

const bool EngineInterface::text3d_isWireframed(const string& ID) const
{
	return _core->getText3dEntityManager()->getEntity(ID)->isWireframed();
}