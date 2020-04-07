#include <WE3D/PostRenderer.hpp>
#include <WE3D/ShaderBus.hpp>

void PostRenderer::bind()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	p_shader.bind();
}

void PostRenderer::unbind()
{
	glDisable(GL_BLEND);
	p_shader.unbind();
}

void PostRenderer::render(const GuiEntity * entity, GLuint sceneMap, GLuint bloomMap, GLuint dofMap, GLuint blurMap)
{
	if (entity != nullptr)
	{
		if (entity->isEnabled())
		{
			// Shader uniforms
			p_shader.uploadUniform("u_modelMatrix", entity->getModelMatrix());
			p_shader.uploadUniform("u_mirrorHor", entity->isMirroredHorizonally());
			p_shader.uploadUniform("u_mirrorVer", entity->isMirroredVertically());
			p_shader.uploadUniform("u_nearZ", p_shaderBus.getNearZ());
			p_shader.uploadUniform("u_farZ", p_shaderBus.getFarZ());
			p_shader.uploadUniform("u_dofMinDistance", p_shaderBus.getDofMinDistance() / 1000.0f);
			p_shader.uploadUniform("u_bloomEnabled", p_shaderBus.isBloomEnabled());
			p_shader.uploadUniform("u_dofEnabled", p_shaderBus.isDofEnabled());

			// Texture uniforms
			p_shader.uploadUniform("u_sampler_scene", 0);
			p_shader.uploadUniform("u_sampler_bloom", 1);
			p_shader.uploadUniform("u_sampler_dof",   2);
			p_shader.uploadUniform("u_sampler_blur",  3);

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