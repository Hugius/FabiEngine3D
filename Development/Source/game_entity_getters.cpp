#include "game_entity.hpp"
#include "logger.hpp"

const Matrix44& GameEntity::getModelMatrix(unsigned int index)
{
	return _modelMatrices[index];
}

const GLuint GameEntity::getDiffuseMap(unsigned int index) const
{
	return _diffuseMaps[index];
}

const GLuint GameEntity::getLightMap(unsigned int index) const
{
	return _lightMaps[index];
}

const GLuint GameEntity::getReflectionMap(unsigned int index) const
{
	return _reflectionMaps[index];
}

const GLuint GameEntity::getNormalMap(unsigned int index) const
{
	return _normalMaps[index];
}

const Vec3 GameEntity::getColor(unsigned int index)
{
	return _colors[index];
}

const Vec3 GameEntity::getOriginalTranslation() const
{
	return _originalTranslation;
}

const Vec3 GameEntity::getTranslation(const string& partName)
{
	if (partName.empty() && _partNames.size() > 1)
	{
		return _baseTranslation;
	}
	else
	{
		return _translations[_getPartIndex(partName)];
	}
}

const Vec3 GameEntity::getOriginalRotation() const
{
	return _originalRotation;
}

const Vec3 GameEntity::getRotation(const string& partName)
{
	if (partName.empty() && _partNames.size() > 1)
	{
		return _baseRotation;
	}
	else
	{
		return _rotations[_getPartIndex(partName)];
	}
}

const Vec3 GameEntity::getRotationOrigin(const string& partName)
{
	if (partName.empty() && _partNames.size() > 1)
	{
		return _baseRotationOrigin;
	}
	else
	{
		return _rotationOrigins[_getPartIndex(partName)];
	}
}

const Vec3 GameEntity::getOriginalScaling() const
{
	return _originalScaling;
}

const Vec3 GameEntity::getScaling(const string& partName)
{
	if (partName.empty() && _partNames.size() > 1)
	{
		return _baseScaling;
	}
	else
	{
		return _scalings[_getPartIndex(partName)];
	}
}

const Vec3 GameEntity::getColor(const string& partName)
{
	if (partName.empty() && _partNames.size() > 1)
	{
		return _calculateAverageValue(_colors);
	}
	else
	{
		return _colors[_getPartIndex(partName)];
	}
}

const string& GameEntity::getMeshPath() const
{
	return _meshPath;
}

const string& GameEntity::getDiffuseMapPath() const
{
	return _diffuseMapPath;
}

const string& GameEntity::getLightMapPath() const
{
	return _lightMapPath;
}

const string& GameEntity::getReflectionMapPath() const
{
	return _reflectionMapPath;
}

const string& GameEntity::getNormalMapPath() const
{
	return _normalMapPath;
}

const string& GameEntity::getLodEntityID() const
{
	return _lodEntityID;
}

const vector<string>& GameEntity::getDiffuseMapPaths() const
{
	return _diffuseMapPaths;
}

const vector<string>& GameEntity::getLightMapPaths() const
{
	return _lightMapPaths;
}

const vector<string>& GameEntity::getReflectionMapPaths() const
{
	return _reflectionMapPaths;
}

const vector<string>& GameEntity::getNormalMapPaths() const
{
	return _normalMapPaths;
}

const vector<string>& GameEntity::getPartNames() const
{
	return _partNames;
}

const bool GameEntity::isTransparent() const
{
	return _isTransparent;
}

const bool GameEntity::isFaceCulled() const
{
	return _isFaceCulled;
}

const bool GameEntity::isLightMapped() const
{
	return _isLightMapped;
}

const bool GameEntity::isNormalMapped() const
{
	return _isNormalMapped;
}

const bool GameEntity::isSkyReflective() const
{
	return _isSkyReflective;
}

const bool GameEntity::isSceneReflective() const
{
	return _isSceneReflective;
}

const bool GameEntity::isSpecularLighted() const
{
	return _isSpecularLighted;
}

const bool GameEntity::isShadowed() const
{
	return _isShadowed;
}

const bool GameEntity::hasDiffuseMap() const
{
	return !_diffuseMaps.empty();
}

const bool GameEntity::hasLightMap() const
{
	return !_lightMaps.empty();
}

const bool GameEntity::hasReflectionMap() const
{
	return !_reflectionMaps.empty();
}

const bool GameEntity::hasNormalMap() const
{
	return !_normalMaps.empty();
}

const bool GameEntity::isCameraStatic() const
{
	return _isCameraStatic;
}

const bool GameEntity::isDepthMapIncluded() const
{
	return _isDepthMapIncluded;
}

const bool GameEntity::isLevelOfDetailed() const
{
	return _isLevelOfDetailed;
}

const bool GameEntity::isWireframed() const
{
	return _wireframed;
}

unsigned int GameEntity::_getPartIndex(string partName)
{
	// Find index
	for (unsigned int i = 0; i < _partNames.size(); i++)
	{
		if (partName == _partNames[i])
		{
			return i;
		}
	}

	// Error
	Logger::throwError("Game entity with ID \"" + getID() + "\" has no part called \"" + partName + "\"");
}

Vec3 GameEntity::_calculateAverageValue(vector<Vec3> elements)
{
	Vec3 total = Vec3(0.0f);

	for (auto& element : elements)
	{
		total += element;
	}

	return total / static_cast<float>(elements.size());
}

const float GameEntity::getLightness() const
{
	return _lightness;
}

const float GameEntity::getSpecularFactor() const
{
	return _specularFactor;
}

const float GameEntity::getSpecularIntensity() const
{
	return _specularIntensity;
}

const float GameEntity::getMinHeight() const
{
	return _minHeight;
}

const float GameEntity::getMaxHeight() const
{
	return _maxHeight;
}

const float GameEntity::getAlpha() const
{
	return _alpha;
}

const float GameEntity::getUvRepeat() const
{
	return _uvRepeat;
}