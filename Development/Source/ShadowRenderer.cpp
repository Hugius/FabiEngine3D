#include <WE3D/ShadowRenderer.hpp>
#include <WE3D/ShaderBus.hpp>
#include <WE3D/Configuration.hpp>

void ShadowRenderer::bind()
{	
	// Shader
	p_shader.bind();
	p_shader.uploadUniform("u_lightSpaceMatrix", p_shaderBus.getShadowMatrix());

	// OpenGL
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CLIP_DISTANCE1);
}

void ShadowRenderer::unbind()
{
	glDisable(GL_CLIP_DISTANCE1);
	glDisable(GL_DEPTH_TEST);

	p_shader.unbind();
}

void ShadowRenderer::renderGameEntity(const GameEntity * entity)
{
	if (entity->isEnabled() && entity->isShadowed())
	{
		// Face culling
		if (entity->isFaceCulled())
		{
			glEnable(GL_CULL_FACE);
		}

		// Uniforms
		p_shader.uploadUniform("u_modelMatrix",        entity->getModelMatrix());
		p_shader.uploadUniform("u_alphaObject",        entity->isTransparent());
		p_shader.uploadUniform("u_maxY",               entity->getMaxY());
		p_shader.uploadUniform("u_sampler_diffuseMap", 0);

		// Bind
		int index = 0;
		for (auto & buffer : entity->getOglBuffers())
		{
			if (entity->isTransparent())
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap(index));
			}

			glBindVertexArray(buffer->getVAO());

			// Render
			if (buffer->isInstanced())
			{
				p_shader.uploadUniform("u_isInstanced", true);
				glDrawArraysInstanced(GL_TRIANGLES, 0, buffer->getVertexCount(), buffer->getOffsetCount());
			}
			else
			{
				p_shader.uploadUniform("u_isInstanced", false);
				glDrawArrays(GL_TRIANGLES, 0, buffer->getVertexCount());
			}

			index++;
		}

		// Unbind
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);

		// Face culling
		if (entity->isFaceCulled())
		{
			glDisable(GL_CULL_FACE);
		}
	}
}