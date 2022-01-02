#include "model_entity.hpp"
#include "logger.hpp"

#include <algorithm>

using std::max;
using std::clamp;

void ModelEntity::createPart(const string& ID)
{
	_parts.push_back(ModelEntityPart(ID));
}

void ModelEntity::updateTransformation()
{
	if(_basePosition != _basePositionTarget)
	{
		auto speedMultiplier = Math::normalize(_basePositionTarget - _basePosition);
		_basePosition += (speedMultiplier * _basePositionTargetSpeed);
		_correctPositionTarget(_basePosition, _basePositionTarget, _basePositionTargetSpeed);
	}

	if(_baseRotation != _baseRotationTarget)
	{
		auto difference = Math::calculateDifference(_baseRotation, _baseRotationTarget);
		fvec3 multiplier = fvec3(
			((difference.x < 180.0f) ? 1.0f : -1.0f),
			((difference.y < 180.0f) ? 1.0f : -1.0f),
			((difference.z < 180.0f) ? 1.0f : -1.0f));
		fvec3 speed = (fvec3(_baseRotationTargetSpeed) * multiplier);
		_baseRotation.x += ((_baseRotation.x < _baseRotationTarget.x) ? speed.x : (_baseRotation.x > _baseRotationTarget.x) ? -speed.x : 0.0f);
		_baseRotation.y += ((_baseRotation.y < _baseRotationTarget.y) ? speed.y : (_baseRotation.y > _baseRotationTarget.y) ? -speed.y : 0.0f);
		_baseRotation.z += ((_baseRotation.z < _baseRotationTarget.z) ? speed.z : (_baseRotation.z > _baseRotationTarget.z) ? -speed.z : 0.0f);
		_correctRotationTarget(_baseRotation, _baseRotationTarget, _baseRotationTargetSpeed);
	}

	if(_baseSize != _baseSizeTarget)
	{
		auto speedMultiplier = Math::normalize(_baseSizeTarget - _baseSize);
		_baseSize += (speedMultiplier * _baseSizeTargetSpeed);
		_correctSizeTarget(_baseSize, _baseSizeTarget, _baseSizeTargetSpeed);
	}

	for(auto& part : _parts)
	{
		if(part.position != part.positionTarget)
		{
			auto speedMultiplier = Math::normalize(part.positionTarget - part.position);
			part.position += (speedMultiplier * part.positionTargetSpeed);
			_correctPositionTarget(part.position, part.positionTarget, part.positionTargetSpeed);
		}

		if(part.rotation != part.rotationTarget)
		{
			auto difference = Math::calculateDifference(part.rotation, part.rotationTarget);
			fvec3 multiplier = fvec3(
				((difference.x < 180.0f) ? 1.0f : -1.0f),
				((difference.y < 180.0f) ? 1.0f : -1.0f),
				((difference.z < 180.0f) ? 1.0f : -1.0f));
			fvec3 speed = (fvec3(part.rotationTargetSpeed) * multiplier);
			fvec3 rotation = part.rotation;
			fvec3 target = part.rotationTarget;
			part.rotation.x += ((rotation.x < target.x) ? speed.x : (rotation.x > target.x) ? -speed.x : 0.0f);
			part.rotation.y += ((rotation.y < target.y) ? speed.y : (rotation.y > target.y) ? -speed.y : 0.0f);
			part.rotation.z += ((rotation.z < target.z) ? speed.z : (rotation.z > target.z) ? -speed.z : 0.0f);
			_correctRotationTarget(part.rotation, part.rotationTarget, part.rotationTargetSpeed);
		}

		if(part.size != part.sizeTarget)
		{
			auto speedMultiplier = Math::normalize(part.sizeTarget - part.size);
			part.size += (speedMultiplier * part.sizeTargetSpeed);
			_correctSizeTarget(part.size, part.sizeTarget, part.sizeTargetSpeed);
		}
	}
}

void ModelEntity::updateTransformationMatrix()
{
	for(size_t i = 0; i < _parts.size(); i++)
	{
		_parts[i].transformationMatrix = mat44(1.0f);

		auto baseTranslationMatrix = Math::createTranslationMatrix(_basePosition.x, _basePosition.y, _basePosition.z);
		_parts[i].transformationMatrix = (_parts[i].transformationMatrix * baseTranslationMatrix);

		auto translationMatrix = Math::createTranslationMatrix(_parts[i].position.x, _parts[i].position.y, _parts[i].position.z);
		_parts[i].transformationMatrix = (_parts[i].transformationMatrix * translationMatrix);

		auto baseRotationOriginMatrix = Math::createTranslationMatrix(_baseRotationOrigin.x, _baseRotationOrigin.y, _baseRotationOrigin.z);
		_parts[i].transformationMatrix = (_parts[i].transformationMatrix * baseRotationOriginMatrix);

		auto baseRotationMatrix = Math::createRotationMatrix(
			Math::convertToRadians(_baseRotation.x),
			Math::convertToRadians(_baseRotation.y),
			Math::convertToRadians(_baseRotation.z), _rotationOrder);
		_parts[i].transformationMatrix = (_parts[i].transformationMatrix * baseRotationMatrix);

		baseRotationOriginMatrix = Math::createTranslationMatrix(-_baseRotationOrigin.x, -_baseRotationOrigin.y, -_baseRotationOrigin.z);
		_parts[i].transformationMatrix = (_parts[i].transformationMatrix * baseRotationOriginMatrix);

		auto rotationOriginMatrix = Math::createTranslationMatrix(_parts[i].rotationOrigin.x, _parts[i].rotationOrigin.y, _parts[i].rotationOrigin.z);
		_parts[i].transformationMatrix = (_parts[i].transformationMatrix * rotationOriginMatrix);

		auto rotationMatrix = Math::createRotationMatrix(
			Math::convertToRadians(_parts[i].rotation.x),
			Math::convertToRadians(_parts[i].rotation.y),
			Math::convertToRadians(_parts[i].rotation.z), _rotationOrder);
		_parts[i].transformationMatrix = (_parts[i].transformationMatrix * rotationMatrix);

		rotationOriginMatrix = Math::createTranslationMatrix(-_parts[i].rotationOrigin.x, -_parts[i].rotationOrigin.y, -_parts[i].rotationOrigin.z);
		_parts[i].transformationMatrix = (_parts[i].transformationMatrix * rotationOriginMatrix);

		auto baseScalingMatrix = Math::createScalingMatrix(_baseSize.x, _baseSize.y, _baseSize.z);
		_parts[i].transformationMatrix = (_parts[i].transformationMatrix * baseScalingMatrix);

		auto scalingMatrix = Math::createScalingMatrix(_parts[i].size.x, _parts[i].size.y, _parts[i].size.z);
		_parts[i].transformationMatrix = (_parts[i].transformationMatrix * scalingMatrix);
	}
}

void ModelEntity::setVertexBuffer(const string& partID, shared_ptr<VertexBuffer> value)
{
	_parts[_getPartIndex(partID)].vertexBuffer = value;
}

void ModelEntity::setDiffuseMap(const string& partID, shared_ptr<TextureBuffer> value)
{
	_parts[_getPartIndex(partID)].diffuseMap = value;
}

void ModelEntity::setEmissionMap(const string& partID, shared_ptr<TextureBuffer> value)
{
	_parts[_getPartIndex(partID)].emissionMap = value;
}

void ModelEntity::setSpecularMap(const string& partID, shared_ptr<TextureBuffer> value)
{
	_parts[_getPartIndex(partID)].specularMap = value;
}

void ModelEntity::setReflectionMap(const string& partID, shared_ptr<TextureBuffer> value)
{
	_parts[_getPartIndex(partID)].reflectionMap = value;
}

void ModelEntity::setNormalMap(const string& partID, shared_ptr<TextureBuffer> value)
{
	_parts[_getPartIndex(partID)].normalMap = value;
}

void ModelEntity::setBasePosition(fvec3 value)
{
	_basePosition = value;
	_basePositionTarget = _basePosition;
}

void ModelEntity::setBaseRotation(fvec3 value)
{
	_baseRotation = fvec3(Math::limitAngle(value.x), Math::limitAngle(value.y), Math::limitAngle(value.z));
	_baseRotationTarget = fvec3(Math::limitAngle(value.x), Math::limitAngle(value.y), Math::limitAngle(value.z));
}

void ModelEntity::setBaseRotationOrigin(fvec3 value)
{
	_baseRotationOrigin = value;
}

void ModelEntity::setBaseSize(fvec3 value)
{
	_baseSize = fvec3(max(0.0f, value.x), max(0.0f, value.y), max(0.0f, value.z));
	_baseSizeTarget = fvec3(max(0.0f, value.x), max(0.0f, value.y), max(0.0f, value.z));
}

void ModelEntity::setPartPosition(const string& partID, fvec3 value)
{
	_parts[_getPartIndex(partID)].position = value;
	_parts[_getPartIndex(partID)].positionTarget = value;
}

void ModelEntity::setPartRotation(const string& partID, fvec3 value)
{
	_parts[_getPartIndex(partID)].rotation = fvec3(Math::limitAngle(value.x), Math::limitAngle(value.y), Math::limitAngle(value.z));
	_parts[_getPartIndex(partID)].rotationTarget = fvec3(Math::limitAngle(value.x), Math::limitAngle(value.y), Math::limitAngle(value.z));
}

void ModelEntity::setPartRotationOrigin(const string& partID, fvec3 value)
{
	_parts[_getPartIndex(partID)].rotationOrigin = value;
}

void ModelEntity::setPartSize(const string& partID, fvec3 value)
{
	_parts[_getPartIndex(partID)].size = fvec3(max(0.0f, value.x), max(0.0f, value.y), max(0.0f, value.z));
	_parts[_getPartIndex(partID)].sizeTarget = fvec3(max(0.0f, value.x), max(0.0f, value.y), max(0.0f, value.z));
}

void ModelEntity::moveBase(fvec3 value)
{
	_basePosition += value;
	_basePositionTarget += value;
}

void ModelEntity::rotateBase(fvec3 value)
{
	_baseRotation += value;
	_baseRotationTarget += value;
	_baseRotation = fvec3(Math::limitAngle(_baseRotation.x), Math::limitAngle(_baseRotation.y), Math::limitAngle(_baseRotation.z));
	_baseRotationTarget = fvec3(Math::limitAngle(_baseRotationTarget.x), Math::limitAngle(_baseRotationTarget.y), Math::limitAngle(_baseRotationTarget.z));
}

void ModelEntity::scaleBase(fvec3 value)
{
	_baseSize += value;
	_baseSizeTarget += value;
	_baseSize = fvec3(max(0.0f, _baseSize.x), max(0.0f, _baseSize.y), max(0.0f, _baseSize.z));
	_baseSizeTarget = fvec3(max(0.0f, _baseSizeTarget.x), max(0.0f, _baseSizeTarget.y), max(0.0f, _baseSizeTarget.z));
}

void ModelEntity::movePart(const string& partID, fvec3 value)
{
	_parts[_getPartIndex(partID)].position += value;
	_parts[_getPartIndex(partID)].positionTarget += value;
}

void ModelEntity::rotatePart(const string& partID, fvec3 value)
{
	fvec3& rotation = _parts[_getPartIndex(partID)].rotation;
	fvec3& rotationTarget = _parts[_getPartIndex(partID)].rotationTarget;
	rotation += value;
	rotationTarget += value;
	rotation = fvec3(Math::limitAngle(rotation.x), Math::limitAngle(rotation.y), Math::limitAngle(rotation.z));
	rotationTarget = fvec3(Math::limitAngle(rotationTarget.x), Math::limitAngle(rotationTarget.y), Math::limitAngle(rotationTarget.z));
}

void ModelEntity::scalePart(const string& partID, fvec3 value)
{
	fvec3& size = _parts[_getPartIndex(partID)].size;
	fvec3& sizeTarget = _parts[_getPartIndex(partID)].sizeTarget;
	size += value;
	sizeTarget += value;
	size = fvec3(max(0.0f, size.x), max(0.0f, size.y), max(0.0f, size.z));
	sizeTarget = fvec3(max(0.0f, sizeTarget.x), max(0.0f, sizeTarget.y), max(0.0f, sizeTarget.z));
}

void ModelEntity::moveBaseTo(fvec3 target, float speed)
{
	_basePositionTarget = target;
	_basePositionTargetSpeed = max(0.0f, speed);
}

void ModelEntity::rotateBaseTo(fvec3 target, float speed)
{
	_baseRotationTarget = fvec3(Math::limitAngle(target.x), Math::limitAngle(target.y), Math::limitAngle(target.z));
	_baseRotationTargetSpeed = max(0.0f, speed);
}

void ModelEntity::scaleBaseTo(fvec3 target, float speed)
{
	_baseSizeTarget = fvec3(max(0.0f, target.x), max(0.0f, target.y), max(0.0f, target.z));
	_baseSizeTargetSpeed = max(0.0f, speed);
}

void ModelEntity::movePartTo(const string& partID, fvec3 target, float speed)
{
	_parts[_getPartIndex(partID)].positionTarget = target;
	_parts[_getPartIndex(partID)].positionTargetSpeed = max(0.0f, speed);
}

void ModelEntity::rotatePartTo(const string& partID, fvec3 target, float speed)
{
	_parts[_getPartIndex(partID)].rotationTarget = fvec3(Math::limitAngle(target.x), Math::limitAngle(target.y), Math::limitAngle(target.z));
	_parts[_getPartIndex(partID)].rotationTargetSpeed = max(0.0f, speed);
}

void ModelEntity::scalePartTo(const string& partID, fvec3 target, float speed)
{
	_parts[_getPartIndex(partID)].sizeTarget = fvec3(max(0.0f, target.x), max(0.0f, target.y), max(0.0f, target.z));
	_parts[_getPartIndex(partID)].sizeTargetSpeed = max(0.0f, speed);
}

void ModelEntity::setColor(const string& partID, fvec3 value)
{
	_parts[_getPartIndex(partID)].color = fvec3(clamp(value.x, 0.0f, 1.0f), clamp(value.y, 0.0f, 1.0f), clamp(value.z, 0.0f, 1.0f));
}

void ModelEntity::setWireframeColor(const string& partID, fvec3 value)
{
	_parts[_getPartIndex(partID)].wireframeColor = fvec3(clamp(value.x, 0.0f, 1.0f), clamp(value.y, 0.0f, 1.0f), clamp(value.z, 0.0f, 1.0f));
}

void ModelEntity::setMeshPath(const string& value)
{
	_meshPath = value;
}

void ModelEntity::setLevelOfDetailSize(fvec3 value)
{
	_levelOfDetailSize = value;
}

void ModelEntity::setDiffuseMapPath(const string& partID, const string& value)
{
	_parts[_getPartIndex(partID)].diffuseMapPath = value;
}

void ModelEntity::setEmissionMapPath(const string& partID, const string& value)
{
	_parts[_getPartIndex(partID)].emissionMapPath = value;
}

void ModelEntity::setSpecularMapPath(const string& partID, const string& value)
{
	_parts[_getPartIndex(partID)].specularMapPath = value;
}

void ModelEntity::setReflectionMapPath(const string& partID, const string& value)
{
	_parts[_getPartIndex(partID)].reflectionMapPath = value;
}

void ModelEntity::setNormalMapPath(const string& partID, const string& value)
{
	_parts[_getPartIndex(partID)].normalMapPath = value;
}

void ModelEntity::setLevelOfDetailEntityID(const string& value)
{
	_levelOfDetailEntityID = value;
}

void ModelEntity::setPreviousReflectionEntityID(const string& value)
{
	_previousReflectionEntityID = value;
}

void ModelEntity::setCurrentReflectionEntityID(const string& value)
{
	_currentReflectionEntityID = value;
}

void ModelEntity::setCubeReflectionMixValue(float value)
{
	_cubeReflectionMixValue = clamp(value, 0.0f, 1.0f);
}

void ModelEntity::setReflectivity(const string& partID, float value)
{
	_parts[_getPartIndex(partID)].reflectivity = clamp(value, 0.0f, 1.0f);
}

void ModelEntity::setFaceCulled(bool value)
{
	_isFaceCulled = value;
}

void ModelEntity::setRotationOrder(DirectionOrder value)
{
	_rotationOrder = value;
}

void ModelEntity::setReflectionType(const string& partID, ReflectionType value)
{
	_parts[_getPartIndex(partID)].reflectionType = value;
}

void ModelEntity::setSpecular(const string& partID, bool value)
{
	_parts[_getPartIndex(partID)].isSpecular = value;
}

void ModelEntity::setReflective(const string& partID, bool value)
{
	_parts[_getPartIndex(partID)].isReflective = value;
}

void ModelEntity::setShadowed(bool value)
{
	_isShadowed = value;
}

void ModelEntity::setReflected(bool value)
{
	_isReflected = value;
}

void ModelEntity::setFrozen(bool value)
{
	_isFrozen = value;
}

void ModelEntity::setDepthMapIncluded(bool value)
{
	_isDepthMapIncluded = value;
}

void ModelEntity::setLevelOfDetailed(bool value)
{
	_isLevelOfDetailed = value;
}

void ModelEntity::setWireframed(const string& partID, bool value)
{
	_parts[_getPartIndex(partID)].isWireframed = value;
}

void ModelEntity::setBright(bool value)
{
	_isBright = value;
}

void ModelEntity::deleteParts()
{
	_parts.clear();
}

void ModelEntity::setLightness(const string& partID, float value)
{
	_parts[_getPartIndex(partID)].lightness = max(0.0f, value);
}

void ModelEntity::setSpecularShininess(const string& partID, float value)
{
	_parts[_getPartIndex(partID)].specularShininess = max(0.0f, value);
}

void ModelEntity::setSpecularIntensity(const string& partID, float value)
{
	_parts[_getPartIndex(partID)].specularIntensity = max(0.0f, value);
}

void ModelEntity::setMinHeight(float value)
{
	_minHeight = value;
}

void ModelEntity::setMaxHeight(float value)
{
	_maxHeight = value;
}

void ModelEntity::setLevelOfDetailDistance(float value)
{
	_levelOfDetailDistance = value;
}

void ModelEntity::setTransparency(const string& partID, float value)
{
	_parts[_getPartIndex(partID)].transparency = clamp(value, 0.0f, 1.0f);
}

void ModelEntity::setTextureRepeat(const string& partID, float value)
{
	_parts[_getPartIndex(partID)].textureRepeat = max(0.0f, value);
}

void ModelEntity::setEmissionIntensity(const string& partID, float value)
{
	_parts[_getPartIndex(partID)].emissionIntensity = max(0.0f, value);
}

void ModelEntity::_correctPositionTarget(fvec3& current, fvec3 target, float speed)
{
	if(fabsf(target.x - current.x) <= speed)
	{
		current.x = target.x;
	}

	if(fabsf(target.y - current.y) <= speed)
	{
		current.y = target.y;
	}

	if(fabsf(target.z - current.z) <= speed)
	{
		current.z = target.z;
	}
}

void ModelEntity::_correctRotationTarget(fvec3& current, fvec3 target, float speed)
{
	current = fvec3(Math::limitAngle(current.x), Math::limitAngle(current.y), Math::limitAngle(current.z));

	if(Math::calculateAngleDifference(current.x, target.x) <= speed)
	{
		current.x = target.x;
	}

	if(Math::calculateAngleDifference(current.y, target.y) <= speed)
	{
		current.y = target.y;
	}

	if(Math::calculateAngleDifference(current.z, target.z) <= speed)
	{
		current.z = target.z;
	}
}

void ModelEntity::_correctSizeTarget(fvec3& current, fvec3 target, float speed)
{
	current = fvec3(max(0.0f, current.x), max(0.0f, current.y), max(0.0f, current.z));

	if(fabsf(target.x - current.x) <= speed)
	{
		current.x = target.x;
	}

	if(fabsf(target.y - current.y) <= speed)
	{
		current.y = target.y;
	}

	if(fabsf(target.z - current.z) <= speed)
	{
		current.z = target.z;
	}
}