#include "lens_renderer.hpp"
#include "render_bus.hpp"

void LensRenderer::bind()
{
	// Bind shader
	_shader.bind();

	// Shader uniforms
	_shader.uploadUniform("u_depthMap", 0);
	_shader.uploadUniform("u_sceneMap", 1);
	_shader.uploadUniform("u_flareMap", 2);
	_shader.uploadUniform("u_dirtMap", 3);
	_shader.uploadUniform("u_nearZ", _renderBus.getNearZ());
	_shader.uploadUniform("u_farZ", _renderBus.getFarZ());
	_shader.uploadUniform("u_lensFlareAlpha", _renderBus.getLensFlareAlpha());
	_shader.uploadUniform("u_lensFlareIntensity", _renderBus.getLensFlareIntensity());
	_shader.uploadUniform("u_flareSourcePositionClipspace", _renderBus.getFlareSourcePositionClipspace());
	_shader.uploadUniform("u_flareSourcePosition", _renderBus.getFlareSourcePosition());
	_shader.uploadUniform("u_cameraPosition", _renderBus.getCameraPosition());
	_shader.uploadUniform("u_isLensFlareEnabled", _renderBus.isLensFlareEnabled());

	// Bind textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _renderBus.getDepthMap());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, _renderBus.getFinalSceneMap());
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, _renderBus.getLensFlareMap());
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, _renderBus.getLensFlareMap());
}

void LensRenderer::unbind()
{
	// Unbind textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Unbind shader
	_shader.unbind();
}

void LensRenderer::render(const shared_ptr<ImageEntity> entity)
{
	// Bind buffer
	glBindVertexArray(entity->getRenderBuffer()->getVAO());

	// Render
	glDrawArrays(GL_TRIANGLES, 0, 6);

	// Unbind buffer
	glBindVertexArray(0);
}