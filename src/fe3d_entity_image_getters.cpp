#include "fe3d.hpp"
#include "core_engine.hpp"

const bool FabiEngine3D::image_isExisting(const string& ID) const
{
	return _core->_imageEntityManager.isExisting(ID);
}

const fvec2 FabiEngine3D::image_getPosition(const string& ID) const
{
	return _core->_imageEntityManager.getEntity(ID)->getPosition();
}

const float FabiEngine3D::image_getRotation(const string& ID) const
{
	return _core->_imageEntityManager.getEntity(ID)->getRotation();
}

const float FabiEngine3D::image_getTransparency(const string& ID) const
{
	return _core->_imageEntityManager.getEntity(ID)->getTransparency();
}

const int FabiEngine3D::image_getRemainingSpriteAnimationLoops(const string& ID) const
{
	auto maxLoops = _core->_imageEntityManager.getEntity(ID)->getMaxSpriteAnimationLoops();
	auto currentLoops = _core->_imageEntityManager.getEntity(ID)->getSpriteAnimationLoops();

	return (maxLoops - currentLoops);
}

const vector<string> FabiEngine3D::image_getAllIDs() const
{
	vector<string> IDs;

	for(const auto& [keyID, entity] : _core->_imageEntityManager.getEntities())
	{
		IDs.push_back(entity->getID());
	}

	return IDs;
}

const string& FabiEngine3D::image_getDiffuseMapPath(const string& ID) const
{
	_core->_imageEntityManager.getEntity(ID)->getDiffuseMapPath();
}

const fvec3 FabiEngine3D::image_getWireframeColor(const string& ID) const
{
	_core->_imageEntityManager.getEntity(ID)->getWireframeColor();
}

const fvec2 FabiEngine3D::image_getSize(const string& ID) const
{
	return _core->_imageEntityManager.getEntity(ID)->getSize();
}

const fvec2 FabiEngine3D::image_getMinPosition(const string& ID) const
{
	return _core->_imageEntityManager.getEntity(ID)->getMinPosition();
}

const fvec2 FabiEngine3D::image_getMaxPosition(const string& ID) const
{
	return _core->_imageEntityManager.getEntity(ID)->getMaxPosition();
}

const fvec3 FabiEngine3D::image_getColor(const string& ID) const
{
	return _core->_imageEntityManager.getEntity(ID)->getColor();
}

const bool FabiEngine3D::image_isVisible(const string& ID) const
{
	return _core->_imageEntityManager.getEntity(ID)->isVisible();
}

const bool FabiEngine3D::image_isCentered(const string& ID) const
{
	return _core->_imageEntityManager.getEntity(ID)->isCentered();
}

const bool FabiEngine3D::image_isSpriteAnimationStarted(const string& ID) const
{
	return _core->_imageEntityManager.getEntity(ID)->isSpriteAnimationStarted();
}

const bool FabiEngine3D::image_isSpriteAnimationPlaying(const string& ID) const
{
	return (image_isSpriteAnimationStarted(ID) && !image_isSpriteAnimationPaused(ID));
}

const bool FabiEngine3D::image_isSpriteAnimationPaused(const string& ID) const
{
	return _core->_imageEntityManager.getEntity(ID)->isSpriteAnimationPaused();
}

const bool FabiEngine3D::image_hasDiffuseMap(const string& ID) const
{
	return _core->_imageEntityManager.getEntity(ID)->hasDiffuseMap();
}

const bool FabiEngine3D::image_isWireframed(const string& ID) const
{
	return _core->_imageEntityManager.getEntity(ID)->isWireframed();
}

const bool FabiEngine3D::image_isMirroredHorizontally(const string& ID) const
{
	return _core->_imageEntityManager.getEntity(ID)->isMirroredHorizonally();
}

const bool FabiEngine3D::image_isMirroredVertically(const string& ID) const
{
	return _core->_imageEntityManager.getEntity(ID)->isMirroredVertically();
}

const unsigned int FabiEngine3D::image_getSpriteAnimationRowCount(const string& ID) const
{
	return _core->_imageEntityManager.getEntity(ID)->getTotalSpriteAnimationRowCount();
}

const unsigned int FabiEngine3D::image_getSpriteAnimationColumnCount(const string& ID) const
{
	return _core->_imageEntityManager.getEntity(ID)->getTotalSpriteAnimationColumnCount();
}

const unsigned int FabiEngine3D::image_getSpriteAnimationFramestep(const string& ID) const
{
	return _core->_imageEntityManager.getEntity(ID)->getSpriteAnimationFramestep();
}

const unsigned int FabiEngine3D::image_getSpriteAnimationRowIndex(const string& ID) const
{
	return _core->_imageEntityManager.getEntity(ID)->getSpriteAnimationRowIndex();
}

const unsigned int FabiEngine3D::image_getSpriteAnimationColumnIndex(const string& ID) const
{
	return _core->_imageEntityManager.getEntity(ID)->getSpriteAnimationColumnIndex();
}