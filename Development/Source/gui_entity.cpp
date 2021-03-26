#include "gui_entity.hpp"

#include <algorithm>

void GuiEntity::updateModelMatrix()
{
	Matrix44 translationMatrix = Matrix44::createTranslation(_translation.x, _translation.y, 0.0f);
	Matrix44 rotationMatrix = Matrix44::createRotationX(Math::degreesToRadians(_rotation));
	Matrix44 scalingMatrix = Matrix44::createScaling(_scaling.x, _scaling.y, 1.0f);

	_modelMatrix = translationMatrix * rotationMatrix * scalingMatrix;
}

void GuiEntity::setTexture(GLuint value)
{
	_texture = value;
}

void GuiEntity::setColor(Vec3 value)
{
	_color = Vec3(std::clamp(value.r, 0.0f, 1.0f), std::clamp(value.g, 0.0f, 1.0f), std::clamp(value.b, 0.0f, 1.0f));
}

void GuiEntity::setMirroredHorizontally(bool value)
{
	_mirroredHorizontally = value;
}

void GuiEntity::setMirroredVertically(bool value)
{
	_mirroredVertically = value;
}

void GuiEntity::setAlpha(float value)
{
	_alpha = std::max(0.0f, value);
}

void GuiEntity::setCentered(bool value)
{
	_isCentered = value;
}

void GuiEntity::setTranslation(Vec2 value)
{
	_translation = value;
}

void GuiEntity::setRotation(float value)
{
	_rotation = value;

	// Limit rotation
	_rotation = std::fmodf(_rotation, 360.0f);
}

void GuiEntity::setScaling(Vec2 value)
{
	_scaling = Vec2(std::max(0.0f, value.x), std::max(0.0f, value.y));
}

void GuiEntity::translate(Vec2 value)
{
	_translation += value;
}

void GuiEntity::rotate(float value)
{
	_rotation += value;

	// Limit rotation
	_rotation = std::fmodf(_rotation, 360.0f);
}

void GuiEntity::scale(Vec2 value)
{
	_scaling += value;
	_scaling = Vec2(std::max(0.0f, _scaling.x), std::max(0.0f, _scaling.y));
}

void GuiEntity::setMinPosition(Vec2 value)
{
	_minPosition = value;
}

void GuiEntity::setMaxPosition(Vec2 value)
{
	_maxPosition = value;
}

void GuiEntity::setDepth(unsigned int value)
{
	_depth = value;
}

void GuiEntity::playSpriteAnimation(int maxAnimationRepeats)
{
	_isSpriteAnimationPlaying = true;
	_passedSpriteAnimationFrames = 0;
	_spriteAnimationRepeats = 0;
	_maxSpriteAnimationRepeats = maxAnimationRepeats;
}

void GuiEntity::pauseSpriteAnimation()
{
	_isSpriteAnimationPaused = true;
}

void GuiEntity::resumeSpriteAnimation()
{
	_isSpriteAnimationPaused = false;
}

void GuiEntity::stopSpriteAnimationAnimation()
{
	_isSpriteAnimationPlaying = false;
}

void GuiEntity::setSpriteAnimationRowIndex(int value)
{
	_spriteAnimationRowIndex = std::max(0, value);
}

void GuiEntity::setSpriteAnimationColumnIndex(int value)
{
	_spriteAnimationColumnIndex = std::max(0, value);
}

void GuiEntity::setTotalSpriteAnimationRows(int value)
{
	_totalSpriteAnimationRows = std::max(0, value);
}

void GuiEntity::setTotalSpriteAnimationColumns(int value)
{
	_totalSpriteAnimationColumns = std::max(0, value);
}

void GuiEntity::setMaxSpriteAnimationFramestep(int value)
{
	_maxSpriteAnimationFramestep = std::max(0, value);
}

void GuiEntity::increasePassedSpriteAnimationFrames()
{
	_passedSpriteAnimationFrames++;
}

void GuiEntity::resetPassedSpriteAnimationFrames()
{
	_passedSpriteAnimationFrames = 0;
}

void GuiEntity::increaseSpriteAnimationRepeats()
{
	_spriteAnimationRepeats++;
}

const bool GuiEntity::isSpriteAnimationPlaying() const
{
	return _isSpriteAnimationPlaying;
}

const bool GuiEntity::isSpriteAnimationPaused() const
{
	return _isSpriteAnimationPaused;
}

const int GuiEntity::getPassedSpriteAnimationFrames() const
{
	return _passedSpriteAnimationFrames;
}

const int GuiEntity::getMaxSpriteAnimationFramestep() const
{
	return _maxSpriteAnimationFramestep;
}

const int GuiEntity::getTotalSpriteAnimationRows() const
{
	return _totalSpriteAnimationRows;
}

const int GuiEntity::getTotalSpriteAnimationColumns() const
{
	return _totalSpriteAnimationColumns;
}

const int GuiEntity::getSpriteAnimationRowIndex() const
{
	return _spriteAnimationRowIndex;
}

const int GuiEntity::getSpriteAnimationColumnIndex() const
{
	return _spriteAnimationColumnIndex;
}

const int GuiEntity::getSpriteAnimationRepeats() const
{
	return _spriteAnimationRepeats;
}

const int GuiEntity::getMaxSpriteAnimationRepeats() const
{
	return _maxSpriteAnimationRepeats;
}

const GLuint GuiEntity::getTexture() const
{
	return _texture;
}

const Vec3 GuiEntity::getColor() const
{
	return _color;
}

const float GuiEntity::getAlpha() const
{
	return _alpha;
}

const bool GuiEntity::isMirroredHorizonally() const
{
	return _mirroredHorizontally;
}

const bool GuiEntity::isMirroredVertically() const
{
	return _mirroredVertically;
}

const bool GuiEntity::hasTexture() const
{
	return (_texture != 0);
}

const bool GuiEntity::isCentered() const
{
	return _isCentered;
}

const Matrix44 GuiEntity::getModelMatrix() const
{
	return _modelMatrix;
}

const Vec2 GuiEntity::getTranslation() const
{
	return _translation;
}

const float GuiEntity::getRotation() const
{
	return _rotation;
}

const Vec2 GuiEntity::getScaling() const
{
	return _scaling;
}

const Vec2 GuiEntity::getMinPosition() const
{
	return _minPosition;
}

const Vec2 GuiEntity::getMaxPosition() const
{
	return _maxPosition;
}

const unsigned int GuiEntity::getDepth() const
{
	return _depth;
}

void GuiEntity::setDepthEntity(bool value)
{
	_isDepthEntity = value;
}

const bool GuiEntity::isDepthEntity() const
{
	return _isDepthEntity;
}
