#include "quad2d_entity_color_renderer.hpp"
#include "configuration.hpp"
#include "text2d_entity.hpp"

void Quad2dEntityColorRenderer::bind()
{
	_shader->bind();

	_shader->uploadUniform("u_nearDistance", _renderBus->getNearDistance());
	_shader->uploadUniform("u_farDistance", _renderBus->getFarDistance());
	_shader->uploadUniform("u_diffuseMap", 0);

	glEnable(GL_BLEND);
}

void Quad2dEntityColorRenderer::unbind()
{
	glDisable(GL_BLEND);

	_shader->unbind();
}

void Quad2dEntityColorRenderer::render(const shared_ptr<Quad2dEntity> entity)
{
	if(entity->isVisible() &&
	   ((entity->getPosition().y - entity->getSize().y) < entity->getMaxPosition().y) &&
	   ((entity->getPosition().y + entity->getSize().y) > entity->getMinPosition().y))
	{
		_shader->uploadUniform("u_uvMultiplier", entity->getUvMultiplier());
		_shader->uploadUniform("u_uvOffset", entity->getUvOffset());
		_shader->uploadUniform("u_transformationMatrix", entity->getTransformationMatrix());
		_shader->uploadUniform("u_isHorizontallyFlipped", entity->isFlippedHorizonally());
		_shader->uploadUniform("u_isVerticallyFlipped", entity->isVerticallyFlipped());
		_shader->uploadUniform("u_color", entity->getColor());
		_shader->uploadUniform("u_windowSize", fvec2(Config::getInst().getWindowSize()));
		_shader->uploadUniform("u_minPosition", entity->getMinPosition());
		_shader->uploadUniform("u_maxPosition", entity->getMaxPosition());
		_shader->uploadUniform("u_opacity", entity->getOpacity());
		_shader->uploadUniform("u_hasDiffuseMap", (entity->getDiffuseMap() != nullptr));
		_shader->uploadUniform("u_wireframeColor", entity->getWireframeColor());
		_shader->uploadUniform("u_isWireframed", entity->isWireframed());

		if(entity->getDiffuseMap() != nullptr)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap()->getId());
		}

		glBindVertexArray(entity->getMesh()->getVaoId());

		glDrawArrays(GL_TRIANGLES, 0, entity->getMesh()->getVertexCount());
		_renderBus->increaseTriangleCount(entity->getMesh()->getVertexCount() / 3);

		glBindVertexArray(0);

		if(entity->getDiffuseMap() != nullptr)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}