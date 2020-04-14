#include "BillboardEntity.hpp"

void BillboardEntity::updateModelMatrix()
{
	_modelMatrix = mat4(1.0f);
	_modelMatrix = glm::translate(_modelMatrix, _translation);
	_modelMatrix = glm::rotate(_modelMatrix, glm::radians(_rotation.z), vec3(0.0f, 0.0f, 1.0f));
	_modelMatrix = glm::rotate(_modelMatrix, glm::radians(_rotation.y), vec3(0.0f, 1.0f, 0.0f));
	_modelMatrix = glm::rotate(_modelMatrix, glm::radians(_rotation.x), vec3(1.0f, 0.0f, 0.0f));
	_modelMatrix = glm::scale(_modelMatrix, _scaling);
}

void BillboardEntity::setCameraFacing(ivec2 val)
{
	_cameraFacing = val;
}

void BillboardEntity::setDiffuseMap(GLuint val)
{
	_diffuseMap = val;
}

void BillboardEntity::setTranslation(vec3 val)
{
	_translation = val;
}

void BillboardEntity::setInitialRotation(vec3 val)
{
	_initialRotation = val;
}

void BillboardEntity::setRotation(vec3 val)
{
	_rotation = val;
}

void BillboardEntity::setScaling(vec3 val)
{
	_scaling = val;
}

void BillboardEntity::setColor(vec3 color)
{
	_color = color;
}

void BillboardEntity::translate(vec3 val, float delta)
{
	_translation += val * delta;
}

void BillboardEntity::rotate(vec3 val, float delta)
{
	_rotation += val * delta;
}

void BillboardEntity::scale(vec3 val, float delta)
{
	_scaling += val * delta;
}

void BillboardEntity::setText(const string & text)
{
	_textContent = text;
}

void BillboardEntity::setFontPath(const string& fontPath)
{
	_fontPath = fontPath;
}

void BillboardEntity::setTransparent(bool val)
{
	_isTransparent = val;
}

void BillboardEntity::setSpriteAnimation(int rows, int columns, float maxDelta, int animationRepeats)
{
	_hasSpriteAnimation = true;
	_totalSpriteRows = rows;
	_totalSpriteColumns = columns;
	_maxDelta = maxDelta;
	_animationRepeats = 0;
	_maxAnimationRepeats = animationRepeats;
}

void BillboardEntity::setSpriteRowIndex(int val)
{
	_spriteRowIndex = val;
}

void BillboardEntity::setSpriteColumnIndex(int val)
{
	_spriteColumnIndex = val;
}

void BillboardEntity::addToDelta(float val)
{
	_totalDelta += val;
}

void BillboardEntity::resetDelta()
{
	_totalDelta = 0.0f;
}

void BillboardEntity::increaseAnimationRepeats()
{
	_animationRepeats++;
}

void BillboardEntity::setUvRepeat(float val)
{
	_uvRepeat = val;
}

const mat4 & BillboardEntity::getModelMatrix() const
{
	return _modelMatrix;
}

const GLuint BillboardEntity::getDiffuseMap() const
{
	return _diffuseMap;
}

const vec3 BillboardEntity::getTranslation() const
{
	return _translation;
}

const vec3 BillboardEntity::getInitialRotation() const
{
	return _initialRotation;
}

const vec3 BillboardEntity::getRotation() const
{
	return _rotation;
}

const vec3 BillboardEntity::getScaling() const
{
	return _scaling;
}

const vec3 BillboardEntity::getColor() const
{
	return _color;
}

const string & BillboardEntity::getText() const
{
	return _textContent;
}

const string& BillboardEntity::getFontPath() const
{
	return _fontPath;
}

const float BillboardEntity::getMaxDelta() const
{
	return _maxDelta;
}

const float BillboardEntity::getTotalDelta() const
{
	return _totalDelta;
}

const float BillboardEntity::getUvRepeat() const
{
	return _uvRepeat;
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

const ivec2 BillboardEntity::getCameraFacing() const
{
	return _cameraFacing;
}

const bool BillboardEntity::isTransparent() const
{
	return _isTransparent;
}

const bool BillboardEntity::hasSpriteAnimation() const
{
	return _hasSpriteAnimation;
}