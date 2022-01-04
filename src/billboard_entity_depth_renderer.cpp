#include "billboard_entity_depth_renderer.hpp"

void BillboardEntityDepthRenderer::bind(shared_ptr<ShaderBuffer> shader, RenderBus& renderBus)
{
	shader->bind();

	shader->uploadUniform("u_viewMatrix", renderBus.getViewMatrix());
	shader->uploadUniform("u_projectionMatrix", renderBus.getProjectionMatrix());
	shader->uploadUniform("u_diffuseMap", 0);

	glEnable(GL_CLIP_DISTANCE0);
	glEnable(GL_CLIP_DISTANCE1);
	glEnable(GL_CLIP_DISTANCE2);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void BillboardEntityDepthRenderer::unbind(shared_ptr<ShaderBuffer> shader)
{
	glDisable(GL_DEPTH_TEST);

	glDisable(GL_CLIP_DISTANCE0);
	glDisable(GL_CLIP_DISTANCE1);
	glDisable(GL_CLIP_DISTANCE2);

	shader->unbind();
}

void BillboardEntityDepthRenderer::render(shared_ptr<ShaderBuffer> shader, RenderBus& renderBus, const shared_ptr<BillboardEntity> entity, float clippingY, bool isUnderWater)
{
	if(entity->isVisible())
	{
		const auto buffer = entity->getMesh();

		shader->uploadUniform("u_viewMatrix", (entity->isFrozen() ? mat44(mat33(renderBus.getViewMatrix())) : renderBus.getViewMatrix()));
		shader->uploadUniform("u_transformationMatrix", entity->getTransformationMatrix());
		shader->uploadUniform("u_minHeight", entity->getMinHeight());
		shader->uploadUniform("u_maxHeight", entity->getMaxHeight());
		shader->uploadUniform("u_clippingY", clippingY);
		shader->uploadUniform("u_isUnderWater", isUnderWater);
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