#include "billboard_entity_color_renderer.hpp"
#include "configuration.hpp"

void BillboardEntityColorRenderer::bind(shared_ptr<ShaderBuffer> shader, RenderBus& renderBus)
{
	shader->bind();

	shader->uploadUniform("u_projectionMatrix", renderBus.getProjectionMatrix());
	shader->uploadUniform("u_clippingPlane", renderBus.getClippingPlane());
	shader->uploadUniform("u_cameraPosition", renderBus.getCameraPosition());
	shader->uploadUniform("u_fogMinDistance", renderBus.getFogMinDistance());
	shader->uploadUniform("u_fogMaxDistance", renderBus.getFogMaxDistance());
	shader->uploadUniform("u_fogThickness", renderBus.getFogThickness());
	shader->uploadUniform("u_fogColor", renderBus.getFogColor());
	shader->uploadUniform("u_isFogEnabled", renderBus.isFogEnabled());
	shader->uploadUniform("u_diffuseMap", 0);
	shader->uploadUniform("u_emissionMap", 1);

	glEnable(GL_CLIP_DISTANCE0);
	glEnable(GL_CLIP_DISTANCE1);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void BillboardEntityColorRenderer::unbind(shared_ptr<ShaderBuffer> shader)
{
	glDisable(GL_BLEND);

	glDisable(GL_DEPTH_TEST);

	glDisable(GL_CLIP_DISTANCE0);
	glDisable(GL_CLIP_DISTANCE1);

	shader->unbind();
}

void BillboardEntityColorRenderer::render(shared_ptr<ShaderBuffer> shader, RenderBus& renderBus, const shared_ptr<BillboardEntity> entity)
{
	if(entity->isVisible())
	{
		const auto buffer = entity->getMesh();

		if(entity->isWireframed())
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}

		shader->uploadUniform("u_viewMatrix", (entity->isFrozen() ? mat44(mat33(renderBus.getViewMatrix())) : renderBus.getViewMatrix()));
		shader->uploadUniform("u_isWireframed", (entity->isWireframed() || renderBus.isWireframeRenderingEnabled()));
		shader->uploadUniform("u_transformationMatrix", entity->getTransformationMatrix());
		shader->uploadUniform("u_hasDiffuseMap", entity->hasDiffuseMap());
		shader->uploadUniform("u_hasEmissionMap", entity->hasEmissionMap());
		shader->uploadUniform("u_color", entity->getColor());
		shader->uploadUniform("u_wireframeColor", entity->getWireframeColor());
		shader->uploadUniform("u_lightness", entity->getLightness());
		shader->uploadUniform("u_minHeight", entity->getMinHeight());
		shader->uploadUniform("u_maxHeight", entity->getMaxHeight());
		shader->uploadUniform("u_transparency", entity->getTransparency());
		shader->uploadUniform("u_isBright", entity->isBright());
		shader->uploadUniform("u_emissionIntensity", entity->getEmissionIntensity());
		shader->uploadUniform("u_textureRepeat", entity->getTextureRepeat());
		shader->uploadUniform("u_uvMultiplier", entity->getUvMultiplier());
		shader->uploadUniform("u_uvOffset", entity->getUvOffset());
		shader->uploadUniform("u_minTextureTransparency", MIN_TEXTURE_TRANSPARENCY);

		if(entity->hasDiffuseMap())
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap()->getID());
		}
		if(entity->hasEmissionMap())
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, entity->getEmissionMap()->getID());
		}

		glBindVertexArray(buffer->getVaoID());

		glDrawArrays(GL_TRIANGLES, 0, buffer->getVertexCount());
		renderBus.increaseTriangleCount(buffer->getVertexCount() / 3);

		glBindVertexArray(0);

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

		if(entity->isWireframed())
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}
}