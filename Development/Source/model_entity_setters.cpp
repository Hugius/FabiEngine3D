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
		_basePosition += _basePositionTargetSpeed;
		_correctTransformationTarget(_basePosition, _basePositionTarget, _basePositionTargetSpeed);
	}

	// Base rotation target
	if (_baseRotation != _baseRotationTarget)
	{
		_baseRotation += _baseRotationTargetSpeed;
		_correctTransformationTarget(_baseRotation, _baseRotationTarget, _baseRotationTargetSpeed);
	}

	// Base size target
	if (_baseSize != _baseSizeTarget)
	{
		_baseSize += _baseSizeTargetSpeed;
		_correctTransformationTarget(_baseSize, _baseSizeTarget, _baseSizeTargetSpeed);
	}

	// Iterate through parts
	for (auto& part : _parts)
	{
		// Local position target
		if (part.localPosition != part.localPositionTarget)
		{
			part.localPosition += part.localPositionTargetSpeed;
			_correctTransformationTarget(part.localPosition, part.localPositionTarget, part.localPositionTargetSpeed);
		}

		// Local rotation target
		if (part.localRotation != part.localRotationTarget)
		{
			part.localRotation += part.localRotationTargetSpeed;
			_correctTransformationTarget(part.localRotation, part.localRotationTarget, part.localRotationTargetSpeed);
		}

		// Local size target
		if (part.localSize != part.localSizeTarget)
		{
			part.localSize += part.localSizeTargetSpeed;
			_correctTransformationTarget(part.localSize, part.localSizeTarget, part.localSizeTargetSpeed);
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
			Math::convertToRadians(_baseRotation.z));
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
			Math::convertToRadians(_parts[i].localRotation.z));
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

void ModelEntity::setRenderBuffer(shared_ptr<RenderBuffer> value, const string& partID)
{
	_parts[_getPartIndex(partID)].renderBuffer = value;
}

void ModelEntity::setDiffuseMap(TextureID value, const string& partID)
{
	_parts[_getPartIndex(partID)].diffuseMap = value;
}

void ModelEntity::setEmissionMap(TextureID value, const string& partID)
{
	_parts[_getPartIndex(partID)].emissionMap = value;
}

void ModelEntity::setReflectionMap(TextureID value, const string& partID)
{
	_parts[_getPartIndex(partID)].reflectionMap = value;
}

void ModelEntity::setNormalMap(TextureID value, const string& partID)
{
	_parts[_getPartIndex(partID)].normalMap = value;
}

void ModelEntity::setPosition(Vec3 value, const string& partID)
{
	if (_parts.size() == 1 || (_parts.size() > 1 && partID.empty()))
	{
		_basePosition = value;
		_basePositionTarget = value;
	}
	else
	{
		_parts[_getPartIndex(partID)].localPosition = value;
		_parts[_getPartIndex(partID)].localPositionTarget = value;
	}
}

void ModelEntity::setRotation(Vec3 value, const string& partID)
{
	value = Vec3(fmodf(value.x, 360.0f), fmodf(value.y, 360.0f), fmodf(value.z, 360.0f));

	if (_parts.size() == 1 || (_parts.size() > 1 && partID.empty()))
	{
		_baseRotation = value;
	}
	else
	{
		_parts[_getPartIndex(partID)].localRotation = value;
	}
}

void ModelEntity::setRotationOrigin(Vec3 value, const string& partID)
{
	if (_parts.size() == 1 || (_parts.size() > 1 && partID.empty()))
	{
		_baseRotationOrigin = value;
	}
	else
	{
		_parts[_getPartIndex(partID)].localRotationOrigin = value;
	}
}

void ModelEntity::setSize(Vec3 value, const string& partID)
{
	value = Vec3(max(0.0f, value.x), max(0.0f, value.y), max(0.0f, value.z));

	if (_parts.size() == 1 || (_parts.size() > 1 && partID.empty()))
	{
		_baseSize = value;
	}
	else
	{
		_parts[_getPartIndex(partID)].localSize = value;
	}
}

void ModelEntity::move(Vec3 value, const string& partID)
{
	if (_parts.size() == 1 || (_parts.size() > 1 && partID.empty()))
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

void ModelEntity::rotate(Vec3 value, const string& partID)
{
	if (_parts.size() == 1 || (_parts.size() > 1 && partID.empty()))
	{
		_baseRotation += value;
	}
	else
	{
		_parts[_getPartIndex(partID)].localRotation += value;
	}
}

void ModelEntity::scale(Vec3 value, const string& partID)
{
	if (_parts.size() == 1 || (_parts.size() > 1 && partID.empty()))
	{
		_baseSize += value;
	}
	else
	{
		_parts[_getPartIndex(partID)].localSize += value;
	}
}

void ModelEntity::moveTo(Vec3 target, Vec3 speed, const string& partID)
{
	if (_parts.size() == 1 || (_parts.size() > 1 && partID.empty()))
	{
		_basePositionTarget = target;
		_basePositionTargetSpeed = speed;
	}
	else
	{
		_parts[_getPartIndex(partID)].localPositionTarget = target;
		_parts[_getPartIndex(partID)].localPositionTargetSpeed = speed;
	}
}

void ModelEntity::rotateTo(Vec3 target, Vec3 speed, const string& partID)
{
	if (_parts.size() == 1 || (_parts.size() > 1 && partID.empty()))
	{
		_baseRotationTarget = target;
		_baseRotationTargetSpeed = speed;
	}
	else
	{
		_parts[_getPartIndex(partID)].localRotationTarget = target;
		_parts[_getPartIndex(partID)].localRotationTargetSpeed = speed;
	}
}

void ModelEntity::scaleTo(Vec3 target, Vec3 speed, const string& partID)
{
	if (_parts.size() == 1 || (_parts.size() > 1 && partID.empty()))
	{
		_baseSizeTarget = target;
		_baseSizeTargetSpeed = speed;
	}
	else
	{
		_parts[_getPartIndex(partID)].localSizeTarget = target;
		_parts[_getPartIndex(partID)].localSizeTargetSpeed = speed;
	}
}

void ModelEntity::setColor(Vec3 value, const string& partID)
{
	value = Vec3(clamp(value.x, 0.0f, 1.0f), clamp(value.y, 0.0f, 1.0f), clamp(value.z, 0.0f, 1.0f));

	if (partID.empty())
	{
		for (auto& part : _parts)
		{
			part.color = value;
		}
	}
	else
	{
		_parts[_getPartIndex(partID)].color = value;
	}
}

void ModelEntity::setLevelOfDetailSize(Vec3 value)
{
	_levelOfDetailSize = value;
}

void ModelEntity::setInversion(float value, const string& partID)
{
	value = clamp(value, 0.0f, 1.0f);

	if (partID.empty())
	{
		for (auto& part : _parts)
		{
			part.inversion = value;
		}
	}
	else
	{
		_parts[_getPartIndex(partID)].inversion = value;
	}
}

void ModelEntity::setMeshPath(const string& value)
{
	_meshPath = value;
}

void ModelEntity::setDiffuseMapPath(const string& value, const string& partID)
{
	_parts[_getPartIndex(partID)].diffuseMapPath = value;
}

void ModelEntity::setEmissionMapPath(const string& value, const string& partID)
{
	_parts[_getPartIndex(partID)].emissionMapPath = value;
}

void ModelEntity::setReflectionMapPath(const string& value, const string& partID)
{
	_parts[_getPartIndex(partID)].reflectionMapPath = value;
}

void ModelEntity::setNormalMapPath(const string& value, const string& partID)
{
	_parts[_getPartIndex(partID)].normalMapPath = value;
}

void ModelEntity::setLodModelEntityID(const string& value)
{
	_lodModelEntityID = value;
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

void ModelEntity::setTransparent(bool value)
{
	_isTransparent = value;
}

void ModelEntity::setFaceCulled(bool value)
{
	_isFaceCulled = value;
}

void ModelEntity::setReflectionType(ReflectionType value)
{
	_reflectionType = value;
}

void ModelEntity::setSpecularLighted(bool value)
{
	_isSpecularLighted = value;
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
	_wireFramed = value;
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

void ModelEntity::setSpecularFactor(float value)
{
	_specularFactor = max(0.0f, value);
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