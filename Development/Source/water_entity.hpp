#pragma once
#include "base_entity.hpp"

class WaterEntity final : public BaseEntity
{
public:
	WaterEntity()  = default;
	~WaterEntity() = default;

	// Setters
	void setColor(vec3 val);
	void setDudvMap(GLuint val);
	void setNormalMap(GLuint val);
	void setWaveValue(float val);
	void setUvRepeat(float val);
	void setWavingSpeed(float val);
	void setTimeX(float val);
	void setTimeZ(float val);
	void setShininess(float val);
	void setSurfaceHeight(float val);
	void setSize(float val);
	void setTransparency(float val);
	void setWaving(bool val);
	void setRippling(bool val);
	void setSpecular(bool val);
	void setReflective(bool val);
	void setRefractive(bool val);

	// Getters
	const vec3   getColor()         const;
	const GLuint getDudvMap()       const;
	const GLuint getNormalMap()     const;
	const float  getWaveValue()     const;
	const float  getUvRepeat()    const;
	const float  getWavingSpeed()   const;
	const float  getTimeX()         const;
	const float  getTimeZ()         const;
	const float  getShininess()     const;
	const float  getSurfaceHeight() const;
	const float  getSize()          const;
	const float  getTransparency()  const;
	const bool   isWaving()         const;
	const bool   isRippling()       const;
	const bool   isSpecular()       const;
	const bool   isReflective()     const;
	const bool   isRefractive()     const;

private:
	vec3 _color = vec3(0.0f);

	GLuint _dudvMap   = 0;
	GLuint _normalMap = 0;

	float _size			 = 0.0f;
	float _waveValue     = 0.0f;
	float _uvRepeat    = 1.0f;
	float _wavingSpeed   = 0.0f;
	float _timeX         = 0.1f;
	float _timeZ         = 0.25f;
	float _shininess     = 0.0f;
	float _surfaceHeight = 0.0f;
	float _transparency  = 0.0f;
	
	bool _waving   = false;
	bool _rippling = false;
	bool _specular = false;
	bool _reflective = false;
	bool _refractive = false;
};