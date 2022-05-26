#pragma once

#include "mathematics.hpp"
#include "bloom_type.hpp"
#include "configuration.hpp"
#include "texture_buffer.hpp"

#include <string>

using std::string;

class RenderStorage final
{
public:
	void setPrimarySceneMap(shared_ptr<TextureBuffer> value);
	void setSecondarySceneMap(shared_ptr<TextureBuffer> value);
	void setPlanarReflectionMap(shared_ptr<TextureBuffer> value);
	void setPlanarRefractionMap(shared_ptr<TextureBuffer> value);
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
	void setCursorId(const string & value);
	void setLensFlareMapPath(const string & value);
	void setShadowView(const mat44 & value);
	void setShadowProjection(const mat44 & value);
	void setMinClipPosition(const fvec3 & value);
	void setMaxClipPosition(const fvec3 & value);
	void setAmbientLightingEnabled(bool value);
	void setAmbientLightingColor(const fvec3 & value);
	void setAmbientLightingIntensity(float value);
	void setDirectionalLightingIntensity(float value);
	void setDirectionalLightingPosition(const fvec3 & value);
	void setDirectionalLightingColor(const fvec3 & value);
	void setShadowPosition(const fvec3 & value);
	void setShadowPositionOffset(const fvec3 & value);
	void setShadowLookat(const fvec3 & value);
	void setShadowLookatOffset(const fvec3 & value);
	void setFogColor(const fvec3 & value);
	void setFlareSourcePosition(const fvec3 & value);
	void setFlareSourceUv(const fvec2 & value);
	void setMinFogDistance(float value);
	void setMaxFogDistance(float value);
	void setFogThickness(float value);
	void setBloomIntensity(float value);
	void setDofDynamicDistance(float value);
	void setDofBlurDistance(float value);
	void setPlanarReflectionHeight(float value);
	void setPlanarRefractionHeight(float value);
	void setShadowSize(float value);
	void setShadowLightness(float value);
	void setShadowBias(float value);
	void setLensFlareOpacity(float value);
	void setLensFlareIntensity(float value);
	void setLensFlareSensitivity(float value);
	void setMotionBlurIntensity(float value);
	void setMotionBlurMixValue(float value);
	void setMotionBlurDifference(const fvec2 & value);
	void setBloomQuality(int value);
	void setDofQuality(int value);
	void setMotionBlurQuality(int value);
	void setShadowQuality(int value);
	void setPlanarReflectionQuality(int value);
	void setPlanarRefractionQuality(int value);
	void setAnisotropicFilteringQuality(int value);
	void increaseTriangleCount(int value);
	void setBloomBlurCount(int value);
	void resetTriangleCount();
	void setReflectionsEnabled(bool value);
	void setRefractionsEnabled(bool value);
	void setAntiAliasingEnabled(bool value);
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
	void setGuiDepth(int value);
	void setSkyExposureIntensity(float value);
	void setSkyExposureSpeed(float value);
	void setSkyExposureLightness(float value);
	void setSkyExposureEnabled(bool value);
	void setShadowInterval(int value);
	void setShadowPcfCount(int value);
	void setShadowsFollowingCameraX(bool value);
	void setShadowsFollowingCameraY(bool value);
	void setShadowsFollowingCameraZ(bool value);

	const shared_ptr<TextureBuffer> getPrimarySceneTextureBuffer() const;
	const shared_ptr<TextureBuffer> getSecondarySceneTextureBuffer() const;
	const shared_ptr<TextureBuffer> getPlanarReflectionTextureBuffer() const;
	const shared_ptr<TextureBuffer> getPlanarRefractionTextureBuffer() const;
	const shared_ptr<TextureBuffer> getWaterReflectionTextureBuffer() const;
	const shared_ptr<TextureBuffer> getWaterRefractionTextureBuffer() const;
	const shared_ptr<TextureBuffer> getWaterEdgeTextureBuffer() const;
	const shared_ptr<TextureBuffer> getShadowTextureBuffer() const;
	const shared_ptr<TextureBuffer> getBloomTextureBuffer() const;
	const shared_ptr<TextureBuffer> getDepthTextureBuffer() const;
	const shared_ptr<TextureBuffer> getDofTextureBuffer() const;
	const shared_ptr<TextureBuffer> getLensFlareTextureBuffer() const;
	const shared_ptr<TextureBuffer> getFinalSceneTextureBuffer() const;
	const shared_ptr<TextureBuffer> getMotionBlurTextureBuffer() const;

	const string & getCursorId() const;
	const string & getLensFlareMapPath() const;

	const mat44 & getShadowView() const;
	const mat44 & getShadowProjection() const;

	const fvec3 & getMinClipPosition() const;
	const fvec3 & getMaxClipPosition() const;
	const fvec3 & getAmbientLightingColor() const;
	const fvec3 & getDirectionalLightingColor() const;
	const fvec3 & getDirectionalLightingPosition() const;
	const fvec3 & getShadowPosition() const;
	const fvec3 & getShadowPositionOffset() const;
	const fvec3 & getShadowLookat() const;
	const fvec3 & getShadowLookatOffset() const;
	const fvec3 & getFogColor() const;
	const fvec3 & getFlareSourcePosition() const;

	const fvec2 & getFlareSourceUv() const;
	const fvec2 getMotionBlurDifference() const;

	const float getAmbientLightingIntensity() const;
	const float getDirectionalLightingIntensity() const;
	const float getMinFogDistance() const;
	const float getMaxFogDistance() const;
	const float getFogThickness() const;
	const float getBloomIntensity() const;
	const float getDofDynamicDistance() const;
	const float getDofBlurDistance() const;
	const float getPlanarReflectionHeight() const;
	const float getPlanarRefractionHeight() const;
	const float getShadowSize() const;
	const float getShadowLightness() const;
	const float getShadowBias() const;
	const float getLensFlareOpacity() const;
	const float getLensFlareIntensity() const;
	const float getLensFlareSensitivity() const;
	const float getMotionBlurIntensity() const;
	const float getMotionBlurMixValue() const;
	const float getSkyExposureIntensity() const;
	const float getSkyExposureSpeed() const;
	const float getSkyExposureLightness() const;

	const int getBloomQuality() const;
	const int getDofQuality() const;
	const int getMotionBlurQuality() const;
	const int getShadowQuality() const;
	const int getPlanarReflectionQuality() const;
	const int getPlanarRefractionQuality() const;
	const int getAnisotropicFilteringQuality() const;
	const int getBloomBlurCount() const;
	const int getTriangleCount() const;
	const int getGuiDepth() const;
	const int getShadowInterval() const;
	const int getShadowPcfCount() const;

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
	const bool isShadowsFollowingCameraX() const;
	const bool isShadowsFollowingCameraY() const;
	const bool isShadowsFollowingCameraZ() const;

	const BloomType getBloomType() const;

private:
	shared_ptr<TextureBuffer> _primarySceneTextureBuffer = nullptr;
	shared_ptr<TextureBuffer> _secondarySceneTextureBuffer = nullptr;
	shared_ptr<TextureBuffer> _planarReflectionTextureBuffer = nullptr;
	shared_ptr<TextureBuffer> _planarRefractionTextureBuffer = nullptr;
	shared_ptr<TextureBuffer> _waterReflectionTextureBuffer = nullptr;
	shared_ptr<TextureBuffer> _waterRefractionTextureBuffer = nullptr;
	shared_ptr<TextureBuffer> _waterEdgeTextureBuffer = nullptr;
	shared_ptr<TextureBuffer> _shadowTextureBuffer = nullptr;
	shared_ptr<TextureBuffer> _bloomTextureBuffer = nullptr;
	shared_ptr<TextureBuffer> _depthTextureBuffer = nullptr;
	shared_ptr<TextureBuffer> _dofTextureBuffer = nullptr;
	shared_ptr<TextureBuffer> _lensFlareTextureBuffer = nullptr;
	shared_ptr<TextureBuffer> _finalSceneTextureBuffer = nullptr;
	shared_ptr<TextureBuffer> _motionBlurTextureBuffer = nullptr;

	string _cursorId = "";
	string _lensFlareMapPath = "";

	mat44 _shadowView = mat44(1.0f);
	mat44 _shadowProjection = mat44(1.0f);

	fvec3 _minClipPosition = fvec3(-FLT_MAX);
	fvec3 _maxClipPosition = fvec3(FLT_MAX);
	fvec3 _directionalLightingPosition = fvec3(0.0f);
	fvec3 _shadowPosition = fvec3(0.0f);
	fvec3 _shadowPositionOffset = fvec3(0.0f);
	fvec3 _shadowLookat = fvec3(0.0f);
	fvec3 _shadowLookatOffset = fvec3(0.0f);
	fvec3 _flareSourcePosition = fvec3(0.0f);
	fvec3 _ambientLightingColor = fvec3(1.0f);
	fvec3 _directionalLightingColor = fvec3(1.0f);
	fvec3 _fogColor = fvec3(1.0f);

	fvec2 _flareSourceUv = fvec2(0.0f);
	fvec2 _motionBlurDifference = fvec2(0.0f);

	float _ambientLightingIntensity = 1.0f;
	float _directionalLightingIntensity = 1.0f;
	float _bloomIntensity = 1.0f;
	float _minFogDistance = 0.0f;
	float _maxFogDistance = 0.0f;
	float _fogThickness = 1.0f;
	float _dofDynamicDistance = 0.0f;
	float _dofBlurDistance = 0.0f;
	float _planarReflectionHeight = 0.0f;
	float _planarRefractionHeight = 0.0f;
	float _shadowSize = 0.0f;
	float _shadowLightness = 0.0f;
	float _shadowBias = 0.0f;
	float _lensFlareOpacity = 0.0f;
	float _lensFlareSensitivity = 1.0f;
	float _lensFlareIntensity = 1.0f;
	float _motionBlurIntensity = 1.0f;
	float _motionBlurMixValue = 0.0f;
	float _skyExposureIntensity = 1.0f;
	float _skyExposureSpeed = 0.0f;
	float _skyExposureLightness = 1.0f;

	int _bloomQuality = 1;
	int _dofQuality = 1;
	int _motionBlurQuality = 1;
	int _shadowQuality = 2048;
	int _planarReflectionQuality = 128;
	int _planarRefractionQuality = 128;
	int _anisotropicFilteringQuality = 1;
	int _bloomBlurCount = 0;
	int _triangleCount = 0;
	int _guiDepth = 0;
	int _shadowInterval = 0;
	int _shadowPcfCount = 0;

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
	bool _isShadowsFollowingCameraX = false;
	bool _isShadowsFollowingCameraY = false;
	bool _isShadowsFollowingCameraZ = false;

	BloomType _bloomType = BloomType::EVERYTHING;
};