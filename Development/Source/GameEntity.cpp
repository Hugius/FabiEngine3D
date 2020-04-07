#include <GLM/gtc/matrix_transform.hpp>

#include <WE3D/GameEntity.hpp>

void GameEntity::updateModelMatrix()
{
	p_modelMatrix = mat4(1.0f);
	p_modelMatrix = glm::translate(p_modelMatrix, p_translation);
	p_modelMatrix = glm::rotate(p_modelMatrix, glm::radians(p_rotation.x), vec3(1.0f, 0.0f, 0.0f));
	p_modelMatrix = glm::rotate(p_modelMatrix, glm::radians(p_rotation.y), vec3(0.0f, 1.0f, 0.0f));
	p_modelMatrix = glm::rotate(p_modelMatrix, glm::radians(p_rotation.z), vec3(0.0f, 0.0f, 1.0f));
	p_modelMatrix = glm::scale(p_modelMatrix, p_scaling);
}

void GameEntity::addDiffuseMap(GLuint val)
{
	if (std::find(p_diffuseMaps.begin(), p_diffuseMaps.end(), val) == p_diffuseMaps.end())
	{
		p_diffuseMaps.push_back(val);
	}
}

void GameEntity::addLightmap(GLuint val)
{
	if (std::find(p_lightMaps.begin(), p_lightMaps.end(), val) == p_lightMaps.end())
	{
		p_lightMaps.push_back(val);
	}
}

void GameEntity::addReflectionMap(GLuint val)
{
	if (std::find(p_reflectionMaps.begin(), p_reflectionMaps.end(), val) == p_reflectionMaps.end())
	{
		p_reflectionMaps.push_back(val);
	}
}

void GameEntity::setTranslation(vec3 val)
{
	p_translation = val;
}

void GameEntity::setRotation(vec3 val)
{
	p_rotation = val;
}

void GameEntity::setScaling(vec3 val)
{
	p_scaling = val;
}

void GameEntity::translate(vec3 val, float delta)
{
	p_translation += val * delta;
}

void GameEntity::rotate(vec3 val, float delta)
{
	p_rotation += val * delta;
}

void GameEntity::scale(vec3 val, float delta)
{
	p_scaling += val * delta;
}

void GameEntity::setColor(vec3 val)
{
	p_color = val;
}

void GameEntity::setModelName(const string & val)
{
	p_modelName = val;
}

void GameEntity::setTransparent(bool val)
{
	p_isTransparent = val;
}

void GameEntity::setFaceCulled(bool val)
{
	p_isFaceCulled = val;
}

void GameEntity::setLightMapped(bool val)
{
	p_isLightMapped = val;
}

void GameEntity::setSkyReflective(bool val)
{
	p_isSkyReflective = val;
}

void GameEntity::setScreenReflective(bool val)
{
	p_isScreenReflective = val;
}

void GameEntity::setSpecular(bool val)
{
	p_isSpecular = val;
}

void GameEntity::setShadowed(bool val)
{
	p_isShadowed = val;
}

void GameEntity::setMaxY(float val)
{
	p_maxY = val;
}

void GameEntity::setAlpha(float alpha)
{
	p_alpha = alpha;
}

void GameEntity::setUvRepeat(float val)
{
	p_uvRepeat = val;
}

const mat4 & GameEntity::getModelMatrix() const
{
	return p_modelMatrix;
}

const GLuint GameEntity::getDiffuseMap(int index) const
{
	return p_diffuseMaps[index];
}

const GLuint GameEntity::getLightMap(int index) const
{
	return p_lightMaps[index];
}

const GLuint GameEntity::getReflectionMap(int index) const
{
	return p_reflectionMaps[index];
}

const vec3 GameEntity::getTranslation() const
{
	return p_translation;
}

const vec3 GameEntity::getRotation() const
{
	return p_rotation;
}

const vec3 GameEntity::getScaling() const
{
	return p_scaling;
}

const vec3 GameEntity::getColor() const
{
	return p_color;
}

const string & GameEntity::getModelName() const
{
	return p_modelName;
}

const bool GameEntity::isTransparent() const
{
	return p_isTransparent;
}

const bool GameEntity::isFaceCulled() const
{
	return p_isFaceCulled;
}

const bool GameEntity::isLightMapped() const
{
	return p_isLightMapped;
}

const bool GameEntity::isSkyReflective() const
{
	return p_isSkyReflective;
}

const bool GameEntity::isScreenReflective() const
{
	return p_isScreenReflective;
}

const bool GameEntity::isSpecular() const
{
	return p_isSpecular;
}

const bool GameEntity::isShadowed() const
{
	return p_isShadowed;
}

const float GameEntity::getMaxY() const
{
	return p_maxY;
}

const float GameEntity::getAlpha() const
{
	return p_alpha;
}

const float GameEntity::getUvRepeat() const
{
	return p_uvRepeat;
}
