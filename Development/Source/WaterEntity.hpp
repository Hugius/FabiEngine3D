#pragma once
#include "Entity.hpp"

class WaterEntity final : public Entity
{
public:
	WaterEntity()  = default;
	~WaterEntity() = default;

	// Setters
	void setColor(vec3 val);
	void setDudvMap(GLuint val);
	void setNormalMap(GLuint val);
	void setWaveValue(float val);
	void setTileRepeat(float val);
	void setWavingSpeed(float val);
	void setTimeX(float val);
	void setTimeZ(float val);
	void setShininess(float val);
	void setWaving(bool val);
	void setRippling(bool val);
	void setSurfaceHeight(float val);
	void setTransparency(float val);

	// Getters
	const vec3   getColor()         const;
	const GLuint getDudvMap()       const;
	const GLuint getNormalMap()     const;
	const float  getWaveValue()     const;
	const float  getTileRepeat()    const;
	const float  getWavingSpeed()   const;
	const float  getTimeX()         const;
	const float  getTimeZ()         const;
	const float  getShininess()     const;
	const float  getSurfaceHeight() const;
	const float  getTransparency() const;
	const bool   isWaving()         const;
	const bool   isRippling()       const;

private:
	vec3 p_color = vec3(0.0f);

	GLuint p_dudvMap   = 0;
	GLuint p_normalMap = 0;

	float p_waveValue     = 0.0f;
	float p_tileRepeat    = 1.0f;
	float p_wavingSpeed   = 0.0f;
	float p_timeX         = 0.1f;
	float p_timeZ         = 0.25f;
	float p_shininess     = 0.0f;
	float p_surfaceHeight = 0.0f;
	float p_transparency  = 0.0f;
	
	bool p_waving   = false;
	bool p_rippling = false;
};