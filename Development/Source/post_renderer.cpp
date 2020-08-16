#include "post_renderer.hpp"
#include "render_bus.hpp"

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
		_shader.uploadUniform("u_nearZ", _renderBus.getNearZ());
		_shader.uploadUniform("u_farZ", _renderBus.getFarZ());
		_shader.uploadUniform("u_bloomEnabled", _renderBus.isBloomEnabled());
		_shader.uploadUniform("u_dofEnabled", _renderBus.isDofEnabled());
		_shader.uploadUniform("u_lensFlareEnabled", _renderBus.isLensFlareEnabled());
		_shader.uploadUniform("u_dofMinDistance", _renderBus.getDofMinDistance());
		_shader.uploadUniform("u_lensFlareAlpha", _renderBus.getLensFlareAlpha());
		_shader.uploadUniform("u_lensFlareIntensity", _renderBus.getLensFlareIntensity());

		// Texture uniforms
		_shader.uploadUniform("u_sampler_scene", 0);
		_shader.uploadUniform("u_sampler_bloom", 1);
		_shader.uploadUniform("u_sampler_depth", 2);
		_shader.uploadUniform("u_sampler_blur", 3);
		_shader.uploadUniform("u_sampler_flare", 4);
		
		// Bind
		glBindVertexArray(entity->getOglBuffer()->getVAO());
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _renderBus.getSceneMap());
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, _renderBus.getBloomMap());
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, _renderBus.getDofDepthMap());
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, _renderBus.getBlurMap());
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, _renderBus.getLensFlareMap());

		// Render
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// Unbind
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
	}
}