#include <WE3D/AabbEntityRenderer.hpp>

void AabbEntityRenderer::bind()
{
	// Bind shader
	p_shader.bind();

	// Vertex shader uniforms
	p_shader.uploadUniform("u_viewMatrix", p_shaderBus.getViewMatrix());
	p_shader.uploadUniform("u_projMatrix", p_shaderBus.getProjectionMatrix());

	// Depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void AabbEntityRenderer::unbind()
{
	p_shader.unbind();
	glDisable(GL_DEPTH_TEST);
}

void AabbEntityRenderer::render(const AabbEntity* entity)
{
	if (entity != nullptr)
	{
		if (entity->isEnabled())
		{
			// Shader uniforms
			p_shader.uploadUniform("u_modelMatrix", entity->getModelMatrix());

			// VAO
			glBindVertexArray(entity->getOglBuffer()->getVAO());

			// Render
			glDrawArrays(GL_LINE_STRIP, 0, entity->getOglBuffer()->getVertexCount());

			// Unbind
			glBindVertexArray(0);
		}
	}
}