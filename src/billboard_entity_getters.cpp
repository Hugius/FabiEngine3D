#include "billboard_entity.hpp"

const shared_ptr<RenderBuffer> BillboardEntity::getRenderBuffer() const
{
	return _renderBuffer;
}

const Matrix44& BillboardEntity::getTransformationMatrix() const
{
	return _transformationMatrix;
}

const TextureID BillboardEntity::getDiffuseMap() const
{
	return _diffuseMap;
}

const TextureID BillboardEntity::getEmissionMap() const
{
	return _emissionMap;
}

const Vec3 BillboardEntity::getPosition() const
{
	return _position;
}

const Vec3 BillboardEntity::getRotation() const
{
	return _rotation;
}

const Vec2 BillboardEntity::getSize() const
{
	return _size;
}

const Vec3 BillboardEntity::getColor() const
{
	return _color;
}

const string& BillboardEntity::getTextContent() const
{
	return _textContent;
}

const string& BillboardEntity::getFontPath() const
{
	return _fontPath;
}

const string& BillboardEntity::getDiffuseMapPath() const
{
	return _diffuseMapPath;
}

const string& BillboardEntity::getEmissionMapPath() const
{
	return _emissionMapPath;
}

const float BillboardEntity::getLightness() const
{
	return _lightness;
}

const float BillboardEntity::getColorInversion() const
{
	return _colorInversion;
}

const float BillboardEntity::getTransparency() const
{
	return _transparency;
}

const float BillboardEntity::getMinHeight() const
{
	return _minHeight;
}

const float BillboardEntity::getMaxHeight() const
{
	return _maxHeight;
}

const float BillboardEntity::getTextureRepeat() const
{
	return _textureRepeat;
}

const float BillboardEntity::getEmissionIntensity() const
{
	return _emissionIntensity;
}

const unsigned int BillboardEntity::getPassedSpriteAnimationFrames() const
{
	return _passedSpriteAnimationFrames;
}

const unsigned int BillboardEntity::getMaxSpriteAnimationFramestep() const
{
	return _maxSpriteAnimationFramestep;
}

const unsigned int BillboardEntity::getTotalSpriteAnimationRows() const
{
	return _totalSpriteAnimationRows;
}

const unsigned int BillboardEntity::getTotalSpriteAnimationColumns() const
{
	return _totalSpriteAnimationColumns;
}

const unsigned int BillboardEntity::getSpriteAnimationRowIndex() const
{
	return _spriteAnimationRowIndex;
}

const unsigned int BillboardEntity::getSpriteAnimationColumnIndex() const
{
	return _spriteAnimationColumnIndex;
}

const unsigned int BillboardEntity::getSpriteAnimationLoops() const
{
	return _spriteAnimationLoops;
}

const int BillboardEntity::getMaxSpriteAnimationLoops() const
{
	return _maxSpriteAnimationLoops;
}

const bool BillboardEntity::isSpriteAnimationStarted() const
{
	return _isSpriteAnimationStarted;
}

const bool BillboardEntity::isSpriteAnimationPaused() const
{
	return _isSpriteAnimationPaused;
}

const bool BillboardEntity::isFacingCameraX() const
{
	return _isFacingCameraX;
}

const bool BillboardEntity::isFacingCameraY() const
{
	return _isFacingCameraY;
}

const bool BillboardEntity::isDepthMapIncluded() const
{
	return _isDepthMapIncluded;
}

const bool BillboardEntity::isShadowed() const
{
	return _isShadowed;
}

const bool BillboardEntity::isReflected() const
{
	return _isReflected;
}

const bool BillboardEntity::isBright() const
{
	return _isBright;
}

const bool BillboardEntity::isWireframed() const
{
	return _isWireframed;
}

const bool BillboardEntity::hasRenderBuffer() const
{
	return (_renderBuffer != nullptr);
}

const bool BillboardEntity::hasDiffuseMap() const
{
	return (_diffuseMap != 0);
}

const bool BillboardEntity::hasEmissionMap() const
{
	return (_emissionMap != 0);
}

const bool BillboardEntity::isText() const
{
	return _isText;
}