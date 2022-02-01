#include "model_entity_depth_renderer.hpp"

using std::min;
using std::max;

void ModelEntityDepthRenderer::bind()
{
	_shader->bind();

	_shader->uploadUniform("u_cameraView", _renderBus->getCameraView());
	_shader->uploadUniform("u_cameraProjection", _renderBus->getCameraProjection());
	_shader->uploadUniform("u_diffuseMap", 0);

	glEnable(GL_CLIP_DISTANCE0);
	glEnable(GL_CLIP_DISTANCE1);
	glEnable(GL_CLIP_DISTANCE2);
	glEnable(GL_CLIP_DISTANCE3);
	glEnable(GL_CLIP_DISTANCE4);
	glEnable(GL_CLIP_DISTANCE5);
	glEnable(GL_DEPTH_TEST);
}

void ModelEntityDepthRenderer::unbind()
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

void ModelEntityDepthRenderer::render(const shared_ptr<ModelEntity> entity)
{
	if(!entity->isVisible())
	{
		return;
	}

	_shader->uploadUniform("u_minX", _renderBus->getMinPosition().x);
	_shader->uploadUniform("u_maxX", _renderBus->getMaxPosition().x);
	_shader->uploadUniform("u_minY", max(_renderBus->getMinPosition().y, entity->getMinHeight()));
	_shader->uploadUniform("u_maxY", min(_renderBus->getMaxPosition().y, entity->getMaxHeight()));
	_shader->uploadUniform("u_minZ", _renderBus->getMinPosition().z);
	_shader->uploadUniform("u_maxZ", _renderBus->getMaxPosition().z);
	_shader->uploadUniform("u_cameraView", (entity->isFrozen() ? mat44(mat33(_renderBus->getCameraView())) : _renderBus->getCameraView()));

	for(const auto& partId : entity->getPartIds())
	{
		_shader->uploadUniform("u_transformation", entity->getTransformation(partId));
		_shader->uploadUniform("u_textureRepeat", entity->getTextureRepeat(partId));
		_shader->uploadUniform("u_minTextureAlpha", entity->getMinTextureAlpha(partId));

		if(entity->isFaceCulled(partId))
		{
			glEnable(GL_CULL_FACE);
		}

		if(entity->getDiffuseMap(partId) != nullptr)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap(partId)->getId());
		}

		glBindVertexArray(entity->getMesh(partId)->getVaoId());

		glDrawArrays(GL_TRIANGLES, 0, entity->getMesh(partId)->getVertexCount());

		glBindVertexArray(0);

		if(entity->getDiffuseMap(partId) != nullptr)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		if(entity->isFaceCulled(partId))
		{
			glDisable(GL_CULL_FACE);
		}
	}
}