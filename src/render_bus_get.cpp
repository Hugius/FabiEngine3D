#include "render_bus.hpp"
#include "render_bus.hpp"

const shared_ptr<TextureBuffer> RenderBus::getPlanarReflectionMap() const
{
	return _planarReflectionMap;
}

const shared_ptr<TextureBuffer> RenderBus::getWaterReflectionMap() const
{
	return _waterReflectionMap;
}

const shared_ptr<TextureBuffer> RenderBus::getWaterRefractionMap() const
{
	return _waterRefractionMap;
}

const shared_ptr<TextureBuffer> RenderBus::getBloomMap() const
{
	return _bloomMap;
}

const shared_ptr<TextureBuffer> RenderBus::getPrimarySceneMap() const
{
	return _primarySceneMap;
}

const shared_ptr<TextureBuffer> RenderBus::getSecondarySceneMap() const
{
	return _secondarySceneMap;
}

const shared_ptr<TextureBuffer> RenderBus::getShadowMap() const
{
	return _shadowMap;
}

const shared_ptr<TextureBuffer> RenderBus::getMotionBlurMap() const
{
	return _motionBlurMap;
}

const shared_ptr<TextureBuffer> RenderBus::getLensFlareMap() const
{
	return _lensFlareMap;
}

const shared_ptr<TextureBuffer> RenderBus::getDepthMap() const
{
	return _depthMap;
}

const shared_ptr<TextureBuffer> RenderBus::getDofMap() const
{
	return _dofMap;
}

const shared_ptr<TextureBuffer> RenderBus::getFinalSceneMap() const
{
	return _finalSceneMap;
}

const mat44 RenderBus::getViewMatrix() const
{
	return _viewMatrix;
}

const mat44 RenderBus::getProjectionMatrix() const
{
	return _projectionMatrix;
}

const mat44 RenderBus::getShadowMatrix() const
{
	return _shadowMatrix;
}

const fvec2 RenderBus::getFlareSourceUv() const
{
	return _flareSourceUv;
}

const fvec4 RenderBus::getClippingPlane() const
{
	return _clippingPlane;
}

const fvec3 RenderBus::getCameraPosition() const
{
	return _cameraPosition;
}

const fvec3 RenderBus::getCameraFront() const
{
	return _cameraFront;
}

const fvec3 RenderBus::getAmbientLightingColor() const
{
	return _ambientLightColor;
}

const fvec3 RenderBus::getDirectionalLightingPosition() const
{
	return _directionalLightPosition;
}

const fvec3 RenderBus::getShadowEyePosition() const
{
	return _shadowEyePosition;
}

const fvec3 RenderBus::getShadowCenterPosition() const
{
	return _shadowCenterPosition;
}

const fvec3 RenderBus::getFogColor() const
{
	return _fogColor;
}

const fvec3 RenderBus::getFlareSourcePosition() const
{
	return _flareSourcePosition;
}

const fvec3 RenderBus::getDirectionalLightingColor() const
{
	return _directionalLightColor;
}

const float RenderBus::getPlanarReflectionHeight() const
{
	return _planarReflectionHeight;
}

const float RenderBus::getShadowSize() const
{
	return _shadowSize;
}

const float RenderBus::getShadowReach() const
{
	return _shadowReach;
}

const float RenderBus::getShadowLightness() const
{
	return _shadowLightness;
}

const float RenderBus::getLensFlareTransparency() const
{
	return _lensFlareTransparency;
}

const float RenderBus::getLensFlareIntensity() const
{
	return _lensFlareIntensity;
}

const float RenderBus::getLensFlareSensitivity() const
{
	return _lensFlareSensitivity;
}

const float RenderBus::getMotionBlurStrength() const
{
	return _motionBlurStrength;
}

const float RenderBus::getMotionBlurMixValue() const
{
	return _motionBlurMixValue;
}

const float RenderBus::getSkyMixValue() const
{
	return _skyMixValue;
}

const unsigned int RenderBus::getBloomQuality() const
{
	return _bloomQuality;
}

const unsigned int RenderBus::getDofQuality() const
{
	return _dofQuality;
}

const unsigned int RenderBus::getMotionBlurQuality() const
{
	return _motionBlurQuality;
}

const float RenderBus::getAmbientLightingIntensity() const
{
	return _ambientLightIntensity;
}

const float RenderBus::getDirectionalLightingIntensity() const
{
	return _directionalLightIntensity;
}

const float RenderBus::getFogMinDistance() const
{
	return _fogMinDistance;
}

const float RenderBus::getFogMaxDistance() const
{
	return _fogMaxDistance;
}

const float RenderBus::getFogThickness() const
{
	return _fogThickness;
}

const float RenderBus::getBloomIntensity() const
{
	return _bloomIntensity;
}

const float RenderBus::getCameraYaw() const
{
	return _cameraYaw;
}

const float RenderBus::getCameraPitch() const
{
	return _cameraPitch;
}

const float RenderBus::getNearDistance() const
{
	return _nearDistance;
}

const float RenderBus::getFarDistance() const
{
	return _farDistance;
}

const float RenderBus::getDofDynamicDistance() const
{
	return _dofDynamicDistance;
}

const float RenderBus::getDofBlurDistance() const
{
	return _dofBlurDistance;
}

const unsigned int RenderBus::getBloomBlurCount() const
{
	return _bloomBlurCount;
}

const unsigned int RenderBus::getTriangleCount() const
{
	return _triangleCount;
}

const unsigned int RenderBus::getGuiDepth() const
{
	return _guiDepth;
}

const unsigned int RenderBus::getAnisotropicFilteringQuality() const
{
	return _anisotropicFilteringQuality;
}

const unsigned int RenderBus::getShadowQuality() const
{
	return _shadowQuality;
}

const unsigned int RenderBus::getCubeReflectionQuality() const
{
	return _cubeReflectionQuality;
}

const unsigned int RenderBus::getPlanarReflectionQuality() const
{
	return _planarReflectionQuality;
}

const unsigned int RenderBus::getPlanarRefractionQuality() const
{
	return _planarRefractionQuality;
}

const bool RenderBus::isAntiAliasingEnabled() const
{
	return _isAntiAliasingEnabled;
}

const bool RenderBus::isAmbientLightingEnabled() const
{
	return _isAmbientLightingEnabled;
}

const bool RenderBus::isDirectionalLightingEnabled() const
{
	return _isDirectionalLightingEnabled;
}

const bool RenderBus::isReflectionsEnabled() const
{
	return _isReflectionsEnabled;
}

const bool RenderBus::isFogEnabled() const
{
	return _isFogEnabled;
}

const bool RenderBus::isBloomEnabled() const
{
	return _isBloomEnabled;
}

const bool RenderBus::isShadowsEnabled() const
{
	return _isShadowsEnabled;
}

const bool RenderBus::isDofEnabled() const
{
	return _isDofEnabled;
}

const bool RenderBus::isMotionBlurEnabled() const
{
	return _isMotionBlurEnabled;
}

const bool RenderBus::isLensFlareEnabled() const
{
	return _isLensFlareEnabled;
}

const bool RenderBus::isWireframeRenderingEnabled() const
{
	return _isWireframeRenderingEnabled;
}

const bool RenderBus::isAabbFrameRenderingEnabled() const
{
	return _isAabbFrameRenderingEnabled;
}

const bool RenderBus::isShadowFrameRenderingEnabled() const
{
	return _isShadowFrameRenderingEnabled;
}

const bool RenderBus::isTriangleCountingEnabled() const
{
	return _isTriangleCountingEnabled;
}

const bool RenderBus::isDofDynamic() const
{
	return _isDofDynamic;
}

const BloomType RenderBus::getBloomType() const
{
	return _bloomType;
}

const string& RenderBus::getCursorEntityID() const
{
	return _cursorEntityID;
}

const string& RenderBus::getLensFlareMapPath() const
{
	return _lensFlareMapPath;
}