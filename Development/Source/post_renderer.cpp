#include "post_renderer.hpp"
#include "shader_bus.hpp"

void PostRenderer::bind()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	_shader.bind();
}

void PostRenderer::unbind()
{
	glDisable(GL_BLEND);
	_shader.unbind();
}

void PostRenderer::render(const GuiEntity* entity)
{
	if (entity->isVisible())
	{
		// Shader uniforms
		_shader.uploadUniform("u_modelMatrix", entity->getModelMatrix());
		_shader.uploadUniform("u_mirrorHor", entity->isMirroredHorizonally());
		_shader.uploadUniform("u_mirrorVer", entity->isMirroredVertically());
		_shader.uploadUniform("u_nearZ", _shaderBus.getNearZ());
		_shader.uploadUniform("u_farZ", _shaderBus.getFarZ());
		_shader.uploadUniform("u_bloomEnabled", _shaderBus.isBloomEnabled());
		_shader.uploadUniform("u_dofEnabled", _shaderBus.isDofEnabled());
		_shader.uploadUniform("u_lensFlareEnabled", _shaderBus.isLensFlareEnabled());
		_shader.uploadUniform("u_dofMinDistance", _shaderBus.getDofMinDistance());
		_shader.uploadUniform("u_lensFlareAlpha", _shaderBus.getLensFlareAlpha());
		_shader.uploadUniform("u_lensFlareIntensity", _shaderBus.getLensFlareIntensity());

		// Texture uniforms
		_shader.uploadUniform("u_sampler_scene", 0);
		_shader.uploadUniform("u_sampler_bloom", 1);
		_shader.uploadUniform("u_sampler_depth", 2);
		_shader.uploadUniform("u_sampler_blur", 3);
		_shader.uploadUniform("u_sampler_flare", 4);
		
		// Bind
		glBindVertexArray(entity->getOglBuffer()->getVAO());
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _shaderBus.getSceneMap());
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, _shaderBus.getBloomMap());
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, _shaderBus.getDepthMap());
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, _shaderBus.getBlurMap());
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, _shaderBus.getLensFlareMap());

		// Render
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// Unbind
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
	}
}