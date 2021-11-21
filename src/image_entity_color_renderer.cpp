#include "image_entity_color_renderer.hpp"
#include "configuration.hpp"
#include "text_entity.hpp"

void ImageEntityColorRenderer::bind()
{
	// Bind shader
	_shader.bind();

	// Shader uniforms
	_shader.uploadUniform("u_nearDistance", _renderBus.getNearDistance());
	_shader.uploadUniform("u_farDistance", _renderBus.getFarDistance());
	_shader.uploadUniform("u_diffuseMap", 0);

	// Enable transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ImageEntityColorRenderer::unbind()
{
	// Disable transparency
	glDisable(GL_BLEND);

	// Unbind shader
	_shader.unbind();
}

void ImageEntityColorRenderer::render(const shared_ptr<ImageEntity> entity)
{
	if(entity->isVisible() &&
	   ((entity->getPosition().y - entity->getSize().y) < entity->getMaxPosition().y) &&
	   ((entity->getPosition().y + entity->getSize().y) > entity->getMinPosition().y))
	{
		// Temporary values
		const auto buffer = entity->getRenderBuffer();

		// Sprite animation
		Vec2 uvMultiplier = Vec2(1.0f);
		Vec2 uvAdder = Vec2(0.0f);
		if(entity->isSpriteAnimationStarted())
		{
			// Retrieve values
			const auto rowCount = entity->getTotalSpriteAnimationRowCount();
			const auto columnCount = entity->getTotalSpriteAnimationColumnCount();
			const auto rowIndex = entity->getSpriteAnimationRowIndex();
			const auto columnIndex = entity->getSpriteAnimationColumnIndex();

			// Apply values
			uvMultiplier = Vec2(1.0f / static_cast<float>(columnCount), 1.0f / static_cast<float>(rowCount));
			uvAdder = Vec2(static_cast<float>(columnIndex) * uvMultiplier.x, static_cast<float>(rowIndex) * uvMultiplier.y);
		}

		// Shader uniforms
		_shader.uploadUniform("u_uvAdder", uvAdder);
		_shader.uploadUniform("u_uvMultiplier", uvMultiplier);
		_shader.uploadUniform("u_transformationMatrix", entity->getTransformationMatrix());
		_shader.uploadUniform("u_isMirroredHorizontally", entity->isMirroredHorizonally());
		_shader.uploadUniform("u_isMirroredVertically", entity->isMirroredVertically());
		_shader.uploadUniform("u_color", entity->getColor());
		_shader.uploadUniform("u_windowSize", Vec2(Config::getInst().getWindowSize()));
		_shader.uploadUniform("u_minPosition", entity->getMinPosition());
		_shader.uploadUniform("u_maxPosition", entity->getMaxPosition());
		_shader.uploadUniform("u_transparency", entity->getTransparency());
		_shader.uploadUniform("u_isPerspectiveDepthEntity", entity->isPerspectiveDepthEntity());
		_shader.uploadUniform("u_hasDiffuseMap", entity->hasDiffuseMap());
		_shader.uploadUniform("u_wireframeColor", entity->getWireframeColor());
		_shader.uploadUniform("u_isWireframed", entity->isWireframed());

		// Bind textures
		if(entity->hasDiffuseMap())
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
		if(entity->hasDiffuseMap())
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}