#include "water_entity_renderer.hpp"
#include "configuration.hpp"

void WaterEntityRenderer::bind()
{
	// Bind shader
	_shader.bind();

	// Global shader uniforms
	_shader.uploadUniform("u_viewMatrix",				   _renderBus.getViewMatrix());
	_shader.uploadUniform("u_projectionMatrix",			   _renderBus.getProjectionMatrix());
	_shader.uploadUniform("u_directionalLightingPosition", _renderBus.getDirectionalLightingPosition());
	_shader.uploadUniform("u_cameraPosition",			   _renderBus.getCameraPos());
	_shader.uploadUniform("u_fogEnabled",				   _renderBus.isFogEnabled());
	_shader.uploadUniform("u_fogMinDistance",			   _renderBus.getFogMinDistance());
	_shader.uploadUniform("u_effectsEnabled",			   _renderBus.isWaterEffectsEnabled());
	_shader.uploadUniform("u_nearZ",					   _renderBus.getNearZ());
	_shader.uploadUniform("u_farZ",						   _renderBus.getFarZ());

	// Depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// Blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void WaterEntityRenderer::unbind()
{
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	_shader.unbind();
}

void WaterEntityRenderer::render(const WaterEntity* entity)
{
	if (entity->isVisible())
	{
		// Shader uniforms
		_shader.uploadUniform("u_rippleOffset", entity->getRippleOffset());
		_shader.uploadUniform("u_waveOffset", entity->getWaveOffset());
		_shader.uploadUniform("u_waveHeightFactor", entity->getWaveHeightFactor());
		_shader.uploadUniform("u_customPositionOffset", entity->getPosition());
		_shader.uploadUniform("u_uvRepeat", entity->getUvRepeat());
		_shader.uploadUniform("u_specularLightingFactor", entity->getSpecularLightingFactor());
		_shader.uploadUniform("u_specularLightingIntensity", entity->getSpecularLightingIntensity());
		_shader.uploadUniform("u_transparency", entity->getTransparency());
		_shader.uploadUniform("u_isWaving", entity->isWaving());
		_shader.uploadUniform("u_isRippling", entity->isRippling());
		_shader.uploadUniform("u_isSpecular", entity->isSpecularLighted());
		_shader.uploadUniform("u_isReflective", entity->isReflective());
		_shader.uploadUniform("u_isRefractive", entity->isRefractive());
		_shader.uploadUniform("u_color", entity->getColor());
		
		// Texture uniforms
		_shader.uploadUniform("u_sampler_reflectionMap", 0);
		_shader.uploadUniform("u_sampler_refractionMap", 1);
		_shader.uploadUniform("u_sampler_depthMap", 2);
		_shader.uploadUniform("u_sampler_dudvMap", 3);
		_shader.uploadUniform("u_sampler_normalMap", 4);
		_shader.uploadUniform("u_sampler_displacementMap", 5);
		
		// Textures
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _renderBus.getSceneReflectionMap());
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, _renderBus.getSceneRefractionMap());
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, _renderBus.getWaterDepthMap());
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, entity->getDudvMap());
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, entity->getNormalMap());
		glActiveTexture(GL_TEXTURE5);
		glBindTexture(GL_TEXTURE_2D, entity->getDisplacementMap());
		glActiveTexture(GL_TEXTURE0);

		// Bind
		glBindVertexArray(entity->getOglBuffer()->getVAO());

		// Render
		glDrawArrays(GL_TRIANGLES, 0, entity->getOglBuffer()->getVertexCount());
		_renderBus.increaseTriangleCount(entity->getOglBuffer()->getVertexCount() / 3);

		// Unbind
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
	}
}