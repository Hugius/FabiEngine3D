#include <GLM\\gtc/matrix_transform.hpp>

#include "game_entity.hpp"

void GameEntity::updateModelMatrix()
{
	_modelMatrix = mat4(1.0f);
	_modelMatrix = glm::translate(_modelMatrix, _translation);
	_modelMatrix = glm::rotate(_modelMatrix, glm::radians(_rotation.x), vec3(1.0f, 0.0f, 0.0f));
	_modelMatrix = glm::rotate(_modelMatrix, glm::radians(_rotation.y), vec3(0.0f, 1.0f, 0.0f));
	_modelMatrix = glm::rotate(_modelMatrix, glm::radians(_rotation.z), vec3(0.0f, 0.0f, 1.0f));
	_modelMatrix = glm::scale(_modelMatrix, _scaling);
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

void GameEntity::addDiffuseMap(GLuint val)
{
	if (std::find(_diffuseMaps.begin(), _diffuseMaps.end(), val) == _diffuseMaps.end())
	{
		_diffuseMaps.push_back(val);
	}
}

void GameEntity::addLightMap(GLuint val)
{
	if (std::find(_lightMaps.begin(), _lightMaps.end(), val) == _lightMaps.end())
	{
		_lightMaps.push_back(val);
	}
}

void GameEntity::addReflectionMap(GLuint val)
{
	if (std::find(_reflectionMaps.begin(), _reflectionMaps.end(), val) == _reflectionMaps.end())
	{
		_reflectionMaps.push_back(val);
	}
}

void GameEntity::setTranslation(vec3 val)
{
	_translation = val;
}

void GameEntity::setRotation(vec3 val)
{
	_rotation = val;
}

void GameEntity::setScaling(vec3 val)
{
	_scaling = val;
}

void GameEntity::translate(vec3 val)
{
	_translation += val;
}

void GameEntity::rotate(vec3 val)
{
	_rotation += val;
}

void GameEntity::scale(vec3 val)
{
	_scaling += val;
}

void GameEntity::setColor(vec3 val)
{
	_color = val;
}

void GameEntity::setObjPath(const string & val)
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
	_isSpecular = val;
}

void GameEntity::setShadowed(bool val)
{
	_isShadowed = val;
}

void GameEntity::setLightness(float val)
{
	_lightness = val;
}

void GameEntity::setSpecularStrength(float val)
{
	_specularStrength = val;
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

const mat4 & GameEntity::getModelMatrix() const
{
	return _modelMatrix;
}

const GLuint GameEntity::getDiffuseMap(int index) const
{
	return _diffuseMaps[index];
}

const GLuint GameEntity::getLightMap(int index) const
{
	return _lightMaps[index];
}

const GLuint GameEntity::getReflectionMap(int index) const
{
	return _reflectionMaps[index];
}

const vec3 GameEntity::getTranslation() const
{
	return _translation;
}

const vec3 GameEntity::getRotation() const
{
	return _rotation;
}

const vec3 GameEntity::getScaling() const
{
	return _scaling;
}

const vec3 GameEntity::getColor() const
{
	return _color;
}

const string & GameEntity::getObjPath() const
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
	return _isSpecular;
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

const float GameEntity::getLightness() const
{
	return _lightness;
}

const float GameEntity::getSpecularStrength() const
{
	return _specularStrength;
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
