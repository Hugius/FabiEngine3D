#pragma once

#include <GLM\\glm.hpp>

using glm::mat4;

#include "base_entity.hpp"

class SkyEntity final : public BaseEntity
{
public:
	SkyEntity()  = default;
	~SkyEntity() = default;

	void setTexturePaths(const vector<string>& val);
	void setRotationMatrix(const mat4& val);
	void setColor(vec3 val);
	void setDayCubeMap(GLuint val);
	void setNightCubeMap(GLuint val);
	void setBrightness(float val);
	void setMixValue(float val);
	void setRotationSpeed(float val);
	void setDayTime();
	void setNightTime();

	const vector<string>& getTexturePaths() const;
	const mat4& getRotationMatrix()			const;
	const vec3 getColor()					const;
	const GLuint getCurrentCubeMap()		const;
	const GLuint getDayCubeMap()			const;
	const GLuint getNightCubeMap()			const;
	const float getBrightness()				const;
	const float getMixValue()				const;
	const float getRotationSpeed()			const;
	const bool  isDayTime()					const;
	const bool  isNightTime()				const;

private:
	vector<string> _texturesPaths;

	mat4 _rotationMatrix = mat4(1.0f);

	vec3 _color = vec3(1.0f);

	GLuint _dayCubeMap   = 0;
	GLuint _nightCubeMap = 0;

	float _brightness		= 1.0f;
	float _mixValue         = 0.0f;
	float _rotationSpeed    = 0.0f;

	bool _dayTime = true;
};