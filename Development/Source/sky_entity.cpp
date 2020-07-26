#include "sky_entity.hpp"

void SkyEntity::setTexturePaths(const vector<string>& val)
{
	_texturesPaths = val;
}

void SkyEntity::setRotationMatrix(const mat4 & val)
{
	_rotationMatrix = val;
}

void SkyEntity::setColor(vec3 val)
{
	_color = val;
}

void SkyEntity::setCubeMap(GLuint val)
{
	_cubeMap = val;
}

void SkyEntity::setLightness(float val)
{
	_lightness = val;
}

void SkyEntity::setRotationSpeed(float val)
{
	_rotationSpeed = val;
}

const vector<string>& SkyEntity::getTexturePaths() const
{
	return _texturesPaths;
}

const mat4 & SkyEntity::getRotationMatrix() const
{
	return _rotationMatrix;
}

const vec3 SkyEntity::getColor() const
{
	return _color;
}

const GLuint SkyEntity::getCubeMap() const
{
	return _cubeMap;
}

const float SkyEntity::getLightness() const
{
	return _lightness;
}

const float SkyEntity::getRotationSpeed() const
{
	return _rotationSpeed;
}