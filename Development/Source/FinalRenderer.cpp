#include <WE3D/FinalRenderer.hpp>
#include <WE3D/ShaderBus.hpp>

void FinalRenderer::bind()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	p_shader.bind();
}

void FinalRenderer::unbind()
{
	glDisable(GL_BLEND);
	p_shader.unbind();
}

void FinalRenderer::render(const GuiEntity * entity, GLuint sceneMap)
{
	if (entity != nullptr)
	{
		if (entity->isEnabled())
		{
			// Uniforms
			p_shader.uploadUniform("u_modelMatrix", entity->getModelMatrix());
			p_shader.uploadUniform("u_mirrorHor", entity->isMirroredHorizonally());
			p_shader.uploadUniform("u_mirrorVer", entity->isMirroredVertically());
			p_shader.uploadUniform("u_sampler_scene", 0);

			// Bind
			glBindVertexArray(entity->getOglBuffer()->getVAO());
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, sceneMap);

			// Render
			glDrawArrays(GL_TRIANGLES, 0, 6);

			// Unbind
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, 0);
			glBindVertexArray(0);
		}
	}
}