#include "fe3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::imageEntity_deleteAll()
{
	_core->_imageEntityManager.deleteAllEntities();
}

void FabiEngine3D::imageEntity_create(const string& ID, bool isCentered)
{
	_core->_imageEntityManager.createEntity(ID, isCentered);
}

void FabiEngine3D::imageEntity_delete(const string& ID)
{
	_core->_imageEntityManager.deleteEntity(ID);
}

void FabiEngine3D::imageEntity_setVisible(const string& ID, bool isVisible)
{
	_core->_imageEntityManager.getEntity(ID)->setVisible(isVisible);
}

void FabiEngine3D::imageEntity_setDiffuseMap(const string& ID, const string& texturePath)
{
	if(texturePath.empty())
	{
		_core->_imageEntityManager.getEntity(ID)->setDiffuseMap(0);
		_core->_imageEntityManager.getEntity(ID)->setDiffuseMapPath("");
	}
	else
	{
		_core->_imageEntityManager.getEntity(ID)->setDiffuseMap(_core->_textureLoader.loadTexture2D(texturePath, false, false));
		_core->_imageEntityManager.getEntity(ID)->setDiffuseMapPath(texturePath);
	}
}

void FabiEngine3D::imageEntity_setPosition(const string& ID, Vec2 position)
{
	_core->_imageEntityManager.getEntity(ID)->setPosition(position);
}

void FabiEngine3D::imageEntity_setRotation(const string& ID, float rotation)
{
	_core->_imageEntityManager.getEntity(ID)->setRotation(rotation);
}

void FabiEngine3D::imageEntity_setSize(const string& ID, Vec2 size)
{
	_core->_imageEntityManager.getEntity(ID)->setSize(size);
}

void FabiEngine3D::imageEntity_move(const string& ID, Vec2 position)
{
	_core->_imageEntityManager.getEntity(ID)->move(position);
}

void FabiEngine3D::imageEntity_rotate(const string& ID, float rotation)
{
	_core->_imageEntityManager.getEntity(ID)->rotate(rotation);
}

void FabiEngine3D::imageEntity_scale(const string& ID, Vec2 size)
{
	_core->_imageEntityManager.getEntity(ID)->scale(size);
}

void FabiEngine3D::imageEntity_moveTo(const string& ID, Vec2 target, float speed)
{
	_core->_imageEntityManager.getEntity(ID)->moveTo(target, speed);
}

void FabiEngine3D::imageEntity_rotateTo(const string& ID, float target, float speed)
{
	_core->_imageEntityManager.getEntity(ID)->rotateTo(target, speed);
}

void FabiEngine3D::imageEntity_scaleTo(const string& ID, Vec2 target, float speed)
{
	_core->_imageEntityManager.getEntity(ID)->scaleTo(target, speed);
}

void FabiEngine3D::imageEntity_setColor(const string& ID, Vec3 color)
{
	_core->_imageEntityManager.getEntity(ID)->setColor(color);
}

void FabiEngine3D::imageEntity_setTransparency(const string& ID, float transparency)
{
	_core->_imageEntityManager.getEntity(ID)->setTransparency(transparency);
}

void FabiEngine3D::imageEntity_setMinPosition(const string& ID, Vec2 minPos)
{
	_core->_imageEntityManager.getEntity(ID)->setMinPosition(minPos);
}

void FabiEngine3D::imageEntity_setMaxPosition(const string& ID, Vec2 maxPos)
{
	_core->_imageEntityManager.getEntity(ID)->setMaxPosition(maxPos);
}

void FabiEngine3D::imageEntity_startSpriteAnimation(const string& ID, int loops)
{
	auto entity = _core->_imageEntityManager.getEntity(ID);

	if(entity->isSpriteAnimationStarted())
	{
		Logger::throwWarning("Tried to start sprite animation on image with ID \"" + ID + "\": animation already started!");
		return;
	}
	if(loops < -1)
	{
		Logger::throwWarning("Tried to start sprite animation on image with ID \"" + ID + "\": invalid loops amount!");
		return;
	}

	entity->startSpriteAnimation(loops);
}

void FabiEngine3D::imageEntity_pauseSpriteAnimation(const string& ID)
{
	auto entity = _core->_imageEntityManager.getEntity(ID);

	if(!entity->isSpriteAnimationStarted())
	{
		Logger::throwWarning("Tried to pause sprite animation on image with ID \"" + ID + "\" animation not started!");
		return;
	}
	else if(entity->isSpriteAnimationPaused())
	{
		Logger::throwWarning("Tried to pause sprite animation on image with ID \"" + ID + "\" animation already paused!");
		return;
	}

	entity->pauseSpriteAnimation();
}

void FabiEngine3D::imageEntity_resumeSpriteAnimation(const string& ID)
{
	auto entity = _core->_imageEntityManager.getEntity(ID);

	if(!entity->isSpriteAnimationPaused())
	{
		Logger::throwWarning("Tried to resume sprite animation on image with ID \"" + ID + "\" animation not paused!");
		return;
	}

	entity->resumeSpriteAnimation();
}

void FabiEngine3D::imageEntity_stopSpriteAnimation(const string& ID)
{
	auto entity = _core->_imageEntityManager.getEntity(ID);

	if(!entity->isSpriteAnimationStarted())
	{
		Logger::throwWarning("Tried to stop sprite animation on image with ID \"" + ID + "\" animation not started!");
		return;
	}

	entity->stopSpriteAnimationAnimation();
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