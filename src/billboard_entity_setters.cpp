#include "billboard_entity.hpp"
#include "logger.hpp"

#include <algorithm>

using std::clamp;
using std::max;

void BillboardEntity::updateTransformation()
{
	// Position target
	if(_position != _positionTarget)
	{
		// Update position
		auto speedMultiplier = Math::normalize(_positionTarget - _position);
		_position += (speedMultiplier * _positionTargetSpeed);

		// Correct position
		if(fabsf(_positionTarget.x - _position.x) <= _positionTargetSpeed)
		{
			_position.x = _positionTarget.x;
		}
		if(fabsf(_positionTarget.y - _position.y) <= _positionTargetSpeed)
		{
			_position.y = _positionTarget.y;
		}
		if(fabsf(_positionTarget.z - _position.z) <= _positionTargetSpeed)
		{
			_position.z = _positionTarget.z;
		}
	}

	// Rotation target
	if(_rotation != _rotationTarget)
	{
		// Update rotation
		auto difference = Math::calculateDifference(_rotation, _rotationTarget);
		Vec3 multiplier = Vec3(
			((difference.x < 180.0f) ? 1.0f : -1.0f),
			((difference.y < 180.0f) ? 1.0f : -1.0f),
			((difference.z < 180.0f) ? 1.0f : -1.0f));
		Vec3 speed = (Vec3(_rotationTargetSpeed) * multiplier);
		_rotation.x += ((_rotation.x < _rotationTarget.x) ? speed.x : (_rotation.x > _rotationTarget.x) ? -speed.x : 0.0f);
		_rotation.y += ((_rotation.y < _rotationTarget.y) ? speed.y : (_rotation.y > _rotationTarget.y) ? -speed.y : 0.0f);
		_rotation.z += ((_rotation.z < _rotationTarget.z) ? speed.z : (_rotation.z > _rotationTarget.z) ? -speed.z : 0.0f);

		// Correct rotation
		_rotation = Vec3(Math::limitAngle(_rotation.x), Math::limitAngle(_rotation.y), Math::limitAngle(_rotation.z));
		if(Math::calculateAngleDifference(_rotation.x, _rotationTarget.x) <= _rotationTargetSpeed)
		{
			_rotation.x = _rotationTarget.x;
		}
		if(Math::calculateAngleDifference(_rotation.y, _rotationTarget.y) <= _rotationTargetSpeed)
		{
			_rotation.y = _rotationTarget.y;
		}
		if(Math::calculateAngleDifference(_rotation.z, _rotationTarget.z) <= _rotationTargetSpeed)
		{
			_rotation.z = _rotationTarget.z;
		}
	}

	// Size target
	if(_size != _sizeTarget)
	{
		// Update size
		auto speedMultiplier = Math::normalize(_sizeTarget - _size);
		_size += (speedMultiplier * _sizeTargetSpeed);

		// Correct size
		_size = Vec2(max(0.0f, _size.x), max(0.0f, _size.y));
		if(fabsf(_sizeTarget.x - _size.x) <= _sizeTargetSpeed)
		{
			_size.x = _positionTarget.x;
		}
		if(fabsf(_sizeTarget.y - _size.y) <= _sizeTargetSpeed)
		{
			_size.y = _positionTarget.y;
		}
	}
}

void BillboardEntity::updateTransformationMatrix()
{
	// Identity matrix
	_transformationMatrix = Matrix44(1.0f);

	// Translation matrix
	Matrix44 translationMatrix = Math::createTranslationMatrix(_position.x, _position.y, _position.z);
	_transformationMatrix = (_transformationMatrix * translationMatrix);

	// Rotation origin matrix - translate
	Matrix44 rotationOriginMatrix = Math::createTranslationMatrix(0.0f, (_size.y / 2.0f), 0.0f);
	_transformationMatrix = (_transformationMatrix * rotationOriginMatrix);

	// Rotation matrix
	Matrix44 rotationMatrix = Math::createRotationMatrix(
		Math::convertToRadians(_rotation.x),
		Math::convertToRadians(_rotation.y),
		Math::convertToRadians(_rotation.z), DirectionOrder::YXZ);
	_transformationMatrix = (_transformationMatrix * rotationMatrix);

	// Rotation origin matrix - translate back
	rotationOriginMatrix = Math::createTranslationMatrix(0.0f, -(_size.y / 2.0f), 0.0f);
	_transformationMatrix = (_transformationMatrix * rotationOriginMatrix);

	// Scaling matrix
	Matrix44 scalingMatrix = Math::createScalingMatrix(_size.x, _size.y, 1.0f);
	_transformationMatrix = (_transformationMatrix * scalingMatrix);
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

void BillboardEntity::setDiffuseMap(TextureID value, bool isTextual)
{
	_diffuseMap = value;
	_isTextual = isTextual;
}

void BillboardEntity::setEmissionMap(TextureID value)
{
	_emissionMap = value;
}

void BillboardEntity::setPosition(Vec3 value)
{
	_position = value;
	_positionTarget = value;
}

void BillboardEntity::setRotation(Vec3 value)
{
	_rotation = Vec3(Math::limitAngle(value.x), Math::limitAngle(value.y), Math::limitAngle(value.z));
	_rotationTarget = Vec3(Math::limitAngle(value.x), Math::limitAngle(value.y), Math::limitAngle(value.z));
}

void BillboardEntity::setSize(Vec2 value)
{
	_size = Vec2(max(0.0f, value.x), max(0.0f, value.y));
	_sizeTarget = Vec2(max(0.0f, value.x), max(0.0f, value.y));
}

void BillboardEntity::move(Vec3 value)
{
	_position += value;
	_positionTarget += value;
}

void BillboardEntity::rotate(Vec3 value)
{
	_rotation += value;
	_rotationTarget += value;
	_rotation = Vec3(Math::limitAngle(_rotation.x), Math::limitAngle(_rotation.y), Math::limitAngle(_rotation.z));
	_rotationTarget = Vec3(Math::limitAngle(_rotationTarget.x), Math::limitAngle(_rotationTarget.y), Math::limitAngle(_rotationTarget.z));
}

void BillboardEntity::scale(Vec2 value)
{
	_size += value;
	_sizeTarget += value;
	_size = Vec2(max(0.0f, _size.x), max(0.0f, _size.y));
	_sizeTarget = Vec2(max(0.0f, _sizeTarget.x), max(0.0f, _sizeTarget.y));
}

void BillboardEntity::moveTo(Vec3 target, float speed)
{
	_positionTarget = target;
	_positionTargetSpeed = speed;
}

void BillboardEntity::rotateTo(Vec3 target, float speed)
{
	_rotationTarget = Vec3(Math::limitAngle(target.x), Math::limitAngle(target.y), Math::limitAngle(target.z));
	_rotationTargetSpeed = speed;
}

void BillboardEntity::scaleTo(Vec2 target, float speed)
{
	_sizeTarget = Vec2(max(0.0f, target.x), max(0.0f, target.y));
	_sizeTargetSpeed = speed;
}

void BillboardEntity::setColor(Vec3 value)
{
	_color = Vec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void BillboardEntity::setWireframeColor(Vec3 value)
{
	_wireframeColor = Vec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
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

void BillboardEntity::setEmissionMapPath(const string& value)
{
	_emissionMapPath = value;
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

void BillboardEntity::setWireframed(bool value)
{
	_isWireframed = value;
}

void BillboardEntity::setShadowed(bool value)
{
	_isShadowed = value;
}

void BillboardEntity::startSpriteAnimation(int loops)
{
	if(_isSpriteAnimationStarted)
	{
		Logger::throwError("BillboardEntity::startSpriteAnimation::1");
	}
	if(loops < -1)
	{
		Logger::throwError("BillboardEntity::startSpriteAnimation::2");
	}

	_isSpriteAnimationStarted = true;
	_passedSpriteAnimationFrames = 0;
	_spriteAnimationLoops = 0;
	_maxSpriteAnimationLoops = loops;
}

void BillboardEntity::pauseSpriteAnimation()
{
	if(!_isSpriteAnimationStarted)
	{
		Logger::throwError("BillboardEntity::pauseSpriteAnimation::1");
	}
	else if(_isSpriteAnimationPaused)
	{
		Logger::throwError("BillboardEntity::pauseSpriteAnimation::2");
	}

	_isSpriteAnimationPaused = true;
}

void BillboardEntity::resumeSpriteAnimation()
{
	if(!_isSpriteAnimationPaused)
	{
		Logger::throwError("BillboardEntity::resumeSpriteAnimation");
	}

	_isSpriteAnimationPaused = false;
}

void BillboardEntity::stopSpriteAnimation()
{
	if(!_isSpriteAnimationStarted)
	{
		Logger::throwError("BillboardEntity::stopSpriteAnimation");
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

void BillboardEntity::setTotalSpriteAnimationRowCount(unsigned int value)
{
	_totalSpriteAnimationRowCount = value;
}

void BillboardEntity::setTotalSpriteAnimationColumnCount(unsigned int value)
{
	_totalSpriteAnimationColumnCount = value;
}

void BillboardEntity::setSpriteAnimationFramestep(unsigned int value)
{
	_spriteAnimationFramestep = value;
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

void BillboardEntity::setTransparency(float value)
{
	_transparency = clamp(value, 0.0f, 1.0f);
}

void BillboardEntity::setMinHeight(float value)
{
	_minHeight = value;
}

void BillboardEntity::setMaxHeight(float value)
{
	_maxHeight = value;
}

void BillboardEntity::setTextureRepeat(float value)
{
	_textureRepeat = max(0.0f, value);
}

void BillboardEntity::setEmissionIntensity(float value)
{
	_emissionIntensity = value;
}