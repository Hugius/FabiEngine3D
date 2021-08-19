#include "model_entity.hpp"
#include "logger.hpp"

#include <algorithm>

using std::max;
using std::clamp;

void ModelEntity::createPart(const string& ID)
{
	_parts.push_back(PartData(ID));
}

void ModelEntity::updateModelMatrix()
{
	for (size_t i = 0; i < _parts.size(); i++)
	{
		// Identity matrix
		_parts[i].modelMatrix = Matrix44(1.0f);

		// Base translation matrix
		Matrix44 baseTranslationMatrix = Matrix44::createTranslation(_basePosition.x, _basePosition.y, _basePosition.z);
		_parts[i].modelMatrix = _parts[i].modelMatrix * baseTranslationMatrix;

		// Translation matrix
		Matrix44 translationMatrix = Matrix44::createTranslation(_parts[i].localPosition.x, _parts[i].localPosition.y, _parts[i].localPosition.z);
		_parts[i].modelMatrix = _parts[i].modelMatrix * translationMatrix;

		// Base rotation origin matrix - translate
		Matrix44 baseRotationOriginMatrix = Matrix44::createTranslation(_baseRotationOrigin.x, _baseRotationOrigin.y, _baseRotationOrigin.z);
		_parts[i].modelMatrix = _parts[i].modelMatrix * baseRotationOriginMatrix;

		// Base rotation matrix
		Matrix44 baseRotationMatrix = Matrix44::createRotation(
			Math::degreesToRadians(_baseRotation.x),
			Math::degreesToRadians(_baseRotation.y),
			Math::degreesToRadians(_baseRotation.z));
		_parts[i].modelMatrix = _parts[i].modelMatrix * baseRotationMatrix;

		// Base rotation origin matrix - translate back
		baseRotationOriginMatrix = Matrix44::createTranslation(-_baseRotationOrigin.x, -_baseRotationOrigin.y, -_baseRotationOrigin.z);
		_parts[i].modelMatrix = _parts[i].modelMatrix * baseRotationOriginMatrix;

		// Rotation origin matrix - translate
		Matrix44 rotationOriginMatrix = Matrix44::createTranslation(_parts[i].localRotationOrigin.x, _parts[i].localRotationOrigin.y, _parts[i].localRotationOrigin.z);
		_parts[i].modelMatrix = _parts[i].modelMatrix * rotationOriginMatrix;

		// Rotation matrix
		Matrix44 rotationMatrix = Matrix44::createRotation(
			Math::degreesToRadians(_parts[i].localRotation.x),
			Math::degreesToRadians(_parts[i].localRotation.y),
			Math::degreesToRadians(_parts[i].localRotation.z));
		_parts[i].modelMatrix = _parts[i].modelMatrix * rotationMatrix;

		// Rotation origin matrix - translate back
		rotationOriginMatrix = Matrix44::createTranslation(-_parts[i].localRotationOrigin.x, -_parts[i].localRotationOrigin.y, -_parts[i].localRotationOrigin.z);
		_parts[i].modelMatrix = _parts[i].modelMatrix * rotationOriginMatrix;

		// Base scaling matrix
		Matrix44 baseScalingMatrix = Matrix44::createScaling(_baseSize.x, _baseSize.y, _baseSize.z);
		_parts[i].modelMatrix = _parts[i].modelMatrix * baseScalingMatrix;

		// Scaling matrix
		Matrix44 scalingMatrix = Matrix44::createScaling(_parts[i].localSize.x, _parts[i].localSize.y, _parts[i].localSize.z);
		_parts[i].modelMatrix = _parts[i].modelMatrix * scalingMatrix;
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

void ModelEntity::setEnvironmentMap(TextureID value)
{
	_environmentMap = value;
}

void ModelEntity::setPosition(Vec3 value, const string& partID)
{
	if (_parts.size() == 1 || (_parts.size() > 1 && partID.empty()))
	{
		_basePosition = value;
	}
	else
	{
		_parts[_getPartIndex(partID)].localPosition = value;
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

void ModelEntity::setLodEntityID(const string& value)
{
	_lodEntityID = value;
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
	_alpha = max(0.0f, value);
}

void ModelEntity::setUvRepeat(float value)
{
	_uvRepeat = max(0.0f, value);
}