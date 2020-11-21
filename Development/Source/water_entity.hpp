#pragma once

#include "base_entity.hpp"

class WaterEntity final : public BaseEntity
{
public:
	using BaseEntity::BaseEntity;
	~WaterEntity() = default;
	
	// Setters
	void setSpeed(Vec2 val);
	void setRippleOffset(Vec2 val);
	void setWaveOffset(Vec2 val);
	void setPosition(Vec3 val);
	void setColor(Vec3 val);
	void setDudvMap(GLuint val);
	void setNormalMap(GLuint val);
	void setDisplacementMap(GLuint val);
	void setDudvMapPath(const string& val);
	void setNormalMapPath(const string& val);
	void setDisplacementMapPath(const string& val);
	void setUvRepeat(float val);
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
	void setSimplifiedOglBuffer(OpenGLBuffer* buffer);

	// Getters
	const Vec2    getSpeed()					 const;
	const Vec2    getRippleOffset()				 const;
	const Vec2    getWaveOffset()				 const;
	const Vec3	  getPosition()					 const;
	const Vec3    getColor()					 const;
	const GLuint  getDudvMap()					 const;
	const GLuint  getNormalMap()				 const;
	const GLuint  getDisplacementMap()			 const;
	const string& getDudvMapPath()				 const;
	const string& getNormalMapPath()			 const;
	const string& getDisplacementMapPath()		 const;
	const float   getUvRepeat()					 const;
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
	const OpenGLBuffer* getSimplifiedOglBuffer() const;

private:
	Vec2 _speed		   = Vec2(0.0f);
	Vec2 _rippleOffset = Vec2(0.0f);
	Vec2 _waveOffset   = Vec2(0.0f);

	Vec3 _position = Vec3(0.0f);
	Vec3 _color = Vec3(0.0f);

	GLuint _dudvMap			= 0;
	GLuint _normalMap		= 0;
	GLuint _displacementMap = 0;

	string _dudvMapPath = "";
	string _normalMapPath = "";
	string _displacementMapPath = "";

	float _size						 = 1.0f;
	float _uvRepeat					 = 1.0f;
	float _waveHeightFactor			 = 1.0f;
	float _specularLightingFactor    = 1.0f;
	float _specularLightingIntensity = 1.0f;
	float _transparency				 = 0.0f;
	
	bool _isRippling		= false;
	bool _isWaving			= false;
	bool _isSpecularLighted	= false;
	bool _isReflective		= false;
	bool _isRefractive		= false;

	OpenGLBuffer* _simplifiedOglBuffer = nullptr;
};