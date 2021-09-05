#include "billboard_entity.hpp"

const shared_ptr<RenderBuffer> BillboardEntity::getRenderBuffer()
{
	return _renderBuffer;
}

const Matrix44 & BillboardEntity::getTransformationMatrix()
{
	return _transformationMatrix;
}

const TextureID BillboardEntity::getDiffuseMap()
{
	return _diffuseMap;
}

const Vec3 BillboardEntity::getPosition()
{
	return _position;
}

const Vec3 BillboardEntity::getRotation()
{
	return _rotation;
}

const Vec2 BillboardEntity::getSize()
{
	return _size;
}

const Vec3 BillboardEntity::getColor()
{
	return _color;
}

const string& BillboardEntity::getTextContent()
{
	return _textContent;
}

const string& BillboardEntity::getFontPath()
{
	return _fontPath;
}

const string& BillboardEntity::getDiffuseMapPath()
{
	return _diffuseMapPath;
}

const float BillboardEntity::getLightness()
{
	return _lightness;
}

const float BillboardEntity::getInversion()
{
	return _inversion;
}

const float BillboardEntity::getAlpha()
{
	return _alpha;
}

const float BillboardEntity::getMinHeight()
{
	return _minHeight;
}

const float BillboardEntity::getMaxHeight()
{
	return _maxHeight;
}

const unsigned int BillboardEntity::getPassedSpriteAnimationFrames()
{
	return _passedSpriteAnimationFrames;
}

const unsigned int BillboardEntity::getMaxSpriteAnimationFramestep()
{
	return _maxSpriteAnimationFramestep;
}

const unsigned int BillboardEntity::getTotalSpriteAnimationRows()
{
	return _totalSpriteAnimationRows;
}

const unsigned int BillboardEntity::getTotalSpriteAnimationColumns()
{
	return _totalSpriteAnimationColumns;
}

const unsigned int BillboardEntity::getSpriteAnimationRowIndex()
{
	return _spriteAnimationRowIndex;
}

const unsigned int BillboardEntity::getSpriteAnimationColumnIndex()
{
	return _spriteAnimationColumnIndex;
}

const unsigned int BillboardEntity::getSpriteAnimationLoops()
{
	return _spriteAnimationLoops;
}

const int BillboardEntity::getMaxSpriteAnimationLoops()
{
	return _maxSpriteAnimationLoops;
}

const bool BillboardEntity::isTransparent()
{
	return _isTransparent;
}

const bool BillboardEntity::isSpriteAnimationStarted()
{
	return _isSpriteAnimationStarted;
}

const bool BillboardEntity::isSpriteAnimationPaused()
{
	return _isSpriteAnimationPaused;
}

const bool BillboardEntity::isFacingCameraX()
{
	return _isFacingCameraX;
}

const bool BillboardEntity::isFacingCameraY()
{
	return _isFacingCameraY;
}

const bool BillboardEntity::isDepthMapIncluded()
{
	return _isDepthMapIncluded;
}

const bool BillboardEntity::isShadowed()
{
	return _isShadowed;
}

const bool BillboardEntity::isReflected()
{
	return _isReflected;
}

const bool BillboardEntity::isBright()
{
	return _isBright;
}

const bool BillboardEntity::isWireFramed()
{
	return _isWireFramed;
}

const bool BillboardEntity::hasRenderBuffer()
{
	return (_renderBuffer != nullptr);
}

const bool BillboardEntity::hasDiffuseMap()
{
	return (_diffuseMap != 0);
}