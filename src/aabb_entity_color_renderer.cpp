#include "aabb_entity_color_renderer.hpp"

using std::min;
using std::max;

void AabbEntityColorRenderer::bind()
{
	_shaderBuffer->bind();

	_shaderBuffer->uploadUniform("u_cameraView", _camera->getView());
	_shaderBuffer->uploadUniform("u_cameraProjection", _camera->getProjection());
	_shaderBuffer->uploadUniform("u_cameraPosition", _camera->getPosition());
	_shaderBuffer->uploadUniform("u_minFogDistance", _renderStorage->getMinFogDistance());
	_shaderBuffer->uploadUniform("u_maxFogDistance", _renderStorage->getMaxFogDistance());
	_shaderBuffer->uploadUniform("u_fogThickness", _renderStorage->getFogThickness());
	_shaderBuffer->uploadUniform("u_fogColor", _renderStorage->getFogColor());
	_shaderBuffer->uploadUniform("u_isFogEnabled", _renderStorage->isFogEnabled());

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

	_shaderBuffer->unbind();
}

void AabbEntityColorRenderer::render(const shared_ptr<AabbEntity> entity)
{
	if(!entity->isVisible())
	{
		return;
	}

	_shaderBuffer->uploadUniform("u_transformation", entity->getTransformation());
	_shaderBuffer->uploadUniform("u_color", entity->getColor());
	_shaderBuffer->uploadUniform("u_minX", _renderStorage->getMinPosition().x);
	_shaderBuffer->uploadUniform("u_maxX", _renderStorage->getMaxPosition().x);
	_shaderBuffer->uploadUniform("u_minY", _renderStorage->getMinPosition().y);
	_shaderBuffer->uploadUniform("u_maxY", _renderStorage->getMaxPosition().y);
	_shaderBuffer->uploadUniform("u_minZ", _renderStorage->getMinPosition().z);
	_shaderBuffer->uploadUniform("u_maxZ", _renderStorage->getMaxPosition().z);

	glBindVertexArray(entity->getVertexBuffer()->getVaoId());

	glDrawArrays(GL_LINE_STRIP, 0, entity->getVertexBuffer()->getVertexCount());
	_renderStorage->increaseTriangleCount(entity->getVertexBuffer()->getVertexCount() / 3);

	glBindVertexArray(0);
}