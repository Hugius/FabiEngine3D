#include "gui_entity.hpp"

void GuiEntity::updateModelMatrix()
{
	Matrix44 translationMatrix = Matrix44::createTranslation(_translation.x, _translation.y, 0.0f);
	Matrix44 rotationMatrix = Matrix44::createRotationZ(Math::degreesToRadians(_rotation));
	Matrix44 scalingMatrix = Matrix44::createScaling(_scaling.x, _scaling.y, 1.0f);

	_modelMatrix = translationMatrix * rotationMatrix * scalingMatrix;
}

void GuiEntity::setDiffuseMap(GLuint diffuseMap)
{
	_diffuseMap = diffuseMap;
}

void GuiEntity::setColor(Vec3 color)
{
	_color = color;
}

void GuiEntity::setMirroredHorizontally(bool val)
{
	_mirroredHorizontally = val;
}

void GuiEntity::setMirroredVertically(bool val)
{
	_mirroredVertically = val;
}

void GuiEntity::setAlpha(float val)
{
	_alpha = val;
}

void GuiEntity::setCentered(bool val)
{
	_isCentered = val;
}

void GuiEntity::setTranslation(Vec2 val)
{
	_translation = val;
}

void GuiEntity::setRotation(float val)
{
	_rotation = val;
}

void GuiEntity::setScaling(Vec2 val)
{
	_scaling = val;
}

void GuiEntity::translate(Vec2 val)
{
	_translation += val;
}

void GuiEntity::rotate(float val)
{
	_rotation += val;
}

void GuiEntity::scale(Vec2 val)
{
	_scaling += val;
}

void GuiEntity::setMinPosition(Vec2 val)
{
	_minPosition = val;
}

void GuiEntity::setMaxPosition(Vec2 val)
{
	_maxPosition = val;
}

void GuiEntity::setDepth(unsigned int val)
{
	_depth = val;
}

const GLuint GuiEntity::getDiffuseMap() const
{
	return _diffuseMap;
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

void GuiEntity::setDepthEntity(bool val)
{
	_isDepthEntity = val;
}

const bool GuiEntity::isDepthEntity() const
{
	return _isDepthEntity;
}
