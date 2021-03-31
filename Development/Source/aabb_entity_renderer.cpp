#include "aabb_entity_renderer.hpp"

void AabbEntityRenderer::bind()
{
	// Bind shader
	_shader.bind();

	// Vertex shader uniforms
	_shader.uploadUniform("u_viewMatrix", _renderBus.getViewMatrix());
	_shader.uploadUniform("u_projMatrix", _renderBus.getProjectionMatrix());

	// Depth testing
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_CLAMP_NV);
	glDepthFunc(GL_LEQUAL);
}

void AabbEntityRenderer::unbind()
{
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_DEPTH_CLAMP_NV);
	_shader.unbind();
}

void AabbEntityRenderer::render(const shared_ptr<AabbEntity> entity)
{
	if (entity->isVisible())
	{
		// Shader uniforms
		_shader.uploadUniform("u_modelMatrix", entity->getModelMatrix());

		// Check if entity has a render buffer
		if (!entity->getRenderBuffers().empty())
		{
			// Bind
			glBindVertexArray(entity->getRenderBuffer()->getVAO());

			// Render
			glDrawArrays(GL_LINE_STRIP, 0, entity->getRenderBuffer()->getVertexCount());
			_renderBus.increaseTriangleCount(entity->getRenderBuffer()->getVertexCount() / 3);

			// Unbind
			glBindVertexArray(0);
		}
	}
}