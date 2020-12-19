#include "game_entity.hpp"
#include "logger.hpp"

void GameEntity::addPart(const string& val)
{
	_partNames.push_back(val);
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

void GameEntity::setDiffuseMap(GLuint val)
{
	if (_diffuseMaps.empty())
	{
		_diffuseMaps.push_back(val);
	}
	else
	{
		_diffuseMaps[0] = val;
	}
}

void GameEntity::setLightMap(GLuint val)
{
	if (_lightMaps.empty())
	{
		_lightMaps.push_back(val);
	}
	else
	{
		_lightMaps[0] = val;
	}
}

void GameEntity::setReflectionMap(GLuint val)
{
	if (_reflectionMaps.empty())
	{
		_reflectionMaps.push_back(val);
	}
	else
	{
		_reflectionMaps[0] = val;
	}
}

void GameEntity::setNormalMap(GLuint val)
{
	if (_normalMaps.empty())
	{
		_normalMaps.push_back(val);
	}
	else
	{
		_normalMaps[0] = val;
	}
}

void GameEntity::addDiffuseMap(GLuint val)
{
	_diffuseMaps.push_back(val);
}

void GameEntity::addLightMap(GLuint val)
{
	_lightMaps.push_back(val);
}

void GameEntity::addReflectionMap(GLuint val)
{
	_reflectionMaps.push_back(val);
}

void GameEntity::addNormalMap(GLuint val)
{
	_normalMaps.push_back(val);
}

void GameEntity::setOriginalTranslation(Vec3 val)
{
	_originalTranslation = val;
}

void GameEntity::setTranslation(Vec3 val, const string& partName)
{
	if (partName.empty() && _partNames.size() > 1)
	{
		_baseTranslation = val;
	}
	else
	{
		_translations[_getPartIndex(partName)] = val;
	}
}

void GameEntity::setOriginalRotation(Vec3 val)
{
	_originalRotation = val;
}

void GameEntity::setRotation(Vec3 val, const string& partName)
{
	if (partName.empty() && _partNames.size() > 1)
	{
		_baseRotation = val;
	}
	else
	{
		_rotations[_getPartIndex(partName)] = val;
	}
}

void GameEntity::setRotationOrigin(Vec3 val, const string& partName)
{
	if (partName.empty() && _partNames.size() > 1)
	{
		_baseRotationOrigin = val;
	}
	else
	{
		_rotationOrigins[_getPartIndex(partName)] = val;
	}
}

void GameEntity::setOriginalScaling(Vec3 val)
{
	_originalScaling = val;
}

void GameEntity::setScaling(Vec3 val, const string& partName)
{
	if (partName.empty() && _partNames.size() > 1)
	{
		_baseScaling = val;
	}
	else
	{
		_scalings[_getPartIndex(partName)] = val;
	}
}

void GameEntity::translate(Vec3 val, const string& partName)
{
	if (partName.empty() && _partNames.size() > 1)
	{
		_baseTranslation += val;
	}
	else
	{
		_translations[_getPartIndex(partName)] += val;
	}
}

void GameEntity::rotate(Vec3 val, const string& partName)
{
	if (partName.empty() && _partNames.size() > 1)
	{
		_baseRotation += val;
	}
	else
	{
		_rotations[_getPartIndex(partName)] += val;
	}
}

void GameEntity::scale(Vec3 val, const string& partName)
{
	if (partName.empty() && _partNames.size() > 1)
	{
		_baseScaling += val;
	}
	else
	{
		_scalings[_getPartIndex(partName)] += val;
	}
}

void GameEntity::setColor(Vec3 val, const string& partName)
{
	if (partName.empty() && _partNames.size() > 1)
	{
		for (auto& color : _colors)
		{
			color = val;
		}
	}
	else
	{
		_colors[_getPartIndex(partName)] = val;
	}
}

void GameEntity::setObjPath(const string& val)
{
	_objPath = val;
}

void GameEntity::setDiffuseMapPath(const string& val)
{
	_diffuseMapPath = val;
}

void GameEntity::setLightMapPath(const string& val)
{
	_lightMapPath = val;
}

void GameEntity::setReflectionMapPath(const string& val)
{
	_reflectionMapPath = val;
}

void GameEntity::setNormalMapPath(const string& val)
{
	_normalMapPath = val;
}

void GameEntity::setLodEntityID(const string& val)
{
	_lodEntityID = val;
}

void GameEntity::addDiffuseMapPath(string val)
{
	_diffuseMapPaths.push_back(val);
}

void GameEntity::addLightMapPath(string val)
{
	_lightMapPaths.push_back(val);
}

void GameEntity::addReflectionMapPath(string val)
{
	_reflectionMapPaths.push_back(val);
}

void GameEntity::addNormalMapPath(string val)
{
	_normalMapPaths.push_back(val);
}

void GameEntity::setTransparent(bool val)
{
	_isTransparent = val;
}

void GameEntity::setFaceCulled(bool val)
{
	_isFaceCulled = val;
}

void GameEntity::setLightMapped(bool val)
{
	_isLightMapped = val;
}

void GameEntity::setNormalMapped(bool val)
{
	_isNormalMapped = val;
}

void GameEntity::setSkyReflective(bool val)
{
	_isSkyReflective = val;
}

void GameEntity::setSceneReflective(bool val)
{
	_isSceneReflective = val;
}

void GameEntity::setSpecularLighted(bool val)
{
	_isSpecularLighted = val;
}

void GameEntity::setShadowed(bool val)
{
	_isShadowed = val;
}

void GameEntity::setCameraStatic(bool val)
{
	_isCameraStatic = val;
}

void GameEntity::setDepthMapIncluded(bool val)
{
	_isDepthMapIncluded = val;
}

void GameEntity::setLevelOfDetailed(bool val)
{
	_isLevelOfDetailed = val;
}

void GameEntity::setWireframed(bool val)
{
	_wireframed = val;
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

void GameEntity::setLightness(float val)
{
	_lightness = val;
}

void GameEntity::setSpecularFactor(float val)
{
	_specularFactor = val;
}

void GameEntity::setSpecularIntensity(float val)
{
	_specularIntensity = val;
}

void GameEntity::setMaxY(float val)
{
	_maxY = val;
}

void GameEntity::setAlpha(float alpha)
{
	_alpha = alpha;
}

void GameEntity::setUvRepeat(float val)
{
	_uvRepeat = val;
}

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
		return _calculateAverage(_colors);
	}
	else
	{
		return _colors[_getPartIndex(partName)];
	}
}

const string& GameEntity::getObjPath() const
{
	return _objPath;
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

Vec3 GameEntity::_calculateAverage(vector<Vec3> elements)
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

const float GameEntity::getMaxY() const
{
	return _maxY;
}

const float GameEntity::getAlpha() const
{
	return _alpha;
}

const float GameEntity::getUvRepeat() const
{
	return _uvRepeat;
}
