#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::imageEntity_deleteAll()
{
	_core->_imageEntityManager.deleteAllEntities();
}

void FabiEngine3D::imageEntity_add(const string& ID, const string& texturePath, Vec2 translation, float rotation, Vec2 scaling, bool isCentered, bool visible)
{
	_core->_imageEntityManager.addImageEntity(ID, texturePath, translation, rotation, scaling, false, isCentered);
	_core->_imageEntityManager.getEntity(ID)->setVisible(visible);
}

void FabiEngine3D::imageEntity_add(const string& ID, Vec3 color, Vec2 translation, float rotation, Vec2 scaling, bool isCentered, bool visible)
{
	_core->_imageEntityManager.addImageEntity(ID, color, translation, rotation, scaling, isCentered);
	_core->_imageEntityManager.getEntity(ID)->setVisible(visible);
}

void FabiEngine3D::imageEntity_delete(const string& ID)
{
	_core->_imageEntityManager.deleteEntity(ID);
}

void FabiEngine3D::imageEntity_setVisible(const string& ID, bool isVisible)
{
	_core->_imageEntityManager.getEntity(ID)->setVisible(isVisible);
}

void FabiEngine3D::imageEntity_changeTexture(const string& ID, const string& texturePath)
{
	_core->_imageEntityManager.getEntity(ID)->setDiffuseMap(_core->_textureLoader.getTexture2D(texturePath, false, false));
}

const bool FabiEngine3D::imageEntity_isExisting(const string& ID)
{
	return _core->_imageEntityManager.isExisting(ID);
}

void FabiEngine3D::imageEntity_setPosition(const string& ID, Vec2 position)
{
	_core->_imageEntityManager.getEntity(ID)->setTranslation(position);
}

void FabiEngine3D::imageEntity_setRotation(const string& ID, float rotation)
{
	_core->_imageEntityManager.getEntity(ID)->setRotation(rotation);
}

void FabiEngine3D::imageEntity_setSize(const string& ID, Vec2 size)
{
	_core->_imageEntityManager.getEntity(ID)->setScaling(size);
}

void FabiEngine3D::imageEntity_move(const string& ID, Vec2 position)
{
	_core->_imageEntityManager.getEntity(ID)->translate(position);
}

void FabiEngine3D::imageEntity_rotate(const string& ID, float rotation)
{
	_core->_imageEntityManager.getEntity(ID)->rotate(rotation);
}

void FabiEngine3D::imageEntity_scale(const string& ID, Vec2 size)
{
	_core->_imageEntityManager.getEntity(ID)->scale(size);
}

void FabiEngine3D::imageEntity_setColor(const string& ID, Vec3 color)
{
	_core->_imageEntityManager.getEntity(ID)->setColor(color);
}

void FabiEngine3D::imageEntity_setAlpha(const string& ID, float alpha)
{
	_core->_imageEntityManager.getEntity(ID)->setAlpha(alpha);
}

void FabiEngine3D::imageEntity_setMinPosition(const string& ID, Vec2 minPos)
{
	_core->_imageEntityManager.getEntity(ID)->setMinPosition(minPos);
}

void FabiEngine3D::imageEntity_setMaxPosition(const string& ID, Vec2 maxPos)
{
	_core->_imageEntityManager.getEntity(ID)->setMaxPosition(maxPos);
}

const Vec2 FabiEngine3D::imageEntity_getPosition(const string& ID)
{
	return _core->_imageEntityManager.getEntity(ID)->getTranslation();
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

	for (const auto& [keyID, entity] : _core->_imageEntityManager.getEntities())
	{
		IDs.push_back(entity->getID());
	}

	return IDs;
}

const Vec2 FabiEngine3D::imageEntity_getSize(const string& ID)
{
	return _core->_imageEntityManager.getEntity(ID)->getScaling();
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

const bool FabiEngine3D::imageEntity_isCentered(const string& ID)
{
	return _core->_imageEntityManager.getEntity(ID)->isCentered();
}

void FabiEngine3D::imageEntity_startSpriteAnimation(const string& ID, int loops)
{
	_core->_imageEntityManager.getEntity(ID)->startSpriteAnimation(loops);
}

void FabiEngine3D::imageEntity_pauseSpriteAnimation(const string& ID)
{
	_core->_imageEntityManager.getEntity(ID)->pauseSpriteAnimation();
}

void FabiEngine3D::imageEntity_resumeSpriteAnimation(const string& ID)
{
	_core->_imageEntityManager.getEntity(ID)->resumeSpriteAnimation();
}

void FabiEngine3D::imageEntity_stopSpriteAnimation(const string& ID)
{
	_core->_imageEntityManager.getEntity(ID)->stopSpriteAnimationAnimation();
}

void FabiEngine3D::imageEntity_setSpriteAnimationRows(const string& ID, int rows)
{
	_core->_imageEntityManager.getEntity(ID)->setTotalSpriteAnimationRows(rows);
}

void FabiEngine3D::imageEntity_setSpriteAnimationColumns(const string& ID, int columns)
{
	_core->_imageEntityManager.getEntity(ID)->setTotalSpriteAnimationColumns(columns);
}

void FabiEngine3D::imageEntity_setSpriteAnimationFramestep(const string& ID, int framestep)
{
	_core->_imageEntityManager.getEntity(ID)->setMaxSpriteAnimationFramestep(framestep);
}

void FabiEngine3D::imageEntity_setSpriteAnimationRowIndex(const string& ID, unsigned int index)
{
	_core->_imageEntityManager.getEntity(ID)->setSpriteAnimationRowIndex(index);
}

void FabiEngine3D::imageEntity_setSpriteAnimationColumnIndex(const string& ID, unsigned int index)
{
	_core->_imageEntityManager.getEntity(ID)->setSpriteAnimationColumnIndex(index);
}

void FabiEngine3D::imageEntity_setMirroredHorizontally(const string& ID, bool mirrored)
{
	_core->_imageEntityManager.getEntity(ID)->setMirroredHorizontally(mirrored);
}

void FabiEngine3D::imageEntity_setMirroredVertically(const string& ID, bool mirrored)
{
	_core->_imageEntityManager.getEntity(ID)->setMirroredVertically(mirrored);
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

const bool FabiEngine3D::imageEntity_isMirroredHorizontally(const string& ID)
{
	return _core->_imageEntityManager.getEntity(ID)->isMirroredHorizonally();;
}

const bool FabiEngine3D::imageEntity_isMirroredVertically(const string& ID)
{
	return _core->_imageEntityManager.getEntity(ID)->isMirroredVertically();;
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