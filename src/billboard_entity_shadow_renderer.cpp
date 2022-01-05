#include "billboard_entity_shadow_renderer.hpp"

void BillboardEntityShadowRenderer::bind(shared_ptr<ShaderBuffer> shader, RenderBus& renderBus)
{
	shader->bind();

	shader->uploadUniform("u_lightSpaceMatrix", renderBus->getShadowMatrix());
	shader->uploadUniform("u_diffuseMap", 0);

	glEnable(GL_CLIP_DISTANCE0);
	glEnable(GL_CLIP_DISTANCE1);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void BillboardEntityShadowRenderer::unbind(shared_ptr<ShaderBuffer> shader)
{
	glDisable(GL_DEPTH_TEST);

	glDisable(GL_CLIP_DISTANCE0);
	glDisable(GL_CLIP_DISTANCE1);

	shader->unbind();
}

void BillboardEntityShadowRenderer::render(shared_ptr<ShaderBuffer> shader, const shared_ptr<BillboardEntity> entity)
{
	if(entity->isVisible() && entity->isShadowed())
	{
		const auto buffer = entity->getMesh();

		shader->uploadUniform("u_transformationMatrix", entity->getTransformationMatrix());
		shader->uploadUniform("u_minHeight", entity->getMinHeight());
		shader->uploadUniform("u_maxHeight", entity->getMaxHeight());
		shader->uploadUniform("u_textureRepeat", entity->getTextureRepeat());
		shader->uploadUniform("u_uvMultiplier", entity->getUvMultiplier());
		shader->uploadUniform("u_uvOffset", entity->getUvOffset());
		shader->uploadUniform("u_minTextureTransparency", MIN_TEXTURE_TRANSPARENCY);

		if(entity->hasDiffuseMap())
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap()->getID());
		}

		glBindVertexArray(buffer->getVaoID());

		glDrawArrays(GL_TRIANGLES, 0, buffer->getVertexCount());

		glBindVertexArray(0);

		if(entity->hasDiffuseMap())
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}