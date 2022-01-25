#include "quad3d_entity_color_renderer.hpp"
#include "configuration.hpp"

void Quad3dEntityColorRenderer::bind()
{
	_shader->bind();

	_shader->uploadUniform("u_projectionMatrix", _renderBus->getProjectionMatrix());
	_shader->uploadUniform("u_cameraPosition", _renderBus->getCameraPosition());
	_shader->uploadUniform("u_fogMinDistance", _renderBus->getFogMinDistance());
	_shader->uploadUniform("u_fogMaxDistance", _renderBus->getFogMaxDistance());
	_shader->uploadUniform("u_fogThickness", _renderBus->getFogThickness());
	_shader->uploadUniform("u_fogColor", _renderBus->getFogColor());
	_shader->uploadUniform("u_isFogEnabled", _renderBus->isFogEnabled());
	_shader->uploadUniform("u_diffuseMap", 0);
	_shader->uploadUniform("u_emissionMap", 1);

	glEnable(GL_CLIP_DISTANCE0);
	glEnable(GL_CLIP_DISTANCE1);
	glEnable(GL_CLIP_DISTANCE2);
	glEnable(GL_CLIP_DISTANCE3);
	glEnable(GL_CLIP_DISTANCE4);
	glEnable(GL_CLIP_DISTANCE5);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Quad3dEntityColorRenderer::unbind()
{
	glDisable(GL_BLEND);

	glDisable(GL_DEPTH_TEST);

	glDisable(GL_CLIP_DISTANCE0);
	glDisable(GL_CLIP_DISTANCE1);
	glDisable(GL_CLIP_DISTANCE2);
	glDisable(GL_CLIP_DISTANCE3);
	glDisable(GL_CLIP_DISTANCE4);
	glDisable(GL_CLIP_DISTANCE5);

	_shader->unbind();
}

void Quad3dEntityColorRenderer::render(const shared_ptr<Quad3dEntity> entity)
{
	if(entity->isVisible())
	{
		const auto buffer = entity->getMesh();

		if(entity->isWireframed())
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}

		_shader->uploadUniform("u_viewMatrix", (entity->isFrozen() ? mat44(mat33(_renderBus->getViewMatrix())) : _renderBus->getViewMatrix()));
		_shader->uploadUniform("u_isWireframed", (entity->isWireframed() || _renderBus->isWireframeRenderingEnabled()));
		_shader->uploadUniform("u_transformationMatrix", entity->getTransformationMatrix());
		_shader->uploadUniform("u_hasDiffuseMap", (entity->getDiffuseMap() != nullptr));
		_shader->uploadUniform("u_hasEmissionMap", (entity->getEmissionMap() != nullptr));
		_shader->uploadUniform("u_color", entity->getColor());
		_shader->uploadUniform("u_wireframeColor", entity->getWireframeColor());
		_shader->uploadUniform("u_lightness", entity->getLightness());
		_shader->uploadUniform("u_minX", _renderBus->getMinPosition().x);
		_shader->uploadUniform("u_maxX", _renderBus->getMaxPosition().x);
		_shader->uploadUniform("u_minY", _renderBus->getMinPosition().y);
		_shader->uploadUniform("u_maxY", _renderBus->getMaxPosition().y);
		_shader->uploadUniform("u_minZ", _renderBus->getMinPosition().z);
		_shader->uploadUniform("u_maxZ", _renderBus->getMaxPosition().z);
		_shader->uploadUniform("u_opacity", entity->getOpacity());
		_shader->uploadUniform("u_isBright", entity->isBright());
		_shader->uploadUniform("u_emissionIntensity", entity->getEmissionIntensity());
		_shader->uploadUniform("u_textureRepeat", entity->getTextureRepeat());
		_shader->uploadUniform("u_uvMultiplier", entity->getUvMultiplier());
		_shader->uploadUniform("u_uvOffset", entity->getUvOffset());
		_shader->uploadUniform("u_minTextureOpacity", MIN_TEXTURE_OPACITY);

		if(entity->getDiffuseMap() != nullptr)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap()->getId());
		}
		if(entity->getEmissionMap() != nullptr)
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, entity->getEmissionMap()->getId());
		}

		glBindVertexArray(buffer->getVaoId());

		glDrawArrays(GL_TRIANGLES, 0, buffer->getVertexCount());
		_renderBus->increaseTriangleCount(buffer->getVertexCount() / 3);

		glBindVertexArray(0);

		if(entity->getDiffuseMap() != nullptr)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		if(entity->getEmissionMap() != nullptr)
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		if(entity->isWireframed())
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}
}