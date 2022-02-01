#include "aabb_entity_color_renderer.hpp"

using std::min;
using std::max;

void AabbEntityColorRenderer::bind()
{
	_shader->bind();

	_shader->uploadUniform("u_cameraView", _renderBus->getCameraView());
	_shader->uploadUniform("u_cameraProjection", _renderBus->getCameraProjection());
	_shader->uploadUniform("u_cameraPosition", _renderBus->getCameraPosition());
	_shader->uploadUniform("u_fogMinDistance", _renderBus->getFogMinDistance());
	_shader->uploadUniform("u_fogMaxDistance", _renderBus->getFogMaxDistance());
	_shader->uploadUniform("u_fogThickness", _renderBus->getFogThickness());
	_shader->uploadUniform("u_fogColor", _renderBus->getFogColor());
	_shader->uploadUniform("u_isFogEnabled", _renderBus->isFogEnabled());

	glEnable(GL_CLIP_DISTANCE0);
	glEnable(GL_CLIP_DISTANCE1);
	glEnable(GL_CLIP_DISTANCE2);
	glEnable(GL_CLIP_DISTANCE3);
	glEnable(GL_CLIP_DISTANCE4);
	glEnable(GL_CLIP_DISTANCE5);
	glEnable(GL_DEPTH_TEST);
}

void AabbEntityColorRenderer::unbind()
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

void AabbEntityColorRenderer::render(const shared_ptr<AabbEntity> entity)
{
	if(!entity->isVisible())
	{
		return;
	}

	_shader->uploadUniform("u_transformation", entity->getTransformation());
	_shader->uploadUniform("u_color", entity->getColor());
	_shader->uploadUniform("u_minX", _renderBus->getMinPosition().x);
	_shader->uploadUniform("u_maxX", _renderBus->getMaxPosition().x);
	_shader->uploadUniform("u_minY", _renderBus->getMinPosition().y);
	_shader->uploadUniform("u_maxY", _renderBus->getMaxPosition().y);
	_shader->uploadUniform("u_minZ", _renderBus->getMinPosition().z);
	_shader->uploadUniform("u_maxZ", _renderBus->getMaxPosition().z);

	glBindVertexArray(entity->getMesh()->getVaoId());

	glDrawArrays(GL_LINE_STRIP, 0, entity->getMesh()->getVertexCount());
	_renderBus->increaseTriangleCount(entity->getMesh()->getVertexCount() / 3);

	glBindVertexArray(0);
}