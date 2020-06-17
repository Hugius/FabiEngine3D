#include "shadow_renderer.hpp"
#include "shader_bus.hpp"
#include "configuration.hpp"

void ShadowRenderer::bind()
{	
	// Shader
	_shader.bind();
	_shader.uploadUniform("u_lightSpaceMatrix", _shaderBus.getShadowMatrix());

	// OpenGL
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CLIP_DISTANCE1);
}

void ShadowRenderer::unbind()
{
	glDisable(GL_CLIP_DISTANCE1);
	glDisable(GL_DEPTH_TEST);

	_shader.unbind();
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
		_shader.uploadUniform("u_modelMatrix",        entity->getModelMatrix());
		_shader.uploadUniform("u_alphaObject",        entity->isTransparent());
		_shader.uploadUniform("u_maxY",               entity->getMaxY());
		_shader.uploadUniform("u_sampler_diffuseMap", 0);

		// Bind
		int index = 0;
		for (auto & buffer : entity->getOglBuffers())
		{
			if (entity->isTransparent() && entity->hasDiffuseMap())
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap(index));
			}

			glBindVertexArray(buffer->getVAO());

			// Render
			if (buffer->isInstanced())
			{
				_shader.uploadUniform("u_isInstanced", true);
				glDrawArraysInstanced(GL_TRIANGLES, 0, buffer->getVertexCount(), buffer->getOffsetCount());
			}
			else
			{
				_shader.uploadUniform("u_isInstanced", false);
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