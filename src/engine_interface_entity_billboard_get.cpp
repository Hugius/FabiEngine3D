#include "engine_interface.hpp"
#include "engine_core.hpp"

const float EngineInterface::billboard_getLightness(const string& ID) const
{
	return _core->getBillboardEntityManager()->getEntity(ID)->getLightness();
}

const float EngineInterface::billboard_getMinHeight(const string& ID) const
{
	return _core->getBillboardEntityManager()->getEntity(ID)->getMinHeight();
}

const float EngineInterface::billboard_getMaxHeight(const string& ID) const
{
	return _core->getBillboardEntityManager()->getEntity(ID)->getMaxHeight();
}

const float EngineInterface::billboard_getTransparency(const string& ID) const
{
	return _core->getBillboardEntityManager()->getEntity(ID)->getTransparency();
}

const float EngineInterface::billboard_getTextureRepeat(const string& ID) const
{
	return _core->getBillboardEntityManager()->getEntity(ID)->getTextureRepeat();
}

const float EngineInterface::billboard_getEmissionIntensity(const string& ID) const
{
	return _core->getBillboardEntityManager()->getEntity(ID)->getEmissionIntensity();
}

const bool EngineInterface::billboard_isExisting(const string& ID) const
{
	return _core->getBillboardEntityManager()->isEntityExisting(ID);
}

const bool EngineInterface::billboard_isVisible(const string& ID) const
{
	return _core->getBillboardEntityManager()->getEntity(ID)->isVisible();
}

const fvec3 EngineInterface::billboard_getPosition(const string& ID) const
{
	return _core->getBillboardEntityManager()->getEntity(ID)->getPosition();
}

const fvec3 EngineInterface::billboard_getRotation(const string& ID) const
{
	return _core->getBillboardEntityManager()->getEntity(ID)->getRotation();
}

const fvec2 EngineInterface::billboard_getSize(const string& ID) const
{
	return _core->getBillboardEntityManager()->getEntity(ID)->getSize().x;
}

const fvec2 EngineInterface::billboard_getUvMultiplier(const string& ID) const
{
	return _core->getBillboardEntityManager()->getEntity(ID)->getUvMultiplier();
}

const fvec2 EngineInterface::billboard_getUvOffset(const string& ID) const
{
	return _core->getBillboardEntityManager()->getEntity(ID)->getUvOffset();
}

const fvec3 EngineInterface::billboard_getColor(const string& ID) const
{
	return _core->getBillboardEntityManager()->getEntity(ID)->getColor();
}

const fvec3 EngineInterface::billboard_getWireframeColor(const string& ID) const
{
	return _core->getBillboardEntityManager()->getEntity(ID)->getWireframeColor();
}

const vector<string> EngineInterface::billboard_getIDs() const
{
	vector<string> result;

	for(const auto& [key, entity] : _core->getBillboardEntityManager()->getEntities())
	{
		result.push_back(entity->getID());
	}

	return result;
}

const bool EngineInterface::billboard_isFacingCameraX(const string& ID) const
{
	return _core->getBillboardEntityManager()->getEntity(ID)->isFacingCameraX();
}

const bool EngineInterface::billboard_isFacingCameraY(const string& ID) const
{
	return _core->getBillboardEntityManager()->getEntity(ID)->isFacingCameraY();
}

const bool EngineInterface::billboard_isDepthMapIncluded(const string& ID) const
{
	return _core->getBillboardEntityManager()->getEntity(ID)->isDepthMapIncluded();
}

const bool EngineInterface::billboard_isShadowed(const string& ID) const
{
	return _core->getBillboardEntityManager()->getEntity(ID)->isShadowed();
}

const bool EngineInterface::billboard_isReflected(const string& ID) const
{
	return _core->getBillboardEntityManager()->getEntity(ID)->isReflected();
}

const bool EngineInterface::billboard_isBright(const string& ID) const
{
	return _core->getBillboardEntityManager()->getEntity(ID)->isBright();
}

const string& EngineInterface::billboard_getFontPath(const string& ID) const
{
	return _core->getBillboardEntityManager()->getEntity(ID)->getFontPath();
}

const string& EngineInterface::billboard_getTextContent(const string& ID) const
{
	return _core->getBillboardEntityManager()->getEntity(ID)->getTextContent();
}

const string& EngineInterface::billboard_getDiffuseMapPath(const string& ID) const
{
	return _core->getBillboardEntityManager()->getEntity(ID)->getDiffuseMapPath();
}

const string& EngineInterface::billboard_getEmissionMapPath(const string& ID) const
{
	return _core->getBillboardEntityManager()->getEntity(ID)->getEmissionMapPath();
}

const bool EngineInterface::billboard_hasDiffuseMap(const string& ID) const
{
	return _core->getBillboardEntityManager()->getEntity(ID)->hasDiffuseMap();
}

const bool EngineInterface::billboard_hasEmissionMap(const string& ID) const
{
	return _core->getBillboardEntityManager()->getEntity(ID)->hasEmissionMap();
}

const bool EngineInterface::billboard_isTextual(const string& ID) const
{
	return _core->getBillboardEntityManager()->getEntity(ID)->isTextual();
}

const bool EngineInterface::billboard_isFrozen(const string& ID) const
{
	return _core->getBillboardEntityManager()->getEntity(ID)->isFrozen();
}

const bool EngineInterface::billboard_isWireframed(const string& ID) const
{
	return _core->getBillboardEntityManager()->getEntity(ID)->isWireframed();
}