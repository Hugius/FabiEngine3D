#pragma once

#include "mathematics.hpp"
#include "bloom_type.hpp"
#include "render_utils.hpp"
#include "configuration.hpp"

#include <string>

using std::string;

class RenderBus final
{
public:
	// Textures
	void setPrimarySceneMap(TextureID value);
	void setSecondarySceneMap(TextureID value);
	void setPlanarReflectionMap(TextureID value);
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
	void setShadowMatrix(const Matrix44 value);

	// Vectors
	void setClippingPlane(Vec4 value);
	void setCameraPosition(Vec3 value);
	void setCameraFront(Vec3 value);
	void setAmbientLightingColor(Vec3 value);
	void setDirectionalLightingPosition(Vec3 value);
	void setDirectionalLightingColor(Vec3 value);
	void setSpotLightingColor(Vec3 value);
	void setShadowEyePosition(Vec3 value);
	void setShadowCenterPosition(Vec3 value);
	void setFogColor(Vec3 value);
	void setFlareSourcePosition(Vec3 value);
	void setFlareSourceUV(Vec2 value);

	// Floats
	void setAmbientLightingIntensity(float value);
	void setDirectionalLightingIntensity(float value);
	void setSpotLightingIntensity(float value);
	void setMaxSpotLightingAngle(float value);
	void setMaxSpotLightingDistance(float value);
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
	void setPlanarReflectionHeight(float value);
	void setShadowAreaSize(float value);
	void setShadowAreaReach(float value);
	void setShadowLightness(float value);
	void setLensFlareAlpha(float value);
	void setLensFlareIntensity(float value);
	void setLensFlareSize(float value);
	void setMotionBlurStrength(float value);
	void setMotionBlurMixValue(float value);
	void setSkyMixValue(float value);

	// Integers
	void setBloomSize(unsigned int value);
	void setDofSize(unsigned int value);
	void setMotionBlurSize(unsigned int value);
	void setShadowQuality(unsigned int value);
	void setCubeReflectionQuality(unsigned int value);
	void setPlanarReflectionQuality(unsigned int value);
	void setRefractionQuality(unsigned int value);
	void increaseTriangleCount(unsigned int value);
	void setBloomBlurCount(unsigned int value);
	void resetTriangleCount();

	// Booleans
	void setReflectionsEnabled(bool value);
	void setAntiAliasingEnabled(bool value);
	void setAmbientLightingEnabled(bool value);
	void setDirectionalLightingEnabled(bool value);
	void setSpotLightingEnabled(bool value);
	void setFogEnabled(bool value);
	void setBloomEnabled(bool value);
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
	const TextureID getPlanarReflectionMap();
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
	const Matrix44 getShadowMatrix();

	// Vectors
	const Vec4 getClippingPlane();
	const Vec3 getCameraPosition();
	const Vec3 getCameraFront();
	const Vec3 getAmbientLightingColor();
	const Vec3 getDirectionalLightingColor();
	const Vec3 getDirectionalLightingPosition();
	const Vec3 getSpotLightingColor();
	const Vec3 getShadowEyePosition();
	const Vec3 getShadowCenterPosition();
	const Vec3 getFogColor();
	const Vec3 getFlareSourcePosition();
	const Vec2 getFlareSourceUV();

	// Floats
	const float getAmbientLightingIntensity();
	const float getDirectionalLightingIntensity();
	const float getSpotLightingIntensity();
	const float getMaxSpotLightingAngle();
	const float getMaxSpotLightingDistance();
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
	const float getPlanarReflectionHeight();
	const float getShadowAreaSize();
	const float getShadowAreaReach();
	const float getShadowLightness();
	const float getLensFlareAlpha();
	const float getLensFlareIntensity();
	const float getLensFlareSize();
	const float getMotionBlurStrength();
	const float getMotionBlurMixValue();
	const float getSkyMixValue();

	// Integers
	const unsigned int getBloomSize();
	const unsigned int getDofSize();
	const unsigned int getMotionBlurSize();
	const unsigned int getShadowQuality();
	const unsigned int getCubeReflectionQuality();
	const unsigned int getPlanarReflectionQuality();
	const unsigned int getRefractionQuality();
	const unsigned int getBloomBlurCount();
	const unsigned int getTriangleCount();

	// Booleans
	const bool isReflectionsEnabled();
	const bool isAntiAliasingEnabled();
	const bool isAmbientLightingEnabled();
	const bool isDirectionalLightingEnabled();
	const bool isSpotLightingEnabled();
	const bool isFogEnabled();
	const bool isBloomEnabled();
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
	TextureID _planarReflectionMap = 0;
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
	Matrix44 _shadowMatrix = Matrix44(1.0f);

	// Vectors
	Vec4 _clippingPlane = Vec4(0.0f);
	Vec3 _cameraPosition = Vec3(0.0f);
	Vec3 _cameraFront = Vec3(0.0f);
	Vec3 _directionalLightPosition = Vec3(0.0f);
	Vec3 _shadowEyePosition = Vec3(0.0f);
	Vec3 _shadowCenterPosition = Vec3(0.0f);
	Vec3 _flareSourcePosition = Vec3(0.0f);
	Vec3 _ambientLightColor = Vec3(1.0f);
	Vec3 _directionalLightColor = Vec3(1.0f);
	Vec3 _spotLightColor = Vec3(1.0f);
	Vec3 _fogColor = Vec3(1.0f);
	Vec2 _flareSourceUV = Vec2(0.0f);

	// Floats
	float _ambientLightIntensity = 1.0f;
	float _directionalLightIntensity = 1.0f;
	float _spotLightIntensity = 1.0f;
	float _bloomIntensity = 1.0f;
	float _maxSpotLightAngle = 0.0f;
	float _maxSpotLightDistance = 0.0f;
	float _fogMinDistance = 0.0f;
	float _fogMaxDistance = 0.0f;
	float _fogThickness = 1.0f;
	float _cameraYaw = 0.0f;
	float _cameraPitch = 0.0f;
	float _nearZ = 0.0f;
	float _farZ = 0.0f;
	float _dofMaxDistance = 0.0f;
	float _dofBlurDistance = 0.0f;
	float _planarReflectionHeight = 0.0f;
	float _shadowAreaSize = 0.0f;
	float _shadowAreaReach = 0.0f;
	float _shadowLightness = 0.0f;
	float _lensFlareAlpha = 0.0f;
	float _lensFlareSize = 1.0f;
	float _lensFlareIntensity = 1.0f;
	float _motionBlurStrength = 0.0f;
	float _motionBlurMixValue = 0.0f;
	float _skyMixValue = 0.0f;

	// Integers
	unsigned int _bloomSize = Config::MIN_BLOOM_SIZE;
	unsigned int _dofSize = Config::MIN_DOF_SIZE;
	unsigned int _motionBlurSize = Config::MIN_MOTION_BLUR_SIZE;
	unsigned int _shadowQuality = Config::MIN_SHADOW_QUALITY;
	unsigned int _cubeReflectionQuality = Config::MIN_REFLECTION_QUALITY;
	unsigned int _planarReflectionQuality = Config::MIN_REFLECTION_QUALITY;
	unsigned int _refractionQuality = Config::MIN_REFRACTION_QUALITY;
	unsigned int _bloomBlurCount = 0;
	unsigned int _triangleCount = 0;

	// Booleans
	bool _isReflectionsEnabled = true;
	bool _isAntiAliasingEnabled = false;
	bool _isAmbientLightingEnabled = false;
	bool _isDirectionalLightingEnabled = false;
	bool _isSpotLightingEnabled = false;
	bool _isFogEnabled = false;
	bool _isBloomEnabled = false;
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