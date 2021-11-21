#include "fe3d.hpp"
#include "core_engine.hpp"

const float FabiEngine3D::billboardEntity_getLightness(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->getLightness();
}

const float FabiEngine3D::billboardEntity_getMinHeight(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->getMinHeight();
}

const float FabiEngine3D::billboardEntity_getMaxHeight(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->getMaxHeight();
}

const float FabiEngine3D::billboardEntity_getTransparency(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->getTransparency();
}

const float FabiEngine3D::billboardEntity_getTextureRepeat(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->getTextureRepeat();
}

const float FabiEngine3D::billboardEntity_getEmissionIntensity(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->getEmissionIntensity();
}

const bool FabiEngine3D::billboardEntity_isExisting(const string& ID) const
{
	return _core->_billboardEntityManager.isExisting(ID);
}

const bool FabiEngine3D::billboardEntity_isVisible(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->isVisible();
}

const Vec3 FabiEngine3D::billboardEntity_getPosition(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->getPosition();
}

const Vec3 FabiEngine3D::billboardEntity_getRotation(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->getRotation();
}

const Vec2 FabiEngine3D::billboardEntity_getSize(const string& ID) const
{
	return Vec2(_core->_billboardEntityManager.getEntity(ID)->getSize().x, _core->_billboardEntityManager.getEntity(ID)->getSize().y);
}

const Vec3 FabiEngine3D::billboardEntity_getColor(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->getColor();
}

const Vec3 FabiEngine3D::billboardEntity_getWireframeColor(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->getWireframeColor();
}

const vector<string> FabiEngine3D::billboardEntity_getAllIDs() const
{
	vector<string> IDs;

	for(const auto& [keyID, entity] : _core->_billboardEntityManager.getEntities())
	{
		IDs.push_back(entity->getID());
	}

	return IDs;
}

const bool FabiEngine3D::billboardEntity_isFacingCameraX(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->isFacingCameraX();
}

const bool FabiEngine3D::billboardEntity_isFacingCameraY(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->isFacingCameraY();
}

const bool FabiEngine3D::billboardEntity_isDepthMapIncluded(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->isDepthMapIncluded();
}

const bool FabiEngine3D::billboardEntity_isShadowed(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->isShadowed();
}

const bool FabiEngine3D::billboardEntity_isReflected(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->isReflected();
}

const bool FabiEngine3D::billboardEntity_isBright(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->isBright();
}

const string& FabiEngine3D::billboardEntity_getFontPath(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->getFontPath();
}

const string& FabiEngine3D::billboardEntity_getTextContent(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->getTextContent();
}

const string& FabiEngine3D::billboardEntity_getDiffuseMapPath(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->getDiffuseMapPath();
}

const string& FabiEngine3D::billboardEntity_getEmissionMapPath(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->getEmissionMapPath();
}

const bool FabiEngine3D::billboardEntity_isSpriteAnimationStarted(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->isSpriteAnimationStarted();
}

const bool FabiEngine3D::billboardEntity_isSpriteAnimationPlaying(const string& ID) const
{
	return (billboardEntity_isSpriteAnimationStarted(ID) && !billboardEntity_isSpriteAnimationPaused(ID));
}

const bool FabiEngine3D::billboardEntity_isSpriteAnimationPaused(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->isSpriteAnimationPaused();
}

const bool FabiEngine3D::billboardEntity_hasDiffuseMap(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->hasDiffuseMap();
}

const bool FabiEngine3D::billboardEntity_hasEmissionMap(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->hasEmissionMap();
}

const bool FabiEngine3D::billboardEntity_isText(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->isTextual();
}

const bool FabiEngine3D::billboardEntity_isWireframed(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->isWireframed();
}

const int FabiEngine3D::billboardEntity_getRemainingSpriteAnimationLoops(const string& ID) const
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

const unsigned int FabiEngine3D::billboardEntity_getSpriteAnimationRowCount(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->getTotalSpriteAnimationRowCount();
}

const unsigned int FabiEngine3D::billboardEntity_getSpriteAnimationColumnCount(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->getTotalSpriteAnimationColumnCount();
}

const unsigned int FabiEngine3D::billboardEntity_getSpriteAnimationFramestep(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->getSpriteAnimationFramestep();
}

const unsigned int FabiEngine3D::billboardEntity_getSpriteAnimationRowIndex(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->getSpriteAnimationRowIndex();
}

const unsigned int FabiEngine3D::billboardEntity_getSpriteAnimationColumnIndex(const string& ID) const
{
	return _core->_billboardEntityManager.getEntity(ID)->getSpriteAnimationColumnIndex();
}