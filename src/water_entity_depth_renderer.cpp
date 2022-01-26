#include "water_entity_depth_renderer.hpp"

void WaterEntityDepthRenderer::bind()
{
	_shader->bind();

	_shader->uploadUniform("u_viewMatrix", _renderBus->getViewMatrix());
	_shader->uploadUniform("u_projectionMatrix", _renderBus->getProjectionMatrix());
	_shader->uploadUniform("u_displacementMap", 0);

	glEnable(GL_CLIP_DISTANCE0);
	glEnable(GL_CLIP_DISTANCE1);
	glEnable(GL_CLIP_DISTANCE2);
	glEnable(GL_CLIP_DISTANCE3);
	glEnable(GL_CLIP_DISTANCE4);
	glEnable(GL_CLIP_DISTANCE5);
	glEnable(GL_DEPTH_TEST);
}

void WaterEntityDepthRenderer::unbind()
{
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CLIP_DISTANCE0);
	glDisable(GL_CLIP_DISTANCE1);
	glDisable(GL_CLIP_DISTANCE2);
	glDisable(GL_CLIP_DISTANCE3);
	glDisable(GL_CLIP_DISTANCE4);
	glDisable(GL_CLIP_DISTANCE5);

	_shader->unbind();
}

void WaterEntityDepthRenderer::render(const shared_ptr<WaterEntity> entity)
{
	if(entity->isVisible())
	{
		_shader->uploadUniform("u_waveOffset", entity->getWaveOffset());
		_shader->uploadUniform("u_waveHeight", entity->getWaveHeight());
		_shader->uploadUniform("u_height", entity->getHeight());
		_shader->uploadUniform("u_textureRepeat", entity->getTextureRepeat());
		_shader->uploadUniform("u_minX", _renderBus->getMinPosition().x);
		_shader->uploadUniform("u_maxX", _renderBus->getMaxPosition().x);
		_shader->uploadUniform("u_minY", _renderBus->getMinPosition().y);
		_shader->uploadUniform("u_maxY", _renderBus->getMaxPosition().y);
		_shader->uploadUniform("u_minZ", _renderBus->getMinPosition().z);
		_shader->uploadUniform("u_maxZ", _renderBus->getMaxPosition().z);
		_shader->uploadUniform("u_hasDisplacementMap", (entity->getDisplacementMap() != nullptr));

		if(entity->getDisplacementMap() != nullptr)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, entity->getDisplacementMap()->getId());
		}

		if(entity->getDisplacementMap() != nullptr)
		{
			glBindVertexArray(entity->getHighQualityMesh()->getVaoId());
		}
		else
		{
			glBindVertexArray(entity->getLowQualityMesh()->getVaoId());
		}

		if(entity->getDisplacementMap() != nullptr)
		{
			glDrawArrays(GL_TRIANGLES, 0, entity->getHighQualityMesh()->getVertexCount());
			_renderBus->increaseTriangleCount(entity->getHighQualityMesh()->getVertexCount() / 3);
		}
		else
		{
			glDrawArrays(GL_TRIANGLES, 0, entity->getLowQualityMesh()->getVertexCount());
			_renderBus->increaseTriangleCount(entity->getLowQualityMesh()->getVertexCount() / 3);
		}

		glBindVertexArray(0);

		if(entity->getDisplacementMap() != nullptr)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}