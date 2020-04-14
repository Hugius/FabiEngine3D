#include <GLM/gtc/matrix_transform.hpp>

#include "GameEntity.hpp"

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

void GameEntity::translate(vec3 val, float delta)
{
	_translation += val * delta;
}

void GameEntity::rotate(vec3 val, float delta)
{
	_rotation += val * delta;
}

void GameEntity::scale(vec3 val, float delta)
{
	_scaling += val * delta;
}

void GameEntity::setColor(vec3 val)
{
	_color = val;
}

void GameEntity::setModelName(const string & val)
{
	_modelName = val;
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

void GameEntity::setSpecular(bool val)
{
	_isSpecular = val;
}

void GameEntity::setShadowed(bool val)
{
	_isShadowed = val;
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

const string & GameEntity::getModelName() const
{
	return _modelName;
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

const bool GameEntity::isSpecular() const
{
	return _isSpecular;
}

const bool GameEntity::isShadowed() const
{
	return _isShadowed;
}

const bool GameEntity::hasTexture() const
{
	return !_diffuseMaps.empty();
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
