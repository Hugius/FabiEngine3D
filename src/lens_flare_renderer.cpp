#include "lens_flare_renderer.hpp"
#include "render_bus.hpp"

void LensFlareRenderer::bind()
{
	// Bind shader
	_shader.bind();

	// Shader uniforms
	_shader.uploadUniform("u_depthMap", 0);
	_shader.uploadUniform("u_worldMap", 1);
	_shader.uploadUniform("u_flareMap", 2);
	_shader.uploadUniform("u_nearDistance", _renderBus.getNearDistance());
	_shader.uploadUniform("u_farDistance", _renderBus.getFarDistance());
	_shader.uploadUniform("u_lensFlareTransparency", _renderBus.getLensFlareTransparency());
	_shader.uploadUniform("u_lensFlareIntensity", _renderBus.getLensFlareIntensity());
	_shader.uploadUniform("u_cameraPosition", _renderBus.getCameraPosition());
	_shader.uploadUniform("u_flareSourcePosition", _renderBus.getFlareSourcePosition());
	_shader.uploadUniform("u_flareSourceUV", _renderBus.getFlareSourceUV());
	_shader.uploadUniform("u_isLensFlareEnabled", _renderBus.isLensFlareEnabled());

	// Bind textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _renderBus.getDepthMap());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, _renderBus.getFinalWorldMap());
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, _renderBus.getLensFlareMap());
}

void LensFlareRenderer::unbind()
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

void LensFlareRenderer::render(const shared_ptr<ImageEntity> entity)
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