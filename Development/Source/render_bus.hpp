#pragma once

#include "mathematics.hpp"
#include "bloom_type.hpp"
#include "render_utils.hpp"

#include <string>

using std::string;

class RenderBus final
{
public:
	// Textures
	void setPrimarySceneMap(TextureID value);
	void setSecondarySceneMap(TextureID value);
	void setMainSkyReflectionCubeMap(TextureID value);
	void setMixSkyReflectionCubeMap(TextureID value);
	void setSceneReflectionMap(TextureID value);
	void setWaterReflectionMap(TextureID value);
	void setWaterRefractionMap(TextureID value);
	void setShadowMap(TextureID value);
	void setBloomMap(TextureID value);
	void setDepthMap(TextureID value);
	void setDofMap(TextureID value);
	void setLensFlareMap(TextureID value);
	void setMotionBlurMap(TextureID value);
	void setFinalSceneMap(TextureID value);

	// Strings
	void setCursorEntityID(const string& value);
	void setLensFlareMapPath(const string& value);

	// Matrices
	void setViewMatrix(const Matrix44 value);
	void setProjectionMatrix(const Matrix44 value);
	void setSkyRotationMatrix(const Matrix44 value);
	void setShadowMatrix(const Matrix44 value);

	// Vector4
	void setFlareSourcePositionClipspace(Vec4 value);
	void setClippingPlane(Vec4 value);

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
	void setCameraYaw(float value);
	void setCameraPitch(float value);
	void setNearZ(float value);
	void setFarZ(float value);
	void setDofMaxDistance(float value);
	void setDofBlurDistance(float value);
	void setSceneReflectionHeight(float value);
	void setShadowAreaSize(float value);
	void setShadowAreaReach(float value);
	void setShadowLightness(float value);
	void setLensFlareAlpha(float value);
	void setLensFlareIntensity(float value);
	void setLensFlareMultiplier(float value);
	void setMotionBlurStrength(float value);
	void setMotionBlurMixValue(float value);
	void setSkyMixValue(float value);
	void setMainSkyLightness(float value);
	void setMixSkyLightness(float value);

	// Integers
	void setBloomBlurCount(unsigned int value);
	void setAnisotropicFilteringQuality(unsigned int value);
	void setShadowQuality(unsigned int value);
	void setReflectionQuality(unsigned int value);
	void setRefractionQuality(unsigned int value);
	void increaseTriangleCount(unsigned int value);
	void resetTriangleCount();

	// Booleans
	void setFxaaEnabled(bool value);
	void setAmbientLightingEnabled(bool value);
	void setDirectionalLightingEnabled(bool value);
	void setSpecularLightingEnabled(bool value);
	void setPointLightingEnabled(bool value);
	void setSpotLightingEnabled(bool value);
	void setFogEnabled(bool value);
	void setBloomEnabled(bool value);
	void setSkyExposureEnabled(bool value);
	void setShadowsEnabled(bool value);
	void setDofEnabled(bool value);
	void setMotionBlurEnabled(bool value);
	void setLensFlareEnabled(bool value);
	void setWireFrameRenderingEnabled(bool value);
	void setAabbFrameRenderingEnabled(bool value);
	void setDebugRenderingEnabled(bool value);
	void setShadowFrameRenderingEnabled(bool value);
	void setTriangleCountingEnabled(bool value);
	void setDofDynamic(bool value);

	// Miscellaneous
	void setBloomType(BloomType value);

	// Textures
	const TextureID getPrimarySceneMap();
	const TextureID getSecondarySceneMap();
	const TextureID getMainSkyReflectionCubeMap();
	const TextureID getMixSkyReflectionCubeMap();
	const TextureID getSceneReflectionMap();
	const TextureID getWaterReflectionMap();
	const TextureID getWaterRefractionMap();
	const TextureID getShadowMap();
	const TextureID getBloomMap();
	const TextureID getDepthMap();
	const TextureID getDofMap();
	const TextureID getLensFlareMap();
	const TextureID getFinalSceneMap();
	const TextureID getMotionBlurMap();

	// Strings
	const string& getCursorEntityID();
	const string& getLensFlareMapPath();

	// Matrices
	const Matrix44 getViewMatrix();
	const Matrix44 getProjectionMatrix();
	const Matrix44 getSkyRotationMatrix();
	const Matrix44 getShadowMatrix();

	// Vector4
	const Vec4 getFlareSourcePositionClipspace();
	const Vec4 getClippingPlane();

	// Vector3
	const Vec3 getCameraPosition();
	const Vec3 getCameraFront();
	const Vec3 getAmbientLightColor();
	const Vec3 getDirectionalLightColor();
	const Vec3 getDirectionalLightPosition();
	const Vec3 getSpotLightColor();
	const Vec3 getShadowEyePosition();
	const Vec3 getShadowAreaCenter();
	const Vec3 getFogColor();
	const Vec3 getFlareSourcePosition();
	const Vec3 getMainSkyColor();
	const Vec3 getMixSkyColor();

	// Floats
	const float getAmbientLightIntensity();
	const float getDirectionalLightIntensity();
	const float getSpotLightIntensity();
	const float getMaxSpotLightAngle();
	const float getMaxSpotLightDistance();
	const float getFogMinDistance();
	const float getFogMaxDistance();
	const float getFogThickness();
	const float getBloomIntensity();
	const float getCameraYaw();
	const float getCameraPitch();
	const float getNearZ();
	const float getFarZ();
	const float getDofMaxDistance();
	const float getDofBlurDistance();
	const float getSceneReflectionHeight();
	const float getShadowAreaSize();
	const float getShadowAreaReach();
	const float getShadowLightness();
	const float getLensFlareAlpha();
	const float getLensFlareIntensity();
	const float getLensFlareMultiplier();
	const float getMotionBlurStrength();
	const float getMotionBlurMixValue();
	const float getSkyMixValue();
	const float getMainSkyLightness();
	const float getMixSkyLightness();

	// Integers
	const unsigned int getBloomBlurCount();
	const unsigned int getTriangleCount();
	const unsigned int getAnisotropicFilteringQuality();
	const unsigned int getShadowQuality();
	const unsigned int getReflectionQuality();
	const unsigned int getRefractionQuality();

	// Booleans
	const bool isFxaaEnabled();
	const bool isAmbientLightingEnabled();
	const bool isDirectionalLightingEnabled();
	const bool isSpecularLightingEnabled();
	const bool isPointLightingEnabled();
	const bool isSpotLightingEnabled();
	const bool isFogEnabled();
	const bool isBloomEnabled();
	const bool isSkyExposureEnabled();
	const bool isShadowsEnabled();
	const bool isDofEnabled();
	const bool isMotionBlurEnabled();
	const bool isLensFlareEnabled();
	const bool isWireFrameRenderingEnabled();
	const bool isAabbFrameRenderingEnabled();
	const bool isShadowFrameRenderingEnabled();
	const bool isDebugRenderingEnabled();
	const bool isTriangleCountingEnabled();
	const bool isDofDynamic();

	// Miscellaneous
	const BloomType getBloomType();

private:
	// Textures
	TextureID _primarySceneMap = 0;
	TextureID _secondarySceneMap = 0;
	TextureID _mainSkyReflectionCubeMap = 0;
	TextureID _mixSkyReflectionCubeMap = 0;
	TextureID _sceneReflectionMap = 0;
	TextureID _waterReflectionMap = 0;
	TextureID _waterRefractionMap = 0;
	TextureID _shadowMap = 0;
	TextureID _bloomMap = 0;
	TextureID _depthMap = 0;
	TextureID _dofMap = 0;
	TextureID _lensFlareMap = 0;
	TextureID _finalSceneMap = 0;
	TextureID _motionBlurMap = 0;

	// Strings
	string _cursorEntityID = "";
	string _lensFlareMapPath = "";

	// Matrices
	Matrix44 _viewMatrix = Matrix44(1.0f);
	Matrix44 _projectionMatrix = Matrix44(1.0f);
	Matrix44 _skyRotationMatrix = Matrix44(1.0f);
	Matrix44 _shadowMatrix = Matrix44(1.0f);

	// Vector4
	Vec4 _flareSourcePositionClipspace = Vec4(0.0f);
	Vec4 _clippingPlane = Vec4(0.0f);

	// Vector3
	Vec3 _cameraPosition = Vec3(0.0f);
	Vec3 _cameraFront = Vec3(0.0f);
	Vec3 _directionalLightPosition = Vec3(0.0f);
	Vec3 _shadowEyePosition = Vec3(0.0f);
	Vec3 _shadowAreaCenter = Vec3(0.0f);
	Vec3 _flareSourcePosition = Vec3(0.0f);
	Vec3 _ambientLightColor = Vec3(1.0f);
	Vec3 _directionalLightColor = Vec3(1.0f);
	Vec3 _spotLightColor = Vec3(1.0f);
	Vec3 _fogColor = Vec3(1.0f);
	Vec3 _mainSkyColor = Vec3(1.0f);
	Vec3 _mixSkyColor = Vec3(1.0f);

	// Floats
	float _ambientLightIntensity = 1.0f;
	float _directionalLightIntensity = 1.0f;
	float _spotLightIntensity = 1.0f;
	float _maxSpotLightAngle = 0.0f;
	float _maxSpotLightDistance = 0.0f;
	float _fogMinDistance = 0.0f;
	float _fogMaxDistance = 0.0f;
	float _fogThickness = 0.0f;
	float _bloomIntensity = 0.0f;
	float _cameraYaw = 0.0f;
	float _cameraPitch = 0.0f;
	float _nearZ = 0.0f;
	float _farZ = 0.0f;
	float _dofMaxDistance = 0.0f;
	float _dofBlurDistance = 0.0f;
	float _sceneReflectionHeight = 0.0f;
	float _shadowAreaSize = 0.0f;
	float _shadowAreaReach = 0.0f;
	float _shadowLightness = 0.0f;
	float _lensFlareAlpha = 0.0f;
	float _lensFlareIntensity = 0.0f;
	float _lensFlareMultiplier = 0.0f;
	float _motionBlurStrength = 0.0f;
	float _motionBlurMixValue = 0.0f;
	float _skyMixValue = 0.0f;
	float _mainSkyLightness = 0.0f;
	float _mixSkyLightness = 0.0f;

	// Integers
	unsigned int _bloomBlurCount = 0;
	unsigned int _triangleCount = 0;
	unsigned int _anisotropicFilteringQuality = 0;
	unsigned int _shadowQuality = 0;
	unsigned int _reflectionQuality = 0;
	unsigned int _refractionQuality = 0;

	// Booleans
	bool _isFxaaEnabled = false;
	bool _isAmbientLightingEnabled = false;
	bool _isDirectionalLightingEnabled = false;
	bool _isSpecularLightingEnabled = false;
	bool _isPointLightingEnabled = false;
	bool _isSpotLightingEnabled = false;
	bool _isFogEnabled = false;
	bool _isBloomEnabled = false;
	bool _isSkyExposureEnabled = false;
	bool _isShadowsEnabled = false;
	bool _isDofEnabled = false;
	bool _isMotionBlurEnabled = false;
	bool _isLensFlareEnabled = false;
	bool _isWireFrameRenderingEnabled = false;
	bool _isAabbFrameRenderingEnabled = false;
	bool _isShadowFrameRenderingEnabled = false;
	bool _isDebugRenderingEnabled = false;
	bool _isTriangleCountingEnabled = false;
	bool _isDofDynamic = false;

	// Miscellaneous
	BloomType _bloomType;
};