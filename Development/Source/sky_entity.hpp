#pragma once

#include <GLM/glm.hpp>

using glm::mat4;

#include "base_entity.hpp"

class SkyEntity final : public BaseEntity
{
public:
	SkyEntity()  = default;
	~SkyEntity() = default;

	void setRotationMatrix(const mat4 & val);
	void setDayCubeMap(GLuint val);
	void setNightCubeMap(GLuint val);
	void setMixValue(float val);
	void setRotationSpeed(float val);
	void setDayTime();
	void setNightTime();

	const mat4 & getRotationMatrix() const;
	const GLuint getCurrentCubeMap() const;
	const GLuint getDayCubeMap()     const;
	const GLuint getNightCubeMap()   const;
	const float getMixValue()        const;
	const float getRotationSpeed()   const;
	const bool  isDayTime()          const;
	const bool  isNightTime()        const;

private:
	mat4 _rotationMatrix = mat4(1.0f);

	GLuint _dayCubeMap   = 0;
	GLuint _nightCubeMap = 0;

	float _mixValue         = 0.0f;
	float _rotationSpeed    = 0.0f;

	bool _dayTime = true;
};