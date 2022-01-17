#include "engine_interface.hpp"
#include "engine_core.hpp"

const float EngineInterface::quad3d_getLightness(const string& ID) const
{
	return _core->getQuad3dEntityManager()->getEntity(ID)->getLightness();
}

const float EngineInterface::quad3d_getMinHeight(const string& ID) const
{
	return _core->getQuad3dEntityManager()->getEntity(ID)->getMinHeight();
}

const float EngineInterface::quad3d_getMaxHeight(const string& ID) const
{
	return _core->getQuad3dEntityManager()->getEntity(ID)->getMaxHeight();
}

const float EngineInterface::quad3d_getTransparency(const string& ID) const
{
	return _core->getQuad3dEntityManager()->getEntity(ID)->getTransparency();
}

const float EngineInterface::quad3d_getTextureRepeat(const string& ID) const
{
	return _core->getQuad3dEntityManager()->getEntity(ID)->getTextureRepeat();
}

const float EngineInterface::quad3d_getEmissionIntensity(const string& ID) const
{
	return _core->getQuad3dEntityManager()->getEntity(ID)->getEmissionIntensity();
}

const bool EngineInterface::quad3d_isExisting(const string& ID) const
{
	return _core->getQuad3dEntityManager()->isEntityExisting(ID);
}

const bool EngineInterface::quad3d_isVisible(const string& ID) const
{
	return _core->getQuad3dEntityManager()->getEntity(ID)->isVisible();
}

const fvec3 EngineInterface::quad3d_getPosition(const string& ID) const
{
	return _core->getQuad3dEntityManager()->getEntity(ID)->getPosition();
}

const fvec3 EngineInterface::quad3d_getRotation(const string& ID) const
{
	return _core->getQuad3dEntityManager()->getEntity(ID)->getRotation();
}

const fvec2 EngineInterface::quad3d_getSize(const string& ID) const
{
	return _core->getQuad3dEntityManager()->getEntity(ID)->getSize().x;
}

const fvec2 EngineInterface::quad3d_getUvMultiplier(const string& ID) const
{
	return _core->getQuad3dEntityManager()->getEntity(ID)->getUvMultiplier();
}

const fvec2 EngineInterface::quad3d_getUvOffset(const string& ID) const
{
	return _core->getQuad3dEntityManager()->getEntity(ID)->getUvOffset();
}

const fvec3 EngineInterface::quad3d_getColor(const string& ID) const
{
	return _core->getQuad3dEntityManager()->getEntity(ID)->getColor();
}

const fvec3 EngineInterface::quad3d_getWireframeColor(const string& ID) const
{
	return _core->getQuad3dEntityManager()->getEntity(ID)->getWireframeColor();
}

const vector<string> EngineInterface::quad3d_getIDs() const
{
	vector<string> result;

	for(const auto& [key, entity] : _core->getQuad3dEntityManager()->getEntities())
	{
		result.push_back(entity->getID());
	}

	return result;
}

const bool EngineInterface::quad3d_isFacingCameraX(const string& ID) const
{
	return _core->getQuad3dEntityManager()->getEntity(ID)->isFacingCameraX();
}

const bool EngineInterface::quad3d_isFacingCameraY(const string& ID) const
{
	return _core->getQuad3dEntityManager()->getEntity(ID)->isFacingCameraY();
}

const bool EngineInterface::quad3d_isDepthMapIncluded(const string& ID) const
{
	return _core->getQuad3dEntityManager()->getEntity(ID)->isDepthMapIncluded();
}

const bool EngineInterface::quad3d_isShadowed(const string& ID) const
{
	return _core->getQuad3dEntityManager()->getEntity(ID)->isShadowed();
}

const bool EngineInterface::quad3d_isReflected(const string& ID) const
{
	return _core->getQuad3dEntityManager()->getEntity(ID)->isReflected();
}

const bool EngineInterface::quad3d_isBright(const string& ID) const
{
	return _core->getQuad3dEntityManager()->getEntity(ID)->isBright();
}

const string& EngineInterface::quad3d_getDiffuseMapPath(const string& ID) const
{
	return _core->getQuad3dEntityManager()->getEntity(ID)->getDiffuseMapPath();
}

const string& EngineInterface::quad3d_getEmissionMapPath(const string& ID) const
{
	return _core->getQuad3dEntityManager()->getEntity(ID)->getEmissionMapPath();
}

const bool EngineInterface::quad3d_hasDiffuseMap(const string& ID) const
{
	return _core->getQuad3dEntityManager()->getEntity(ID)->hasDiffuseMap();
}

const bool EngineInterface::quad3d_hasEmissionMap(const string& ID) const
{
	return _core->getQuad3dEntityManager()->getEntity(ID)->hasEmissionMap();
}

const bool EngineInterface::quad3d_isFrozen(const string& ID) const
{
	return _core->getQuad3dEntityManager()->getEntity(ID)->isFrozen();
}

const bool EngineInterface::quad3d_isWireframed(const string& ID) const
{
	return _core->getQuad3dEntityManager()->getEntity(ID)->isWireframed();
}