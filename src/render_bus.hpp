#pragma once

#include "mathematics.hpp"
#include "bloom_type.hpp"
#include "configuration.hpp"
#include "texture_buffer.hpp"

#include <string>

using std::string;

class RenderBus final
{
public:
	void setPrimarySceneMap(shared_ptr<TextureBuffer> value);
	void setSecondarySceneMap(shared_ptr<TextureBuffer> value);
	void setPlanarReflectionMap(shared_ptr<TextureBuffer> value);
	void setWaterReflectionMap(shared_ptr<TextureBuffer> value);
	void setWaterRefractionMap(shared_ptr<TextureBuffer> value);
	void setWaterEdgeMap(shared_ptr<TextureBuffer> value);
	void setShadowMap(shared_ptr<TextureBuffer> value);
	void setBloomMap(shared_ptr<TextureBuffer> value);
	void setDepthMap(shared_ptr<TextureBuffer> value);
	void setDofMap(shared_ptr<TextureBuffer> value);
	void setLensFlareMap(shared_ptr<TextureBuffer> value);
	void setMotionBlurMap(shared_ptr<TextureBuffer> value);
	void setFinalSceneMap(shared_ptr<TextureBuffer> value);
	void setCursorEntityId(const string& value);
	void setLensFlareMapPath(const string& value);
	void setCameraView(const mat44& value);
	void setCameraProjection(const mat44& value);
	void setShadowView(const mat44& value);
	void setShadowProjection(const mat44& value);
	void setMinPosition(const fvec3& value);
	void setMaxPosition(const fvec3& value);
	void setCameraPosition(const fvec3& value);
	void setCameraUp(const fvec3& value);
	void setCameraFront(const fvec3& value);
	void setCameraRight(const fvec3& value);
	void setAmbientLightingColor(const fvec3& value);
	void setDirectionalLightingPosition(const fvec3& value);
	void setDirectionalLightingColor(const fvec3& value);
	void setShadowEyePosition(const fvec3& value);
	void setShadowEyeOffset(const fvec3& value);
	void setShadowCenterPosition(const fvec3& value);
	void setShadowCenterOffset(const fvec3& value);
	void setFogColor(const fvec3& value);
	void setFlareSourcePosition(const fvec3& value);
	void setFlareSourceUv(const fvec2& value);
	void setAmbientLightingIntensity(float value);
	void setDirectionalLightingIntensity(float value);
	void setFogMinDistance(float value);
	void setFogMaxDistance(float value);
	void setFogThickness(float value);
	void setBloomIntensity(float value);
	void setCameraYaw(float value);
	void setCameraPitch(float value);
	void setCameraNear(float value);
	void setCameraFar(float value);
	void setDofDynamicDistance(float value);
	void setDofBlurDistance(float value);
	void setPlanarReflectionHeight(float value);
	void setShadowSize(float value);
	void setShadowLightness(float value);
	void setLensFlareOpacity(float value);
	void setLensFlareIntensity(float value);
	void setLensFlareSensitivity(float value);
	void setMotionBlurIntensity(float value);
	void setMotionBlurMixValue(float value);
	void setMotionBlurDifference(fvec2 value);
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
	void setRefractionsEnabled(bool value);
	void setAntiAliasingEnabled(bool value);
	void setAmbientLightingEnabled(bool value);
	void setDirectionalLightingEnabled(bool value);
	void setFogEnabled(bool value);
	void setBloomEnabled(bool value);
	void setShadowsEnabled(bool value);
	void setDofEnabled(bool value);
	void setMotionBlurEnabled(bool value);
	void setLensFlareEnabled(bool value);
	void setShadowCircleEnabled(bool value);
	void setTriangleCountingEnabled(bool value);
	void setDofDynamic(bool value);
	void setBloomType(BloomType value);
	void setGuiDepth(unsigned int value);
	void setAnisotropicFilteringQuality(unsigned int value);
	void setSkyExposureIntensity(float value);
	void setSkyExposureSpeed(float value);
	void setSkyExposureLightness(float value);
	void setSkyExposureEnabled(bool value);
	void setShadowInterval(unsigned int value);
	void setShadowsFollowingCamera(bool value);

	const string& getCursorEntityId() const;
	const string& getLensFlareMapPath() const;

	const mat44& getCameraView() const;
	const mat44& getCameraProjection() const;
	const mat44& getShadowView() const;
	const mat44& getShadowProjection() const;

	const fvec3& getMinPosition() const;
	const fvec3& getMaxPosition() const;
	const fvec3& getCameraPosition() const;
	const fvec3& getCameraUp() const;
	const fvec3& getCameraFront() const;
	const fvec3& getCameraRight() const;
	const fvec3& getAmbientLightingColor() const;
	const fvec3& getDirectionalLightingColor() const;
	const fvec3& getDirectionalLightingPosition() const;
	const fvec3& getShadowEyePosition() const;
	const fvec3& getShadowEyeOffset() const;
	const fvec3& getShadowCenterPosition() const;
	const fvec3& getShadowCenterOffset() const;
	const fvec3& getFogColor() const;
	const fvec3& getFlareSourcePosition() const;

	const fvec2& getFlareSourceUv() const;
	const fvec2 getMotionBlurDifference() const;

	const float getAmbientLightingIntensity() const;
	const float getDirectionalLightingIntensity() const;
	const float getFogMinDistance() const;
	const float getFogMaxDistance() const;
	const float getFogThickness() const;
	const float getBloomIntensity() const;
	const float getCameraYaw() const;
	const float getCameraPitch() const;
	const float getCameraNear() const;
	const float getCameraFar() const;
	const float getDofDynamicDistance() const;
	const float getDofBlurDistance() const;
	const float getPlanarReflectionHeight() const;
	const float getShadowSize() const;
	const float getShadowLightness() const;
	const float getLensFlareOpacity() const;
	const float getLensFlareIntensity() const;
	const float getLensFlareSensitivity() const;
	const float getMotionBlurIntensity() const;
	const float getMotionBlurMixValue() const;
	const float getSkyExposureIntensity() const;
	const float getSkyExposureSpeed() const;
	const float getSkyExposureLightness() const;

	const unsigned int getBloomQuality() const;
	const unsigned int getDofQuality() const;
	const unsigned int getMotionBlurQuality() const;
	const unsigned int getShadowQuality() const;
	const unsigned int getCubeReflectionQuality() const;
	const unsigned int getPlanarReflectionQuality() const;
	const unsigned int getPlanarRefractionQuality() const;
	const unsigned int getBloomBlurCount() const;
	const unsigned int getTriangleCount() const;
	const unsigned int getGuiDepth() const;
	const unsigned int getAnisotropicFilteringQuality() const;
	const unsigned int getShadowInterval() const;

	const bool isReflectionsEnabled() const;
	const bool isRefractionsEnabled() const;
	const bool isAntiAliasingEnabled() const;
	const bool isAmbientLightingEnabled() const;
	const bool isDirectionalLightingEnabled() const;
	const bool isFogEnabled() const;
	const bool isBloomEnabled() const;
	const bool isShadowsEnabled() const;
	const bool isDofEnabled() const;
	const bool isMotionBlurEnabled() const;
	const bool isLensFlareEnabled() const;
	const bool isShadowCircleEnabled() const;
	const bool isTriangleCountingEnabled() const;
	const bool isDofDynamic() const;
	const bool isSkyExposureEnabled() const;
	const bool isShadowsFollowingCamera() const;

	const shared_ptr<TextureBuffer> getPrimarySceneMap() const;
	const shared_ptr<TextureBuffer> getSecondarySceneMap() const;
	const shared_ptr<TextureBuffer> getPlanarReflectionMap() const;
	const shared_ptr<TextureBuffer> getWaterReflectionMap() const;
	const shared_ptr<TextureBuffer> getWaterRefractionMap() const;
	const shared_ptr<TextureBuffer> getWaterEdgeMap() const;
	const shared_ptr<TextureBuffer> getShadowMap() const;
	const shared_ptr<TextureBuffer> getBloomMap() const;
	const shared_ptr<TextureBuffer> getDepthMap() const;
	const shared_ptr<TextureBuffer> getDofMap() const;
	const shared_ptr<TextureBuffer> getLensFlareMap() const;
	const shared_ptr<TextureBuffer> getFinalSceneMap() const;
	const shared_ptr<TextureBuffer> getMotionBlurMap() const;
	const BloomType getBloomType() const;

private:
	shared_ptr<TextureBuffer> _primarySceneMap = nullptr;
	shared_ptr<TextureBuffer> _secondarySceneMap = nullptr;
	shared_ptr<TextureBuffer> _planarReflectionMap = nullptr;
	shared_ptr<TextureBuffer> _waterReflectionMap = nullptr;
	shared_ptr<TextureBuffer> _waterRefractionMap = nullptr;
	shared_ptr<TextureBuffer> _waterEdgeMap = nullptr;
	shared_ptr<TextureBuffer> _shadowMap = nullptr;
	shared_ptr<TextureBuffer> _bloomMap = nullptr;
	shared_ptr<TextureBuffer> _depthMap = nullptr;
	shared_ptr<TextureBuffer> _dofMap = nullptr;
	shared_ptr<TextureBuffer> _lensFlareMap = nullptr;
	shared_ptr<TextureBuffer> _finalSceneMap = nullptr;
	shared_ptr<TextureBuffer> _motionBlurMap = nullptr;

	string _cursorEntityId = "";
	string _lensFlareMapPath = "";

	mat44 _cameraView = mat44(1.0f);
	mat44 _cameraProjection = mat44(1.0f);
	mat44 _shadowView = mat44(1.0f);
	mat44 _shadowProjection = mat44(1.0f);

	fvec3 _minPosition = fvec3(-FLT_MAX);
	fvec3 _maxPosition = fvec3(FLT_MAX);
	fvec3 _cameraPosition = fvec3(0.0f);
	fvec3 _cameraUp = fvec3(0.0f);
	fvec3 _cameraFront = fvec3(0.0f);
	fvec3 _cameraRight = fvec3(0.0f);
	fvec3 _directionalLightPosition = fvec3(0.0f);
	fvec3 _shadowEyePosition = fvec3(0.0f);
	fvec3 _shadowEyeOffset = fvec3(0.0f);
	fvec3 _shadowCenterPosition = fvec3(0.0f);
	fvec3 _shadowCenterOffset = fvec3(0.0f);
	fvec3 _flareSourcePosition = fvec3(0.0f);
	fvec3 _ambientLightColor = fvec3(1.0f);
	fvec3 _directionalLightColor = fvec3(1.0f);
	fvec3 _fogColor = fvec3(1.0f);

	fvec2 _flareSourceUv = fvec2(0.0f);
	fvec2 _motionBlurDifference = fvec2(0.0f);

	float _ambientLightIntensity = 1.0f;
	float _directionalLightIntensity = 1.0f;
	float _bloomIntensity = 1.0f;
	float _fogMinDistance = 0.0f;
	float _fogMaxDistance = 0.0f;
	float _fogThickness = 1.0f;
	float _cameraYaw = 0.0f;
	float _cameraPitch = 0.0f;
	float _cameraNear = 0.0f;
	float _cameraFar = 0.0f;
	float _dofDynamicDistance = 0.0f;
	float _dofBlurDistance = 0.0f;
	float _planarReflectionHeight = 0.0f;
	float _shadowSize = 0.0f;
	float _shadowLightness = 0.0f;
	float _lensFlareOpacity = 0.0f;
	float _lensFlareSensitivity = 1.0f;
	float _lensFlareIntensity = 1.0f;
	float _motionBlurIntensity = 0.0f;
	float _motionBlurMixValue = 0.0f;
	float _skyExposureIntensity = 0.0f;
	float _skyExposureSpeed = 0.0f;
	float _skyExposureLightness = 0.0f;

	unsigned int _bloomQuality = Config::MIN_BLOOM_QUALITY;
	unsigned int _dofQuality = Config::MIN_DOF_QUALITY;
	unsigned int _motionBlurQuality = Config::MIN_MOTION_BLUR_QUALITY;
	unsigned int _shadowQuality = Config::MIN_SHADOW_QUALITY;
	unsigned int _cubeReflectionQuality = Config::MIN_REFLECTION_QUALITY;
	unsigned int _planarReflectionQuality = Config::MIN_REFLECTION_QUALITY;
	unsigned int _planarRefractionQuality = Config::MIN_REFRACTION_QUALITY;
	unsigned int _anisotropicFilteringQuality = Config::MIN_ANISOTROPIC_FILTERING_QUALITY;
	unsigned int _bloomBlurCount = 0;
	unsigned int _triangleCount = 0;
	unsigned int _guiDepth = 0;
	unsigned int _shadowInterval = 0;

	bool _isReflectionsEnabled = true;
	bool _isRefractionsEnabled = true;
	bool _isAntiAliasingEnabled = false;
	bool _isAmbientLightingEnabled = false;
	bool _isDirectionalLightingEnabled = false;
	bool _isFogEnabled = false;
	bool _isBloomEnabled = false;
	bool _isShadowsEnabled = false;
	bool _isDofEnabled = false;
	bool _isMotionBlurEnabled = false;
	bool _isLensFlareEnabled = false;
	bool _isShadowCircleEnabled = false;
	bool _isTriangleCountingEnabled = false;
	bool _isDofDynamic = false;
	bool _isSkyExposureEnabled = false;
	bool _isShadowsFollowingCamera = false;

	BloomType _bloomType = BloomType::EVERYTHING;
};