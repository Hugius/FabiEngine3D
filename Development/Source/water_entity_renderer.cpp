#include "water_entity_renderer.hpp"
#include "configuration.hpp"

void WaterEntityRenderer::bind()
{
	// Bind shader
	_shader.bind();

	// Global shader uniforms
	_shader.uploadUniform("u_viewMatrix",       _shaderBus.getViewMatrix());
	_shader.uploadUniform("u_projectionMatrix", _shaderBus.getProjectionMatrix());
	_shader.uploadUniform("u_dirLightPos",      _shaderBus.getDirLightPos());
	_shader.uploadUniform("u_cameraPos",        _shaderBus.getCameraPos());
	_shader.uploadUniform("u_fogEnabled",       _shaderBus.isFogEnabled());
	_shader.uploadUniform("u_fogMinDistance",   _shaderBus.getFogMinDistance());
	_shader.uploadUniform("u_effectsEnabled",   _shaderBus.isWaterEffectsEnabled());
	_shader.uploadUniform("u_nearZ",            _shaderBus.getNearZ());
	_shader.uploadUniform("u_farZ",             _shaderBus.getFarZ());

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

void WaterEntityRenderer::render(const WaterEntity * entity)
{
	if (entity != nullptr)
	{
		if (entity->isEnabled())
		{
			// Shader uniforms
			_shader.uploadUniform("u_wavePos", entity->getWaveValue());
			_shader.uploadUniform("u_timeX", entity->getTimeX());
			_shader.uploadUniform("u_timeZ", entity->getTimeZ());
			_shader.uploadUniform("u_tileAmount", entity->getTileRepeat());
			_shader.uploadUniform("u_waving", entity->isWaving());
			_shader.uploadUniform("u_rippling", entity->isRippling());
			_shader.uploadUniform("u_color", entity->getColor());
			_shader.uploadUniform("u_shininess", entity->getShininess());
			_shader.uploadUniform("u_transparency", entity->getTransparency());

			// Texture uniforms
			_shader.uploadUniform("u_sampler_reflectionMap", 0);
			_shader.uploadUniform("u_sampler_refractionMap", 1);
			_shader.uploadUniform("u_sampler_depthMap", 2);
			_shader.uploadUniform("u_sampler_dudvMap", 3);
			_shader.uploadUniform("u_sampler_normalMap", 4);

			// Textures
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, _shaderBus.getSceneReflectionMap());
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, _shaderBus.getWaterRefractionMap());
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, _shaderBus.getDepthMap());
			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, entity->getDudvMap());
			glActiveTexture(GL_TEXTURE4);
			glBindTexture(GL_TEXTURE_2D, entity->getNormalMap());
			glActiveTexture(GL_TEXTURE0);

			// Bind
			glBindVertexArray(entity->getOglBuffer()->getVAO());

			// Render
			glDrawArrays(GL_TRIANGLES, 0, entity->getOglBuffer()->getVertexCount());

			// Unbind
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, 0);
			glBindVertexArray(0);
		}
	}
}