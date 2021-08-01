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
	if (entity->hasRenderBuffer() && entity->isVisible() && entity->isShadowed())
	{
		// Enable face culling
		if (entity->isFaceCulled())
		{
			glEnable(GL_CULL_FACE);
		}

		// Shader uniforms
		_shader.uploadUniform("u_isTransparent", entity->isTransparent());
		_shader.uploadUniform("u_currentY", entity->getPosition().y);
		_shader.uploadUniform("u_minHeight", entity->getMinHeight());
		_shader.uploadUniform("u_maxHeight", entity->getMaxHeight());
		_shader.uploadUniform("u_minDiffuseMapAlpha", MIN_DIFFUSE_MAP_ALPHA);

		// Iterate through parts
		for (const auto& partID : entity->getPartIDs())
		{
			// Temporary values
			const auto buffer = entity->getRenderBuffer(partID);

			// Shader uniforms
			_shader.uploadUniform("u_modelMatrix", entity->getModelMatrix(partID));
			_shader.uploadUniform("u_isInstanced", buffer->isInstanced());

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
				const auto offsetCount = static_cast<unsigned int>(buffer->getInstancedOffsets().size());
				glDrawArraysInstanced(GL_TRIANGLES, 0, buffer->getVertexCount(), offsetCount);
			}
			else
			{
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
	if (entity->hasRenderBuffer() && entity->isVisible() && entity->isShadowed())
	{
		// Shader uniforms
		_shader.uploadUniform("u_isTransparent", entity->isTransparent());
		_shader.uploadUniform("u_currentY", entity->getPosition().y);
		_shader.uploadUniform("u_minHeight", entity->getMinHeight());
		_shader.uploadUniform("u_maxHeight", entity->getMaxHeight());
		_shader.uploadUniform("u_minDiffuseMapAlpha", MIN_DIFFUSE_MAP_ALPHA);
		_shader.uploadUniform("u_isInstanced", false);

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