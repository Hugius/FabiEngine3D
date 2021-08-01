#include "depth_renderer.hpp"
#include "render_bus.hpp"
#include "configuration.hpp"

void DepthRenderer::bind()
{
	// Bind shader
	_shader.bind();

	// Shader uniforms
	_shader.uploadUniform("u_viewMatrix", _renderBus.getViewMatrix());
	_shader.uploadUniform("u_projectionMatrix", _renderBus.getProjectionMatrix());
	_shader.uploadUniform("u_diffuseMap", 0);

	// Enable clipping
	glEnable(GL_CLIP_DISTANCE0);
	glEnable(GL_CLIP_DISTANCE1);
	glEnable(GL_CLIP_DISTANCE2);

	// Enable depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void DepthRenderer::unbind()
{
	// Disable depth testing
	glDisable(GL_DEPTH_TEST);

	// Disable clipping
	glDisable(GL_CLIP_DISTANCE0);
	glDisable(GL_CLIP_DISTANCE1);
	glDisable(GL_CLIP_DISTANCE2);

	// Unbind shader
	_shader.unbind();
}

void DepthRenderer::render(const shared_ptr<TerrainEntity> entity)
{
	if (entity->hasRenderBuffer() && entity->isVisible())
	{
		// Temporary values
		auto buffer = entity->getRenderBuffer();

		// Enable face culling
		glEnable(GL_CULL_FACE);

		// Shader uniforms
		_shader.uploadUniform("u_modelMatrix", Matrix44(1.0f));
		_shader.uploadUniform("u_currentY", 0.0f);
		_shader.uploadUniform("u_minHeight", -(std::numeric_limits<float>::max)());
		_shader.uploadUniform("u_maxHeight", (std::numeric_limits<float>::max)());
		_shader.uploadUniform("u_clippingY", -(std::numeric_limits<float>::max)());
		_shader.uploadUniform("u_isTransparent", false);
		_shader.uploadUniform("u_isInstanced", false);
		_shader.uploadUniform("u_isBillboard", false);
		_shader.uploadUniform("u_isUnderWater", false);

		// Bind buffer
		glBindVertexArray(buffer->getVAO());

		// Render
		glDrawArrays(GL_TRIANGLES, 0, buffer->getVertexCount());

		// Unbind buffer
		glBindVertexArray(0);

		// Disable face culling
		glDisable(GL_CULL_FACE);
	}
}

void DepthRenderer::render(const shared_ptr<WaterEntity> entity)
{
	if (entity->hasLowQualityRenderBuffer() && entity->isVisible())
	{
		// Model matrix
		Matrix44 modelMatrix = Matrix44::createTranslation(entity->getPosition().x, entity->getPosition().y, entity->getPosition().z);
		
		// Shader uniforms
		_shader.uploadUniform("u_modelMatrix", modelMatrix);
		_shader.uploadUniform("u_isTransparent", false);
		_shader.uploadUniform("u_isInstanced", false);
		_shader.uploadUniform("u_currentY", entity->getPosition().y);
		_shader.uploadUniform("u_minHeight", -(std::numeric_limits<float>::max)());
		_shader.uploadUniform("u_maxHeight", (std::numeric_limits<float>::max)());
		_shader.uploadUniform("u_clippingY", -(std::numeric_limits<float>::max)());

		// Bind buffer
		glBindVertexArray(entity->getLowQualityRenderBuffer()->getVAO());

		// Render
		glDrawArrays(GL_TRIANGLES, 0, entity->getLowQualityRenderBuffer()->getVertexCount());

		// Unbind buffer
		glBindVertexArray(0);
	}
}

void DepthRenderer::render(const shared_ptr<ModelEntity> entity, float clippingY, bool isUnderWater)
{
	if (entity->hasRenderBuffer() && entity->isVisible())
	{
		// Enable face culling
		if (entity->isFaceCulled())
		{
			glEnable(GL_CULL_FACE);
		}

		// View matrix
		auto viewMatrix = (entity->isCameraStatic() ? Matrix44(Matrix33(_renderBus.getViewMatrix())) : _renderBus.getViewMatrix());

		// Shader uniforms
		_shader.uploadUniform("u_isTransparent", entity->isTransparent());
		_shader.uploadUniform("u_currentY", entity->getPosition().y);
		_shader.uploadUniform("u_minHeight", entity->getMinHeight());
		_shader.uploadUniform("u_maxHeight", entity->getMaxHeight());
		_shader.uploadUniform("u_clippingY", clippingY);
		_shader.uploadUniform("u_isBillboard", false);
		_shader.uploadUniform("u_isUnderWater", isUnderWater);
		_shader.uploadUniform("u_minDiffuseMapAlpha", MIN_DIFFUSE_MAP_ALPHA);
		_shader.uploadUniform("u_viewMatrix", viewMatrix);

		// Iterate through parts
		for (const auto& partID : entity->getPartIDs())
		{
			// Temporary values
			auto buffer = entity->getRenderBuffer(partID);

			// Shader uniforms
			_shader.uploadUniform("u_modelMatrix", entity->getModelMatrix(partID));
			_shader.uploadUniform("u_isInstanced", buffer->isInstanced());

			// Bind textures
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
				const auto offsetCount = static_cast<unsigned int>(buffer->getInstancedOffsets().size());
				glDrawArraysInstanced(GL_TRIANGLES, 0, buffer->getVertexCount(), offsetCount);
			}
			else
			{
				glDrawArrays(GL_TRIANGLES, 0, buffer->getVertexCount());
			}

			// Unbind textures
			if (entity->hasDiffuseMap(partID))
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, 0);
			}

			// Unbind buffer
			glBindVertexArray(0);
		}

		// Disable face culling
		if (entity->isFaceCulled())
		{
			glDisable(GL_CULL_FACE);
		}
	}
}

void DepthRenderer::render(const shared_ptr<BillboardEntity> entity, float clippingY, bool isUnderWater)
{
	if (entity->hasRenderBuffer() && entity->isVisible())
	{
		// Temporary values
		auto buffer = entity->getRenderBuffer();

		// Sprite animation
		Vec2 uvMultiplier = Vec2(1.0f);
		Vec2 uvAdder = Vec2(0.0f);
		if (entity->isSpriteAnimationStarted())
		{
			// Retrieve values
			const auto totalColumns = entity->getTotalSpriteAnimationColumns();
			const auto totalRows = entity->getTotalSpriteAnimationRows();
			const auto columnIndex = entity->getSpriteAnimationColumnIndex();
			const auto rowIndex = entity->getSpriteAnimationRowIndex();

			// Apply values
			uvMultiplier = Vec2(1.0f / static_cast<float>(totalColumns), 1.0f / static_cast<float>(totalRows));
			uvAdder = Vec2(static_cast<float>(columnIndex) * uvMultiplier.x, static_cast<float>(rowIndex) * uvMultiplier.y);
		}

		// Shader uniforms
		_shader.uploadUniform("u_modelMatrix", entity->getModelMatrix());
		_shader.uploadUniform("u_isTransparent", entity->isTransparent());
		_shader.uploadUniform("u_currentY", entity->getPosition().y);
		_shader.uploadUniform("u_minHeight", entity->getMinHeight());
		_shader.uploadUniform("u_maxHeight", entity->getMaxHeight());
		_shader.uploadUniform("u_clippingY", clippingY);
		_shader.uploadUniform("u_isUnderWater", isUnderWater);
		_shader.uploadUniform("u_minDiffuseMapAlpha", MIN_DIFFUSE_MAP_ALPHA);
		_shader.uploadUniform("u_uvAdder", uvAdder);
		_shader.uploadUniform("u_uvMultiplier", uvMultiplier);
		_shader.uploadUniform("u_isBillboard", true);
		_shader.uploadUniform("u_isInstanced", false);

		// Bind textures
		if (entity->hasDiffuseMap())
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap());
		}

		// Bind buffer
		glBindVertexArray(buffer->getVAO());

		// Render
		glDrawArrays(GL_TRIANGLES, 0, buffer->getVertexCount());
		_renderBus.increaseTriangleCount(buffer->getVertexCount() / 3);

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
	if (entity->hasRenderBuffer() && entity->isVisible())
	{
		// Temporary values
		auto buffer = entity->getRenderBuffer();

		// Shader uniforms
		_shader.uploadUniform("u_modelMatrix", entity->getModelMatrix());
		_shader.uploadUniform("u_currentY", entity->getPosition().y);
		_shader.uploadUniform("u_minHeight", -(std::numeric_limits<float>::max)());
		_shader.uploadUniform("u_maxHeight", (std::numeric_limits<float>::max)());
		_shader.uploadUniform("u_clippingY", clippingY);
		_shader.uploadUniform("u_isBillboard", true);
		_shader.uploadUniform("u_isInstanced", false);
		_shader.uploadUniform("u_isTransparent", false);
		_shader.uploadUniform("u_isUnderWater", isUnderWater);

		// Bind buffer
		glBindVertexArray(buffer->getVAO());

		// Render
		glDrawArrays(GL_LINE_STRIP, 0, buffer->getVertexCount());

		// Unbind buffer
		glBindVertexArray(0);
	}
}