#include "image_entity_renderer.hpp"
#include "configuration.hpp"
#include "text_entity.hpp"

void ImageEntityRenderer::bind()
{
	// Bind shader
	_shader.bind();

	// Shader uniforms
	_shader.uploadUniform("u_nearZ", _renderBus.getNearZ());
	_shader.uploadUniform("u_farZ", _renderBus.getFarZ());
	_shader.uploadUniform("u_diffuseMap", 0);

	// Enable alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ImageEntityRenderer::unbind()
{
	// Disable alpha blending
	glDisable(GL_BLEND);

	// Unbind shader
	_shader.unbind();
}

void ImageEntityRenderer::render(const shared_ptr<ImageEntity> entity)
{
	if (entity->isVisible() && !entity->getRenderBuffers().empty() &&
		((entity->getTranslation().y - entity->getScaling().y) < entity->getMaxPosition().y) &&
		((entity->getTranslation().y + entity->getScaling().y) > entity->getMinPosition().y))
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
		_shader.uploadUniform("u_uvAdder", uvAdder);
		_shader.uploadUniform("u_uvMultiplier", uvMultiplier);
		_shader.uploadUniform("u_modelMatrix", entity->getModelMatrix());
		_shader.uploadUniform("u_isMirroredHorizontally", entity->isMirroredHorizonally());
		_shader.uploadUniform("u_isMirroredVertically", entity->isMirroredVertically());
		_shader.uploadUniform("u_color", entity->getColor());
		_shader.uploadUniform("u_windowSize", Vec2(Config::getInst().getWindowSize()));
		_shader.uploadUniform("u_minPosition", entity->getMinPosition());
		_shader.uploadUniform("u_maxPosition", entity->getMaxPosition());
		_shader.uploadUniform("u_alpha", entity->getAlpha());
		_shader.uploadUniform("u_isPerspectiveDepthEntity", entity->isPerspectiveDepthEntity());
		_shader.uploadUniform("u_hasDiffuseMap", entity->hasDiffuseMap());

		// Bind textures
		if (entity->hasDiffuseMap())
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap());
		}

		// Bind buffer
		glBindVertexArray(entity->getRenderBuffer()->getVAO());

		// Render
		glDrawArrays(GL_TRIANGLES, 0, 6);
		_renderBus.increaseTriangleCount(2);

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