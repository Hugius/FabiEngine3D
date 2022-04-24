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
	_shaderBuffer->uploadUniform("u_minX", max(_renderStorage->getMinClipPosition().x, entity->getMinClipPosition().x));
	_shaderBuffer->uploadUniform("u_maxX", min(_renderStorage->getMaxClipPosition().x, entity->getMaxClipPosition().x));
	_shaderBuffer->uploadUniform("u_minY", max(_renderStorage->getMinClipPosition().y, entity->getMinClipPosition().y));
	_shaderBuffer->uploadUniform("u_maxY", min(_renderStorage->getMaxClipPosition().y, entity->getMaxClipPosition().y));
	_shaderBuffer->uploadUniform("u_minZ", max(_renderStorage->getMinClipPosition().z, entity->getMinClipPosition().z));
	_shaderBuffer->uploadUniform("u_maxZ", min(_renderStorage->getMaxClipPosition().z, entity->getMaxClipPosition().z));

	glBindVertexArray(entity->getVertexBuffer()->getVaoId());

	glDrawArrays(GL_LINE_STRIP, 0, entity->getVertexBuffer()->getVertexCount());
	_renderStorage->increaseTriangleCount(entity->getVertexBuffer()->getVertexCount() / 3);

	glBindVertexArray(0);
}