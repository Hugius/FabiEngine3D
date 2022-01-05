#include "quad_entity_color_renderer.hpp"
#include "configuration.hpp"
#include "text_entity.hpp"

void QuadEntityColorRenderer::bind(shared_ptr<ShaderBuffer> shader, RenderBus& renderBus)
{
	shader->bind();

	shader->uploadUniform("u_nearDistance", renderBus->getNearDistance());
	shader->uploadUniform("u_farDistance", renderBus->getFarDistance());
	shader->uploadUniform("u_diffuseMap", 0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void QuadEntityColorRenderer::unbind(shared_ptr<ShaderBuffer> shader)
{
	glDisable(GL_BLEND);

	shader->unbind();
}

void QuadEntityColorRenderer::render(shared_ptr<ShaderBuffer> shader, RenderBus& renderBus, const shared_ptr<QuadEntity> entity)
{
	if(entity->isVisible() &&
	   ((entity->getPosition().y - entity->getSize().y) < entity->getMaxPosition().y) &&
	   ((entity->getPosition().y + entity->getSize().y) > entity->getMinPosition().y))
	{
		const auto buffer = entity->getMesh();

		shader->uploadUniform("u_uvMultiplier", entity->getUvMultiplier());
		shader->uploadUniform("u_uvOffset", entity->getUvOffset());
		shader->uploadUniform("u_transformationMatrix", entity->getTransformationMatrix());
		shader->uploadUniform("u_isMirroredHorizontally", entity->isMirroredHorizonally());
		shader->uploadUniform("u_isMirroredVertically", entity->isMirroredVertically());
		shader->uploadUniform("u_color", entity->getColor());
		shader->uploadUniform("u_windowSize", fvec2(Config::getInst().getWindowSize()));
		shader->uploadUniform("u_minPosition", entity->getMinPosition());
		shader->uploadUniform("u_maxPosition", entity->getMaxPosition());
		shader->uploadUniform("u_transparency", entity->getTransparency());
		shader->uploadUniform("u_isPerspectiveDepthEntity", entity->isPerspectiveDepthEntity());
		shader->uploadUniform("u_hasDiffuseMap", entity->hasDiffuseMap());
		shader->uploadUniform("u_wireframeColor", entity->getWireframeColor());
		shader->uploadUniform("u_isWireframed", entity->isWireframed());

		if(entity->hasDiffuseMap())
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap()->getID());
		}

		glBindVertexArray(buffer->getVaoID());

		glDrawArrays(GL_TRIANGLES, 0, buffer->getVertexCount());
		renderBus->increaseTriangleCount(buffer->getVertexCount() / 3);

		glBindVertexArray(0);

		if(entity->hasDiffuseMap())
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}