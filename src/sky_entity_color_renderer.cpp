#include "sky_entity_color_renderer.hpp"

void SkyEntityColorRenderer::bind()
{
	_shader->bind();

	_shader->uploadUniform("u_viewMatrix", mat44(mat33(_renderBus->getViewMatrix())));
	_shader->uploadUniform("u_projectionMatrix", _renderBus->getProjectionMatrix());
	_shader->uploadUniform("u_mixValue", _renderBus->getSkyMixValue());
	_shader->uploadUniform("u_mainCubeMap", 0);
	_shader->uploadUniform("u_mixCubeMap", 1);
}

void SkyEntityColorRenderer::unbind()
{
	_shader->unbind();
}

void SkyEntityColorRenderer::render(const shared_ptr<SkyEntity> mainEntity, const shared_ptr<SkyEntity> mixEntity)
{
	if(mainEntity->isVisible())
	{
		if(mainEntity->isWireframed())
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}

		_shader->uploadUniform("u_isWireframed", (mainEntity->isWireframed() || _renderBus->isWireframeRenderingEnabled()));
		_shader->uploadUniform("u_rotationMatrix", mainEntity->getRotationMatrix());
		_shader->uploadUniform("u_mainLightness", mainEntity->getLightness());
		_shader->uploadUniform("u_mainColor", mainEntity->getColor());
		_shader->uploadUniform("u_wireframeColor", mainEntity->getWireframeColor());

		if(mixEntity != nullptr)
		{
			_shader->uploadUniform("u_mixLightness", mixEntity->getLightness());
			_shader->uploadUniform("u_mixColor", mixEntity->getColor());
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
		_renderBus->increaseTriangleCount(mainEntity->getMesh()->getVertexCount() / 3);

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