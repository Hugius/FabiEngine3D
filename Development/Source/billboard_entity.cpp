#include "billboard_entity.hpp"
#include <iostream>
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

void BillboardEntity::translate(vec3 val)
{
	_translation += val;
}

void BillboardEntity::rotate(vec3 val)
{
	_rotation += val;
}

void BillboardEntity::scale(vec3 val)
{
	_scaling += val;
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

void BillboardEntity::playSpriteAnimation(int rows, int columns, int maxAnimationRepeats, int frameStep)
{
	_hasSpriteAnimation = true;
	_totalSpriteRows = rows;
	_totalSpriteColumns = columns;
	_totalPassedFrames = 0;
	_maxPassedFrames = frameStep;
	_animationRepeats = 0;
	_maxAnimationRepeats = maxAnimationRepeats;
}

void BillboardEntity::stopSpriteAnimation()
{
	_hasSpriteAnimation = false;
}

void BillboardEntity::setSpriteRowIndex(int val)
{
	_spriteRowIndex = val;
}

void BillboardEntity::setSpriteColumnIndex(int val)
{
	_spriteColumnIndex = val;
}

void BillboardEntity::setMaxPassedFrames(int val)
{
	_maxPassedFrames = val;
}

void BillboardEntity::increasePassedFrames()
{
	_totalPassedFrames++;
}

void BillboardEntity::resetPassedFrames()
{
	_totalPassedFrames = 0;
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

const float BillboardEntity::getUvRepeat() const
{
	return _uvRepeat;
}

const int BillboardEntity::getPassedFrames() const
{
	return _totalPassedFrames;
}

const int BillboardEntity::getMaxPassedFrames() const
{
	return _maxPassedFrames;
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