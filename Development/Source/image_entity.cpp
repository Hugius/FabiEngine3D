#include "image_entity.hpp"

#include <algorithm>

void ImageEntity::updateModelMatrix()
{
	Matrix44 translationMatrix = Matrix44::createTranslation(_translation.x, _translation.y, 0.0f);
	Matrix44 rotationMatrix = Matrix44::createRotationX(Math::degreesToRadians(_rotation));
	Matrix44 scalingMatrix = Matrix44::createScaling(_scaling.x, _scaling.y, 1.0f);

	_modelMatrix = translationMatrix * rotationMatrix * scalingMatrix;
}

void ImageEntity::setTexture(GLuint value)
{
	_texture = value;
}

void ImageEntity::setColor(Vec3 value)
{
	_color = Vec3(std::clamp(value.r, 0.0f, 1.0f), std::clamp(value.g, 0.0f, 1.0f), std::clamp(value.b, 0.0f, 1.0f));
}

void ImageEntity::setMirroredHorizontally(bool value)
{
	_mirroredHorizontally = value;
}

void ImageEntity::setMirroredVertically(bool value)
{
	_mirroredVertically = value;
}

void ImageEntity::setAlpha(float value)
{
	_alpha = std::max(0.0f, value);
}

void ImageEntity::setCentered(bool value)
{
	_isCentered = value;
}

void ImageEntity::setTranslation(Vec2 value)
{
	_translation = value;
}

void ImageEntity::setRotation(float value)
{
	_rotation = value;

	// Limit rotation
	_rotation = std::fmodf(_rotation, 360.0f);
}

void ImageEntity::setScaling(Vec2 value)
{
	_scaling = Vec2(std::max(0.0f, value.x), std::max(0.0f, value.y));
}

void ImageEntity::translate(Vec2 value)
{
	_translation += value;
}

void ImageEntity::rotate(float value)
{
	_rotation += value;

	// Limit rotation
	_rotation = std::fmodf(_rotation, 360.0f);
}

void ImageEntity::scale(Vec2 value)
{
	_scaling += value;
	_scaling = Vec2(std::max(0.0f, _scaling.x), std::max(0.0f, _scaling.y));
}

void ImageEntity::setMinPosition(Vec2 value)
{
	_minPosition = value;
}

void ImageEntity::setMaxPosition(Vec2 value)
{
	_maxPosition = value;
}

void ImageEntity::setDepth(unsigned int value)
{
	_depth = value;
}

void ImageEntity::playSpriteAnimation(int maxAnimationRepeats)
{
	_isSpriteAnimationPlaying = true;
	_passedSpriteAnimationFrames = 0;
	_spriteAnimationRepeats = 0;
	_maxSpriteAnimationRepeats = maxAnimationRepeats;
}

void ImageEntity::pauseSpriteAnimation()
{
	_isSpriteAnimationPaused = true;
}

void ImageEntity::resumeSpriteAnimation()
{
	_isSpriteAnimationPaused = false;
}

void ImageEntity::stopSpriteAnimationAnimation()
{
	_isSpriteAnimationPlaying = false;
}

void ImageEntity::setSpriteAnimationRowIndex(int value)
{
	_spriteAnimationRowIndex = std::max(0, value);
}

void ImageEntity::setSpriteAnimationColumnIndex(int value)
{
	_spriteAnimationColumnIndex = std::max(0, value);
}

void ImageEntity::setTotalSpriteAnimationRows(int value)
{
	_totalSpriteAnimationRows = std::max(0, value);
}

void ImageEntity::setTotalSpriteAnimationColumns(int value)
{
	_totalSpriteAnimationColumns = std::max(0, value);
}

void ImageEntity::setMaxSpriteAnimationFramestep(int value)
{
	_maxSpriteAnimationFramestep = std::max(0, value);
}

void ImageEntity::increasePassedSpriteAnimationFrames()
{
	_passedSpriteAnimationFrames++;
}

void ImageEntity::resetPassedSpriteAnimationFrames()
{
	_passedSpriteAnimationFrames = 0;
}

void ImageEntity::increaseSpriteAnimationRepeats()
{
	_spriteAnimationRepeats++;
}

const bool ImageEntity::isSpriteAnimationPlaying() const
{
	return _isSpriteAnimationPlaying;
}

const bool ImageEntity::isSpriteAnimationPaused() const
{
	return _isSpriteAnimationPaused;
}

const int ImageEntity::getPassedSpriteAnimationFrames() const
{
	return _passedSpriteAnimationFrames;
}

const int ImageEntity::getMaxSpriteAnimationFramestep() const
{
	return _maxSpriteAnimationFramestep;
}

const int ImageEntity::getTotalSpriteAnimationRows() const
{
	return _totalSpriteAnimationRows;
}

const int ImageEntity::getTotalSpriteAnimationColumns() const
{
	return _totalSpriteAnimationColumns;
}

const int ImageEntity::getSpriteAnimationRowIndex() const
{
	return _spriteAnimationRowIndex;
}

const int ImageEntity::getSpriteAnimationColumnIndex() const
{
	return _spriteAnimationColumnIndex;
}

const int ImageEntity::getSpriteAnimationRepeats() const
{
	return _spriteAnimationRepeats;
}

const int ImageEntity::getMaxSpriteAnimationRepeats() const
{
	return _maxSpriteAnimationRepeats;
}

const GLuint ImageEntity::getTexture() const
{
	return _texture;
}

const Vec3 ImageEntity::getColor() const
{
	return _color;
}

const float ImageEntity::getAlpha() const
{
	return _alpha;
}

const bool ImageEntity::isMirroredHorizonally() const
{
	return _mirroredHorizontally;
}

const bool ImageEntity::isMirroredVertically() const
{
	return _mirroredVertically;
}

const bool ImageEntity::hasTexture() const
{
	return (_texture != 0);
}

const bool ImageEntity::isCentered() const
{
	return _isCentered;
}

const Matrix44 ImageEntity::getModelMatrix() const
{
	return _modelMatrix;
}

const Vec2 ImageEntity::getTranslation() const
{
	return _translation;
}

const float ImageEntity::getRotation() const
{
	return _rotation;
}

const Vec2 ImageEntity::getScaling() const
{
	return _scaling;
}

const Vec2 ImageEntity::getMinPosition() const
{
	return _minPosition;
}

const Vec2 ImageEntity::getMaxPosition() const
{
	return _maxPosition;
}

const unsigned int ImageEntity::getDepth() const
{
	return _depth;
}

void ImageEntity::setDepthEntity(bool value)
{
	_isDepthEntity = value;
}

const bool ImageEntity::isDepthEntity() const
{
	return _isDepthEntity;
}
