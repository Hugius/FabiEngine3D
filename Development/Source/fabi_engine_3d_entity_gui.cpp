#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::guiEntity_deleteAll()
{
	_core->_guiEntityManager.deleteAllEntities();
}

void FabiEngine3D::guiEntity_hideAll()
{
	for (auto& [keyID, entity] : _core->_guiEntityManager.getEntities())
	{
		entity->setVisible(false);
	}
}

void FabiEngine3D::guiEntity_showAll()
{
	for (auto& [keyID, entity] : _core->_guiEntityManager.getEntities())
	{
		entity->setVisible(true);
	}
}

void FabiEngine3D::guiEntity_add(const string& ID, const string& texturePath, Vec2 translation, float rotation, Vec2 scaling, bool isCentered, bool visible)
{
	_core->_guiEntityManager.addGuiEntity(ID, texturePath, translation, rotation, scaling, false, isCentered);
	_core->_guiEntityManager.getEntity(ID)->setVisible(visible);
}

void FabiEngine3D::guiEntity_add(const string& ID, Vec3 color, Vec2 translation, float rotation, Vec2 scaling, bool isCentered, bool visible)
{
	_core->_guiEntityManager.addGuiEntity(ID, color, translation, rotation, scaling, isCentered);
	_core->_guiEntityManager.getEntity(ID)->setVisible(visible);
}

void FabiEngine3D::guiEntity_hide(const string& ID)
{
	_core->_guiEntityManager.getEntity(ID)->setVisible(false);
}

void FabiEngine3D::guiEntity_show(const string& ID)
{
	_core->_guiEntityManager.getEntity(ID)->setVisible(true);
}

void FabiEngine3D::guiEntity_delete(const string& ID)
{
	_core->_guiEntityManager.deleteEntity(ID);
}

void FabiEngine3D::guiEntity_changeTexture(const string& ID, const string& texturePath)
{
	_core->_guiEntityManager.getEntity(ID)->setTexture(_core->_textureLoader.getTexture2D(texturePath, true, false, false));
}

bool FabiEngine3D::guiEntity_isExisting(const string& ID)
{
	return _core->_guiEntityManager.isExisting(ID);
}

void FabiEngine3D::guiEntity_setPosition(const string& ID, Vec2 position)
{
	_core->_guiEntityManager.getEntity(ID)->setTranslation(position);
}

void FabiEngine3D::guiEntity_setRotation(const string& ID, float rotation)
{
	_core->_guiEntityManager.getEntity(ID)->setRotation(rotation);
}

void FabiEngine3D::guiEntity_setSize(const string& ID, Vec2 size)
{
	_core->_guiEntityManager.getEntity(ID)->setScaling(size);
}

void FabiEngine3D::guiEntity_move(const string& ID, Vec2 position)
{
	_core->_guiEntityManager.getEntity(ID)->translate(position);
}

void FabiEngine3D::guiEntity_rotate(const string& ID, float rotation)
{
	_core->_guiEntityManager.getEntity(ID)->rotate(rotation);
}

void FabiEngine3D::guiEntity_scale(const string& ID, Vec2 size)
{
	_core->_guiEntityManager.getEntity(ID)->scale(size);
}

void FabiEngine3D::guiEntity_setColor(const string& ID, Vec3 color)
{
	_core->_guiEntityManager.getEntity(ID)->setColor(color);
}

void FabiEngine3D::guiEntity_setAlpha(const string& ID, float alpha)
{
	_core->_guiEntityManager.getEntity(ID)->setAlpha(alpha);
}

void FabiEngine3D::guiEntity_setMinPosition(const string& ID, Vec2 minPos)
{
	_core->_guiEntityManager.getEntity(ID)->setMinPosition(minPos);
}

void FabiEngine3D::guiEntity_setMaxPosition(const string& ID, Vec2 maxPos)
{
	_core->_guiEntityManager.getEntity(ID)->setMaxPosition(maxPos);
}

Vec2 FabiEngine3D::guiEntity_getPosition(const string& ID)
{
	return _core->_guiEntityManager.getEntity(ID)->getTranslation();
}

float FabiEngine3D::guiEntity_getRotation(const string& ID)
{
	return _core->_guiEntityManager.getEntity(ID)->getRotation();
}

float FabiEngine3D::guiEntity_getAlpha(const string& ID)
{
	return _core->_guiEntityManager.getEntity(ID)->getAlpha();
}

vector<string> FabiEngine3D::guiEntity_getAllIDs()
{
	vector<string> IDs;

	for (auto [keyID, entity] : _core->_guiEntityManager.getEntities())
	{
		IDs.push_back(entity->getID());
	}

	return IDs;
}

Vec2 FabiEngine3D::guiEntity_getSize(const string& ID)
{
	return _core->_guiEntityManager.getEntity(ID)->getScaling();
}

Vec2 FabiEngine3D::guiEntity_getMinPosition(const string& ID)
{
	return _core->_guiEntityManager.getEntity(ID)->getMinPosition();
}

Vec2 FabiEngine3D::guiEntity_getMaxPosition(const string& ID)
{
	return _core->_guiEntityManager.getEntity(ID)->getMaxPosition();
}

Vec3 FabiEngine3D::guiEntity_getColor(const string& ID)
{
	return _core->_guiEntityManager.getEntity(ID)->getColor();
}

bool FabiEngine3D::guiEntity_isVisible(const string& ID)
{
	return _core->_guiEntityManager.getEntity(ID)->isVisible();
}

bool FabiEngine3D::guiEntity_isCentered(const string& ID)
{
	return _core->_guiEntityManager.getEntity(ID)->isCentered();
}

void FabiEngine3D::guiEntity_playAnimation(const string& ID, int maxAnimationRepeats)
{
	_core->_guiEntityManager.getEntity(ID)->playSpriteAnimation(maxAnimationRepeats);
}

void FabiEngine3D::guiEntity_pauseAnimation(const string& ID)
{
	_core->_guiEntityManager.getEntity(ID)->pauseSpriteAnimation();
}

void FabiEngine3D::guiEntity_resumeAnimation(const string& ID)
{
	_core->_guiEntityManager.getEntity(ID)->resumeSpriteAnimation();
}

void FabiEngine3D::guiEntity_stopAnimation(const string& ID)
{
	_core->_guiEntityManager.getEntity(ID)->stopSpriteAnimationAnimation();
}

void FabiEngine3D::guiEntity_setAnimationRows(const string& ID, int rows)
{
	_core->_guiEntityManager.getEntity(ID)->setTotalSpriteAnimationRows(rows);
}

void FabiEngine3D::guiEntity_setAnimationColumns(const string& ID, int columns)
{
	_core->_guiEntityManager.getEntity(ID)->setTotalSpriteAnimationColumns(columns);
}

void FabiEngine3D::guiEntity_setAnimationFramestep(const string& ID, int framestep)
{
	_core->_guiEntityManager.getEntity(ID)->setMaxSpriteAnimationFramestep(framestep);
}

void FabiEngine3D::guiEntity_setMirroredHorizontally(const string& ID, bool mirrored)
{
	_core->_guiEntityManager.getEntity(ID)->setMirroredHorizontally(mirrored);
}

void FabiEngine3D::guiEntity_setMirroredVertically(const string& ID, bool mirrored)
{
	_core->_guiEntityManager.getEntity(ID)->setMirroredVertically(mirrored);
}

bool FabiEngine3D::guiEntity_isAnimationFinished(const string& ID)
{
	int repeats = _core->_guiEntityManager.getEntity(ID)->getSpriteAnimationRepeats();
	int maxRepeats = _core->_guiEntityManager.getEntity(ID)->getMaxSpriteAnimationRepeats();
	return (repeats == maxRepeats);
}

bool FabiEngine3D::guiEntity_isAnimationPlaying(const string& ID)
{
	return _core->_guiEntityManager.getEntity(ID)->isSpriteAnimationPlaying();
}

bool FabiEngine3D::guiEntity_isAnimationPaused(const string& ID)
{
	return _core->_guiEntityManager.getEntity(ID)->isSpriteAnimationPaused();
}

bool FabiEngine3D::guiEntity_isMirroredHorizontally(const string& ID)
{
	return _core->_guiEntityManager.getEntity(ID)->isMirroredHorizonally();;
}

bool FabiEngine3D::guiEntity_isMirroredVertically(const string& ID)
{
	return _core->_guiEntityManager.getEntity(ID)->isMirroredVertically();;
}

int FabiEngine3D::guiEntity_getAnimationRows(const string& ID)
{
	return _core->_guiEntityManager.getEntity(ID)->getTotalSpriteAnimationRows();
}

int FabiEngine3D::guiEntity_getAnimationColumns(const string& ID)
{
	return _core->_guiEntityManager.getEntity(ID)->getTotalSpriteAnimationColumns();
}

int FabiEngine3D::guiEntity_getAnimationFramestep(const string& ID)
{
	return _core->_guiEntityManager.getEntity(ID)->getMaxSpriteAnimationFramestep();
}