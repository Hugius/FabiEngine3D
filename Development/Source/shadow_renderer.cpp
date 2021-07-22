#include "shadow_renderer.hpp"
#include "render_bus.hpp"
#include "configuration.hpp"

void ShadowRenderer::bind()
{	
	// Bind shader
	_shader.bind();

	// Shader uniforms
	_shader.uploadUniform("u_lightSpaceMatrix", _renderBus.getShadowMatrix());
	_shader.uploadUniform("u_diffuseMap", 0);

	// Enable clipping
	glEnable(GL_CLIP_DISTANCE0);
	glEnable(GL_CLIP_DISTANCE1);

	// Enable depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void ShadowRenderer::unbind()
{
	// Disable depth testing
	glDisable(GL_DEPTH_TEST);

	// Disable clipping
	glDisable(GL_CLIP_DISTANCE0);
	glDisable(GL_CLIP_DISTANCE1);

	// Unbind shader
	_shader.unbind();
}

void ShadowRenderer::render(const shared_ptr<ModelEntity> entity)
{
	if (entity->isVisible() && !entity->getRenderBuffers().empty() && entity->isShadowed())
	{
		// Enable face culling
		if (entity->isFaceCulled())
		{
			glEnable(GL_CULL_FACE);
		}

		// Shader uniforms
		_shader.uploadUniform("u_isAlphaObject", entity->isTransparent());
		_shader.uploadUniform("u_currentY", entity->getPosition().y);
		_shader.uploadUniform("u_minHeight", entity->getMinHeight());
		_shader.uploadUniform("u_maxHeight", entity->getMaxHeight());

		// Iterate through parts
		for (size_t i = 0; i < entity->getRenderBuffers().size(); i++)
		{
			// Temporary values
			auto partID = entity->getPartIDs()[i];
			auto buffer = entity->getRenderBuffers()[i];

			// Shader uniforms
			_shader.uploadUniform("u_modelMatrix", entity->getModelMatrix(partID));

			// Bind textures
			if (entity->isTransparent() && entity->hasDiffuseMap(partID))
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap(partID));
			}

			// Bind buffer
			glBindVertexArray(buffer->getVAO());

			// Render
			if (buffer->isInstanced())
			{
				_shader.uploadUniform("u_isInstanced", true);
				glDrawArraysInstanced(GL_TRIANGLES, 0, buffer->getVertexCount(), buffer->getInstancedOffsetCount());
			}
			else
			{
				_shader.uploadUniform("u_isInstanced", false);
				glDrawArrays(GL_TRIANGLES, 0, buffer->getVertexCount());
			}

			// Unbind buffer
			glBindVertexArray(0);

			// Unbind textures
			if (entity->isTransparent() && entity->hasDiffuseMap(partID))
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, 0);
			}
		}

		// Disable face culling
		if (entity->isFaceCulled())
		{
			glDisable(GL_CULL_FACE);
		}
	}
}

void ShadowRenderer::render(const shared_ptr<BillboardEntity> entity)
{
	if (entity->isVisible() && entity->isShadowed())
	{
		// Shader uniforms
		_shader.uploadUniform("u_isAlphaObject", entity->isTransparent());
		_shader.uploadUniform("u_currentY", entity->getPosition().y);
		_shader.uploadUniform("u_minHeight", entity->getMinHeight());
		_shader.uploadUniform("u_maxHeight", entity->getMaxHeight());

		// Model matrix
		_shader.uploadUniform("u_modelMatrix", entity->getModelMatrix());

		// Bind diffuse map
		if (entity->isTransparent() && entity->hasDiffuseMap())
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap());
		}

		// Bind buffer
		glBindVertexArray(entity->getRenderBuffer()->getVAO());

		// Render
		_shader.uploadUniform("u_isInstanced", false);
		glDrawArrays(GL_TRIANGLES, 0, entity->getRenderBuffer()->getVertexCount());

		// Unbind buffer
		glBindVertexArray(0);

		// Unbind diffuse map
		if (entity->isTransparent() && entity->hasDiffuseMap())
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}