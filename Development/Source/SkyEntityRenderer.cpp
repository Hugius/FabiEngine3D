#include <WE3D/SkyEntityRenderer.hpp>

void SkyEntityRenderer::bind()
{
	// Bind shader
	p_shader.bind();

	// Global shader uniforms
	p_shader.uploadUniform("u_viewMatrix", mat4(mat3(p_shaderBus.getViewMatrix())));
	p_shader.uploadUniform("u_projectionMatrix",     p_shaderBus.getProjectionMatrix());
	p_shader.uploadUniform("u_rotationMatrix",       p_shaderBus.getSkyRotationMatrix());
	p_shader.uploadUniform("u_brightness",           p_shaderBus.getSkyBrightness());

	// Depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void SkyEntityRenderer::unbind()
{
	glDisable(GL_DEPTH_TEST);
	p_shader.unbind();
}

void SkyEntityRenderer::render(const SkyEntity * entity)
{
	if (entity != nullptr)
	{
		if (entity->isEnabled())
		{
			// Uniforms
			p_shader.uploadUniform("u_mixValue", entity->getMixValue());

			// Day texture
			p_shader.uploadUniform("u_sampler_day", 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, entity->getDayCubeMap());

			// Night texture
			p_shader.uploadUniform("u_sampler_night", 1);
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