#include "model_entity_depth_renderer.hpp"

using std::min;
using std::max;

void ModelEntityDepthRenderer::bind()
{
	_shader->bind();

	_shader->uploadUniform("u_cameraView", _camera->getView());
	_shader->uploadUniform("u_cameraProjection", _camera->getProjection());
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

	_shader->uploadUniform("u_minX", _renderStorage->getMinPosition().x);
	_shader->uploadUniform("u_maxX", _renderStorage->getMaxPosition().x);
	_shader->uploadUniform("u_minY", max(_renderStorage->getMinPosition().y, entity->getMinHeight()));
	_shader->uploadUniform("u_maxY", min(_renderStorage->getMaxPosition().y, entity->getMaxHeight()));
	_shader->uploadUniform("u_minZ", _renderStorage->getMinPosition().z);
	_shader->uploadUniform("u_maxZ", _renderStorage->getMaxPosition().z);
	_shader->uploadUniform("u_cameraView", (entity->isFrozen() ? mat44(mat33(_camera->getView())) : _camera->getView()));

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