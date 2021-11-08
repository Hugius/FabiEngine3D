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
	// Voids
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
	void setCursorEntityID(const string& value);
	void setLensFlareMapPath(const string& value);
	void setViewMatrix(const Matrix44 value);
	void setProjectionMatrix(const Matrix44 value);
	void setShadowMatrix(const Matrix44 value);
	void setClippingPlane(Vec4 value);
	void setCameraPosition(Vec3 value);
	void setCameraFront(Vec3 value);
	void setAmbientLightingColor(Vec3 value);
	void setDirectionalLightingPosition(Vec3 value);
	void setDirectionalLightingColor(Vec3 value);
	void setShadowEyePosition(Vec3 value);
	void setShadowCenterPosition(Vec3 value);
	void setFogColor(Vec3 value);
	void setFlareSourcePosition(Vec3 value);
	void setFlareSourceUV(Vec2 value);
	void setAmbientLightingIntensity(float value);
	void setDirectionalLightingIntensity(float value);
	void setFogMinDistance(float value);
	void setFogMaxDistance(float value);
	void setFogThickness(float value);
	void setBloomIntensity(float value);
	void setCameraYaw(float value);
	void setCameraPitch(float value);
	void setNearDistance(float value);
	void setFarDistance(float value);
	void setDofMaxDistance(float value);
	void setDofBlurDistance(float value);
	void setPlanarReflectionHeight(float value);
	void setShadowAreaSize(float value);
	void setShadowAreaReach(float value);
	void setShadowLightness(float value);
	void setLensFlareAlpha(float value);
	void setLensFlareIntensity(float value);
	void setLensFlareSensitivity(float value);
	void setMotionBlurStrength(float value);
	void setMotionBlurMixValue(float value);
	void setSkyMixValue(float value);
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
	void setReflectionsEnabled(bool value);
	void setAntiAliasingEnabled(bool value);
	void setAmbientLightingEnabled(bool value);
	void setDirectionalLightingEnabled(bool value);
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
	void setBloomType(BloomType value);

	// Strings
	const string& getCursorEntityID() const;
	const string& getLensFlareMapPath() const;

	// Matrices
	const Matrix44 getViewMatrix() const;
	const Matrix44 getProjectionMatrix() const;
	const Matrix44 getShadowMatrix() const;

	// Vectors
	const Vec4 getClippingPlane() const;
	const Vec3 getCameraPosition() const;
	const Vec3 getCameraFront() const;
	const Vec3 getAmbientLightingColor() const;
	const Vec3 getDirectionalLightingColor() const;
	const Vec3 getDirectionalLightingPosition() const;
	const Vec3 getShadowEyePosition() const;
	const Vec3 getShadowCenterPosition() const;
	const Vec3 getFogColor() const;
	const Vec3 getFlareSourcePosition() const;
	const Vec2 getFlareSourceUV() const;

	// Decimals
	const float getAmbientLightingIntensity() const;
	const float getDirectionalLightingIntensity() const;
	const float getFogMinDistance() const;
	const float getFogMaxDistance() const;
	const float getFogThickness() const;
	const float getBloomIntensity() const;
	const float getCameraYaw() const;
	const float getCameraPitch() const;
	const float getNearDistance() const;
	const float getFarDistance() const;
	const float getDofMaxDistance() const;
	const float getDofBlurDistance() const;
	const float getPlanarReflectionHeight() const;
	const float getShadowAreaSize() const;
	const float getShadowAreaReach() const;
	const float getShadowLightness() const;
	const float getLensFlareAlpha() const;
	const float getLensFlareIntensity() const;
	const float getLensFlareSensitivity() const;
	const float getMotionBlurStrength() const;
	const float getMotionBlurMixValue() const;
	const float getSkyMixValue() const;

	// Integers
	const unsigned int getBloomSize() const;
	const unsigned int getDofSize() const;
	const unsigned int getMotionBlurSize() const;
	const unsigned int getShadowQuality() const;
	const unsigned int getCubeReflectionQuality() const;
	const unsigned int getPlanarReflectionQuality() const;
	const unsigned int getRefractionQuality() const;
	const unsigned int getBloomBlurCount() const;
	const unsigned int getTriangleCount() const;

	// Booleans
	const bool isReflectionsEnabled() const;
	const bool isAntiAliasingEnabled() const;
	const bool isAmbientLightingEnabled() const;
	const bool isDirectionalLightingEnabled() const;
	const bool isFogEnabled() const;
	const bool isBloomEnabled() const;
	const bool isShadowsEnabled() const;
	const bool isDofEnabled() const;
	const bool isMotionBlurEnabled() const;
	const bool isLensFlareEnabled() const;
	const bool isWireFrameRenderingEnabled() const;
	const bool isAabbFrameRenderingEnabled() const;
	const bool isShadowFrameRenderingEnabled() const;
	const bool isDebugRenderingEnabled() const;
	const bool isTriangleCountingEnabled() const;
	const bool isDofDynamic() const;

	// Miscellaneous
	const TextureID getPrimarySceneMap() const;
	const TextureID getSecondarySceneMap() const;
	const TextureID getPlanarReflectionMap() const;
	const TextureID getWaterReflectionMap() const;
	const TextureID getWaterRefractionMap() const;
	const TextureID getShadowMap() const;
	const TextureID getBloomMap() const;
	const TextureID getDepthMap() const;
	const TextureID getDofMap() const;
	const TextureID getLensFlareMap() const;
	const TextureID getFinalSceneMap() const;
	const TextureID getMotionBlurMap() const;
	const BloomType getBloomType() const;

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
	Vec3 _fogColor = Vec3(1.0f);
	Vec2 _flareSourceUV = Vec2(0.0f);

	// Decimals
	float _ambientLightIntensity = 1.0f;
	float _directionalLightIntensity = 1.0f;
	float _bloomIntensity = 1.0f;
	float _fogMinDistance = 0.0f;
	float _fogMaxDistance = 0.0f;
	float _fogThickness = 1.0f;
	float _cameraYaw = 0.0f;
	float _cameraPitch = 0.0f;
	float _nearDistance = 0.0f;
	float _farDistance = 0.0f;
	float _dofMaxDistance = 0.0f;
	float _dofBlurDistance = 0.0f;
	float _planarReflectionHeight = 0.0f;
	float _shadowAreaSize = 0.0f;
	float _shadowAreaReach = 0.0f;
	float _shadowLightness = 0.0f;
	float _lensFlareAlpha = 0.0f;
	float _lensFlareSensitivity = 1.0f;
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
	BloomType _bloomType = BloomType::EVERYTHING;
};