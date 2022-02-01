#include "terrain_entity_depth_renderer.hpp"
#include "render_bus.hpp"

using std::min;
using std::max;

void TerrainEntityDepthRenderer::bind()
{
	_shader->bind();

	_shader->uploadUniform("u_cameraView", _renderBus->getCameraView());
	_shader->uploadUniform("u_cameraProjection", _renderBus->getCameraProjection());

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

	_shader->unbind();
}

void TerrainEntityDepthRenderer::render(const shared_ptr<TerrainEntity> entity)
{
	if(!entity->isVisible())
	{
		return;
	}

	_shader->uploadUniform("u_minX", _renderBus->getMinPosition().x);
	_shader->uploadUniform("u_maxX", _renderBus->getMaxPosition().x);
	_shader->uploadUniform("u_minY", _renderBus->getMinPosition().y);
	_shader->uploadUniform("u_maxY", _renderBus->getMaxPosition().y);
	_shader->uploadUniform("u_minZ", _renderBus->getMinPosition().z);
	_shader->uploadUniform("u_maxZ", _renderBus->getMaxPosition().z);

	glEnable(GL_CULL_FACE);

	glBindVertexArray(entity->getMesh()->getVaoId());

	glDrawArrays(GL_TRIANGLES, 0, entity->getMesh()->getVertexCount());

	glBindVertexArray(0);

	glDisable(GL_CULL_FACE);
}