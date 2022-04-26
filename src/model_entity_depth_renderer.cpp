#include "model_entity_depth_renderer.hpp"

using std::min;
using std::max;

void ModelEntityDepthRenderer::bind()
{
	_shaderBuffer->bind();

	_shaderBuffer->uploadUniform("u_cameraView", _camera->getView());
	_shaderBuffer->uploadUniform("u_cameraProjection", _camera->getProjection());
	_shaderBuffer->uploadUniform("u_diffuseMap", 0);

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

	_shaderBuffer->unbind();
}

void ModelEntityDepthRenderer::render(const shared_ptr<ModelEntity> entity)
{
	if(!entity->isVisible())
	{
		return;
	}

	_shaderBuffer->uploadUniform("u_minX", max(_renderStorage->getMinClipPosition().x, entity->getMinClipPosition().x));
	_shaderBuffer->uploadUniform("u_minY", max(_renderStorage->getMinClipPosition().y, entity->getMinClipPosition().y));
	_shaderBuffer->uploadUniform("u_minZ", max(_renderStorage->getMinClipPosition().z, entity->getMinClipPosition().z));
	_shaderBuffer->uploadUniform("u_maxX", min(_renderStorage->getMaxClipPosition().x, entity->getMaxClipPosition().x));
	_shaderBuffer->uploadUniform("u_maxY", min(_renderStorage->getMaxClipPosition().y, entity->getMaxClipPosition().y));
	_shaderBuffer->uploadUniform("u_maxZ", min(_renderStorage->getMaxClipPosition().z, entity->getMaxClipPosition().z));
	_shaderBuffer->uploadUniform("u_cameraView", (entity->isFrozen() ? mat44(mat33(_camera->getView())) : _camera->getView()));

	for(const auto & partId : entity->getPartIds())
	{
		_shaderBuffer->uploadUniform("u_transformation", entity->getTransformation(partId));
		_shaderBuffer->uploadUniform("u_textureRepeat", entity->getTextureRepeat(partId));
		_shaderBuffer->uploadUniform("u_minTextureAlpha", entity->getMinTextureAlpha(partId));

		if(entity->isFaceCulled(partId))
		{
			glEnable(GL_CULL_FACE);
		}

		if(entity->getDiffuseTextureBuffer(partId) != nullptr)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, entity->getDiffuseTextureBuffer(partId)->getTboId());
		}

		glBindVertexArray(entity->getVertexBuffer(partId)->getVaoId());

		glDrawArrays(GL_TRIANGLES, 0, entity->getVertexBuffer(partId)->getVertexCount());

		glBindVertexArray(0);

		if(entity->getDiffuseTextureBuffer(partId) != nullptr)
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