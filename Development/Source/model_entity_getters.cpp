#include "model_entity.hpp"
#include "logger.hpp"

const Matrix44& ModelEntity::getModelMatrix(unsigned int index)
{
	return _modelMatrices[index];
}

const GLuint ModelEntity::getDiffuseMap(unsigned int index) const
{
	return _diffuseMaps[index];
}

const GLuint ModelEntity::getLightMap(unsigned int index) const
{
	return _lightMaps[index];
}

const GLuint ModelEntity::getReflectionMap(unsigned int index) const
{
	return _reflectionMaps[index];
}

const GLuint ModelEntity::getNormalMap(unsigned int index) const
{
	return _normalMaps[index];
}

const Vec3 ModelEntity::getColor(unsigned int index)
{
	return _colors[index];
}

const Vec3 ModelEntity::getOriginalTranslation() const
{
	return _originalTranslation;
}

const Vec3 ModelEntity::getTranslation(const string& partID)
{
	if (partID.empty() && _partIDs.size() > 1)
	{
		return _baseTranslation;
	}
	else
	{
		return _translations[_getPartIndex(partID)];
	}
}

const Vec3 ModelEntity::getOriginalRotation() const
{
	return _originalRotation;
}

const Vec3 ModelEntity::getRotation(const string& partID)
{
	if (partID.empty() && _partIDs.size() > 1)
	{
		return _baseRotation;
	}
	else
	{
		return _rotations[_getPartIndex(partID)];
	}
}

const Vec3 ModelEntity::getRotationOrigin(const string& partID)
{
	if (partID.empty() && _partIDs.size() > 1)
	{
		return _baseRotationOrigin;
	}
	else
	{
		return _rotationOrigins[_getPartIndex(partID)];
	}
}

const Vec3 ModelEntity::getOriginalScaling() const
{
	return _originalScaling;
}

const Vec3 ModelEntity::getScaling(const string& partID)
{
	if (partID.empty() && _partIDs.size() > 1)
	{
		return _baseScaling;
	}
	else
	{
		return _scalings[_getPartIndex(partID)];
	}
}

const Vec3 ModelEntity::getColor(const string& partID)
{
	if (partID.empty() && _partIDs.size() > 1)
	{
		return _calculateAverageValue(_colors);
	}
	else
	{
		return _colors[_getPartIndex(partID)];
	}
}

const string& ModelEntity::getMeshPath() const
{
	return _meshPath;
}

const string& ModelEntity::getDiffuseMapPath() const
{
	return _diffuseMapPath;
}

const string& ModelEntity::getLightMapPath() const
{
	return _lightMapPath;
}

const string& ModelEntity::getReflectionMapPath() const
{
	return _reflectionMapPath;
}

const string& ModelEntity::getNormalMapPath() const
{
	return _normalMapPath;
}

const string& ModelEntity::getLodEntityID() const
{
	return _lodEntityID;
}

const vector<string>& ModelEntity::getDiffuseMapPaths() const
{
	return _diffuseMapPaths;
}

const vector<string>& ModelEntity::getLightMapPaths() const
{
	return _lightMapPaths;
}

const vector<string>& ModelEntity::getReflectionMapPaths() const
{
	return _reflectionMapPaths;
}

const vector<string>& ModelEntity::getNormalMapPaths() const
{
	return _normalMapPaths;
}

const vector<string>& ModelEntity::getPartIDs() const
{
	return _partIDs;
}

const bool ModelEntity::isTransparent() const
{
	return _isTransparent;
}

const bool ModelEntity::isFaceCulled() const
{
	return _isFaceCulled;
}

const bool ModelEntity::isLightMapped() const
{
	return _isLightMapped;
}

const bool ModelEntity::isNormalMapped() const
{
	return _isNormalMapped;
}

const bool ModelEntity::isSkyReflective() const
{
	return _isSkyReflective;
}

const bool ModelEntity::isSceneReflective() const
{
	return _isSceneReflective;
}

const bool ModelEntity::isSpecularLighted() const
{
	return _isSpecularLighted;
}

const bool ModelEntity::isShadowed() const
{
	return _isShadowed;
}

const bool ModelEntity::hasDiffuseMap() const
{
	return !_diffuseMaps.empty();
}

const bool ModelEntity::hasLightMap() const
{
	return !_lightMaps.empty();
}

const bool ModelEntity::hasReflectionMap() const
{
	return !_reflectionMaps.empty();
}

const bool ModelEntity::hasNormalMap() const
{
	return !_normalMaps.empty();
}

const bool ModelEntity::isCameraStatic() const
{
	return _isCameraStatic;
}

const bool ModelEntity::isDepthMapIncluded() const
{
	return _isDepthMapIncluded;
}

const bool ModelEntity::isLevelOfDetailed() const
{
	return _isLevelOfDetailed;
}

const bool ModelEntity::isWireframed() const
{
	return _wireframed;
}

unsigned int ModelEntity::_getPartIndex(string partID)
{
	// Find index
	for (size_t i = 0; i < _partIDs.size(); i++)
	{
		if (partID == _partIDs[i])
		{
			return static_cast<unsigned int>(i);
		}
	}

	// Error
	Logger::throwError("Model entity with ID \"" + getID() + "\" has no part called \"" + partID + "\"");
}

Vec3 ModelEntity::_calculateAverageValue(vector<Vec3> elements)
{
	Vec3 total = Vec3(0.0f);

	for (const auto& element : elements)
	{
		total += element;
	}

	return total / static_cast<float>(elements.size());
}

const float ModelEntity::getLightness() const
{
	return _lightness;
}

const float ModelEntity::getSpecularFactor() const
{
	return _specularFactor;
}

const float ModelEntity::getSpecularIntensity() const
{
	return _specularIntensity;
}

const float ModelEntity::getMinHeight() const
{
	return _minHeight;
}

const float ModelEntity::getMaxHeight() const
{
	return _maxHeight;
}

const float ModelEntity::getAlpha() const
{
	return _alpha;
}

const float ModelEntity::getUvRepeat() const
{
	return _uvRepeat;
}