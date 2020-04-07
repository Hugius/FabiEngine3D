#pragma once

#include <GLM/glm.hpp>

using glm::mat4;

#include "Entity.hpp"

class SkyEntity final : public Entity
{
public:
	SkyEntity()  = default;
	~SkyEntity() = default;

	void setRotationMatrix(const mat4 & val);
	void setDayCubeMap(GLuint val);
	void setNightCubeMap(GLuint val);
	void setMixValue(float val);
	void setDayAmbStrength(float val);
	void setNightAmbStrength(float val);
	void setDayDirStrength(float val);
	void setNightDirStrength(float val);
	void setRotationSpeed(float val);
	void setDayTime();
	void setNightTime();

	const mat4 & getRotationMatrix() const;
	const GLuint getCurrentCubeMap() const;
	const GLuint getDayCubeMap()     const;
	const GLuint getNightCubeMap()   const;
	const float getMixValue()        const;
	const float getAmbStrength()     const;
	const float getDirStrength()     const;
	const float getRotationSpeed()   const;
	const bool  isDayTime()          const;
	const bool  isNightTime()        const;

private:
	mat4 p_rotationMatrix = mat4(1.0f);

	GLuint p_dayCubeMap   = 0;
	GLuint p_nightCubeMap = 0;

	float p_mixValue         = 0.0f;
	float p_dayAmbStrength   = -1.0f;
	float p_dayDirStrength   = -1.0f;
	float p_nightAmbStrength = -1.0f;
	float p_nightDirStrength = -1.0f;
	float p_rotationSpeed    = 0.0f;

	bool p_dayTime = true;
};