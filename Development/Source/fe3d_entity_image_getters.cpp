#include "fe3d.hpp"
#include "core_engine.hpp"

const bool FabiEngine3D::imageEntity_isExisting(const string& ID)
{
	return _core->_imageEntityManager.isExisting(ID);
}

const Vec2 FabiEngine3D::imageEntity_getPosition(const string& ID)
{
	return _core->_imageEntityManager.getEntity(ID)->getPosition();
}

const float FabiEngine3D::imageEntity_getRotation(const string& ID)
{
	return _core->_imageEntityManager.getEntity(ID)->getRotation();
}

const float FabiEngine3D::imageEntity_getAlpha(const string& ID)
{
	return _core->_imageEntityManager.getEntity(ID)->getAlpha();
}

const int FabiEngine3D::imageEntity_getRemainingSpriteAnimationLoops(const string& ID)
{
	auto maxLoops = _core->_imageEntityManager.getEntity(ID)->getMaxSpriteAnimationLoops();
	auto currentLoops = _core->_imageEntityManager.getEntity(ID)->getSpriteAnimationLoops();

	return (maxLoops - currentLoops);
}

const vector<string> FabiEngine3D::imageEntity_getAllIDs()
{
	vector<string> IDs;

	for(const auto& [keyID, entity] : _core->_imageEntityManager.getEntities())
	{
		IDs.push_back(entity->getID());
	}

	return IDs;
}

const string& FabiEngine3D::imageEntity_getDiffuseMapPath(const string& ID)
{
	_core->_imageEntityManager.getEntity(ID)->getDiffuseMapPath();
}

const Vec2 FabiEngine3D::imageEntity_getSize(const string& ID)
{
	return _core->_imageEntityManager.getEntity(ID)->getSize();
}

const Vec2 FabiEngine3D::imageEntity_getMinPosition(const string& ID)
{
	return _core->_imageEntityManager.getEntity(ID)->getMinPosition();
}

const Vec2 FabiEngine3D::imageEntity_getMaxPosition(const string& ID)
{
	return _core->_imageEntityManager.getEntity(ID)->getMaxPosition();
}

const Vec3 FabiEngine3D::imageEntity_getColor(const string& ID)
{
	return _core->_imageEntityManager.getEntity(ID)->getColor();
}

const bool FabiEngine3D::imageEntity_isVisible(const string& ID)
{
	return _core->_imageEntityManager.getEntity(ID)->isVisible();
}

const bool FabiEngine3D::imageEntity_isSpriteAnimationStarted(const string& ID)
{
	return _core->_imageEntityManager.getEntity(ID)->isSpriteAnimationStarted();
}

const bool FabiEngine3D::imageEntity_isSpriteAnimationPlaying(const string& ID)
{
	return (imageEntity_isSpriteAnimationStarted(ID) && !imageEntity_isSpriteAnimationPaused(ID));
}

const bool FabiEngine3D::imageEntity_isSpriteAnimationPaused(const string& ID)
{
	return _core->_imageEntityManager.getEntity(ID)->isSpriteAnimationPaused();
}

const bool FabiEngine3D::imageEntity_hasDiffuseMap(const string& ID)
{
	return _core->_imageEntityManager.getEntity(ID)->hasDiffuseMap();
}

const bool FabiEngine3D::imageEntity_isMirroredHorizontally(const string& ID)
{
	return _core->_imageEntityManager.getEntity(ID)->isMirroredHorizonally();
}

const bool FabiEngine3D::imageEntity_isMirroredVertically(const string& ID)
{
	return _core->_imageEntityManager.getEntity(ID)->isMirroredVertically();
}

const unsigned int FabiEngine3D::imageEntity_getSpriteAnimationRows(const string& ID)
{
	return _core->_imageEntityManager.getEntity(ID)->getTotalSpriteAnimationRows();
}

const unsigned int FabiEngine3D::imageEntity_getSpriteAnimationColumns(const string& ID)
{
	return _core->_imageEntityManager.getEntity(ID)->getTotalSpriteAnimationColumns();
}

const unsigned int FabiEngine3D::imageEntity_getSpriteAnimationFramestep(const string& ID)
{
	return _core->_imageEntityManager.getEntity(ID)->getMaxSpriteAnimationFramestep();
}

const unsigned int FabiEngine3D::imageEntity_getSpriteAnimationRowIndex(const string& ID)
{
	return _core->_imageEntityManager.getEntity(ID)->getSpriteAnimationRowIndex();
}

const unsigned int FabiEngine3D::imageEntity_getSpriteAnimationColumnIndex(const string& ID)
{
	return _core->_imageEntityManager.getEntity(ID)->getSpriteAnimationColumnIndex();
}