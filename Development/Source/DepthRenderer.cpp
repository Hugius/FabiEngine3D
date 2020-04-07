#include "DepthRenderer.hpp"
#include "ShaderBus.hpp"
#include "Configuration.hpp"

void DepthRenderer::bind()
{
	// Bind shader
	_shader.bind();

	// Vertex shader uniforms
	_shader.uploadUniform("u_viewMatrix", _shaderBus.getViewMatrix());
	_shader.uploadUniform("u_projMatrix", _shaderBus.getProjectionMatrix());

	// Texture uniforms
	_shader.uploadUniform("u_sampler_diffuseMap", 0);

	// Depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CLIP_DISTANCE1);
}

void DepthRenderer::unbind()
{
	glDisable(GL_CLIP_DISTANCE1);
	glDisable(GL_DEPTH_TEST);

	_shader.unbind();
}

void DepthRenderer::renderTerrainEntity(const TerrainEntity * entity)
{
	if (entity != nullptr)
	{
		if (entity->isEnabled())
		{
			// Faceculling
			glEnable(GL_CULL_FACE);

			// Shader uniforms
			_shader.uploadUniform("u_modelMatrix",   mat4(1.0f));
			_shader.uploadUniform("u_isAlphaObject", false);
			_shader.uploadUniform("u_isInstanced",   false);
			_shader.uploadUniform("u_maxY",          (std::numeric_limits<float>::max)());

			// Bind
			glBindVertexArray(entity->getOglBuffer()->getVAO());

			// Render
			glDrawArrays(GL_TRIANGLES, 0, entity->getOglBuffer()->getVertexCount());

			// Unbind
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, 0);
			glBindVertexArray(0);

			// Face culling
			glDisable(GL_CULL_FACE);
		}
	}
}

void DepthRenderer::renderGameEntity(const GameEntity * entity)
{
	if (entity != nullptr)
	{
		if (entity->isEnabled())
		{
			// Faceculling
			if (entity->isFaceCulled())
			{
				glEnable(GL_CULL_FACE);
			}

			// Shader uniforms
			_shader.uploadUniform("u_modelMatrix",   entity->getModelMatrix());
			_shader.uploadUniform("u_isAlphaObject", entity->isTransparent());
			_shader.uploadUniform("u_maxY",          entity->getMaxY());

			// OpenGL parts
			int index = 0;
			for (auto & buffer : entity->getOglBuffers())
			{
				// Texture
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap(index));

				// VAO
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
}

void DepthRenderer::renderBillboardEntity(const BillboardEntity * entity)
{
	if (entity != nullptr)
	{
		if (entity->isEnabled())
		{
			// Shader uniforms
			_shader.uploadUniform("u_modelMatrix",   entity->getModelMatrix());
			_shader.uploadUniform("u_isAlphaObject", entity->isTransparent());
			_shader.uploadUniform("u_isInstanced",   false);

			// Texture
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap());

			// Bind
			glBindVertexArray(entity->getOglBuffer()->getVAO());

			// Render
			glDrawArrays(GL_TRIANGLES, 0, entity->getOglBuffer()->getVertexCount());

			// Unbind
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, 0);
			glBindVertexArray(0);
		}
	}
}

void DepthRenderer::renderAabbEntity(const AabbEntity* entity)
{
	if (entity != nullptr)
	{
		if (entity->isEnabled())
		{
			// Shader uniforms
			_shader.uploadUniform("u_modelMatrix",   entity->getModelMatrix());
			_shader.uploadUniform("u_isAlphaObject", false);
			_shader.uploadUniform("u_isInstanced",   false);

			// VAO
			glBindVertexArray(entity->getOglBuffer()->getVAO());

			// Render
			glDrawArrays(GL_LINE_STRIP, 0, entity->getOglBuffer()->getVertexCount());

			// Unbind
			glBindVertexArray(0);
		}
	}
}

void DepthRenderer::renderWaterEntity(const WaterEntity* entity)
{
	if (entity != nullptr)
	{
		if (entity->isEnabled())
		{
			// Shader uniforms
			_shader.uploadUniform("u_modelMatrix",   mat4(1.0f));
			_shader.uploadUniform("u_isAlphaObject", false);
			_shader.uploadUniform("u_isInstanced",   false);

			// Bind
			glBindVertexArray(entity->getOglBuffer()->getVAO());

			// Render
			glDrawArrays(GL_TRIANGLES, 0, entity->getOglBuffer()->getVertexCount());

			// Unbind
			glBindVertexArray(0);
		}
	}
}
