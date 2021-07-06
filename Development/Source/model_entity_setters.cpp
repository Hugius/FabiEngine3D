#include "model_entity.hpp"
#include "logger.hpp"

#include <algorithm>

void ModelEntity::addPart(const string& value)
{
	_partIDs.push_back(value);
	_modelMatrices.push_back(Matrix44(1.0f));
	_translations.push_back(Vec3(0.0f));
	_rotations.push_back(Vec3(0.0f));
	_rotationOrigins.push_back(Vec3(0.0f));
	_scalings.push_back(Vec3(1.0f));
	_colors.push_back(Vec3(1.0f));
}

void ModelEntity::updateModelMatrix()
{
	for (size_t i = 0; i < _modelMatrices.size(); i++)
	{
		// Instanced modelpart cannot have a modelmatrix position
		if (!getRenderBuffers().empty() && getRenderBuffer(static_cast<unsigned int>(i))->isInstanced())
		{
			_translations[i] = Vec3(0.0f);
		}

		// Identity matrix
		_modelMatrices[i] = Matrix44(1.0f);

		// Base translation matrix
		Matrix44 baseTranslationMatrix = Matrix44::createTranslation(_baseTranslation.x, _baseTranslation.y, _baseTranslation.z);
		_modelMatrices[i] = _modelMatrices[i] * baseTranslationMatrix;

		// Translation matrix
		Matrix44 translationMatrix = Matrix44::createTranslation(_translations[i].x, _translations[i].y, _translations[i].z);
		_modelMatrices[i] = _modelMatrices[i] * translationMatrix;

		// Base rotation origin matrix - translate
		Matrix44 baseRotationOriginMatrix = Matrix44::createTranslation(_baseRotationOrigin.x, _baseRotationOrigin.y, _baseRotationOrigin.z);
		_modelMatrices[i] = _modelMatrices[i] * baseRotationOriginMatrix;

		// Base rotation matrix
		Matrix44 baseRotationMatrix = Matrix44::createRotation(
			Math::degreesToRadians(_baseRotation.x),
			Math::degreesToRadians(_baseRotation.y),
			Math::degreesToRadians(_baseRotation.z));
		_modelMatrices[i] = _modelMatrices[i] * baseRotationMatrix;

		// Base rotation origin matrix - translate back
		baseRotationOriginMatrix = Matrix44::createTranslation(-_baseRotationOrigin.x, -_baseRotationOrigin.y, -_baseRotationOrigin.z);
		_modelMatrices[i] = _modelMatrices[i] * baseRotationOriginMatrix;

		// Rotation origin matrix - translate
		Matrix44 rotationOriginMatrix = Matrix44::createTranslation(_rotationOrigins[i].x, _rotationOrigins[i].y, _rotationOrigins[i].z);
		_modelMatrices[i] = _modelMatrices[i] * rotationOriginMatrix;

		// Rotation matrix
		Matrix44 rotationMatrix = Matrix44::createRotation(
			Math::degreesToRadians(_rotations[i].x),
			Math::degreesToRadians(_rotations[i].y),
			Math::degreesToRadians(_rotations[i].z));
		_modelMatrices[i] = _modelMatrices[i] * rotationMatrix;

		// Rotation origin matrix - translate back
		rotationOriginMatrix = Matrix44::createTranslation(-_rotationOrigins[i].x, -_rotationOrigins[i].y, -_rotationOrigins[i].z);
		_modelMatrices[i] = _modelMatrices[i] * rotationOriginMatrix;

		// Base scaling matrix
		Matrix44 baseScalingMatrix = Matrix44::createScaling(_baseScaling.x, _baseScaling.y, _baseScaling.z);
		_modelMatrices[i] = _modelMatrices[i] * baseScalingMatrix;

		// Scaling matrix
		Matrix44 scalingMatrix = Matrix44::createScaling(_scalings[i].x, _scalings[i].y, _scalings[i].z);
		_modelMatrices[i] = _modelMatrices[i] * scalingMatrix;
	}
}

void ModelEntity::setDiffuseMap(GLuint value)
{
	if (_diffuseMaps.empty())
	{
		_diffuseMaps.push_back(value);
	}
	else
	{
		_diffuseMaps[0] = value;
	}
}

void ModelEntity::setLightMap(GLuint value)
{
	if (_lightMaps.empty())
	{
		_lightMaps.push_back(value);
	}
	else
	{
		_lightMaps[0] = value;
	}
}

void ModelEntity::setReflectionMap(GLuint value)
{
	if (_reflectionMaps.empty())
	{
		_reflectionMaps.push_back(value);
	}
	else
	{
		_reflectionMaps[0] = value;
	}
}

void ModelEntity::setNormalMap(GLuint value)
{
	if (_normalMaps.empty())
	{
		_normalMaps.push_back(value);
	}
	else
	{
		_normalMaps[0] = value;
	}
}

void ModelEntity::addDiffuseMap(GLuint value)
{
	_diffuseMaps.push_back(value);
}

void ModelEntity::addLightMap(GLuint value)
{
	_lightMaps.push_back(value);
}

void ModelEntity::addReflectionMap(GLuint value)
{
	_reflectionMaps.push_back(value);
}

void ModelEntity::addNormalMap(GLuint value)
{
	_normalMaps.push_back(value);
}

void ModelEntity::setOriginalTranslation(Vec3 value)
{
	_originalTranslation = value;
}

void ModelEntity::setTranslation(Vec3 value, const string& partID)
{
	if (partID.empty() && _partIDs.size() > 1)
	{
		_baseTranslation = value;
	}
	else
	{
		_translations[_getPartIndex(partID)] = value;
	}
}

void ModelEntity::setOriginalRotation(Vec3 value)
{
	_originalRotation = value;

	// Limit rotation
	_originalRotation.x = std::fmodf(_originalRotation.x, 360.0f);
	_originalRotation.y = std::fmodf(_originalRotation.y, 360.0f);
	_originalRotation.z = std::fmodf(_originalRotation.z, 360.0f);
}

void ModelEntity::setRotation(Vec3 value, const string& partID)
{
	if (partID.empty() && _partIDs.size() > 1)
	{
		_baseRotation = value;

		// Limit rotation
		_baseRotation.x = std::fmodf(_baseRotation.x, 360.0f);
		_baseRotation.y = std::fmodf(_baseRotation.y, 360.0f);
		_baseRotation.z = std::fmodf(_baseRotation.z, 360.0f);
	}
	else
	{
		_rotations[_getPartIndex(partID)] = value;

		// Limit rotation
		_rotations[_getPartIndex(partID)].x = std::fmodf(_rotations[_getPartIndex(partID)].x, 360.0f);
		_rotations[_getPartIndex(partID)].y = std::fmodf(_rotations[_getPartIndex(partID)].y, 360.0f);
		_rotations[_getPartIndex(partID)].z = std::fmodf(_rotations[_getPartIndex(partID)].z, 360.0f);
	}
}

void ModelEntity::setRotationOrigin(Vec3 value, const string& partID)
{
	if (partID.empty() && _partIDs.size() > 1)
	{
		_baseRotationOrigin = value;
	}
	else
	{
		_rotationOrigins[_getPartIndex(partID)] = value;
	}
}

void ModelEntity::setOriginalScaling(Vec3 value)
{
	_originalScaling = Vec3(std::max(0.0f, value.x), std::max(0.0f, value.y), std::max(0.0f, value.z));
}

void ModelEntity::setScaling(Vec3 value, const string& partID)
{
	if (partID.empty() && _partIDs.size() > 1)
	{
		_baseScaling = Vec3(std::max(0.0f, value.x), std::max(0.0f, value.y), std::max(0.0f, value.z));
	}
	else
	{
		_scalings[_getPartIndex(partID)] = Vec3(std::max(0.0f, value.x), std::max(0.0f, value.y), std::max(0.0f, value.z));
	}
}

void ModelEntity::translate(Vec3 value, const string& partID)
{
	if (partID.empty() && _partIDs.size() > 1)
	{
		_baseTranslation += value;
	}
	else
	{
		_translations[_getPartIndex(partID)] += value;
	}
}

void ModelEntity::rotate(Vec3 value, const string& partID)
{
	if (partID.empty() && _partIDs.size() > 1)
	{
		_baseRotation += value;

		// Limit rotation
		_baseRotation.x = std::fmodf(_baseRotation.x, 360.0f);
		_baseRotation.y = std::fmodf(_baseRotation.y, 360.0f);
		_baseRotation.z = std::fmodf(_baseRotation.z, 360.0f);
	}
	else
	{
		_rotations[_getPartIndex(partID)] += value;

		// Limit rotation
		_rotations[_getPartIndex(partID)].x = std::fmodf(_rotations[_getPartIndex(partID)].x, 360.0f);
		_rotations[_getPartIndex(partID)].y = std::fmodf(_rotations[_getPartIndex(partID)].y, 360.0f);
		_rotations[_getPartIndex(partID)].z = std::fmodf(_rotations[_getPartIndex(partID)].z, 360.0f);
	}
}

void ModelEntity::scale(Vec3 value, const string& partID)
{
	if (partID.empty() && _partIDs.size() > 1)
	{
		_baseScaling += value;
		_baseScaling = Vec3(std::max(0.0f, _baseScaling.x), std::max(0.0f, _baseScaling.y), std::max(0.0f, _baseScaling.z));
	}
	else
	{
		_scalings[_getPartIndex(partID)] += value;
		_scalings[_getPartIndex(partID)] = Vec3(
				std::max(0.0f, _scalings[_getPartIndex(partID)].x), 
				std::max(0.0f, _scalings[_getPartIndex(partID)].y), 
				std::max(0.0f, _scalings[_getPartIndex(partID)].z));
	}
}

void ModelEntity::setColor(Vec3 value, const string& partID)
{
	if (partID.empty() && _partIDs.size() > 1)
	{
		for (auto& color : _colors)
		{
			color = Vec3(std::clamp(value.r, 0.0f, 1.0f), std::clamp(value.g, 0.0f, 1.0f), std::clamp(value.b, 0.0f, 1.0f));
		}
	}
	else
	{
		_colors[_getPartIndex(partID)] = Vec3(std::clamp(value.r, 0.0f, 1.0f), std::clamp(value.g, 0.0f, 1.0f), std::clamp(value.b, 0.0f, 1.0f));
	}
}

void ModelEntity::setMeshPath(const string& value)
{
	_meshPath = value;
}

void ModelEntity::setDiffuseMapPath(const string& value)
{
	_diffuseMapPath = value;
}

void ModelEntity::setLightMapPath(const string& value)
{
	_lightMapPath = value;
}

void ModelEntity::setReflectionMapPath(const string& value)
{
	_reflectionMapPath = value;
}

void ModelEntity::setNormalMapPath(const string& value)
{
	_normalMapPath = value;
}

void ModelEntity::setLodEntityID(const string& value)
{
	_lodEntityID = value;
}

void ModelEntity::addDiffuseMapPath(string value)
{
	_diffuseMapPaths.push_back(value);
}

void ModelEntity::addLightMapPath(string value)
{
	_lightMapPaths.push_back(value);
}

void ModelEntity::addReflectionMapPath(string value)
{
	_reflectionMapPaths.push_back(value);
}

void ModelEntity::addNormalMapPath(string value)
{
	_normalMapPaths.push_back(value);
}

void ModelEntity::setTransparent(bool value)
{
	_isTransparent = value;
}

void ModelEntity::setFaceCulled(bool value)
{
	_isFaceCulled = value;
}

void ModelEntity::setLightMapped(bool value)
{
	_isLightMapped = value;
}

void ModelEntity::setNormalMapped(bool value)
{
	_isNormalMapped = value;
}

void ModelEntity::setSkyReflective(bool value)
{
	_isSkyReflective = value;
}

void ModelEntity::setSceneReflective(bool value)
{
	_isSceneReflective = value;
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

void ModelEntity::setWireframed(bool value)
{
	_wireframed = value;
}

void ModelEntity::setBloomed(bool value)
{
	_isBloomed = value;
}

void ModelEntity::clearDiffuseMaps()
{
	_diffuseMaps.clear();
	_diffuseMapPaths.clear();
}

void ModelEntity::clearLightMaps()
{
	_lightMaps.clear();
	_lightMapPaths.clear();
}

void ModelEntity::clearReflectionMaps()
{
	_reflectionMaps.clear();
	_reflectionMapPaths.clear();
}

void ModelEntity::clearNormalMaps()
{
	_normalMaps.clear();
	_normalMapPaths.clear();
}

void ModelEntity::setLightness(float value)
{
	_lightness = std::max(0.0f, value);
}

void ModelEntity::setSpecularFactor(float value)
{
	_specularFactor = std::max(0.0f, value);
}

void ModelEntity::setSpecularIntensity(float value)
{
	_specularIntensity = std::max(0.0f, value);
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
	_alpha = std::max(0.0f, value);
}

void ModelEntity::setUvRepeat(float value)
{
	_uvRepeat = std::max(0.0f, value);
}