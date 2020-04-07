#include <WE3D/GuiEntityRenderer.hpp>

void GuiEntityRenderer::bind()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	p_shader.bind();

	p_shader.uploadUniform("u_nearZ", p_shaderBus.getNearZ());
	p_shader.uploadUniform("u_farZ", p_shaderBus.getFarZ());
}

void GuiEntityRenderer::unbind()
{
	glDisable(GL_BLEND);
	p_shader.unbind();
}

void GuiEntityRenderer::render(const GuiEntity * entity)
{
	if (entity != nullptr)
	{
		if (entity->isEnabled())
		{
			// Uniforms
			p_shader.uploadUniform("u_modelMatrix",   entity->getModelMatrix());
			p_shader.uploadUniform("u_mirrorHor",     entity->isMirroredHorizonally());
			p_shader.uploadUniform("u_mirrorVer",     entity->isMirroredVertically());
			p_shader.uploadUniform("u_color",         entity->getColor());
			p_shader.uploadUniform("u_isDepthEntity", entity->isDepthEntity());
			p_shader.uploadUniform("u_sampler_diffuse", 0);

			// Bind
			glBindVertexArray(entity->getOglBuffer()->getVAO());
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap());

			// Render
			glDrawArrays(GL_TRIANGLES, 0, 6);

			// Unbind
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, 0);
			glBindVertexArray(0);
		}
	}
}