#include "dof_renderer.hpp"
#include "render_bus.hpp"

void DofRenderer::bind()
{
	// Bind shader
	_shader.bind();

	// Shader uniforms
	_shader.uploadUniform("u_depthMap", 0);
	_shader.uploadUniform("u_sceneMap", 1);
	_shader.uploadUniform("u_dofMap", 2);
	_shader.uploadUniform("u_nearDistance", _renderBus.getNearDistance());
	_shader.uploadUniform("u_farDistance", _renderBus.getFarDistance());
	_shader.uploadUniform("u_dofMaxDistance", _renderBus.getDofMaxDistance());
	_shader.uploadUniform("u_dofBlurDistance", _renderBus.getDofBlurDistance());
	_shader.uploadUniform("u_isDofEnabled", _renderBus.isDofEnabled());
	_shader.uploadUniform("u_isDofDynamic", _renderBus.isDofDynamic());

	// Bind textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _renderBus.getDepthMap());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, _renderBus.getFinalSceneMap());
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, _renderBus.getDofMap());
}

void DofRenderer::unbind()
{
	// Unbind textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Unbind shader
	_shader.unbind();
}

void DofRenderer::render(const shared_ptr<ImageEntity> entity)
{
	// Temporary values
	const auto buffer = entity->getRenderBuffer();

	// Bind buffer
	glBindVertexArray(buffer->getVAO());

	// Render
	glDrawArrays(GL_TRIANGLES, 0, buffer->getVertexCount());

	// Unbind buffer
	glBindVertexArray(0);
}