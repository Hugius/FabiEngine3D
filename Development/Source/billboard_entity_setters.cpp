#include "billboard_entity.hpp"

#include <algorithm>
#include "logger.hpp"

using std::max;

void BillboardEntity::updateModelMatrix()
{
	// Identity matrix
	_modelMatrix = Matrix44(1.0f);

	// Translation matrix
	Matrix44 translationMatrix = Matrix44::createTranslation(_position.x, _position.y, _position.z);
	_modelMatrix = _modelMatrix * translationMatrix;

	// Rotation origin matrix - translate
	Matrix44 rotationOriginMatrix = Matrix44::createTranslation(0.0f, (_size.y / 2.0f), 0.0f);
	_modelMatrix = _modelMatrix * rotationOriginMatrix;

	// Rotation matrix
	Matrix44 rotationMatrix = Matrix44::createRotation(
		Math::degreesToRadians(_rotation.x),
		Math::degreesToRadians(_rotation.y),
		Math::degreesToRadians(_rotation.z));
	_modelMatrix = _modelMatrix * rotationMatrix;

	// Rotation origin matrix - translate back
	rotationOriginMatrix = Matrix44::createTranslation(0.0f, -(_size.y / 2.0f), 0.0f);
	_modelMatrix = _modelMatrix * rotationOriginMatrix;

	// Scaling matrix
	Matrix44 scalingMatrix = Matrix44::createScaling(_size.x, _size.y, _size.z);
	_modelMatrix = _modelMatrix * scalingMatrix;
}

void BillboardEntity::setRenderBuffer(shared_ptr<RenderBuffer> value)
{
	_renderBuffer = value;
}

void BillboardEntity::setCameraFacingX(bool value)
{
	_isFacingCameraX = value;
}

void BillboardEntity::setCameraFacingY(bool value)
{
	_isFacingCameraY = value;
}

void BillboardEntity::setDiffuseMap(TextureID value)
{
	_diffuseMap = value;
}

void BillboardEntity::setPosition(Vec3 value)
{
	_position = value;
}

void BillboardEntity::setInitialRotation(Vec3 value)
{
	_initialRotation = value;

	// Limit rotation
	_initialRotation.x = std::fmodf(_initialRotation.x, 360.0f);
	_initialRotation.y = std::fmodf(_initialRotation.y, 360.0f);
	_initialRotation.z = std::fmodf(_initialRotation.z, 360.0f);
}

void BillboardEntity::setRotation(Vec3 value)
{
	_rotation = value;

	// Limit rotation
	_rotation.x = std::fmodf(_rotation.x, 360.0f);
	_rotation.y = std::fmodf(_rotation.y, 360.0f);
	_rotation.z = std::fmodf(_rotation.z, 360.0f);
}

void BillboardEntity::setSize(Vec3 value)
{
	_size = Vec3(max(0.0f, value.x), max(0.0f, value.y), max(0.0f, value.z));
}

void BillboardEntity::setColor(Vec3 value)
{
	_color = Vec3(std::clamp(value.r, 0.0f, 1.0f), std::clamp(value.g, 0.0f, 1.0f), std::clamp(value.b, 0.0f, 1.0f));
}

void BillboardEntity::move(Vec3 value)
{
	_position += value;
}

void BillboardEntity::rotate(Vec3 value)
{
	_rotation += value;

	// Limit rotation
	_rotation.x = std::fmodf(_rotation.x, 360.0f);
	_rotation.y = std::fmodf(_rotation.y, 360.0f);
	_rotation.z = std::fmodf(_rotation.z, 360.0f);
}

void BillboardEntity::scale(Vec3 value)
{
	_size += value;
	_size = Vec3(max(0.0f, _size.x), max(0.0f, _size.y), max(0.0f, _size.z));
}

void BillboardEntity::setTextContent(const string& value)
{
	_textContent = value;
}

void BillboardEntity::setFontPath(const string& value)
{
	_fontPath = value;
}

void BillboardEntity::setDiffuseMapPath(const string& value)
{
	_diffuseMapPath = value;
}

void BillboardEntity::setTransparent(bool value)
{
	_isTransparent = value;
}

void BillboardEntity::setDepthMapIncluded(bool value)
{
	_isDepthMapIncluded = value;
}

void BillboardEntity::setReflected(bool value)
{
	_isReflected = value;
}

void BillboardEntity::setBright(bool value)
{
	_isBright = value;
}

void BillboardEntity::setWireFramed(bool value)
{
	_isWireFramed = value;
}

void BillboardEntity::setShadowed(bool value)
{
	_isShadowed = value;
}

void BillboardEntity::startSpriteAnimation(int loops)
{
	// Warning checking
	if (_isSpriteAnimationStarted)
	{
		Logger::throwWarning("Trying to start sprite animation on billboard with ID \"" + getID() + "\": animation already started!");
		return;
	}

	// Error checking
	if (loops < -1)
	{
		Logger::throwError("BillboardEntity::startSpriteAnimation() ---> invalid loops argument!");
	}

	// Set values
	_isSpriteAnimationStarted = true;
	_passedSpriteAnimationFrames = 0;
	_spriteAnimationLoops = 0;
	_maxSpriteAnimationLoops = loops;
}

void BillboardEntity::pauseSpriteAnimation()
{
	if (!_isSpriteAnimationStarted)
	{
		Logger::throwWarning("Trying to pause sprite animation on billboard with ID \"" + getID() + "\" animation not started!");
		return;
	}
	else if (_isSpriteAnimationPaused)
	{
		Logger::throwWarning("Trying to pause sprite animation on billboard with ID \"" + getID() + "\" animation already paused!");
		return;
	}

	_isSpriteAnimationPaused = true;
}

void BillboardEntity::resumeSpriteAnimation()
{
	if (!_isSpriteAnimationPaused)
	{
		Logger::throwWarning("Trying to resume sprite animation on billboard with ID \"" + getID() + "\" animation not paused!");
		return;
	}

	_isSpriteAnimationPaused = false;
}

void BillboardEntity::stopSpriteAnimation()
{
	if (!_isSpriteAnimationStarted)
	{
		Logger::throwWarning("Trying to stop sprite animation on billboard with ID \"" + getID() + "\" animation not started!");
		return;
	}

	_isSpriteAnimationStarted = false;
	_spriteAnimationRowIndex = 0;
	_spriteAnimationColumnIndex = 0;
}

void BillboardEntity::setSpriteAnimationRowIndex(unsigned int value)
{
	_spriteAnimationRowIndex = value;
}

void BillboardEntity::setSpriteAnimationColumnIndex(unsigned int value)
{
	_spriteAnimationColumnIndex = value;
}

void BillboardEntity::setTotalSpriteAnimationRows(unsigned int value)
{
	_totalSpriteAnimationRows = value;
}

void BillboardEntity::setTotalSpriteAnimationColumns(unsigned int value)
{
	_totalSpriteAnimationColumns = value;
}

void BillboardEntity::setMaxSpriteAnimationFramestep(unsigned int value)
{
	_maxSpriteAnimationFramestep = value;
}

void BillboardEntity::increasePassedSpriteAnimationFrames()
{
	_passedSpriteAnimationFrames++;
}

void BillboardEntity::resetPassedSpriteAnimationFrames()
{
	_passedSpriteAnimationFrames = 0;
}

void BillboardEntity::increaseSpriteAnimationLoops()
{
	_spriteAnimationLoops++;
}

void BillboardEntity::setLightness(float value)
{
	_lightness = max(0.0f, value);
}

void BillboardEntity::setInversion(float value)
{
	_inversion = std::clamp(value, 0.0f, 1.0f);
}

void BillboardEntity::setAlpha(float value)
{
	_alpha = value;
}

void BillboardEntity::setMinHeight(float value)
{
	_minHeight = value;
}

void BillboardEntity::setMaxHeight(float value)
{
	_maxHeight = value;
}