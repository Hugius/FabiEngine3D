#include "game_entity.hpp"
#include "logger.hpp"

void GameEntity::addPart(const string& value)
{
	_partNames.push_back(value);
	_modelMatrices.push_back(Matrix44(1.0f));
	_translations.push_back(Vec3(0.0f));
	_rotations.push_back(Vec3(0.0f));
	_rotationOrigins.push_back(Vec3(0.0f));
	_scalings.push_back(Vec3(1.0f));
	_colors.push_back(Vec3(1.0f));
}

void GameEntity::updateModelMatrix()
{
	for (unsigned int i = 0; i < _modelMatrices.size(); i++)
	{
		// Instanced modelpart cannot have a modelmatrix position
		if (!getOglBuffers().empty() && getOglBuffer(i)->isInstanced())
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

void GameEntity::setDiffuseMap(GLuint value)
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

void GameEntity::setLightMap(GLuint value)
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

void GameEntity::setReflectionMap(GLuint value)
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

void GameEntity::setNormalMap(GLuint value)
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

void GameEntity::addDiffuseMap(GLuint value)
{
	_diffuseMaps.push_back(value);
}

void GameEntity::addLightMap(GLuint value)
{
	_lightMaps.push_back(value);
}

void GameEntity::addReflectionMap(GLuint value)
{
	_reflectionMaps.push_back(value);
}

void GameEntity::addNormalMap(GLuint value)
{
	_normalMaps.push_back(value);
}

void GameEntity::setOriginalTranslation(Vec3 value)
{
	_originalTranslation = value;
}

void GameEntity::setTranslation(Vec3 value, const string& partName)
{
	if (partName.empty() && _partNames.size() > 1)
	{
		_baseTranslation = value;
	}
	else
	{
		_translations[_getPartIndex(partName)] = value;
	}
}

void GameEntity::setOriginalRotation(Vec3 value)
{
	_originalRotation = value;
}

void GameEntity::setRotation(Vec3 value, const string& partName)
{
	if (partName.empty() && _partNames.size() > 1)
	{
		_baseRotation = value;

		// Limit rotation
		_baseRotation.x = std::fmodf(_baseRotation.x, 360.0f);
		_baseRotation.y = std::fmodf(_baseRotation.y, 360.0f);
		_baseRotation.z = std::fmodf(_baseRotation.z, 360.0f);
	}
	else
	{
		_rotations[_getPartIndex(partName)] = value;

		// Limit rotation
		_rotations[_getPartIndex(partName)].x = std::fmodf(_rotations[_getPartIndex(partName)].x, 360.0f);
		_rotations[_getPartIndex(partName)].y = std::fmodf(_rotations[_getPartIndex(partName)].y, 360.0f);
		_rotations[_getPartIndex(partName)].z = std::fmodf(_rotations[_getPartIndex(partName)].z, 360.0f);
	}
}

void GameEntity::setRotationOrigin(Vec3 value, const string& partName)
{
	if (partName.empty() && _partNames.size() > 1)
	{
		_baseRotationOrigin = value;
	}
	else
	{
		_rotationOrigins[_getPartIndex(partName)] = value;
	}
}

void GameEntity::setOriginalScaling(Vec3 value)
{
	_originalScaling = value;
}

void GameEntity::setScaling(Vec3 value, const string& partName)
{
	if (partName.empty() && _partNames.size() > 1)
	{
		_baseScaling = value;
	}
	else
	{
		_scalings[_getPartIndex(partName)] = value;
	}
}

void GameEntity::translate(Vec3 value, const string& partName)
{
	if (partName.empty() && _partNames.size() > 1)
	{
		_baseTranslation += value;
	}
	else
	{
		_translations[_getPartIndex(partName)] += value;
	}
}

void GameEntity::rotate(Vec3 value, const string& partName)
{
	if (partName.empty() && _partNames.size() > 1)
	{
		_baseRotation += value;

		// Limit rotation
		_baseRotation.x = std::fmodf(_baseRotation.x, 360.0f);
		_baseRotation.y = std::fmodf(_baseRotation.y, 360.0f);
		_baseRotation.z = std::fmodf(_baseRotation.z, 360.0f);
	}
	else
	{
		_rotations[_getPartIndex(partName)] += value;

		// Limit rotation
		_rotations[_getPartIndex(partName)].x = std::fmodf(_rotations[_getPartIndex(partName)].x, 360.0f);
		_rotations[_getPartIndex(partName)].y = std::fmodf(_rotations[_getPartIndex(partName)].y, 360.0f);
		_rotations[_getPartIndex(partName)].z = std::fmodf(_rotations[_getPartIndex(partName)].z, 360.0f);
	}
}

void GameEntity::scale(Vec3 value, const string& partName)
{
	if (partName.empty() && _partNames.size() > 1)
	{
		_baseScaling += value;
	}
	else
	{
		_scalings[_getPartIndex(partName)] += value;
	}
}

void GameEntity::setColor(Vec3 value, const string& partName)
{
	if (partName.empty() && _partNames.size() > 1)
	{
		for (auto& color : _colors)
		{
			color = value;
		}
	}
	else
	{
		_colors[_getPartIndex(partName)] = value;
	}
}

void GameEntity::setMeshPath(const string& value)
{
	_meshPath = value;
}

void GameEntity::setDiffuseMapPath(const string& value)
{
	_diffuseMapPath = value;
}

void GameEntity::setLightMapPath(const string& value)
{
	_lightMapPath = value;
}

void GameEntity::setReflectionMapPath(const string& value)
{
	_reflectionMapPath = value;
}

void GameEntity::setNormalMapPath(const string& value)
{
	_normalMapPath = value;
}

void GameEntity::setLodEntityID(const string& value)
{
	_lodEntityID = value;
}

void GameEntity::addDiffuseMapPath(string value)
{
	_diffuseMapPaths.push_back(value);
}

void GameEntity::addLightMapPath(string value)
{
	_lightMapPaths.push_back(value);
}

void GameEntity::addReflectionMapPath(string value)
{
	_reflectionMapPaths.push_back(value);
}

void GameEntity::addNormalMapPath(string value)
{
	_normalMapPaths.push_back(value);
}

void GameEntity::setTransparent(bool value)
{
	_isTransparent = value;
}

void GameEntity::setFaceCulled(bool value)
{
	_isFaceCulled = value;
}

void GameEntity::setLightMapped(bool value)
{
	_isLightMapped = value;
}

void GameEntity::setNormalMapped(bool value)
{
	_isNormalMapped = value;
}

void GameEntity::setSkyReflective(bool value)
{
	_isSkyReflective = value;
}

void GameEntity::setSceneReflective(bool value)
{
	_isSceneReflective = value;
}

void GameEntity::setSpecularLighted(bool value)
{
	_isSpecularLighted = value;
}

void GameEntity::setShadowed(bool value)
{
	_isShadowed = value;
}

void GameEntity::setCameraStatic(bool value)
{
	_isCameraStatic = value;
}

void GameEntity::setDepthMapIncluded(bool value)
{
	_isDepthMapIncluded = value;
}

void GameEntity::setLevelOfDetailed(bool value)
{
	_isLevelOfDetailed = value;
}

void GameEntity::setWireframed(bool value)
{
	_wireframed = value;
}

void GameEntity::clearDiffuseMaps()
{
	_diffuseMaps.clear();
	_diffuseMapPaths.clear();
}

void GameEntity::clearLightMaps()
{
	_lightMaps.clear();
	_lightMapPaths.clear();
}

void GameEntity::clearReflectionMaps()
{
	_reflectionMaps.clear();
	_reflectionMapPaths.clear();
}

void GameEntity::clearNormalMaps()
{
	_normalMaps.clear();
	_normalMapPaths.clear();
}

void GameEntity::setLightness(float value)
{
	_lightness = value;
}

void GameEntity::setSpecularFactor(float value)
{
	_specularFactor = value;
}

void GameEntity::setSpecularIntensity(float value)
{
	_specularIntensity = value;
}

void GameEntity::setMinHeight(float value)
{
	_minHeight = value;
}

void GameEntity::setMaxHeight(float value)
{
	_maxHeight = value;
}

void GameEntity::setAlpha(float alpha)
{
	_alpha = alpha;
}

void GameEntity::setUvRepeat(float value)
{
	_uvRepeat = value;
}