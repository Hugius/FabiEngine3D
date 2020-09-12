#include "billboard_entity.hpp"

void BillboardEntity::updateModelMatrix()
{
	_modelMatrix = mat4(1.0f);
	_modelMatrix = glm::translate(_modelMatrix, _translation);
	_modelMatrix = glm::rotate(_modelMatrix, glm::radians(_rotation.z), vec3(0.0f, 0.0f, 1.0f));
	_modelMatrix = glm::rotate(_modelMatrix, glm::radians(_rotation.y), vec3(0.0f, 1.0f, 0.0f));
	_modelMatrix = glm::rotate(_modelMatrix, glm::radians(_rotation.x), vec3(1.0f, 0.0f, 0.0f));
	_modelMatrix = glm::scale(_modelMatrix, _scaling);
}

void BillboardEntity::setCameraFacingX(bool val)
{
	_isCameraFacingX = val;
}

void BillboardEntity::setCameraFacingY(bool val)
{
	_isCameraFacingY = val;
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

void BillboardEntity::setTransparent(bool val)
{
	_isTransparent = val;
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

void BillboardEntity::setSpriteRowIndex(int val)
{
	_spriteRowIndex = val;
}

void BillboardEntity::setSpriteColumnIndex(int val)
{
	_spriteColumnIndex = val;
}

void BillboardEntity::setTotalSpriteRows(int val)
{
	_totalSpriteRows = val;
}

void BillboardEntity::setTotalSpriteColumns(int val)
{
	_totalSpriteColumns = val;
}

void BillboardEntity::setMaxFramestep(int val)
{
	_maxFramestep = val;
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

void BillboardEntity::setUvRepeat(float val)
{
	_uvRepeat = val;
}

void BillboardEntity::setMaxY(float val)
{
	_maxY = val;
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

const float BillboardEntity::getUvRepeat() const
{
	return _uvRepeat;
}

const float BillboardEntity::getMaxY() const
{
	return _maxY;
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