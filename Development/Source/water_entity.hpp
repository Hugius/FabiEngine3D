#pragma once

#include "base_entity.hpp"
#include "water_quality.hpp"

class WaterEntity final : public BaseEntity
{
public:
	using BaseEntity::BaseEntity;
	
	// Setters
	void setQuality(WaterQuality quality);
	void setSpeed(Vec2 value);
	void setRippleOffset(Vec2 value);
	void setWaveOffset(Vec2 value);
	void setPosition(Vec3 value);
	void setColor(Vec3 value);
	void setDudvMap(GLuint value);
	void setNormalMap(GLuint value);
	void setDisplacementMap(GLuint value);
	void setDudvMapPath(const string& value);
	void setNormalMapPath(const string& value);
	void setDisplacementMapPath(const string& value);
	void setUvRepeat(float value);
	void setWaveHeight(float value);
	void setSpecularLightingFactor(float value);
	void setSpecularLightingIntensity(float value);
	void setSize(float value);
	void setTransparency(float value);
	void setWaving(bool value);
	void setRippling(bool value);
	void setSpecularLighted(bool value);
	void setReflective(bool value);
	void setRefractive(bool value);
	void setSimplifiedRenderBuffer(RenderBuffer* buffer);

	// Getters
	const WaterQuality getQuality()					const;
	const Vec2    getSpeed()					    const;
	const Vec2    getRippleOffset()				    const;
	const Vec2    getWaveOffset()				    const;
	const Vec3	  getPosition()				    const;
	const Vec3    getColor()					    const;
	const GLuint  getDudvMap()					    const;
	const GLuint  getNormalMap()				    const;
	const GLuint  getDisplacementMap()			    const;
	const string& getDudvMapPath()				    const;
	const string& getNormalMapPath()			    const;
	const string& getDisplacementMapPath()		    const;
	const float   getUvRepeat()					    const;
	const float   getWaveHeight()					const;
	const float   getSpecularLightingFactor()       const;
	const float   getSpecularLightingIntensity()    const;
	const float   getSize()						    const;
	const float   getTransparency()				    const;
	const bool    isWaving()					    const;
	const bool    isRippling()					    const;
	const bool    isSpecularLighted()			    const;
	const bool    isReflective()				    const;
	const bool    isRefractive()				    const;
	const bool	  hasDudvMap()					    const;
	const bool	  hasNormalMap()				    const;
	const bool	  hasDisplacementMap()			    const;
	const RenderBuffer* getSimplifiedRenderBuffer() const;

private:
	WaterQuality _quality = WaterQuality::SKY;

	Vec2 _speed		   = Vec2(0.0f);
	Vec2 _rippleOffset = Vec2(0.0f);
	Vec2 _waveOffset   = Vec2(0.0f);

	Vec3 _position = Vec3(0.0f);
	Vec3 _color = Vec3(1.0f);

	GLuint _dudvMap			= 0;
	GLuint _normalMap		= 0;
	GLuint _displacementMap = 0;

	string _dudvMapPath = "";
	string _normalMapPath = "";
	string _displacementMapPath = "";

	float _size						 = 1.0f;
	float _uvRepeat					 = 1.0f;
	float _waveHeight				 = 0.0f;
	float _specularLightingFactor    = 1.0f;
	float _specularLightingIntensity = 1.0f;
	float _transparency				 = 0.0f;
	
	bool _isRippling		= false;
	bool _isWaving			= false;
	bool _isSpecularLighted	= false;
	bool _isReflective		= false;
	bool _isRefractive		= false;

	RenderBuffer* _simplifiedRenderBuffer = nullptr;
};