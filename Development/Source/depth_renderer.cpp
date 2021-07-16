#include "depth_renderer.hpp"
#include "render_bus.hpp"
#include "configuration.hpp"

void DepthRenderer::bind()
{
	// Bind shader
	_shader.bind();

	// Vertex shader uniforms
	_shader.uploadUniform("u_viewMatrix", _renderBus.getViewMatrix());
	_shader.uploadUniform("u_projectionMatrix", _renderBus.getProjectionMatrix());

	// Texture uniforms
	_shader.uploadUniform("u_diffuseMap", 0);

	// Clipping (minY & maxY)
	glEnable(GL_CLIP_DISTANCE0);
	glEnable(GL_CLIP_DISTANCE1);
	glEnable(GL_CLIP_DISTANCE2);

	// Depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void DepthRenderer::unbind()
{
	glDisable(GL_CLIP_DISTANCE0);
	glDisable(GL_CLIP_DISTANCE1);
	glDisable(GL_CLIP_DISTANCE2);
	glDisable(GL_DEPTH_TEST);
	_shader.unbind();
}

void DepthRenderer::render(const shared_ptr<TerrainEntity> entity)
{
	if (entity->isVisible() && !entity->getRenderBuffers().empty())
	{
		// Face culling
		glEnable(GL_CULL_FACE);

		// Shader uniforms
		_shader.uploadUniform("u_modelMatrix", Matrix44(1.0f));
		_shader.uploadUniform("u_currentY", 0.0f);
		_shader.uploadUniform("u_minHeight", -(std::numeric_limits<float>::max)());
		_shader.uploadUniform("u_maxHeight", (std::numeric_limits<float>::max)());
		_shader.uploadUniform("u_clippingY", -(std::numeric_limits<float>::max)());
		_shader.uploadUniform("u_isAlphaObject", false);
		_shader.uploadUniform("u_isInstanced", false);
		_shader.uploadUniform("u_isBillboard", false);
		_shader.uploadUniform("u_isUnderWater", false);

		// Bind buffer
		glBindVertexArray(entity->getRenderBuffer()->getVAO());

		// Render
		glDrawArrays(GL_TRIANGLES, 0, entity->getRenderBuffer()->getVertexCount());

		// Unbind buffer
		glBindVertexArray(0);

		// Face culling
		glDisable(GL_CULL_FACE);
	}
}

void DepthRenderer::render(const shared_ptr<WaterEntity> entity)
{
	if (entity->isVisible() && !entity->getRenderBuffers().empty())
	{
		// Shader uniforms
		Matrix44 modelMatrix = Matrix44::createTranslation(entity->getTranslation().x, entity->getTranslation().y, entity->getTranslation().z);
		_shader.uploadUniform("u_modelMatrix", modelMatrix);
		_shader.uploadUniform("u_isAlphaObject", false);
		_shader.uploadUniform("u_isInstanced", false);
		_shader.uploadUniform("u_currentY", entity->getTranslation().y);
		_shader.uploadUniform("u_minHeight", -(std::numeric_limits<float>::max)());
		_shader.uploadUniform("u_maxHeight", (std::numeric_limits<float>::max)());
		_shader.uploadUniform("u_clippingY", -(std::numeric_limits<float>::max)());

		// Bind buffer
		glBindVertexArray(entity->getSimplifiedRenderBuffer()->getVAO());

		// Render
		glDrawArrays(GL_TRIANGLES, 0, entity->getSimplifiedRenderBuffer()->getVertexCount());

		// Unbind buffer
		glBindVertexArray(0);
	}
}

void DepthRenderer::render(const shared_ptr<ModelEntity> entity, float clippingY, bool isUnderWater)
{
	if (entity->isVisible())
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
		_shader.uploadUniform("u_clippingY", clippingY);
		_shader.uploadUniform("u_isBillboard", false);
		_shader.uploadUniform("u_isUnderWater", isUnderWater);
		_shader.uploadUniform("u_minAlpha", 0.25f);

		// Check if entity is static to the camera view
		if (entity->isCameraStatic())
		{
			_shader.uploadUniform("u_viewMatrix", Matrix44(Matrix33(_renderBus.getViewMatrix())));
		}
		else
		{
			_shader.uploadUniform("u_viewMatrix", _renderBus.getViewMatrix());
		}

		// Bind & render
		for (size_t i = 0; i < entity->getRenderBuffers().size(); i++)
		{
			// Temporary values
			auto partID = entity->getPartIDs()[i];
			auto buffer = entity->getRenderBuffers()[i];

			// Model matrix
			_shader.uploadUniform("u_modelMatrix", entity->getModelMatrix(partID));

			// Diffuse map
			if (entity->hasDiffuseMap(partID))
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

			// Diffuse map
			if (entity->hasDiffuseMap(partID))
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, 0);
			}
		}

		// Unbind buffer
		glBindVertexArray(0);

		// Face culling
		if (entity->isFaceCulled())
		{
			glDisable(GL_CULL_FACE);
		}
	}
}

void DepthRenderer::render(const shared_ptr<BillboardEntity> entity, float clippingY, bool isUnderWater)
{
	if (entity->isVisible() && !entity->getRenderBuffers().empty())
	{
		// Sprite animation
		Vec2 uvMultiplier = Vec2(1.0f);
		Vec2 uvAdder = Vec2(0.0f);
		if (entity->isSpriteAnimationStarted())
		{
			uvMultiplier = Vec2(1.0f / static_cast<float>(entity->getTotalSpriteAnimationColumns()), 1.0f / static_cast<float>(entity->getTotalSpriteAnimationRows()));
			uvAdder = Vec2(static_cast<float>(entity->getSpriteAnimationColumnIndex()) * uvMultiplier.x, static_cast<float>(entity->getSpriteAnimationRowIndex()) * uvMultiplier.y);
		}

		// Shader uniforms
		_shader.uploadUniform("u_modelMatrix", entity->getModelMatrix());
		_shader.uploadUniform("u_isAlphaObject", entity->isTransparent());
		_shader.uploadUniform("u_currentY", entity->getTranslation().y);
		_shader.uploadUniform("u_minHeight", entity->getMinHeight());
		_shader.uploadUniform("u_maxHeight", entity->getMaxHeight());
		_shader.uploadUniform("u_clippingY", clippingY);
		_shader.uploadUniform("u_uvAdder", uvAdder);
		_shader.uploadUniform("u_uvMultiplier", uvMultiplier);
		_shader.uploadUniform("u_isBillboard", true);
		_shader.uploadUniform("u_isInstanced", false);
		_shader.uploadUniform("u_isUnderWater", isUnderWater);
		_shader.uploadUniform("u_minAlpha", entity->getTextContent().empty() ? 0.9f : 0.1f);

		// Bind textures
		if (entity->hasDiffuseMap())
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap());
		}

		// Bind buffer
		glBindVertexArray(entity->getRenderBuffer()->getVAO());

		// Render
		if (entity->getRenderBuffer()->isInstanced()) // Instanced
		{
			_shader.uploadUniform("u_isInstanced", true);
			glDrawArraysInstanced(GL_TRIANGLES, 0, entity->getRenderBuffer()->getVertexCount(), entity->getRenderBuffer()->getInstancedOffsetCount());
			_renderBus.increaseTriangleCount((entity->getRenderBuffer()->getInstancedOffsetCount() * entity->getRenderBuffer()->getVertexCount()) / 3);
		}
		else // Non-instanced
		{
			_shader.uploadUniform("u_isInstanced", false);
			glDrawArrays(GL_TRIANGLES, 0, entity->getRenderBuffer()->getVertexCount());
			_renderBus.increaseTriangleCount(entity->getRenderBuffer()->getVertexCount() / 3);
		}

		// Unbind buffer
		glBindVertexArray(0);

		// Unbind textures
		if (entity->hasDiffuseMap())
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}

void DepthRenderer::render(const shared_ptr<AabbEntity> entity, float clippingY, bool isUnderWater)
{
	if (entity->isVisible() && !entity->getRenderBuffers().empty())
	{
		// Shader uniforms
		_shader.uploadUniform("u_modelMatrix", entity->getModelMatrix());
		_shader.uploadUniform("u_currentY", entity->getTranslation().y);
		_shader.uploadUniform("u_minHeight", -(std::numeric_limits<float>::max)());
		_shader.uploadUniform("u_maxHeight", (std::numeric_limits<float>::max)());
		_shader.uploadUniform("u_clippingY", clippingY);
		_shader.uploadUniform("u_isBillboard", true);
		_shader.uploadUniform("u_isInstanced", false);
		_shader.uploadUniform("u_isAlphaObject", false);
		_shader.uploadUniform("u_isUnderWater", isUnderWater);

		// Bind buffer
		glBindVertexArray(entity->getRenderBuffer()->getVAO());

		// Render
		glDrawArrays(GL_LINE_STRIP, 0, entity->getRenderBuffer()->getVertexCount());

		// Unbind buffer
		glBindVertexArray(0);
	}
}