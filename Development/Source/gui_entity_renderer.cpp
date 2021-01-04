#include "gui_entity_renderer.hpp"
#include "configuration.hpp"
#include "text_entity.hpp"

void GuiEntityRenderer::bind()
{
	// Bind shader
	_shader.bind();

	// Vertex shader uniforms
	_shader.uploadUniform("u_nearZ", _renderBus.getNearZ());
	_shader.uploadUniform("u_farZ", _renderBus.getFarZ());

	// Alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void GuiEntityRenderer::unbind()
{
	glDisable(GL_BLEND);
	_shader.unbind();
}

void GuiEntityRenderer::render(const shared_ptr<GuiEntity> entity)
{
	if (entity->isVisible() && 
		((entity->getTranslation().y - entity->getScaling().y) < entity->getMaxPosition().y) &&
		((entity->getTranslation().y + entity->getScaling().y) > entity->getMinPosition().y))
	{
		// Uniforms
		_shader.uploadUniform("u_modelMatrix", entity->getModelMatrix());
		_shader.uploadUniform("u_isMirroredHorizontally", entity->isMirroredHorizonally());
		_shader.uploadUniform("u_isMirroredVertically", entity->isMirroredVertically());
		_shader.uploadUniform("u_color", entity->getColor());
		_shader.uploadUniform("u_windowSize", Vec2(Config::getInst().getWindowSize()));
		_shader.uploadUniform("u_minPosition", entity->getMinPosition());
		_shader.uploadUniform("u_maxPosition", entity->getMaxPosition());
		_shader.uploadUniform("u_alpha", entity->getAlpha());
		_shader.uploadUniform("u_isDepthEntity", entity->isDepthEntity());
		_shader.uploadUniform("u_hasTexture", entity->getDiffuseMap() != 0);
		_shader.uploadUniform("u_sampler_diffuse", 0);

		// Bind
		glBindVertexArray(entity->getOglBuffer()->getVAO());
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap());

		// Render
		glDrawArrays(GL_TRIANGLES, 0, 6);
		_renderBus.increaseTriangleCount(2);

		// Unbind
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
	}
}