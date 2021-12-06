#include "billboard_entity_color_renderer.hpp"
#include "configuration.hpp"

void BillboardEntityColorRenderer::bind()
{
	// Bind shader
	_shader.bind();

	// Shader uniforms
	_shader.uploadUniform("u_projectionMatrix", _renderBus.getProjectionMatrix());
	_shader.uploadUniform("u_clippingPlane", _renderBus.getClippingPlane());
	_shader.uploadUniform("u_cameraPosition", _renderBus.getCameraPosition());
	_shader.uploadUniform("u_fogMinDistance", _renderBus.getFogMinDistance());
	_shader.uploadUniform("u_fogMaxDistance", _renderBus.getFogMaxDistance());
	_shader.uploadUniform("u_fogThickness", _renderBus.getFogThickness());
	_shader.uploadUniform("u_fogColor", _renderBus.getFogColor());
	_shader.uploadUniform("u_isFogEnabled", _renderBus.isFogEnabled());
	_shader.uploadUniform("u_diffuseMap", 0);
	_shader.uploadUniform("u_emissionMap", 1);

	// Enable clipping
	glEnable(GL_CLIP_DISTANCE0);
	glEnable(GL_CLIP_DISTANCE1);

	// Enable depth
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// Enable transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void BillboardEntityColorRenderer::unbind()
{
	// Disable transparency
	glDisable(GL_BLEND);

	// Disable depth
	glDisable(GL_DEPTH_TEST);

	// Disable clipping
	glDisable(GL_CLIP_DISTANCE0);
	glDisable(GL_CLIP_DISTANCE1);

	// Unbind shader
	_shader.unbind();
}

void BillboardEntityColorRenderer::render(const shared_ptr<BillboardEntity> entity)
{
	if(entity->isVisible())
	{
		// Temporary values
		const auto buffer = entity->getRenderBuffer();

		// Enable wireframe
		if(entity->isWireframed())
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}

		// Sprite animation
		fvec2 uvMultiplier = fvec2(1.0f);
		fvec2 uvAdder = fvec2(0.0f);
		if(entity->isSpriteAnimationStarted())
		{
			// Retrieve values
			const auto rowCount = entity->getTotalSpriteAnimationRowCount();
			const auto columnCount = entity->getTotalSpriteAnimationColumnCount();
			const auto rowIndex = entity->getSpriteAnimationRowIndex();
			const auto columnIndex = entity->getSpriteAnimationColumnIndex();

			// Apply values
			uvMultiplier = fvec2(1.0f / static_cast<float>(columnCount), 1.0f / static_cast<float>(rowCount));
			uvAdder = fvec2(static_cast<float>(columnIndex) * uvMultiplier.x, static_cast<float>(rowIndex) * uvMultiplier.y);
		}

		// Shader uniforms
		_shader.uploadUniform("u_viewMatrix", (entity->isFrozen() ? mat44(mat33(_renderBus.getViewMatrix())) : _renderBus.getViewMatrix()));
		_shader.uploadUniform("u_isWireframed", (entity->isWireframed() || _renderBus.isWireframeRenderingEnabled()));
		_shader.uploadUniform("u_transformationMatrix", entity->getTransformationMatrix());
		_shader.uploadUniform("u_hasDiffuseMap", entity->hasDiffuseMap());
		_shader.uploadUniform("u_hasEmissionMap", entity->hasEmissionMap());
		_shader.uploadUniform("u_color", entity->getColor());
		_shader.uploadUniform("u_wireframeColor", entity->getWireframeColor());
		_shader.uploadUniform("u_lightness", entity->getLightness());
		_shader.uploadUniform("u_minHeight", entity->getMinHeight());
		_shader.uploadUniform("u_maxHeight", entity->getMaxHeight());
		_shader.uploadUniform("u_transparency", entity->getTransparency());
		_shader.uploadUniform("u_isBright", entity->isBright());
		_shader.uploadUniform("u_emissionIntensity", entity->getEmissionIntensity());
		_shader.uploadUniform("u_textureRepeat", entity->getTextureRepeat());
		_shader.uploadUniform("u_uvAdder", uvAdder);
		_shader.uploadUniform("u_uvMultiplier", uvMultiplier);
		_shader.uploadUniform("u_minTextureTransparency", MIN_TEXTURE_TRANSPARENCY);

		// Bind textures
		if(entity->hasDiffuseMap())
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap());
		}
		if(entity->hasEmissionMap())
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, entity->getEmissionMap());
		}

		// Bind buffer
		glBindVertexArray(buffer->getVAO());

		// Render
		glDrawArrays(GL_TRIANGLES, 0, buffer->getVertexCount());
		_renderBus.increaseTriangleCount(buffer->getVertexCount() / 3);

		// Unbind buffer
		glBindVertexArray(0);

		// Unbind textures
		if(entity->hasDiffuseMap())
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		if(entity->hasEmissionMap())
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		// Disable wireframe
		if(entity->isWireframed())
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}
}