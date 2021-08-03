#include "billboard_entity_depth_renderer.hpp"

void BillboardEntityDepthRenderer::bind()
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

void BillboardEntityDepthRenderer::unbind()
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

void BillboardEntityDepthRenderer::render(const shared_ptr<BillboardEntity> entity, float clippingY, bool isUnderWater)
{
	if (entity->hasRenderBuffer() && entity->isVisible())
	{
		// Temporary values
		const auto buffer = entity->getRenderBuffer();

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
		_shader.uploadUniform("u_positionY", entity->getPosition().y);
		_shader.uploadUniform("u_minHeight", entity->getMinHeight());
		_shader.uploadUniform("u_maxHeight", entity->getMaxHeight());
		_shader.uploadUniform("u_clippingY", clippingY);
		_shader.uploadUniform("u_isUnderWater", isUnderWater);
		_shader.uploadUniform("u_minDiffuseMapAlpha", MIN_DIFFUSE_MAP_ALPHA);
		_shader.uploadUniform("u_uvAdder", uvAdder);
		_shader.uploadUniform("u_uvMultiplier", uvMultiplier);

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