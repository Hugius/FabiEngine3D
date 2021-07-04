#include "billboard_entity_renderer.hpp"
#include "configuration.hpp"

void BillboardEntityRenderer::bind()
{
	// Bind shader
	_shader.bind();

	// Vertex shader uniforms
	_shader.uploadUniform("u_cameraPosition", _renderBus.getCameraPosition());
	_shader.uploadUniform("u_viewMatrix",	  _renderBus.getViewMatrix());
	_shader.uploadUniform("u_projMatrix",	  _renderBus.getProjectionMatrix());

	// Fragment shader uniforms
	_shader.uploadUniform("u_fogMinDistance",	_renderBus.getFogMinDistance());
	_shader.uploadUniform("u_fogMaxDistance",	_renderBus.getFogMaxDistance());
	_shader.uploadUniform("u_fogThickness",	_renderBus.getFogThickness());
	_shader.uploadUniform("u_fogColor",			_renderBus.getFogColor());
	_shader.uploadUniform("u_isFogEnabled",		_renderBus.isFogEnabled());

	// Texture uniforms
	_shader.uploadUniform("u_sampler", 0);

	// Clipping (minY & maxY)
	glEnable(GL_CLIP_DISTANCE0);
	glEnable(GL_CLIP_DISTANCE1);

	// Depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void BillboardEntityRenderer::unbind()
{
	glDisable(GL_CLIP_DISTANCE0);
	glDisable(GL_CLIP_DISTANCE1);
	glDisable(GL_DEPTH_TEST);
	_shader.unbind();
}

void BillboardEntityRenderer::render(const shared_ptr<BillboardEntity> entity)
{
	if (entity->isVisible() && !entity->getRenderBuffers().empty())
	{
		// Sprite animation
		Vec2 uvMultiplier = Vec2(1.0f);
		Vec2 uvAdder = Vec2(0.0f);
		if (entity->isSpriteAnimationStarted())
		{
			uvMultiplier = Vec2(1.0f / static_cast<float>(entity->getTotalSpriteAnimationColumns()), 1.0f / static_cast<float>(entity->getTotalSpriteAnimationRows()));
			uvAdder = Vec2(static_cast<float>(entity->getSpriteAnimationColumnIndex()) * uvMultiplier.x, static_cast<float>(entity->getSpriteAnimationRowIndex()) * uvMultiplier.y);
		}

		// Shader uniforms
		_shader.uploadUniform("u_uvAdder", uvAdder);
		_shader.uploadUniform("u_uvMultiplier", uvMultiplier);
		_shader.uploadUniform("u_modelMatrix", entity->getModelMatrix());
		_shader.uploadUniform("u_isAlphaObject", entity->isTransparent());
		_shader.uploadUniform("u_hasTexture", entity->getDiffuseMap() != 0);
		_shader.uploadUniform("u_color", entity->getColor());
		_shader.uploadUniform("u_lightness", entity->getLightness());
		_shader.uploadUniform("u_currentY", entity->getTranslation().y);
		_shader.uploadUniform("u_minHeight", entity->getMinHeight());
		_shader.uploadUniform("u_maxHeight", entity->getMaxHeight());
		_shader.uploadUniform("u_minAlpha", entity->getTextContent().empty() ? 0.9f : 0.1f);

		// Bind texture
		if (entity->hasDiffuseMap())
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap());
		}

		// Bind buffer
		glBindVertexArray(entity->getRenderBuffer()->getVAO());

		// Render
		if (entity->getRenderBuffer()->isInstanced()) // Instanced
		{
			_shader.uploadUniform("u_isInstanced", true);
			glDrawArraysInstanced(GL_TRIANGLES, 0, entity->getRenderBuffer()->getVertexCount(), entity->getRenderBuffer()->getInstancedOffsetCount());
			_renderBus.increaseTriangleCount((entity->getRenderBuffer()->getInstancedOffsetCount() * entity->getRenderBuffer()->getVertexCount()) / 3);
		}
		else // Non-instanced
		{
			_shader.uploadUniform("u_isInstanced", false);
			glDrawArrays(GL_TRIANGLES, 0, entity->getRenderBuffer()->getVertexCount());
			_renderBus.increaseTriangleCount(entity->getRenderBuffer()->getVertexCount() / 3);
		}

		// Unbind buffer
		glBindVertexArray(0);

		// Unbind texture
		if (entity->hasDiffuseMap())
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}