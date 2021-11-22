#include "fe3d.hpp"
#include "core_engine.hpp"

const float FabiEngine3D::billboard_getLightness(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->getLightness();
}

const float FabiEngine3D::billboard_getMinHeight(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->getMinHeight();
}

const float FabiEngine3D::billboard_getMaxHeight(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->getMaxHeight();
}

const float FabiEngine3D::billboard_getTransparency(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->getTransparency();
}

const float FabiEngine3D::billboard_getTextureRepeat(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->getTextureRepeat();
}

const float FabiEngine3D::billboard_getEmissionIntensity(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->getEmissionIntensity();
}

const bool FabiEngine3D::billboard_isExisting(const string& ID) const
{
	return _core->_billboardEntityManager.isExisting(ID);
}

const bool FabiEngine3D::billboard_isVisible(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->isVisible();
}

const fvec3 FabiEngine3D::billboard_getPosition(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->getPosition();
}

const fvec3 FabiEngine3D::billboard_getRotation(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->getRotation();
}

const fvec2 FabiEngine3D::billboard_getSize(const string& ID) const
{
	return fvec2(_core->_billboardEntityManager.getEntity(ID)->getSize().x, _core->_billboardEntityManager.getEntity(ID)->getSize().y);
}

const fvec3 FabiEngine3D::billboard_getColor(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->getColor();
}

const fvec3 FabiEngine3D::billboard_getWireframeColor(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->getWireframeColor();
}

const vector<string> FabiEngine3D::billboard_getAllIDs() const
{
	vector<string> IDs;

	for(const auto& [keyID, entity] : _core->_billboardEntityManager.getEntities())
	{
		IDs.push_back(entity->getID());
	}

	return IDs;
}

const bool FabiEngine3D::billboard_isFacingCameraX(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->isFacingCameraX();
}

const bool FabiEngine3D::billboard_isFacingCameraY(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->isFacingCameraY();
}

const bool FabiEngine3D::billboard_isDepthMapIncluded(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->isDepthMapIncluded();
}

const bool FabiEngine3D::billboard_isShadowed(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->isShadowed();
}

const bool FabiEngine3D::billboard_isReflected(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->isReflected();
}

const bool FabiEngine3D::billboard_isBright(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->isBright();
}

const string& FabiEngine3D::billboard_getFontPath(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->getFontPath();
}

const string& FabiEngine3D::billboard_getTextContent(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->getTextContent();
}

const string& FabiEngine3D::billboard_getDiffuseMapPath(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->getDiffuseMapPath();
}

const string& FabiEngine3D::billboard_getEmissionMapPath(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->getEmissionMapPath();
}

const bool FabiEngine3D::billboard_isSpriteAnimationStarted(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->isSpriteAnimationStarted();
}

const bool FabiEngine3D::billboard_isSpriteAnimationPlaying(const string& ID) const
{
	return (billboard_isSpriteAnimationStarted(ID) && !billboard_isSpriteAnimationPaused(ID));
}

const bool FabiEngine3D::billboard_isSpriteAnimationPaused(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->isSpriteAnimationPaused();
}

const bool FabiEngine3D::billboard_hasDiffuseMap(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->hasDiffuseMap();
}

const bool FabiEngine3D::billboard_hasEmissionMap(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->hasEmissionMap();
}

const bool FabiEngine3D::billboard_isTextual(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->isTextual();
}

const bool FabiEngine3D::billboard_isWireframed(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->isWireframed();
}

const int FabiEngine3D::billboard_getRemainingSpriteAnimationLoops(const string& ID) const
{
	// Temporary values
	auto maxLoops = _core->_billboardEntityManager.getEntity(ID)->getMaxSpriteAnimationLoops();
	auto currentLoops = _core->_billboardEntityManager.getEntity(ID)->getSpriteAnimationLoops();

	if(maxLoops == -1) // Infinite
	{
		return -1;
	}
	else // Finite
	{
		return (maxLoops - currentLoops);
	}
}

const unsigned int FabiEngine3D::billboard_getSpriteAnimationRowCount(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->getTotalSpriteAnimationRowCount();
}

const unsigned int FabiEngine3D::billboard_getSpriteAnimationColumnCount(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->getTotalSpriteAnimationColumnCount();
}

const unsigned int FabiEngine3D::billboard_getSpriteAnimationFramestep(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->getSpriteAnimationFramestep();
}

const unsigned int FabiEngine3D::billboard_getSpriteAnimationRowIndex(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->getSpriteAnimationRowIndex();
}

const unsigned int FabiEngine3D::billboard_getSpriteAnimationColumnIndex(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->getSpriteAnimationColumnIndex();
}