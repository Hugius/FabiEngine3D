#include "billboard_entity_color_renderer.hpp"
#include "configuration.hpp"

void BillboardEntityColorRenderer::bind()
{
	// Bind shader
	_shader.bind();

	// Shader uniforms
	_shader.uploadUniform("u_viewMatrix",		_renderBus.getViewMatrix());
	_shader.uploadUniform("u_projectionMatrix",	_renderBus.getProjectionMatrix());
	_shader.uploadUniform("u_clippingPlane",	_renderBus.getClippingPlane());
	_shader.uploadUniform("u_cameraPosition",	_renderBus.getCameraPosition());
	_shader.uploadUniform("u_fogMinDistance",   _renderBus.getFogMinDistance());
	_shader.uploadUniform("u_fogMaxDistance",   _renderBus.getFogMaxDistance());
	_shader.uploadUniform("u_fogThickness",	    _renderBus.getFogThickness());
	_shader.uploadUniform("u_fogColor",		    _renderBus.getFogColor());
	_shader.uploadUniform("u_isFogEnabled",	    _renderBus.isFogEnabled());
	_shader.uploadUniform("u_diffuseMap", 0);

	// Enable clipping
	glEnable(GL_CLIP_DISTANCE0);
	glEnable(GL_CLIP_DISTANCE1);

	// Enable depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// Enable alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void BillboardEntityColorRenderer::unbind()
{
	// Disable alpha blending
	glDisable(GL_BLEND);

	// Disable depth testing
	glDisable(GL_DEPTH_TEST);

	// Disable clipping
	glDisable(GL_CLIP_DISTANCE0);
	glDisable(GL_CLIP_DISTANCE1);

	// Unbind shader
	_shader.unbind();
}

void BillboardEntityColorRenderer::render(const shared_ptr<BillboardEntity> entity)
{
	if (entity->isVisible())
	{
		// Temporary values
		const auto buffer = entity->getRenderBuffer();

		// Enable wire frame
		if (entity->isWireFramed())
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
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
		_shader.uploadUniform("u_isWireFramed", (entity->isWireFramed() || _renderBus.isWireFrameRenderingEnabled()));
		_shader.uploadUniform("u_transformationMatrix", entity->getTransformationMatrix());
		_shader.uploadUniform("u_isTransparent", entity->isTransparent());
		_shader.uploadUniform("u_hasDiffuseMap", entity->hasDiffuseMap());
		_shader.uploadUniform("u_color", entity->getColor());
		_shader.uploadUniform("u_lightness", entity->getLightness());
		_shader.uploadUniform("u_inversion", entity->getInversion());
		_shader.uploadUniform("u_positionY", entity->getPosition().y);
		_shader.uploadUniform("u_minHeight", entity->getMinHeight());
		_shader.uploadUniform("u_maxHeight", entity->getMaxHeight());
		_shader.uploadUniform("u_alpha", entity->getAlpha());
		_shader.uploadUniform("u_isBright", entity->isBright());
		_shader.uploadUniform("u_uvRepeat", entity->getUvRepeat());
		_shader.uploadUniform("u_uvAdder", uvAdder);
		_shader.uploadUniform("u_uvMultiplier", uvMultiplier);
		_shader.uploadUniform("u_minDiffuseMapAlpha", MIN_DIFFUSE_MAP_ALPHA);

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

		// Disable wire frame
		if (entity->isWireFramed())
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}
}