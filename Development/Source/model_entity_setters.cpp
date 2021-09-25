#include "model_entity.hpp"
#include "logger.hpp"

#include <algorithm>

using std::max;
using std::clamp;

void ModelEntity::createPart(const string& ID)
{
	_parts.push_back(PartData(ID));
}

void ModelEntity::updateTransformation()
{
	// Base position target
	if (_basePosition != _basePositionTarget)
	{
		auto speedMultiplier = Math::normalizeVector(_basePositionTarget - _basePosition);
		_basePosition += (speedMultiplier * _basePositionTargetSpeed);
		_correctPositionTarget(_basePosition, _basePositionTarget, _basePositionTargetSpeed);
	}

	// Base rotation target
	if (_baseRotation != _baseRotationTarget)
	{
		auto difference = Math::calculateVectorDifference(_baseRotation, _baseRotationTarget);
		Vec3 multiplier = Vec3(
			((difference.x < 180.0f) ? 1.0f : -1.0f),
			((difference.y < 180.0f) ? 1.0f : -1.0f),
			((difference.z < 180.0f) ? 1.0f : -1.0f));
		Vec3 speed = (Vec3(_baseRotationTargetSpeed) * multiplier);
		_baseRotation.x += ((_baseRotation.x < _baseRotationTarget.x) ? speed.x : (_baseRotation.x > _baseRotationTarget.x) ? -speed.x : 0.0f);
		_baseRotation.y += ((_baseRotation.y < _baseRotationTarget.y) ? speed.y : (_baseRotation.y > _baseRotationTarget.y) ? -speed.y : 0.0f);
		_baseRotation.z += ((_baseRotation.z < _baseRotationTarget.z) ? speed.z : (_baseRotation.z > _baseRotationTarget.z) ? -speed.z : 0.0f);
		_correctRotationTarget(_baseRotation, _baseRotationTarget, _baseRotationTargetSpeed);
	}

	// Base size target
	if (_baseSize != _baseSizeTarget)
	{
		auto speedMultiplier = Math::normalizeVector(_baseSizeTarget - _baseSize);
		_baseSize += (speedMultiplier * _baseSizeTargetSpeed);
		_correctSizeTarget(_baseSize, _baseSizeTarget, _baseSizeTargetSpeed);
	}

	// Iterate through parts
	for (auto& part : _parts)
	{
		// Local position target
		if (part.localPosition != part.localPositionTarget)
		{
			auto speedMultiplier = Math::normalizeVector(part.localPositionTarget - part.localPosition);
			part.localPosition += (speedMultiplier * part.localPositionTargetSpeed);
			_correctPositionTarget(part.localPosition, part.localPositionTarget, part.localPositionTargetSpeed);
		}

		// Local rotation target
		if (part.localRotation != part.localRotationTarget)
		{
			auto difference = Math::calculateVectorDifference(part.localRotation, part.localRotationTarget);
			Vec3 multiplier = Vec3(
				((difference.x < 180.0f) ? 1.0f : -1.0f),
				((difference.y < 180.0f) ? 1.0f : -1.0f),
				((difference.z < 180.0f) ? 1.0f : -1.0f));
			Vec3 speed = (Vec3(part.localRotationTargetSpeed) * multiplier);
			Vec3 rotation = part.localRotation;
			Vec3 target = part.localRotationTarget;
			part.localRotation.x += ((rotation.x < target.x) ? speed.x : (rotation.x > target.x) ? -speed.x : 0.0f);
			part.localRotation.y += ((rotation.y < target.y) ? speed.y : (rotation.y > target.y) ? -speed.y : 0.0f);
			part.localRotation.z += ((rotation.z < target.z) ? speed.z : (rotation.z > target.z) ? -speed.z : 0.0f);
			_correctRotationTarget(part.localRotation, part.localRotationTarget, part.localRotationTargetSpeed);
		}

		// Local size target
		if (part.localSize != part.localSizeTarget)
		{
			auto speedMultiplier = Math::normalizeVector(part.localSizeTarget - part.localSize);
			part.localSize += (speedMultiplier * part.localSizeTargetSpeed);
			_correctSizeTarget(part.localSize, part.localSizeTarget, part.localSizeTargetSpeed);
		}
	}
}

void ModelEntity::updateTransformationMatrix()
{
	for (size_t i = 0; i < _parts.size(); i++)
	{
		// Identity matrix
		_parts[i].transformationMatrix = Matrix44(1.0f);

		// Base translation matrix
		Matrix44 baseTranslationMatrix = Math::createTranslationMatrix(_basePosition.x, _basePosition.y, _basePosition.z);
		_parts[i].transformationMatrix = (_parts[i].transformationMatrix * baseTranslationMatrix);

		// Translation matrix
		Matrix44 translationMatrix = Math::createTranslationMatrix(_parts[i].localPosition.x, _parts[i].localPosition.y, _parts[i].localPosition.z);
		_parts[i].transformationMatrix = (_parts[i].transformationMatrix * translationMatrix);

		// Base rotation origin matrix - translate
		Matrix44 baseRotationOriginMatrix = Math::createTranslationMatrix(_baseRotationOrigin.x, _baseRotationOrigin.y, _baseRotationOrigin.z);
		_parts[i].transformationMatrix = (_parts[i].transformationMatrix * baseRotationOriginMatrix);

		// Base rotation matrix
		Matrix44 baseRotationMatrix = Math::createRotationMatrix(
			Math::convertToRadians(_baseRotation.x),
			Math::convertToRadians(_baseRotation.y),
			Math::convertToRadians(_baseRotation.z), Direction::Y);
		_parts[i].transformationMatrix = (_parts[i].transformationMatrix * baseRotationMatrix);

		// Base rotation origin matrix - translate back
		baseRotationOriginMatrix = Math::createTranslationMatrix(-_baseRotationOrigin.x, -_baseRotationOrigin.y, -_baseRotationOrigin.z);
		_parts[i].transformationMatrix = (_parts[i].transformationMatrix * baseRotationOriginMatrix);

		// Rotation origin matrix - translate
		Matrix44 rotationOriginMatrix = Math::createTranslationMatrix(_parts[i].localRotationOrigin.x, _parts[i].localRotationOrigin.y, _parts[i].localRotationOrigin.z);
		_parts[i].transformationMatrix = (_parts[i].transformationMatrix * rotationOriginMatrix);

		// Rotation matrix
		Matrix44 rotationMatrix = Math::createRotationMatrix(
			Math::convertToRadians(_parts[i].localRotation.x),
			Math::convertToRadians(_parts[i].localRotation.y),
			Math::convertToRadians(_parts[i].localRotation.z), Direction::X);
		_parts[i].transformationMatrix = (_parts[i].transformationMatrix * rotationMatrix);

		// Rotation origin matrix - translate back
		rotationOriginMatrix = Math::createTranslationMatrix(-_parts[i].localRotationOrigin.x, -_parts[i].localRotationOrigin.y, -_parts[i].localRotationOrigin.z);
		_parts[i].transformationMatrix = (_parts[i].transformationMatrix * rotationOriginMatrix);

		// Base scaling matrix
		Matrix44 baseScalingMatrix = Math::createScalingMatrix(_baseSize.x, _baseSize.y, _baseSize.z);
		_parts[i].transformationMatrix = (_parts[i].transformationMatrix * baseScalingMatrix);

		// Scaling matrix
		Matrix44 scalingMatrix = Math::createScalingMatrix(_parts[i].localSize.x, _parts[i].localSize.y, _parts[i].localSize.z);
		_parts[i].transformationMatrix = (_parts[i].transformationMatrix * scalingMatrix);
	}
}

void ModelEntity::setRenderBuffer(const string& partID, shared_ptr<RenderBuffer> value)
{
	_parts[_getPartIndex(partID)].renderBuffer = value;
}

void ModelEntity::setDiffuseMap(const string& partID, TextureID value)
{
	_parts[_getPartIndex(partID)].diffuseMap = value;
}

void ModelEntity::setEmissionMap(const string& partID, TextureID value)
{
	_parts[_getPartIndex(partID)].emissionMap = value;
}

void ModelEntity::setSpecularMap(const string& partID, TextureID value)
{
	_parts[_getPartIndex(partID)].specularMap = value;
}

void ModelEntity::setReflectionMap(const string& partID, TextureID value)
{
	_parts[_getPartIndex(partID)].reflectionMap = value;
}

void ModelEntity::setNormalMap(const string& partID, TextureID value)
{
	_parts[_getPartIndex(partID)].normalMap = value;
}

void ModelEntity::setPosition(const string& partID, Vec3 value)
{
	if ((_parts.size() == 1) || ((_parts.size() > 1) && partID.empty()))
	{
		_basePosition = value;
		_basePositionTarget = _basePosition;
	}
	else
	{
		_parts[_getPartIndex(partID)].localPosition = value;
		_parts[_getPartIndex(partID)].localPositionTarget = value;
	}
}

void ModelEntity::setRotation(const string& partID, Vec3 value)
{
	if ((_parts.size() == 1) || ((_parts.size() > 1) && partID.empty()))
	{
		_baseRotation = Vec3(Math::limitAngle(value.x), Math::limitAngle(value.y), Math::limitAngle(value.z));
		_baseRotationTarget = Vec3(Math::limitAngle(value.x), Math::limitAngle(value.y), Math::limitAngle(value.z));
	}
	else
	{
		_parts[_getPartIndex(partID)].localRotation = Vec3(Math::limitAngle(value.x), Math::limitAngle(value.y), Math::limitAngle(value.z));
		_parts[_getPartIndex(partID)].localRotationTarget = Vec3(Math::limitAngle(value.x), Math::limitAngle(value.y), Math::limitAngle(value.z));
	}
}

void ModelEntity::setRotationOrigin(const string& partID, Vec3 value)
{
	if ((_parts.size() == 1) || ((_parts.size() > 1) && partID.empty()))
	{
		_baseRotationOrigin = value;
	}
	else
	{
		_parts[_getPartIndex(partID)].localRotationOrigin = value;
	}
}

void ModelEntity::setSize(const string& partID, Vec3 value)
{
	if ((_parts.size() == 1) || ((_parts.size() > 1) && partID.empty()))
	{
		_baseSize = Vec3(max(0.0f, value.x), max(0.0f, value.y), max(0.0f, value.z));
		_baseSizeTarget = Vec3(max(0.0f, value.x), max(0.0f, value.y), max(0.0f, value.z));
	}
	else
	{
		_parts[_getPartIndex(partID)].localSize = Vec3(max(0.0f, value.x), max(0.0f, value.y), max(0.0f, value.z));
		_parts[_getPartIndex(partID)].localSizeTarget = Vec3(max(0.0f, value.x), max(0.0f, value.y), max(0.0f, value.z));
	}
}

void ModelEntity::move(const string& partID, Vec3 value)
{
	if ((_parts.size() == 1) || ((_parts.size() > 1) && partID.empty()))
	{
		_basePosition += value;
		_basePositionTarget += value;
	}
	else
	{
		_parts[_getPartIndex(partID)].localPosition += value;
		_parts[_getPartIndex(partID)].localPositionTarget += value;
	}
}

void ModelEntity::rotate(const string& partID, Vec3 value)
{
	if ((_parts.size() == 1) || ((_parts.size() > 1) && partID.empty()))
	{
		_baseRotation += value;
		_baseRotationTarget += value;
		_baseRotation = Vec3(Math::limitAngle(_baseRotation.x), Math::limitAngle(_baseRotation.y), Math::limitAngle(_baseRotation.z));
		_baseRotationTarget = Vec3(Math::limitAngle(_baseRotationTarget.x), Math::limitAngle(_baseRotationTarget.y), Math::limitAngle(_baseRotationTarget.z));
	}
	else
	{
		Vec3& localRotation = _parts[_getPartIndex(partID)].localRotation;
		Vec3& localRotationTarget = _parts[_getPartIndex(partID)].localRotationTarget;
		localRotation += value;
		localRotationTarget += value;
		localRotation = Vec3(Math::limitAngle(localRotation.x), Math::limitAngle(localRotation.y), Math::limitAngle(localRotation.z));
		localRotationTarget = Vec3(Math::limitAngle(localRotationTarget.x), Math::limitAngle(localRotationTarget.y), Math::limitAngle(localRotationTarget.z));

	}
}

void ModelEntity::scale(const string& partID, Vec3 value)
{
	if ((_parts.size() == 1) || ((_parts.size() > 1) && partID.empty()))
	{
		_baseSize += value;
		_baseSizeTarget += value;
		_baseSize = Vec3(max(0.0f, _baseSize.x), max(0.0f, _baseSize.y), max(0.0f, _baseSize.z));
		_baseSizeTarget = Vec3(max(0.0f, _baseSizeTarget.x), max(0.0f, _baseSizeTarget.y), max(0.0f, _baseSizeTarget.z));
	}
	else
	{
		Vec3& localSize = _parts[_getPartIndex(partID)].localSize;
		Vec3& localSizeTarget = _parts[_getPartIndex(partID)].localSizeTarget;
		localSize += value;
		localSizeTarget += value;
		localSize = Vec3(max(0.0f, localSize.x), max(0.0f, localSize.y), max(0.0f, localSize.z));
		localSizeTarget = Vec3(max(0.0f, localSizeTarget.x), max(0.0f, localSizeTarget.y), max(0.0f, localSizeTarget.z));
	}
}

void ModelEntity::moveTo(const string& partID, Vec3 target, float speed)
{
	if ((_parts.size() == 1) || ((_parts.size() > 1) && partID.empty()))
	{
		_basePositionTarget = target;
		_basePositionTargetSpeed = fabsf(speed);
	}
	else
	{
		_parts[_getPartIndex(partID)].localPositionTarget = target;
		_parts[_getPartIndex(partID)].localPositionTargetSpeed = fabsf(speed);
	}
}

void ModelEntity::rotateTo(const string& partID, Vec3 target, float speed)
{
	if ((_parts.size() == 1) || ((_parts.size() > 1) && partID.empty()))
	{
		_baseRotationTarget = Vec3(Math::limitAngle(target.x), Math::limitAngle(target.y), Math::limitAngle(target.z));
		_baseRotationTargetSpeed = fabsf(speed);
	}
	else
	{
		_parts[_getPartIndex(partID)].localRotationTarget = Vec3(Math::limitAngle(target.x), Math::limitAngle(target.y), Math::limitAngle(target.z));
		_parts[_getPartIndex(partID)].localRotationTargetSpeed = fabsf(speed);
	}
}

void ModelEntity::scaleTo(const string& partID, Vec3 target, float speed)
{
	if ((_parts.size() == 1) || ((_parts.size() > 1) && partID.empty()))
	{
		_baseSizeTarget = Vec3(max(0.0f, target.x), max(0.0f, target.y), max(0.0f, target.z));
		_baseSizeTargetSpeed = fabsf(speed);
	}
	else
	{
		_parts[_getPartIndex(partID)].localSizeTarget = Vec3(max(0.0f, target.x), max(0.0f, target.y), max(0.0f, target.z));
		_parts[_getPartIndex(partID)].localSizeTargetSpeed = fabsf(speed);
	}
}

void ModelEntity::setColor(const string& partID, Vec3 value)
{
	if (partID.empty())
	{
		for (auto& part : _parts)
		{
			part.color = Vec3(clamp(value.x, 0.0f, 1.0f), clamp(value.y, 0.0f, 1.0f), clamp(value.z, 0.0f, 1.0f));
		}
	}
	else
	{
		_parts[_getPartIndex(partID)].color = Vec3(clamp(value.x, 0.0f, 1.0f), clamp(value.y, 0.0f, 1.0f), clamp(value.z, 0.0f, 1.0f));
	}
}

void ModelEntity::setLevelOfDetailSize(Vec3 value)
{
	_levelOfDetailSize = value;
}

void ModelEntity::setInversion(const string& partID, float value)
{
	if (partID.empty())
	{
		for (auto& part : _parts)
		{
			part.inversion = clamp(value, 0.0f, 1.0f);
		}
	}
	else
	{
		_parts[_getPartIndex(partID)].inversion = clamp(value, 0.0f, 1.0f);
	}
}

void ModelEntity::setMeshPath(const string& value)
{
	_meshPath = value;
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

void ModelEntity::setReflectivity(float value)
{
	_reflectivity = clamp(value, 0.0f, 1.0f);
}

void ModelEntity::setFaceCulled(bool value)
{
	_isFaceCulled = value;
}

void ModelEntity::setReflectionType(ReflectionType value)
{
	_reflectionType = value;
}

void ModelEntity::setSpecular(bool value)
{
	_isSpecular = value;
}

void ModelEntity::setReflective(bool value)
{
	_isReflective = value;
}

void ModelEntity::setShadowed(bool value)
{
	_isShadowed = value;
}

void ModelEntity::setReflected(bool value)
{
	_isReflected = value;
}

void ModelEntity::setCameraStatic(bool value)
{
	_isCameraStatic = value;
}

void ModelEntity::setDepthMapIncluded(bool value)
{
	_isDepthMapIncluded = value;
}

void ModelEntity::setLevelOfDetailed(bool value)
{
	_isLevelOfDetailed = value;
}

void ModelEntity::setWireFramed(bool value)
{
	_isWireFramed = value;
}

void ModelEntity::setBright(bool value)
{
	_isBright = value;
}

void ModelEntity::clearParts()
{
	_parts.clear();
}

void ModelEntity::setLightness(float value)
{
	_lightness = max(0.0f, value);
}

void ModelEntity::setSpecularShininess(float value)
{
	_specularShininess = max(0.0f, value);
}

void ModelEntity::setSpecularIntensity(float value)
{
	_specularIntensity = max(0.0f, value);
}

void ModelEntity::setMinHeight(float value)
{
	_minHeight = value;
}

void ModelEntity::setMaxHeight(float value)
{
	_maxHeight = value;
}

void ModelEntity::setAlpha(float value)
{
	_alpha = clamp(value, 0.0f, 1.0f);
}

void ModelEntity::setUvRepeat(float value)
{
	_uvRepeat = max(0.0f, value);
}

void ModelEntity::setEmissionIntensity(float value)
{
	_emissionIntensity = value;
}

void ModelEntity::_correctPositionTarget(Vec3& current, Vec3 target, float speed)
{
	// Correct X
	if (fabsf(target.x - current.x) <= speed)
	{
		current.x = target.x;
	}

	// Correct Y
	if (fabsf(target.y - current.y) <= speed)
	{
		current.y = target.y;
	}

	// Correct Z
	if (fabsf(target.z - current.z) <= speed)
	{
		current.z = target.z;
	}
}

void ModelEntity::_correctRotationTarget(Vec3& current, Vec3 target, float speed)
{
	// Correct current
	current = Vec3(Math::limitAngle(current.x), Math::limitAngle(current.y), Math::limitAngle(current.z));

	// Correct X
	if (Math::calculateAngleDifference(current.x, target.x) <= speed)
	{
		current.x = target.x;
	}

	// Correct Y
	if (Math::calculateAngleDifference(current.y, target.y) <= speed)
	{
		current.y = target.y;
	}

	// Correct Z
	if (Math::calculateAngleDifference(current.z, target.z) <= speed)
	{
		current.z = target.z;
	}
}

void ModelEntity::_correctSizeTarget(Vec3& current, Vec3 target, float speed)
{
	// Correct current
	current = Vec3(max(0.0f, current.x), max(0.0f, current.y), max(0.0f, current.z));

	// Correct X
	if (fabsf(target.x - current.x) <= speed)
	{
		current.x = target.x;
	}

	// Correct Y
	if (fabsf(target.y - current.y) <= speed)
	{
		current.y = target.y;
	}

	// Correct Z
	if (fabsf(target.z - current.z) <= speed)
	{
		current.z = target.z;
	}
}