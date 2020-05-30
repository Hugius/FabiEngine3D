#include <GLM/gtc/matrix_transform.hpp>

#include "gui_entity.hpp"

void GuiEntity::updateModelMatrix()
{
	_modelMatrix = mat4(1.0f);
	_modelMatrix = glm::translate(_modelMatrix, vec3(_translation, 0.0f));
	_modelMatrix = glm::rotate(_modelMatrix, glm::radians(_rotation), vec3(0.0f, 0.0f, 1.0f));
	_modelMatrix = glm::scale(_modelMatrix, vec3(_scaling, 1.0f));
}

void GuiEntity::setDiffuseMap(GLuint diffuseMap)
{
	_diffuseMap = diffuseMap;
}

void GuiEntity::setColor(vec3 color)
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

void GuiEntity::setTranslation(vec2 val)
{
	_translation = val;
}

void GuiEntity::setRotation(float val)
{
	_rotation = val;
}

void GuiEntity::setScaling(vec2 val)
{
	_scaling = val;
}

void GuiEntity::translate(vec2 val)
{
	_translation += val;
}

void GuiEntity::rotate(float val)
{
	_rotation += val;
}

void GuiEntity::scale(vec2 val)
{
	_scaling += val;
}

void GuiEntity::setMinPosition(vec2 val)
{
	_minPosition = val;
}

void GuiEntity::setMaxPosition(vec2 val)
{
	_maxPosition = val;
}

const GLuint GuiEntity::getDiffuseMap() const
{
	return _diffuseMap;
}

const vec3 GuiEntity::getColor() const
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

const mat4 GuiEntity::getModelMatrix() const
{
	return _modelMatrix;
}

const vec2 GuiEntity::getTranslation() const
{
	return _translation;
}

const float GuiEntity::getRotation() const
{
	return _rotation;
}

const vec2 GuiEntity::getScaling() const
{
	return _scaling;
}

const vec2 GuiEntity::getMinPosition() const
{
	return _minPosition;
}

const vec2 GuiEntity::getMaxPosition() const
{
	return _maxPosition;
}

void GuiEntity::setDepthEntity(bool val)
{
	_isDepthEntity = val;
}

const bool GuiEntity::isDepthEntity() const
{
	return _isDepthEntity;
}
