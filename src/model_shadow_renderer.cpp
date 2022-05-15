#include "model_shadow_renderer.hpp"
#include "render_storage.hpp"

using std::min;
using std::max;

void ModelShadowRenderer::bind()
{
	_shaderBuffer->bind();
	_shaderBuffer->uploadUniform("u_shadowView", _renderStorage->getShadowView());
	_shaderBuffer->uploadUniform("u_shadowProjection", _renderStorage->getShadowProjection());
	_shaderBuffer->uploadUniform("u_diffuseMap", 0);

	glEnable(GL_CLIP_DISTANCE0);
	glEnable(GL_CLIP_DISTANCE1);
	glEnable(GL_CLIP_DISTANCE2);
	glEnable(GL_CLIP_DISTANCE3);
	glEnable(GL_CLIP_DISTANCE4);
	glEnable(GL_CLIP_DISTANCE5);
	glEnable(GL_DEPTH_TEST);
}

void ModelShadowRenderer::unbind()
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

void ModelShadowRenderer::render(const shared_ptr<Model> model)
{
	if(!model->isVisible() || !model->isShadowed())
	{
		return;
	}

	_shaderBuffer->uploadUniform("u_minX", max(_renderStorage->getMinClipPosition().x, model->getMinClipPosition().x));
	_shaderBuffer->uploadUniform("u_minY", max(_renderStorage->getMinClipPosition().y, model->getMinClipPosition().y));
	_shaderBuffer->uploadUniform("u_minZ", max(_renderStorage->getMinClipPosition().z, model->getMinClipPosition().z));
	_shaderBuffer->uploadUniform("u_maxX", min(_renderStorage->getMaxClipPosition().x, model->getMaxClipPosition().x));
	_shaderBuffer->uploadUniform("u_maxY", min(_renderStorage->getMaxClipPosition().y, model->getMaxClipPosition().y));
	_shaderBuffer->uploadUniform("u_maxZ", min(_renderStorage->getMaxClipPosition().z, model->getMaxClipPosition().z));

	for(const auto & partId : model->getPartIds())
	{
		_shaderBuffer->uploadUniform("u_transformation", model->getTransformation(partId));
		_shaderBuffer->uploadUniform("u_textureRepeat", model->getTextureRepeat(partId));
		_shaderBuffer->uploadUniform("u_minTextureAlpha", model->getMinTextureAlpha(partId));

		if(model->isFaceCulled(partId))
		{
			glEnable(GL_CULL_FACE);
		}

		if(model->getDiffuseTextureBuffer(partId) != nullptr)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, model->getDiffuseTextureBuffer(partId)->getTboId());
		}

		glBindVertexArray(model->getVertexBuffer(partId)->getVaoId());
		glDrawArrays(GL_TRIANGLES, 0, model->getVertexBuffer(partId)->getVertexCount());
		glBindVertexArray(0);

		if(model->getDiffuseTextureBuffer(partId) != nullptr)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		if(model->isFaceCulled(partId))
		{
			glDisable(GL_CULL_FACE);
		}
	}
}