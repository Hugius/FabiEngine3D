#include "water_entity_depth_renderer.hpp"

using std::min;
using std::max;

void WaterEntityDepthRenderer::bind()
{
	_shaderBuffer->bind();

	_shaderBuffer->uploadUniform("u_cameraView", _camera->getView());
	_shaderBuffer->uploadUniform("u_cameraProjection", _camera->getProjection());

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

	_shaderBuffer->unbind();
}

void WaterEntityDepthRenderer::render(const shared_ptr<WaterEntity> entity)
{
	if(!entity->isVisible())
	{
		return;
	}

	_shaderBuffer->uploadUniform("u_height", entity->getHeight());
	_shaderBuffer->uploadUniform("u_minX", _renderStorage->getMinClipPosition().x);
	_shaderBuffer->uploadUniform("u_maxX", _renderStorage->getMaxClipPosition().x);
	_shaderBuffer->uploadUniform("u_minY", _renderStorage->getMinClipPosition().y);
	_shaderBuffer->uploadUniform("u_maxY", _renderStorage->getMaxClipPosition().y);
	_shaderBuffer->uploadUniform("u_minZ", _renderStorage->getMinClipPosition().z);
	_shaderBuffer->uploadUniform("u_maxZ", _renderStorage->getMaxClipPosition().z);

	glBindVertexArray(entity->getLowQualityVertexBuffer()->getVaoId());

	glDrawArrays(GL_TRIANGLES, 0, entity->getLowQualityVertexBuffer()->getVertexCount());
	_renderStorage->increaseTriangleCount(entity->getLowQualityVertexBuffer()->getVertexCount() / 3);

	glBindVertexArray(0);
}