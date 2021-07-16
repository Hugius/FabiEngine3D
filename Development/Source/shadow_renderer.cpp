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

	// Clipping (minY & maxY)
	glEnable(GL_CLIP_DISTANCE0);
	glEnable(GL_CLIP_DISTANCE1);

	// Depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void ShadowRenderer::unbind()
{
	glDisable(GL_CLIP_DISTANCE0);
	glDisable(GL_CLIP_DISTANCE1);
	glDisable(GL_DEPTH_TEST);
	_shader.unbind();
}

void ShadowRenderer::render(const shared_ptr<ModelEntity> entity)
{
	if (entity->isVisible() && !entity->getRenderBuffers().empty() && entity->isShadowed())
	{
		// Face culling
		if (entity->isFaceCulled())
		{
			glEnable(GL_CULL_FACE);
		}

		// Shader uniforms
		_shader.uploadUniform("u_isAlphaObject", entity->isTransparent());
		_shader.uploadUniform("u_currentY", entity->getTranslation().y);
		_shader.uploadUniform("u_minHeight", entity->getMinHeight());
		_shader.uploadUniform("u_maxHeight", entity->getMaxHeight());

		// Bind & render
		for (size_t i = 0; i < entity->getRenderBuffers().size(); i++)
		{
			// Temporary values
			auto partID = entity->getPartIDs()[i];
			auto buffer = entity->getRenderBuffers()[i];

			// Model matrix
			_shader.uploadUniform("u_modelMatrix", entity->getModelMatrix(partID));

			// Diffuse map transparency
			if (entity->isTransparent() && entity->hasDiffuseMap(partID))
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap(partID));
			}

			// Bind
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

void ShadowRenderer::render(const shared_ptr<BillboardEntity> entity)
{
	if (entity->isVisible() && entity->isShadowed())
	{
		// Shader uniforms
		_shader.uploadUniform("u_isAlphaObject", entity->isTransparent());
		_shader.uploadUniform("u_currentY", entity->getTranslation().y);
		_shader.uploadUniform("u_minHeight", entity->getMinHeight());
		_shader.uploadUniform("u_maxHeight", entity->getMaxHeight());

		// Model matrix
		_shader.uploadUniform("u_modelMatrix", entity->getModelMatrix());

		// Diffuse map transparency
		if (entity->isTransparent() && entity->hasDiffuseMap())
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap());
		}

		// Bind
		glBindVertexArray(entity->getRenderBuffer()->getVAO());

		// Render
		_shader.uploadUniform("u_isInstanced", false);
		glDrawArrays(GL_TRIANGLES, 0, entity->getRenderBuffer()->getVertexCount());

		// Unbind
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
	}
}