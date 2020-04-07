#include <GLM/gtc/matrix_transform.hpp>

#include <WE3D/ShadowManager.hpp>
#include <WE3D/ShaderBus.hpp>

void ShadowManager::loadShadows(vec3 eye, vec3 center, float size, float reach)
{
	p_eye    = eye;
	p_center = center;
	p_size   = size;
	p_reach  = reach;
}

void ShadowManager::update(ShaderBus& shaderBus)
{
	shaderBus.setShadowMatrix(p_createLightSpaceMatrix());
}

mat4 ShadowManager::p_createLightSpaceMatrix()
{
	glEnable(GL_DEPTH_CLAMP_NV);

	// Matrix generation
	mat4 lightView = glm::lookAt(p_eye, p_center, vec3(0.0f, 1.0f, 0.0f));
	mat4 lightProj = glm::ortho(-p_size, p_size, -p_size, p_size, 1.0f, p_reach);
	return lightProj * lightView;
}