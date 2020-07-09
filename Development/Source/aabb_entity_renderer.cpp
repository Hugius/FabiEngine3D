#include "aabb_entity_renderer.hpp"

void AabbEntityRenderer::bind()
{
	// Bind shader
	_shader.bind();

	// Vertex shader uniforms
	_shader.uploadUniform("u_viewMatrix", _shaderBus.getViewMatrix());
	_shader.uploadUniform("u_projMatrix", _shaderBus.getProjectionMatrix());

	// Depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void AabbEntityRenderer::unbind()
{
	_shader.unbind();
	glDisable(GL_DEPTH_TEST);
}

void AabbEntityRenderer::render(const AabbEntity* entity)
{
	if (entity->isEnabled())
	{
		// Shader uniforms
		_shader.uploadUniform("u_modelMatrix", entity->getModelMatrix());

		// VAO
		glBindVertexArray(entity->getOglBuffer()->getVAO());

		// Render
		glDrawArrays(GL_LINE_STRIP, 0, entity->getOglBuffer()->getVertexCount());

		// Unbind
		glBindVertexArray(0);
	}
}