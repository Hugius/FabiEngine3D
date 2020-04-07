#include <WE3D/BloomHdrRenderer.hpp>
#include <WE3D/ShaderBus.hpp>

void BloomHdrRenderer::bind()
{
	p_shader.bind();
}

void BloomHdrRenderer::unbind()
{
	p_shader.unbind();
}

void BloomHdrRenderer::render(const GuiEntity * entity, GLuint sceneMap)
{
	if (entity->isEnabled())
	{
		// Uniforms
		p_shader.uploadUniform("u_modelMatrix", entity->getModelMatrix());
		p_shader.uploadUniform("u_mirrorHor",   entity->isMirroredHorizonally());
		p_shader.uploadUniform("u_mirrorVer",   entity->isMirroredVertically());
		p_shader.uploadUniform("u_bloomBrightnessTreshold", p_shaderBus.getBloomTreshold());
		p_shader.uploadUniform("u_sampler_diffuse", 0);

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