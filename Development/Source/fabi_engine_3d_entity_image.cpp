#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::imageEntity_deleteAll()
{
	_core->_imageEntityManager.deleteAllEntities();
}

void FabiEngine3D::imageEntity_hideAll()
{
	for (auto& [keyID, entity] : _core->_imageEntityManager.getEntities())
	{
		entity->setVisible(false);
	}
}

void FabiEngine3D::imageEntity_showAll()
{
	for (auto& [keyID, entity] : _core->_imageEntityManager.getEntities())
	{
		entity->setVisible(true);
	}
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

void FabiEngine3D::imageEntity_hide(const string& ID)
{
	_core->_imageEntityManager.getEntity(ID)->setVisible(false);
}

void FabiEngine3D::imageEntity_show(const string& ID)
{
	_core->_imageEntityManager.getEntity(ID)->setVisible(true);
}

void FabiEngine3D::imageEntity_delete(const string& ID)
{
	_core->_imageEntityManager.deleteEntity(ID);
}

void FabiEngine3D::imageEntity_changeTexture(const string& ID, const string& texturePath)
{
	_core->_imageEntityManager.getEntity(ID)->setTexture(_core->_textureLoader.getTexture2D(texturePath, true, false, false));
}

bool FabiEngine3D::imageEntity_isExisting(const string& ID)
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

Vec2 FabiEngine3D::imageEntity_getPosition(const string& ID)
{
	return _core->_imageEntityManager.getEntity(ID)->getTranslation();
}

float FabiEngine3D::imageEntity_getRotation(const string& ID)
{
	return _core->_imageEntityManager.getEntity(ID)->getRotation();
}

float FabiEngine3D::imageEntity_getAlpha(const string& ID)
{
	return _core->_imageEntityManager.getEntity(ID)->getAlpha();
}

int FabiEngine3D::imageEntity_getRemainingAnimationLoops(const string& ID)
{
	auto maxLoops = _core->_imageEntityManager.getEntity(ID)->getMaxSpriteAnimationLoops();
	auto currentLoops = _core->_imageEntityManager.getEntity(ID)->getSpriteAnimationLoops();

	return (maxLoops - currentLoops);
}

vector<string> FabiEngine3D::imageEntity_getAllIDs()
{
	vector<string> IDs;

	for (const auto& [keyID, entity] : _core->_imageEntityManager.getEntities())
	{
		IDs.push_back(entity->getID());
	}

	return IDs;
}

Vec2 FabiEngine3D::imageEntity_getSize(const string& ID)
{
	return _core->_imageEntityManager.getEntity(ID)->getScaling();
}

Vec2 FabiEngine3D::imageEntity_getMinPosition(const string& ID)
{
	return _core->_imageEntityManager.getEntity(ID)->getMinPosition();
}

Vec2 FabiEngine3D::imageEntity_getMaxPosition(const string& ID)
{
	return _core->_imageEntityManager.getEntity(ID)->getMaxPosition();
}

Vec3 FabiEngine3D::imageEntity_getColor(const string& ID)
{
	return _core->_imageEntityManager.getEntity(ID)->getColor();
}

bool FabiEngine3D::imageEntity_isVisible(const string& ID)
{
	return _core->_imageEntityManager.getEntity(ID)->isVisible();
}

bool FabiEngine3D::imageEntity_isCentered(const string& ID)
{
	return _core->_imageEntityManager.getEntity(ID)->isCentered();
}

void FabiEngine3D::imageEntity_startAnimation(const string& ID, int loops)
{
	_core->_imageEntityManager.getEntity(ID)->startSpriteAnimation(loops);
}

void FabiEngine3D::imageEntity_pauseAnimation(const string& ID)
{
	_core->_imageEntityManager.getEntity(ID)->pauseSpriteAnimation();
}

void FabiEngine3D::imageEntity_resumeAnimation(const string& ID)
{
	_core->_imageEntityManager.getEntity(ID)->resumeSpriteAnimation();
}

void FabiEngine3D::imageEntity_stopAnimation(const string& ID)
{
	_core->_imageEntityManager.getEntity(ID)->stopSpriteAnimationAnimation();
}

void FabiEngine3D::imageEntity_setAnimationRows(const string& ID, int rows)
{
	_core->_imageEntityManager.getEntity(ID)->setTotalSpriteAnimationRows(rows);
}

void FabiEngine3D::imageEntity_setAnimationColumns(const string& ID, int columns)
{
	_core->_imageEntityManager.getEntity(ID)->setTotalSpriteAnimationColumns(columns);
}

void FabiEngine3D::imageEntity_setAnimationFramestep(const string& ID, int framestep)
{
	_core->_imageEntityManager.getEntity(ID)->setMaxSpriteAnimationFramestep(framestep);
}

void FabiEngine3D::imageEntity_setAnimationRowIndex(const string& ID, unsigned int index)
{
	_core->_imageEntityManager.getEntity(ID)->setSpriteAnimationRowIndex(index);
}

void FabiEngine3D::imageEntity_setAnimationColumnIndex(const string& ID, unsigned int index)
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

bool FabiEngine3D::imageEntity_isAnimationStarted(const string& ID)
{
	return _core->_imageEntityManager.getEntity(ID)->isSpriteAnimationStarted();
}

bool FabiEngine3D::imageEntity_isAnimationPlaying(const string& ID)
{
	return (imageEntity_isAnimationStarted(ID) && !imageEntity_isAnimationPaused(ID));
}

bool FabiEngine3D::imageEntity_isAnimationPaused(const string& ID)
{
	return _core->_imageEntityManager.getEntity(ID)->isSpriteAnimationPaused();
}

bool FabiEngine3D::imageEntity_isMirroredHorizontally(const string& ID)
{
	return _core->_imageEntityManager.getEntity(ID)->isMirroredHorizonally();;
}

bool FabiEngine3D::imageEntity_isMirroredVertically(const string& ID)
{
	return _core->_imageEntityManager.getEntity(ID)->isMirroredVertically();;
}

unsigned int FabiEngine3D::imageEntity_getAnimationRows(const string& ID)
{
	return _core->_imageEntityManager.getEntity(ID)->getTotalSpriteAnimationRows();
}

unsigned int FabiEngine3D::imageEntity_getAnimationColumns(const string& ID)
{
	return _core->_imageEntityManager.getEntity(ID)->getTotalSpriteAnimationColumns();
}

unsigned int FabiEngine3D::imageEntity_getAnimationFramestep(const string& ID)
{
	return _core->_imageEntityManager.getEntity(ID)->getMaxSpriteAnimationFramestep();
}

unsigned int FabiEngine3D::imageEntity_getAnimationRowIndex(const string& ID)
{
	return _core->_imageEntityManager.getEntity(ID)->getSpriteAnimationRowIndex();
}

unsigned int FabiEngine3D::imageEntity_getAnimationColumnIndex(const string& ID)
{
	return _core->_imageEntityManager.getEntity(ID)->getSpriteAnimationColumnIndex();
}