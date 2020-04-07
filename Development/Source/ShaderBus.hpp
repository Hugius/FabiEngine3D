#pragma once
#include <GLEW/glew.h>
#include <GLM/glm.hpp>

using glm::vec3;
using glm::mat4;

class ShaderBus final
{
public:
	ShaderBus() = default;

	// Textures
	void setSceneMap(GLuint val);
	void setDayReflectionCubeMap(GLuint val);
	void setNightReflectionCubeMap(GLuint val);
	void setSSRMap(GLuint val);
	void setWaterRefractionMap(GLuint val);
	void setShadowMap(GLuint val);
	void setBloomMap(GLuint val);
	void setBloomedDofSceneMap(GLuint val);
	void setDepthMap(GLuint val);
	void setBlurMap(GLuint val);
	void setMotionBlurMap(GLuint val);

	// Matrices
	void setViewMatrix(const mat4 & val);
	void setProjectionMatrix(const mat4 & val);
	void setSkyRotationMatrix(const mat4 & val);
	void setShadowMatrix(const mat4 & val);

	// Vectors
	void setCameraPos(vec3 val);
	void setDirLightPos(vec3 val);

	// Floats
	void setAmbLightStrength(float val);
	void setDirLightStrength(float val);
	void setSpecLightStrength(float val);
	void setFogMinDistance(float val);
	void setBloomIntensity(float val);
	void setBloomTreshold(float val);
	void setCameraYaw(float val);
	void setCameraPitch(float val);
	void setSkyBrightness(float val);
	void setNearZ(float val);
	void setFarZ(float val);
	void setDofMinDistance(float val);
	void setSkyReflectionMixValue(float val);
	void setSkyReflectionFactor(float val);
	void setSSRHeight(float val);
	void setSSRFactor(float val);

	// Integers
	void setBloomBlurSize(int val);

	// Booleans
	void setMSAAEnabled(bool val);
	void setSSREnabled(bool val);
	void setAmbLightEnabled(bool val);
	void setDirLightEnabled(bool val);
	void setSpecLightEnabled(bool val);
	void setPointLightEnabled(bool val);
	void setFogEnabled(bool val);
	void setLightMappingEnabled(bool val);
	void setSkyReflectionsEnabled(bool val);
	void setBloomEnabled(bool val);
	void setWaterEffectsEnabled(bool val);
	void setSkyHdrEnabled(bool val);
	void setShadowsEnabled(bool val);
	void setDofEnabled(bool val);
	void setMotionBlurEnabled(bool val);
	void setWireframeEnabled(bool val);
	void setAabbFrameEnabled(bool val);
	void setDebugRenderEnabled(bool val);

	// Textures
	const GLuint getSceneMap()               const;
	const GLuint getDayReflectionCubeMap()   const;
	const GLuint getNightReflectionCubeMap() const;
	const GLuint getSSRMap()                 const;
	const GLuint getWaterRefractionMap()     const;
	const GLuint getShadowMap()              const;
	const GLuint getBloomMap()               const;
	const GLuint getBloomedDofSceneMap()     const;
	const GLuint getDepthMap()               const;
	const GLuint getBlurMap()                const;
	const GLuint getMotionBlurMap()          const;

	// Matrices
	const mat4 & getViewMatrix()        const;
	const mat4 & getProjectionMatrix()  const;
	const mat4 & getSkyRotationMatrix() const;
	const mat4 & getShadowMatrix()      const;

	// Vectors
	const vec3  getCameraPos()   const;
	const vec3  getDirLightPos() const;

	// Floats
	const float getAmbLightStrength()      const;
	const float getDirLightStrength()      const;
	const float getSpecLightStrength()     const;
	const float getFogMinDistance()        const;
	const float getBloomIntensity()        const;
	const float getBloomTreshold()         const;
	const float getCameraYaw()             const;
	const float getCameraPitch()           const;
	const float getSkyBrightness()         const;
	const float getNearZ()                 const;
	const float getFarZ()                  const;
	const float getDofMinDistance()        const;
	const float getSkyReflectionMixValue() const;
	const float getSkyReflectionFactor()   const;
	const float getSSRHeight()             const;
	const float getSSRFactor()             const;

	// Integers
	const int getBloomBlurSize() const;

	// Booleans
	const bool isMSAAEnabled()           const;
	const bool isSSREnabled()            const;
	const bool isAmbLightingEnabled()    const;
	const bool isDirLightingEnabled()    const;
	const bool isSpecLightingEnabled()   const;
	const bool isPointLightingEnabled()  const;
	const bool isFogEnabled()            const;
	const bool isLightMappingEnabled()   const;
	const bool isSkyReflectionsEnabled() const;
	const bool isBloomEnabled()          const;
	const bool isWaterEffectsEnabled()   const;
	const bool isSkyHdrEnabled()         const;
	const bool isShadowsEnabled()        const;
	const bool isDofEnabled()            const;
	const bool isMotionBlurEnabled()     const;
	const bool isWireframeEnabled()      const;
	const bool isAabbFrameEnabled()      const;
	const bool isDebugRenderEnabled()    const;

private:
	// Textures
	GLuint p_sceneMap               = 0;
	GLuint p_dayReflectionCubeMap   = 0;
	GLuint p_nightReflectionCubeMap = 0;
	GLuint p_ssrMap                 = 0;
	GLuint p_waterRefractionMap     = 0;
	GLuint p_shadowMap              = 0;
	GLuint p_bloomMap               = 0;
	GLuint p_bloomedDofSceneMap     = 0;
	GLuint p_depthMap               = 0;
	GLuint p_blurMap                = 0;
	GLuint p_motionBlurMap          = 0;
	
	// Matrices
	mat4 p_viewMatrix        = mat4(1.0f);
	mat4 p_projectionMatrix  = mat4(1.0f);
	mat4 p_skyRotationMatrix = mat4(1.0f);
	mat4 p_shadowMatrix      = mat4(1.0f);

	// Vectors
	vec3  p_cameraPosition   = vec3(0.0f);
	vec3  p_dirLightPosition = vec3(0.0f);

	// Floats
	float p_ambientLightingStrength     = 0.0f;
	float p_directionalLightingStrength = 0.0f;
	float p_specularLightingStrength    = 0.0f;
	float p_fogMinDistance              = 0.0f;
	float p_bloomIntensity              = 0.0f;
	float p_bloomTreshold               = 0.0f;
	float p_cameraYaw                   = 0.0f;
	float p_cameraPitch                 = 0.0f;
	float p_skyBrightness               = 0.0f;
	float p_nearZ                       = 0.0f;
	float p_farZ                        = 0.0f;
	float p_dofMinDistance              = 0.0f;
	float p_skyReflectionMixValue       = 0.0f;
	float p_skyReflectionFactor         = 0.0f;
	float p_ssrHeight                   = 0.0f;
	float p_ssrFactor                   = 0.0f;
	
	// Integers
	int p_bloomBlurSize = 0;

	// Booleans
	bool p_msaaEnabled                = false;
	bool p_ambientLightingEnabled     = false;
	bool p_directionalLightingEnabled = false;
	bool p_specularLightingEnabled    = false;
	bool p_pointLightingEnabled       = false;
	bool p_fogEnabled                 = false;
	bool p_lightMappingEnabled        = false;
	bool p_skyReflectionsEnabled      = false;
	bool p_ssrEnabled                 = false;
	bool p_bloomEnabled               = false;
	bool p_waterEffectsEnabled        = false;
	bool p_skyHdrEnabled              = false;
	bool p_shadowsEnabled             = false;
	bool p_dofEnabled                 = false;
	bool p_motionBlurEnabled          = false;
	bool p_wireframeEnabled           = false;
	bool p_aabbFrameEnabled           = false;
	bool p_debugRenderEnabled         = false;
};