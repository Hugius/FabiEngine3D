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
	void setSkyReflectionCubeMapDay(GLuint val);
	void setSkyReflectionCubeMapNight(GLuint val);
	void setSceneReflectionMap(GLuint val);
	void setSceneRefractionMap(GLuint val);
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
	void setSceneReflectionHeight(float val);
	void setSceneReflectionFactor(float val);

	// Integers
	void setBloomBlurSize(int val);

	// Booleans
	void setMSAAEnabled(bool val);
	void setAmbLightEnabled(bool val);
	void setDirLightEnabled(bool val);
	void setSpecLightEnabled(bool val);
	void setPointLightEnabled(bool val);
	void setFogEnabled(bool val);
	void setLightMappingEnabled(bool val);
	void setSkyReflectionsEnabled(bool val);
	void setSceneReflectionsEnabled(bool val);
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
	const GLuint getSceneMap()                    const;
	const GLuint getSkyReflectionCubeMapDay()     const;
	const GLuint getSceneReflectionCubeMapNight() const;
	const GLuint getSceneReflectionMap()          const;
	const GLuint getSceneRefractionMap()          const;
	const GLuint getShadowMap()                   const;
	const GLuint getBloomMap()                    const;
	const GLuint getBloomedDofSceneMap()          const;
	const GLuint getDepthMap()                    const;
	const GLuint getBlurMap()                     const;
	const GLuint getMotionBlurMap()               const;

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
	const float getSceneReflectionHeight() const;
	const float getSceneReflectionFactor() const;

	// Integers
	const int getBloomBlurSize() const;

	// Booleans
	const bool isMSAAEnabled()             const;
	const bool isAmbLightingEnabled()      const;
	const bool isDirLightingEnabled()      const;
	const bool isSpecLightingEnabled()     const;
	const bool isPointLightingEnabled()    const;
	const bool isFogEnabled()              const;
	const bool isLightMappingEnabled()     const;
	const bool isSkyReflectionsEnabled()   const;
	const bool isSceneReflectionsEnabled() const;
	const bool isBloomEnabled()            const;
	const bool isWaterEffectsEnabled()     const;
	const bool isSkyHdrEnabled()           const;
	const bool isShadowsEnabled()          const;
	const bool isDofEnabled()              const;
	const bool isMotionBlurEnabled()       const;
	const bool isWireframeEnabled()        const;
	const bool isAabbFrameEnabled()        const;
	const bool isDebugRenderEnabled()      const;

private:
	// Textures
	GLuint _sceneMap                  = 0;
	GLuint _skyReflectionCubeMapDay   = 0;
	GLuint _skyReflectionCubeMapNight = 0;
	GLuint _sceneReflectionMap        = 0;
	GLuint _sceneRefractionMap        = 0;
	GLuint _shadowMap                 = 0;
	GLuint _bloomMap                  = 0;
	GLuint _bloomedDofSceneMap        = 0;
	GLuint _depthMap                  = 0;
	GLuint _blurMap                   = 0;
	GLuint _motionBlurMap             = 0;
	
	// Matrices
	mat4 _viewMatrix        = mat4(1.0f);
	mat4 _projectionMatrix  = mat4(1.0f);
	mat4 _skyRotationMatrix = mat4(1.0f);
	mat4 _shadowMatrix      = mat4(1.0f);

	// Vectors
	vec3  _cameraPosition   = vec3(0.0f);
	vec3  _dirLightPosition = vec3(0.0f);

	// Floats
	float _ambientLightingStrength     = 0.0f;
	float _directionalLightingStrength = 0.0f;
	float _specularLightingStrength    = 0.0f;
	float _fogMinDistance              = 0.0f;
	float _bloomIntensity              = 0.0f;
	float _bloomTreshold               = 0.0f;
	float _cameraYaw                   = 0.0f;
	float _cameraPitch                 = 0.0f;
	float _skyBrightness               = 0.0f;
	float _nearZ                       = 0.0f;
	float _farZ                        = 0.0f;
	float _dofMinDistance              = 0.0f;
	float _skyReflectionMixValue       = 0.0f;
	float _skyReflectionFactor         = 0.0f;
	float _sceneReflectionHeight       = 0.0f;
	float _sceneReflectionFactor       = 0.0f;
	
	// Integers
	int _bloomBlurSize = 0;

	// Booleans
	bool _msaaEnabled                = false;
	bool _ambientLightingEnabled     = false;
	bool _directionalLightingEnabled = false;
	bool _specularLightingEnabled    = false;
	bool _pointLightingEnabled       = false;
	bool _fogEnabled                 = false;
	bool _lightMappingEnabled        = false;
	bool _skyReflectionsEnabled      = false;
	bool _sceneReflectionsEnabled    = false;
	bool _bloomEnabled               = false;
	bool _waterEffectsEnabled        = false;
	bool _skyHdrEnabled              = false;
	bool _shadowsEnabled             = false;
	bool _dofEnabled                 = false;
	bool _motionBlurEnabled          = false;
	bool _wireframeEnabled           = false;
	bool _aabbFrameEnabled           = false;
	bool _debugRenderEnabled         = false;
};