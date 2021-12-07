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
	// VOID
	void setPrimaryWorldMap(TextureID value);
	void setSecondaryWorldMap(TextureID value);
	void setPlanarReflectionMap(TextureID value);
	void setWaterReflectionMap(TextureID value);
	void setWaterRefractionMap(TextureID value);
	void setShadowMap(TextureID value);
	void setBloomMap(TextureID value);
	void setDepthMap(TextureID value);
	void setDofMap(TextureID value);
	void setLensFlareMap(TextureID value);
	void setMotionBlurMap(TextureID value);
	void setFinalWorldMap(TextureID value);
	void setCursorEntityID(const string& value);
	void setLensFlareMapPath(const string& value);
	void setViewMatrix(const mat44 value);
	void setProjectionMatrix(const mat44 value);
	void setShadowMatrix(const mat44 value);
	void setClippingPlane(fvec4 value);
	void setCameraPosition(fvec3 value);
	void setCameraFront(fvec3 value);
	void setAmbientLightingColor(fvec3 value);
	void setDirectionalLightingPosition(fvec3 value);
	void setDirectionalLightingColor(fvec3 value);
	void setShadowEyePosition(fvec3 value);
	void setShadowCenterPosition(fvec3 value);
	void setFogColor(fvec3 value);
	void setFlareSourcePosition(fvec3 value);
	void setFlareSourceUV(fvec2 value);
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
	void setLensFlareTransparency(float value);
	void setLensFlareIntensity(float value);
	void setLensFlareSensitivity(float value);
	void setMotionBlurStrength(float value);
	void setMotionBlurMixValue(float value);
	void setSkyMixValue(float value);
	void setBloomQuality(unsigned int value);
	void setDofQuality(unsigned int value);
	void setMotionBlurQuality(unsigned int value);
	void setShadowQuality(unsigned int value);
	void setCubeReflectionQuality(unsigned int value);
	void setPlanarReflectionQuality(unsigned int value);
	void setPlanarRefractionQuality(unsigned int value);
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
	void setWireframeRenderingEnabled(bool value);
	void setAabbFrameRenderingEnabled(bool value);
	void setDebugRenderingEnabled(bool value);
	void setShadowFrameRenderingEnabled(bool value);
	void setTriangleCountingEnabled(bool value);
	void setDofDynamic(bool value);
	void setBloomType(BloomType value);

	// STRING
	const string& getCursorEntityID() const;
	const string& getLensFlareMapPath() const;

	// MAT44
	const mat44 getViewMatrix() const;
	const mat44 getProjectionMatrix() const;
	const mat44 getShadowMatrix() const;

	// FVEC4
	const fvec4 getClippingPlane() const;

	// FVEC3
	const fvec3 getCameraPosition() const;
	const fvec3 getCameraFront() const;
	const fvec3 getAmbientLightingColor() const;
	const fvec3 getDirectionalLightingColor() const;
	const fvec3 getDirectionalLightingPosition() const;
	const fvec3 getShadowEyePosition() const;
	const fvec3 getShadowCenterPosition() const;
	const fvec3 getFogColor() const;
	const fvec3 getFlareSourcePosition() const;

	// FVEC2
	const fvec2 getFlareSourceUV() const;

	// FLOAT
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
	const float getLensFlareTransparency() const;
	const float getLensFlareIntensity() const;
	const float getLensFlareSensitivity() const;
	const float getMotionBlurStrength() const;
	const float getMotionBlurMixValue() const;
	const float getSkyMixValue() const;

	// UNSIGNED INT
	const unsigned int getBloomQuality() const;
	const unsigned int getDofQuality() const;
	const unsigned int getMotionBlurQuality() const;
	const unsigned int getShadowQuality() const;
	const unsigned int getCubeReflectionQuality() const;
	const unsigned int getPlanarReflectionQuality() const;
	const unsigned int getPlanarRefractionQuality() const;
	const unsigned int getBloomBlurCount() const;
	const unsigned int getTriangleCount() const;

	// BOOL
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
	const bool isWireframeRenderingEnabled() const;
	const bool isAabbFrameRenderingEnabled() const;
	const bool isShadowFrameRenderingEnabled() const;
	const bool isDebugRenderingEnabled() const;
	const bool isTriangleCountingEnabled() const;
	const bool isDofDynamic() const;

	// MISCELLANEOUS
	const TextureID getPrimaryWorldMap() const;
	const TextureID getSecondaryWorldMap() const;
	const TextureID getPlanarReflectionMap() const;
	const TextureID getWaterReflectionMap() const;
	const TextureID getWaterRefractionMap() const;
	const TextureID getShadowMap() const;
	const TextureID getBloomMap() const;
	const TextureID getDepthMap() const;
	const TextureID getDofMap() const;
	const TextureID getLensFlareMap() const;
	const TextureID getFinalWorldMap() const;
	const TextureID getMotionBlurMap() const;
	const BloomType getBloomType() const;

private:
	// Textures
	TextureID _primaryWorldMap = 0;
	TextureID _secondaryWorldMap = 0;
	TextureID _planarReflectionMap = 0;
	TextureID _waterReflectionMap = 0;
	TextureID _waterRefractionMap = 0;
	TextureID _shadowMap = 0;
	TextureID _bloomMap = 0;
	TextureID _depthMap = 0;
	TextureID _dofMap = 0;
	TextureID _lensFlareMap = 0;
	TextureID _finalWorldMap = 0;
	TextureID _motionBlurMap = 0;

	// STRING
	string _cursorEntityID = "";
	string _lensFlareMapPath = "";

	// MAT44
	mat44 _viewMatrix = mat44(1.0f);
	mat44 _projectionMatrix = mat44(1.0f);
	mat44 _shadowMatrix = mat44(1.0f);

	// FVEC4
	fvec4 _clippingPlane = fvec4(0.0f);

	// FVEC3
	fvec3 _cameraPosition = fvec3(0.0f);
	fvec3 _cameraFront = fvec3(0.0f);
	fvec3 _directionalLightPosition = fvec3(0.0f);
	fvec3 _shadowEyePosition = fvec3(0.0f);
	fvec3 _shadowCenterPosition = fvec3(0.0f);
	fvec3 _flareSourcePosition = fvec3(0.0f);
	fvec3 _ambientLightColor = fvec3(1.0f);
	fvec3 _directionalLightColor = fvec3(1.0f);
	fvec3 _fogColor = fvec3(1.0f);

	// FVEC2
	fvec2 _flareSourceUV = fvec2(0.0f);

	// FLOAT
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
	float _lensFlareTransparency = 0.0f;
	float _lensFlareSensitivity = 1.0f;
	float _lensFlareIntensity = 1.0f;
	float _motionBlurStrength = 0.0f;
	float _motionBlurMixValue = 0.0f;
	float _skyMixValue = 0.0f;

	// UNSIGNED INT
	unsigned int _bloomQuality = Config::MIN_BLOOM_QUALITY;
	unsigned int _dofQuality = Config::MIN_DOF_QUALITY;
	unsigned int _motionBlurQuality = Config::MIN_MOTION_BLUR_QUALITY;
	unsigned int _shadowQuality = Config::MIN_SHADOW_QUALITY;
	unsigned int _cubeReflectionQuality = Config::MIN_REFLECTION_QUALITY;
	unsigned int _planarReflectionQuality = Config::MIN_REFLECTION_QUALITY;
	unsigned int _planarRefractionQuality = Config::MIN_REFRACTION_QUALITY;
	unsigned int _bloomBlurCount = 0;
	unsigned int _triangleCount = 0;

	// BOOL
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
	bool _isWireframeRenderingEnabled = false;
	bool _isAabbFrameRenderingEnabled = false;
	bool _isShadowFrameRenderingEnabled = false;
	bool _isDebugRenderingEnabled = false;
	bool _isTriangleCountingEnabled = false;
	bool _isDofDynamic = false;

	// MISCELLANEOUS
	BloomType _bloomType = BloomType::EVERYTHING;
};