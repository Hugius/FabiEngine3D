#include "sky_entity_renderer.hpp"

void SkyEntityRenderer::bind()
{
	// Bind shader
	_shader.bind();

	// Global shader uniforms
	_shader.uploadUniform("u_viewMatrix", mat4(mat3(_shaderBus.getViewMatrix())));
	_shader.uploadUniform("u_projectionMatrix",     _shaderBus.getProjectionMatrix());
	_shader.uploadUniform("u_rotationMatrix",       _shaderBus.getSkyRotationMatrix());

	// Depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void SkyEntityRenderer::unbind()
{
	glDisable(GL_DEPTH_TEST);
	_shader.unbind();
}

void SkyEntityRenderer::render(const SkyEntity * entity)
{
	if (entity != nullptr)
	{
		if (entity->isEnabled())
		{
			// Uniforms
			_shader.uploadUniform("u_brightness", entity->getBrightness());
			_shader.uploadUniform("u_mixValue", entity->getMixValue());
			_shader.uploadUniform("u_color", entity->getColor());

			// Day texture
			_shader.uploadUniform("u_sampler_day", 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, entity->getDayCubeMap());

			// Night texture
			_shader.uploadUniform("u_sampler_night", 1);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_CUBE_MAP, entity->getNightCubeMap());

			// Bind
			glBindVertexArray(entity->getOglBuffer()->getVAO());

			// Render
			glDrawArrays(GL_TRIANGLES, 0, entity->getOglBuffer()->getVertexCount());

			// Unbind
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
			glBindVertexArray(0);
		}
	}
}