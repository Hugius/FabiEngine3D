#pragma once

#include "mathematics.hpp"

#include <GLEW\\glew.h>
#include <string>

using std::string;

class RenderBus final
{
public:
	RenderBus() = default;
	
	// Textures
	void setSceneMap(GLuint value);
	void setMainSkyReflectionCubeMap(GLuint value);
	void setMixSkyReflectionCubeMap(GLuint value);
	void setSceneReflectionMap(GLuint value);
	void setSceneRefractionMap(GLuint value);
	void setShadowMap(GLuint value);
	void setBloomMap(GLuint value);
	void setPostProcessedSceneMap(GLuint value);
	void setSceneDepthMap(GLuint value);
	void setBlurMap(GLuint value);
	void setMotionBlurMap(GLuint value);
	void setLensFlareMap(GLuint value);

	// Matrices
	void setViewMatrix(const Matrix44 & value);
	void setProjectionMatrix(const Matrix44 & value);
	void setSkyRotationMatrix(const Matrix44 & value);
	void setShadowMatrix(const Matrix44 & value);

	// Vector4
	void setFlareSourcePositionClipspace(Vec4 value);

	// Vector3
	void setCameraPosition(Vec3 value);
	void setCameraFront(Vec3 value);
	void setAmbientLightColor(Vec3 value);
	void setDirectionalLightPosition(Vec3 value);
	void setDirectionalLightColor(Vec3 value);
	void setSpotLightColor(Vec3 value);
	void setShadowEyePosition(Vec3 value);
	void setShadowAreaCenter(Vec3 value);
	void setFogColor(Vec3 value);
	void setFlareSourcePosition(Vec3 value);
	void setMainSkyColor(Vec3 value);
	void setMixSkyColor(Vec3 value);

	// Floats
	void setAmbientLightIntensity(float value);
	void setDirectionalLightIntensity(float value);
	void setSpotLightIntensity(float value);
	void setMaxSpotLightAngle(float value);
	void setMaxSpotLightDistance(float value);
	void setFogMinDistance(float value);
	void setFogMaxDistance(float value);
	void setFogThickness(float value);
	void setBloomIntensity(float value);
	void setBloomBrightnessTreshold(float value);
	void setCameraYaw(float value);
	void setCameraPitch(float value);
	void setNearZ(float value);
	void setFarZ(float value);
	void setDofMaxDistance(float value);
	void setDofBlurDistance(float value);
	void setSkyReflectionFactor(float value);
	void setSceneReflectionHeight(float value);
	void setSceneReflectionOffset(float value);
	void setSceneReflectionFactor(float value);
	void setShadowAreaSize(float value);
	void setShadowAreaReach(float value);
	void setLensFlareAlpha(float value);
	void setLensFlareIntensity(float value);
	void setLensFlareMultiplier(float value);
	void setMotionBlurStrength(float value);
	void setMotionBlurMixValue(float value);
	void setSkyMixValue(float value);
	void setMainSkyLightness(float value);
	void setMixSkyLightness(float value);

	// Integers
	void setBloomBlurSize(int value);
	void resetTriangleCount();
	void increaseTriangleCount(int value);
	void setMsaaSampleCount(int value);
	void setShadowMapSize(int value);
	void setSceneReflectionMapSize(int value);
	void setSceneRefractionMapSize(int value);

	// Booleans
	void setMsaaEnabled(bool value);
	void setAmbientLightingEnabled(bool value);
	void setDirectionalLightingEnabled(bool value);
	void setSpecularLightingEnabled(bool value);
	void setPointLightingEnabled(bool value);
	void setSpotLightingEnabled(bool value);
	void setFogEnabled(bool value);
	void setLightMappingEnabled(bool value);
	void setNormalMappingEnabled(bool value);
	void setSkyReflectionsEnabled(bool value);
	void setSceneReflectionsEnabled(bool value);
	void setBloomEnabled(bool value);
	void setWaterEffectsEnabled(bool value);
	void setSkyHdrEnabled(bool value);
	void setShadowsEnabled(bool value);
	void setDofEnabled(bool value);
	void setMotionBlurEnabled(bool value);
	void setLensFlareEnabled(bool value);
	void setWireframeRenderingEnabled(bool value);
	void setAabbFrameRenderingEnabled(bool value);
	void setDebugRenderingEnabled(bool value);
	void setShadowFrameRenderingEnabled(bool value);
	void setTriangleCountingEnabled(bool value);
	void setDofDynamic(bool value);

	// Strings
	void setCursorEntityID(const string& value);
	void setLensFlareMapPath(const string& value);

	// Textures
	const GLuint getSceneMap()                 const;
	const GLuint getMainSkyReflectionCubeMap() const;
	const GLuint getMixSkyReflectionCubeMap()  const;
	const GLuint getSceneReflectionMap()	   const;
	const GLuint getSceneRefractionMap()	   const;
	const GLuint getShadowMap()				   const;
	const GLuint getBloomMap()				   const;
	const GLuint getPostProcessedSceneMap()	   const;
	const GLuint getSceneDepthMap()			   const;
	const GLuint getBlurMap()				   const;
	const GLuint getMotionBlurMap()			   const;
	const GLuint getLensFlareMap()			   const;
	
	// Matrices
	const Matrix44& getViewMatrix()        const;
	const Matrix44& getProjectionMatrix()  const;
	const Matrix44& getSkyRotationMatrix() const;
	const Matrix44& getShadowMatrix()      const;

	// Vector4
	const Vec4 getFlareSourcePositionClipspace() const;
	
	// Vector3
	const Vec3 getCameraPosition()			 const;
	const Vec3 getCameraFront()				 const;
	const Vec3 getAmbientLightColor()		 const;
	const Vec3 getDirectionalLightColor()    const;
	const Vec3 getDirectionalLightPosition() const;
	const Vec3 getSpotLightColor()			 const;
	const Vec3 getShadowEyePosition()		 const;
	const Vec3 getShadowAreaCenter()		 const;
	const Vec3 getFogColor()				 const;
	const Vec3 getFlareSourcePosition()		 const;
	const Vec3 getMainSkyColor()			 const;
	const Vec3 getMixSkyColor()				 const;

	// Floats
	const float getAmbientLightIntensity()	   const;
	const float getDirectionalLightIntensity() const;
	const float getSpotLightIntensity()		   const;
	const float getMaxSpotLightAngle()		   const;
	const float getMaxSpotLightDistance()	   const;
	const float getFogMinDistance()			   const;
	const float getFogMaxDistance()			   const;
	const float getFogThickness()		   const;
	const float getBloomIntensity()			   const;
	const float getBloomBrightnessTreshold()   const;
	const float getCameraYaw()				   const;
	const float getCameraPitch()			   const;
	const float getNearZ()					   const;
	const float getFarZ()					   const;
	const float getDofMaxDistance()			   const;
	const float getDofBlurDistance()		   const;
	const float getSkyReflectionFactor()	   const;
	const float getSceneReflectionHeight()	   const;
	const float getSceneReflectionOffset()	   const;
	const float getSceneReflectionFactor()	   const;
	const float getShadowAreaSize()			   const;
	const float getShadowAreaReach()		   const;
	const float getLensFlareAlpha()			   const;
	const float getLensFlareIntensity()		   const;
	const float getLensFlareMultiplier()	   const;
	const float getMotionBlurStrength()		   const;
	const float getMotionBlurMixValue()		   const;
	const float getSkyMixValue()			   const;
	const float getMainSkyLightness()		   const;
	const float getMixSkyLightness()		   const;

	// Integers
	const int getBloomBlurSize()		  const;
	const int getTriangleCount()		  const;
	const int getMsaaSampleCount()		  const;
	const int getShadowMapSize()		  const;
	const int getSceneReflectionMapSize() const;
	const int getSceneRefractionMapSize() const;

	// Booleans
	const bool isMsaaEnabled()                 const;
	const bool isAmbientLightingEnabled()      const;
	const bool isDirectionalLightingEnabled()  const;
	const bool isSpecularLightingEnabled()     const;
	const bool isPointLightingEnabled()        const;
	const bool isSpotLightingEnabled()         const;
	const bool isFogEnabled()                  const;
	const bool isLightMappingEnabled()         const;
	const bool isNormalMappingEnabled()		   const;
	const bool isSkyReflectionsEnabled()       const;
	const bool isSceneReflectionsEnabled()     const;
	const bool isBloomEnabled()                const;
	const bool isWaterEffectsEnabled()         const;
	const bool isSkyHdrEnabled()               const;
	const bool isShadowsEnabled()              const;
	const bool isDofEnabled()                  const;
	const bool isMotionBlurEnabled()           const;
	const bool isLensFlareEnabled()			   const;
	const bool isWireframeRenderingEnabled()   const;
	const bool isAabbFrameRenderingEnabled()   const;
	const bool isShadowFrameRenderingEnabled() const;
	const bool isDebugRenderingEnabled()       const;
	const bool isTriangleCountingEnabled()	   const;
	const bool isDofDynamic()				   const;

	// Strings
	const string& getCursorEntityID() const;
	const string& getLensFlareMapPath() const;

private:
	// Textures
	GLuint _sceneMap                 = 0;
	GLuint _mainSkyReflectionCubeMap = 0;
	GLuint _mixSkyReflectionCubeMap  = 0;
	GLuint _sceneReflectionMap       = 0;
	GLuint _sceneRefractionMap       = 0;
	GLuint _shadowMap                = 0;
	GLuint _bloomMap                 = 0;
	GLuint _postProcessedSceneMap    = 0;
	GLuint _sceneDepthMap            = 0;
	GLuint _blurMap                  = 0;
	GLuint _motionBlurMap            = 0;
	GLuint _lensFlareMap		     = 0;
	
	// Matrices
	Matrix44 _viewMatrix        = Matrix44(1.0f);
	Matrix44 _projectionMatrix  = Matrix44(1.0f);
	Matrix44 _skyRotationMatrix = Matrix44(1.0f);
	Matrix44 _shadowMatrix      = Matrix44(1.0f);

	// Vector4
	Vec4 _flareSourcePositionClipspace = Vec4(0.0f);

	// Vector3
	Vec3 _cameraPosition		   = Vec3(0.0f);
	Vec3 _cameraFront			   = Vec3(0.0f);
	Vec3 _ambientLightColor		   = Vec3(1.0f);
	Vec3 _directionalLightColor    = Vec3(1.0f);
	Vec3 _directionalLightPosition = Vec3(0.0f);
	Vec3 _spotLightColor		   = Vec3(1.0f);
	Vec3 _shadowEyePosition		   = Vec3(0.0f);
	Vec3 _shadowAreaCenter		   = Vec3(0.0f);
	Vec3 _fogColor				   = Vec3(1.0f);
	Vec3 _flareSourcePosition	   = Vec3(0.0f);
	Vec3 _mainSkyColor			   = Vec3(0.0f);
	Vec3 _mixSkyColor			   = Vec3(0.0f);

	// Floats
	float _ambientLightIntensity     = 0.0f;
	float _directionalLightIntensity = 0.0f;
	float _spotLightIntensity		 = 0.0f;
	float _maxSpotLightAngle		 = 0.0f;
	float _maxSpotLightDistance		 = 0.0f;
	float _fogMinDistance            = 0.0f;
	float _fogMaxDistance			 = 0.0f;
	float _fogThickness			 = 0.0f;
	float _bloomIntensity            = 0.0f;
	float _bloomBrightnessTreshold   = 0.0f;
	float _cameraYaw                 = 0.0f;
	float _cameraPitch               = 0.0f;
	float _nearZ                     = 0.0f;
	float _farZ                      = 0.0f;
	float _dofMaxDistance            = 0.0f;
	float _dofBlurDistance			 = 0.0f;
	float _skyReflectionFactor       = 0.0f;
	float _sceneReflectionHeight     = 0.0f;
	float _sceneReflectionOffset	 = 0.0f;
	float _sceneReflectionFactor     = 0.0f;
	float _shadowAreaSize			 = 0.0f;
	float _shadowAreaReach			 = 0.0f;
	float _lensFlareAlpha			 = 0.0f;
	float _lensFlareIntensity		 = 0.0f;
	float _lensFlareMultiplier		 = 0.0f;
	float _motionBlurStrength		 = 0.0f;
	float _motionBlurMixValue		 = 0.0f;
	float _skyMixValue				 = 0.0f;
	float _mainSkyLightness			 = 0.0f;
	float _mixSkyLightness			 = 0.0f;
	
	// Integers
	int _bloomBlurSize			= 0;
	int _triangleCount			= 0;
	int _msaaSampleCount		= 0;
	int _shadowMapSize			= 0;
	int _sceneReflectionMapSize = 0;
	int _sceneRefractionMapSize = 0;

	// Booleans
	bool _isMsaaEnabled                 = false;
	bool _isAmbientLightingEnabled      = false;
	bool _isDirectionalLightingEnabled  = false;
	bool _isSpecularLightingEnabled     = false;
	bool _isPointLightingEnabled        = false;
	bool _isSpotLightingEnabled			= false;
	bool _isFogEnabled                  = false;
	bool _isLightMappingEnabled         = false;
	bool _isNormalMappingEnabled		= false;
	bool _isSkyReflectionsEnabled       = false;
	bool _isSceneReflectionsEnabled     = false;
	bool _isBloomEnabled                = false;
	bool _isWaterEffectsEnabled         = false;
	bool _isSkyHdrEnabled               = false;
	bool _isShadowsEnabled              = false;
	bool _isDofEnabled                  = false;
	bool _isMotionBlurEnabled           = false;
	bool _isLensFlareEnabled			= false;
	bool _isWireframeRenderingEnabled   = false;
	bool _isAabbFrameRenderingEnabled   = false;
	bool _isShadowFrameRenderingEnabled	= false;
	bool _isDebugRenderingEnabled		= false;
	bool _isTriangleCountingEnabled		= false;
	bool _isDofDynamic					= false;

	// Strings
	string _cursorEntityID   = "";
	string _lensFlareMapPath = "";
};