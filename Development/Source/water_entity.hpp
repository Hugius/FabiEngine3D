#pragma once

#include "base_entity.hpp"

class WaterEntity final : public BaseEntity
{
public:
	WaterEntity()  = default;
	~WaterEntity() = default;
	
	// Setters
	void setPosition(vec3 val);
	void setColor(vec3 val);
	void setDudvMap(GLuint val);
	void setNormalMap(GLuint val);
	void setDisplacementMap(GLuint val);
	void setDudvMapPath(const string& val);
	void setNormalMapPath(const string& val);
	void setDisplacementMapPath(const string& val);
	void setUvRepeat(float val);
	void setRippleOffset(float val);
	void setSpeed(float val);
	void setWaveOffset(float val);
	void setWaveHeightFactor(float val);
	void setSpecularLightingFactor(float val);
	void setSpecularLightingIntensity(float val);
	void setSize(float val);
	void setTransparency(float val);
	void setWaving(bool val);
	void setRippling(bool val);
	void setSpecularLighted(bool val);
	void setReflective(bool val);
	void setRefractive(bool val);

	// Getters
	const vec3	  getPosition()					 const;
	const vec3    getColor()					 const;
	const GLuint  getDudvMap()					 const;
	const GLuint  getNormalMap()				 const;
	const GLuint  getDisplacementMap()			 const;
	const string& getDudvMapPath()				 const;
	const string& getNormalMapPath()			 const;
	const string& getDisplacementMapPath()		 const;
	const float   getUvRepeat()					 const;
	const float   getRippleOffset()				 const;
	const float   getSpeed()					 const;
	const float   getWaveOffset()				 const;
	const float   getWaveHeightFactor()			 const;
	const float   getSpecularLightingFactor()    const;
	const float   getSpecularLightingIntensity() const;
	const float   getSize()						 const;
	const float   getTransparency()				 const;
	const bool    isWaving()					 const;
	const bool    isRippling()					 const;
	const bool    isSpecularLighted()			 const;
	const bool    isReflective()				 const;
	const bool    isRefractive()				 const;

private:
	vec3 _position = vec3(0.0f);
	vec3 _color = vec3(0.0f);

	GLuint _dudvMap			= 0;
	GLuint _normalMap		= 0;
	GLuint _displacementMap = 0;

	string _dudvMapPath = "";
	string _normalMapPath = "";
	string _displacementMapPath = "";

	float _size						 = 1.0f;
	float _rippleOffset				 = 0.0f;
	float _waveOffset				 = 0.0f;
	float _uvRepeat					 = 1.0f;
	float _speed					 = 0.0f;
	float _waveHeightFactor			 = 0.0f;
	float _specularLightingFactor    = 0.0f;
	float _specularLightingIntensity = 0.0f;
	float _transparency				 = 0.0f;
	
	bool _isRippling		= false;
	bool _isWaving			= false;
	bool _isSpecularLighted	= false;
	bool _isReflective		= false;
	bool _isRefractive		= false;
};