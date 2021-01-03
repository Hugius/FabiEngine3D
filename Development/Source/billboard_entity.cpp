#include "billboard_entity.hpp"

void BillboardEntity::updateModelMatrix()
{
	Matrix44 translationMatrix = Matrix44::createTranslation(_translation.x, _translation.y, _translation.z);
	Matrix44 rotationMatrix = Matrix44::createRotation(
		Math::degreesToRadians(_rotation.x),
		Math::degreesToRadians(_rotation.y),
		Math::degreesToRadians(_rotation.z));
	Matrix44 scalingMatrix = Matrix44::createScaling(_scaling.x, _scaling.y, _scaling.z);

	_modelMatrix = translationMatrix * rotationMatrix * scalingMatrix;
}

void BillboardEntity::setCameraFacingX(bool value)
{
	_isCameraFacingX = value;
}

void BillboardEntity::setCameraFacingY(bool value)
{
	_isCameraFacingY = value;
}

void BillboardEntity::setDiffuseMap(GLuint value)
{
	_diffuseMap = value;
}

void BillboardEntity::setTranslation(Vec3 value)
{
	_translation = value;
}

void BillboardEntity::setInitialRotation(Vec3 value)
{
	_initialRotation = value;
}

void BillboardEntity::setRotation(Vec3 value)
{
	_rotation = value;
}

void BillboardEntity::setScaling(Vec3 value)
{
	_scaling = value;
}

void BillboardEntity::setColor(Vec3 color)
{
	_color = color;
}

void BillboardEntity::translate(Vec3 value)
{
	_translation += value;
}

void BillboardEntity::rotate(Vec3 value)
{
	_rotation += value;
}

void BillboardEntity::scale(Vec3 value)
{
	_scaling += value;
}

void BillboardEntity::setTextContent(const string& text)
{
	_textContent = text;
}

void BillboardEntity::setFontPath(const string& fontPath)
{
	_fontPath = fontPath;
}

void BillboardEntity::setDiffuseMapPath(const string& diffuseMapPath)
{
	_diffuseMapPath = diffuseMapPath;
}

void BillboardEntity::setTransparent(bool value)
{
	_isTransparent = value;
}

void BillboardEntity::setDepthMapIncluded(bool value)
{
	_isDepthMapIncluded = value;
}

void BillboardEntity::playSpriteAnimation(int maxAnimationRepeats)
{
	_hasSpriteAnimation = true;
	_passedFrames = 0;
	_animationRepeats = 0;
	_maxAnimationRepeats = maxAnimationRepeats;
}

void BillboardEntity::stopSpriteAnimation()
{
	_hasSpriteAnimation = false;
}

void BillboardEntity::setSpriteRowIndex(int value)
{
	_spriteRowIndex = value;
}

void BillboardEntity::setSpriteColumnIndex(int value)
{
	_spriteColumnIndex = value;
}

void BillboardEntity::setTotalSpriteRows(int value)
{
	_totalSpriteRows = value;
}

void BillboardEntity::setTotalSpriteColumns(int value)
{
	_totalSpriteColumns = value;
}

void BillboardEntity::setMaxFramestep(int value)
{
	_maxFramestep = value;
}

void BillboardEntity::increasePassedFrames()
{
	_passedFrames++;
}

void BillboardEntity::resetPassedFrames()
{
	_passedFrames = 0;
}

void BillboardEntity::increaseAnimationRepeats()
{
	_animationRepeats++;
}

void BillboardEntity::setLightness(float value)
{
	_lightness = value;
}

void BillboardEntity::setMinHeight(float value)
{
	_minHeight = value;
}

void BillboardEntity::setMaxHeight(float value)
{
	_maxHeight = value;
}

const Matrix44 & BillboardEntity::getModelMatrix() const
{
	return _modelMatrix;
}

const GLuint BillboardEntity::getDiffuseMap() const
{
	return _diffuseMap;
}

const Vec3 BillboardEntity::getTranslation() const
{
	return _translation;
}

const Vec3 BillboardEntity::getInitialRotation() const
{
	return _initialRotation;
}

const Vec3 BillboardEntity::getRotation() const
{
	return _rotation;
}

const Vec3 BillboardEntity::getScaling() const
{
	return _scaling;
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

const float BillboardEntity::getLightness() const
{
	return _lightness;
}

const float BillboardEntity::getMinHeight() const
{
	return _minHeight;
}

const float BillboardEntity::getMaxHeight() const
{
	return _maxHeight;
}

const int BillboardEntity::getPassedFrames() const
{
	return _passedFrames;
}

const int BillboardEntity::getMaxFramestep() const
{
	return _maxFramestep;
}

const int BillboardEntity::getTotalSpriteRows() const
{
	return _totalSpriteRows;
}

const int BillboardEntity::getTotalSpriteColumns() const
{
	return _totalSpriteColumns;
}

const int BillboardEntity::getSpriteRowIndex() const
{
	return _spriteRowIndex;
}

const int BillboardEntity::getSpriteColumnIndex() const
{
	return _spriteColumnIndex;
}

const int BillboardEntity::getAnimationRepeats() const
{
	return _animationRepeats;
}

const int BillboardEntity::getMaxAnimationRepeats() const
{
	return _maxAnimationRepeats;
}

const bool BillboardEntity::isTransparent() const
{
	return _isTransparent;
}

const bool BillboardEntity::hasSpriteAnimation() const
{
	return _hasSpriteAnimation;
}

const bool BillboardEntity::isCameraFacingX() const
{
	return _isCameraFacingX;
}

const bool BillboardEntity::isCameraFacingY() const
{
	return _isCameraFacingY;
}

const bool BillboardEntity::isDepthMapIncluded() const
{
	return _isDepthMapIncluded;
}