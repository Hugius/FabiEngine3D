#include "gui_entity.hpp"

void GuiEntity::updateModelMatrix()
{
	Matrix44 translationMatrix = Matrix44::createTranslation(_translation.x, _translation.y, 0.0f);
	Matrix44 rotationMatrix = Matrix44::createRotationZ(Math::degreesToRadians(_rotation));
	Matrix44 scalingMatrix = Matrix44::createScaling(_scaling.x, _scaling.y, 1.0f);

	_modelMatrix = translationMatrix * rotationMatrix * scalingMatrix;
}

void GuiEntity::setTexture(GLuint texture)
{
	_texture = texture;
}

void GuiEntity::setColor(Vec3 color)
{
	_color = color;
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
	_alpha = value;
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
	_scaling = value;
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
