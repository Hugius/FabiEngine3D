#include "terrain_entity_depth_renderer.hpp"
#include "render_storage.hpp"

using std::min;
using std::max;

void TerrainEntityDepthRenderer::bind()
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

void TerrainEntityDepthRenderer::unbind()
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

void TerrainEntityDepthRenderer::render(const shared_ptr<TerrainEntity> entity)
{
	if(!entity->isVisible())
	{
		return;
	}

	_shaderBuffer->uploadUniform("u_minX", _renderStorage->getMinClippingPosition().x);
	_shaderBuffer->uploadUniform("u_maxX", _renderStorage->getMaxClippingPosition().x);
	_shaderBuffer->uploadUniform("u_minY", _renderStorage->getMinClippingPosition().y);
	_shaderBuffer->uploadUniform("u_maxY", _renderStorage->getMaxClippingPosition().y);
	_shaderBuffer->uploadUniform("u_minZ", _renderStorage->getMinClippingPosition().z);
	_shaderBuffer->uploadUniform("u_maxZ", _renderStorage->getMaxClippingPosition().z);

	glEnable(GL_CULL_FACE);

	glBindVertexArray(entity->getVertexBuffer()->getVaoId());

	glDrawArrays(GL_TRIANGLES, 0, entity->getVertexBuffer()->getVertexCount());

	glBindVertexArray(0);

	glDisable(GL_CULL_FACE);
}