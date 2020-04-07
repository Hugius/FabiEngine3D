#include <WE3D/WaterEntityRenderer.hpp>
#include <WE3D/Configuration.hpp>

void WaterEntityRenderer::bind()
{
	// Bind shader
	p_shader.bind();

	// Global shader uniforms
	p_shader.uploadUniform("u_viewMatrix",       p_shaderBus.getViewMatrix());
	p_shader.uploadUniform("u_projectionMatrix", p_shaderBus.getProjectionMatrix());
	p_shader.uploadUniform("u_dirLightPos",      p_shaderBus.getDirLightPos());
	p_shader.uploadUniform("u_cameraPos",        p_shaderBus.getCameraPos());
	p_shader.uploadUniform("u_fogEnabled",       p_shaderBus.isFogEnabled());
	p_shader.uploadUniform("u_fogMinDistance",   p_shaderBus.getFogMinDistance());
	p_shader.uploadUniform("u_effectsEnabled",   p_shaderBus.isWaterEffectsEnabled());
	p_shader.uploadUniform("u_nearZ",            p_shaderBus.getNearZ());
	p_shader.uploadUniform("u_farZ",             p_shaderBus.getFarZ());

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

	p_shader.unbind();
}

void WaterEntityRenderer::render(const WaterEntity * entity)
{
	if (entity != nullptr)
	{
		if (entity->isEnabled())
		{
			// Shader uniforms
			p_shader.uploadUniform("u_wavePos", entity->getWaveValue());
			p_shader.uploadUniform("u_timeX", entity->getTimeX());
			p_shader.uploadUniform("u_timeZ", entity->getTimeZ());
			p_shader.uploadUniform("u_tileAmount", entity->getTileRepeat());
			p_shader.uploadUniform("u_waving", entity->isWaving());
			p_shader.uploadUniform("u_rippling", entity->isRippling());
			p_shader.uploadUniform("u_color", entity->getColor());
			p_shader.uploadUniform("u_shininess", entity->getShininess());
			p_shader.uploadUniform("u_transparency", entity->getTransparency());

			// Texture uniforms
			p_shader.uploadUniform("u_sampler_reflectionMap", 0);
			p_shader.uploadUniform("u_sampler_refractionMap", 1);
			p_shader.uploadUniform("u_sampler_depthMap", 2);
			p_shader.uploadUniform("u_sampler_dudvMap", 3);
			p_shader.uploadUniform("u_sampler_normalMap", 4);

			// Textures
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, p_shaderBus.getSSRMap());
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, p_shaderBus.getWaterRefractionMap());
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, p_shaderBus.getDepthMap());
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