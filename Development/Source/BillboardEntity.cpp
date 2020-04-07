#include <WE3D/BillboardEntity.hpp>

void BillboardEntity::updateModelMatrix()
{
	p_modelMatrix = mat4(1.0f);
	p_modelMatrix = glm::translate(p_modelMatrix, p_translation);
	p_modelMatrix = glm::rotate(p_modelMatrix, glm::radians(p_rotation.z), vec3(0.0f, 0.0f, 1.0f));
	p_modelMatrix = glm::rotate(p_modelMatrix, glm::radians(p_rotation.y), vec3(0.0f, 1.0f, 0.0f));
	p_modelMatrix = glm::rotate(p_modelMatrix, glm::radians(p_rotation.x), vec3(1.0f, 0.0f, 0.0f));
	p_modelMatrix = glm::scale(p_modelMatrix, p_scaling);
}

void BillboardEntity::setCameraFacing(ivec2 val)
{
	p_cameraFacing = val;
}

void BillboardEntity::setDiffuseMap(GLuint val)
{
	p_diffuseMap = val;
}

void BillboardEntity::setTranslation(vec3 val)
{
	p_translation = val;
}

void BillboardEntity::setInitialRotation(vec3 val)
{
	p_initialRotation = val;
}

void BillboardEntity::setRotation(vec3 val)
{
	p_rotation = val;
}

void BillboardEntity::setScaling(vec3 val)
{
	p_scaling = val;
}

void BillboardEntity::setColor(vec3 color)
{
	p_color = color;
}

void BillboardEntity::translate(vec3 val, float delta)
{
	p_translation += val * delta;
}

void BillboardEntity::rotate(vec3 val, float delta)
{
	p_rotation += val * delta;
}

void BillboardEntity::scale(vec3 val, float delta)
{
	p_scaling += val * delta;
}

void BillboardEntity::setText(const string & text)
{
	p_textContent = text;
}

void BillboardEntity::setTransparent(bool val)
{
	p_isTransparent = val;
}

void BillboardEntity::setSpriteAnimation(int rows, int columns, float maxDelta, int repeats)
{
	p_hasSpriteAnimation = true;
	p_totalSpriteRows = rows;
	p_totalSpriteColumns = columns;
	p_maxDelta = maxDelta;
	p_repeats = 0;
	p_maxRepeats = repeats;
}

void BillboardEntity::setSpriteRowIndex(int val)
{
	p_spriteRowIndex = val;
}

void BillboardEntity::setSpriteColumnIndex(int val)
{
	p_spriteColumnIndex = val;
}

void BillboardEntity::addToDelta(float val)
{
	p_totalDelta += val;
}

void BillboardEntity::resetDelta()
{
	p_totalDelta = 0.0f;
}

void BillboardEntity::increaseRepeats()
{
	p_repeats++;
}

const mat4 & BillboardEntity::getModelMatrix() const
{
	return p_modelMatrix;
}

const GLuint BillboardEntity::getDiffuseMap() const
{
	return p_diffuseMap;
}

const vec3 BillboardEntity::getTranslation() const
{
	return p_translation;
}

const vec3 BillboardEntity::getInitialRotation() const
{
	return p_initialRotation;
}

const vec3 BillboardEntity::getRotation() const
{
	return p_rotation;
}

const vec3 BillboardEntity::getScaling() const
{
	return p_scaling;
}

const vec3 BillboardEntity::getColor() const
{
	return p_color;
}

const string & BillboardEntity::getText() const
{
	return p_textContent;
}

const float BillboardEntity::getMaxDelta() const
{
	return p_maxDelta;
}

const float BillboardEntity::getTotalDelta() const
{
	return p_totalDelta;
}

const int BillboardEntity::getTotalSpriteRows() const
{
	return p_totalSpriteRows;
}

const int BillboardEntity::getTotalSpriteColumns() const
{
	return p_totalSpriteColumns;
}

const int BillboardEntity::getSpriteRowIndex() const
{
	return p_spriteRowIndex;
}

const int BillboardEntity::getSpriteColumnIndex() const
{
	return p_spriteColumnIndex;
}

const int BillboardEntity::getRepeats() const
{
	return p_repeats;
}

const int BillboardEntity::getMaxRepeats() const
{
	return p_maxRepeats;
}

const ivec2 BillboardEntity::getCameraFacing() const
{
	return p_cameraFacing;
}

const bool BillboardEntity::isTransparent() const
{
	return p_isTransparent;
}

const bool BillboardEntity::hasSpriteAnimation() const
{
	return p_hasSpriteAnimation;
}