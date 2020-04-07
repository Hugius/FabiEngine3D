#include <GLM/gtc/matrix_transform.hpp>

#include <WE3D/GuiEntity.hpp>

void GuiEntity::updateModelMatrix()
{
	p_modelMatrix = mat4(1.0f);
	p_modelMatrix = glm::translate(p_modelMatrix, vec3(p_translation, 0.0f));
	p_modelMatrix = glm::rotate(p_modelMatrix, glm::radians(p_rotation), vec3(0.0f, 0.0f, 1.0f));
	p_modelMatrix = glm::scale(p_modelMatrix, vec3(p_scaling, 1.0f));
}

void GuiEntity::setDiffuseMap(GLuint diffuseMap)
{
	p_diffuseMap = diffuseMap;
}

void GuiEntity::setColor(vec3 color)
{
	p_color = color;
}

void GuiEntity::setMirroredHorizontally(bool val)
{
	p_mirroredHorizontally = val;
}

void GuiEntity::setMirroredVertically(bool val)
{
	p_mirroredVertically = val;
}

void GuiEntity::setTranslation(vec2 val)
{
	p_translation = val;
}

void GuiEntity::setRotation(float val)
{
	p_rotation = val;
}

void GuiEntity::setScaling(vec2 val)
{
	p_scaling = val;
}

void GuiEntity::translate(vec2 val, float delta)
{
	p_translation += val * delta;
}

void GuiEntity::rotate(float val, float delta)
{
	p_rotation += val * delta;
}

void GuiEntity::scale(vec2 val, float delta)
{
	p_scaling += val * delta;
}

const GLuint GuiEntity::getDiffuseMap() const
{
	return p_diffuseMap;
}

const vec3 GuiEntity::getColor() const
{
	return p_color;
}

const bool GuiEntity::isMirroredHorizonally() const
{
	return p_mirroredHorizontally;
}

const bool GuiEntity::isMirroredVertically() const
{
	return p_mirroredVertically;
}

const mat4 GuiEntity::getModelMatrix() const
{
	return p_modelMatrix;
}

const vec2 GuiEntity::getTranslation() const
{
	return p_translation;
}

const float GuiEntity::getRotation() const
{
	return p_rotation;
}

const vec2 GuiEntity::getScaling() const
{
	return p_scaling;
}

void GuiEntity::setDepthEntity(bool val)
{
	p_isDepthEntity = val;
}

const bool GuiEntity::isDepthEntity() const
{
	return p_isDepthEntity;
}
