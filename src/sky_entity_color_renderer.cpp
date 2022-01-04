#include "sky_entity_color_renderer.hpp"

void SkyEntityColorRenderer::bind(shared_ptr<ShaderBuffer> shader, RenderBus& renderBus)
{
	shader->bind();

	shader->uploadUniform("u_viewMatrix", mat44(mat33(renderBus.getViewMatrix())));
	shader->uploadUniform("u_projectionMatrix", renderBus.getProjectionMatrix());
	shader->uploadUniform("u_mixValue", renderBus.getSkyMixValue());
	shader->uploadUniform("u_mainCubeMap", 0);
	shader->uploadUniform("u_mixCubeMap", 1);
}

void SkyEntityColorRenderer::unbind(shared_ptr<ShaderBuffer> shader)
{
	shader->unbind();
}

void SkyEntityColorRenderer::render(shared_ptr<ShaderBuffer> shader, RenderBus& renderBus, const shared_ptr<SkyEntity> mainEntity, const shared_ptr<SkyEntity> mixEntity)
{
	if(mainEntity->isVisible())
	{
		if(mainEntity->isWireframed())
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}

		shader->uploadUniform("u_isWireframed", (mainEntity->isWireframed() || renderBus.isWireframeRenderingEnabled()));
		shader->uploadUniform("u_rotationMatrix", mainEntity->getRotationMatrix());
		shader->uploadUniform("u_mainLightness", mainEntity->getLightness());
		shader->uploadUniform("u_mainColor", mainEntity->getColor());
		shader->uploadUniform("u_wireframeColor", mainEntity->getWireframeColor());

		if(mixEntity != nullptr)
		{
			shader->uploadUniform("u_mixLightness", mixEntity->getLightness());
			shader->uploadUniform("u_mixColor", mixEntity->getColor());
		}

		if(mainEntity->hasCubeMap())
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, mainEntity->getCubeMap()->getID());
		}

		if(mixEntity != nullptr)
		{
			if(mixEntity->hasCubeMap())
			{
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_CUBE_MAP, mixEntity->getCubeMap()->getID());
			}
		}

		glBindVertexArray(mainEntity->getMesh()->getVaoID());

		glDrawArrays(GL_TRIANGLES, 0, mainEntity->getMesh()->getVertexCount());
		renderBus.increaseTriangleCount(mainEntity->getMesh()->getVertexCount() / 3);

		glBindVertexArray(0);

		if(mainEntity->hasCubeMap())
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		}

		if(mixEntity != nullptr)
		{
			if(mixEntity->hasCubeMap())
			{
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
			}
		}

		if(mainEntity->isWireframed())
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}
}