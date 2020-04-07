#include "PostRenderer.hpp"
#include "ShaderBus.hpp"

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

void PostRenderer::render(const GuiEntity * entity, GLuint sceneMap, GLuint bloomMap, GLuint dofMap, GLuint blurMap)
{
	if (entity != nullptr)
	{
		if (entity->isEnabled())
		{
			// Shader uniforms
			_shader.uploadUniform("u_modelMatrix", entity->getModelMatrix());
			_shader.uploadUniform("u_mirrorHor", entity->isMirroredHorizonally());
			_shader.uploadUniform("u_mirrorVer", entity->isMirroredVertically());
			_shader.uploadUniform("u_nearZ", _shaderBus.getNearZ());
			_shader.uploadUniform("u_farZ", _shaderBus.getFarZ());
			_shader.uploadUniform("u_dofMinDistance", _shaderBus.getDofMinDistance() / 1000.0f);
			_shader.uploadUniform("u_bloomEnabled", _shaderBus.isBloomEnabled());
			_shader.uploadUniform("u_dofEnabled", _shaderBus.isDofEnabled());

			// Texture uniforms
			_shader.uploadUniform("u_sampler_scene", 0);
			_shader.uploadUniform("u_sampler_bloom", 1);
			_shader.uploadUniform("u_sampler_dof",   2);
			_shader.uploadUniform("u_sampler_blur",  3);

			// Bind
			glBindVertexArray(entity->getOglBuffer()->getVAO());
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, sceneMap);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, bloomMap);
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, dofMap);
			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, blurMap);

			// Render
			glDrawArrays(GL_TRIANGLES, 0, 6);

			// Unbind
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, 0);
			glBindVertexArray(0);
		}
	}
}