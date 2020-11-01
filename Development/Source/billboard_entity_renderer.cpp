#include "billboard_entity_renderer.hpp"
#include "configuration.hpp"

void BillboardEntityRenderer::bind()
{
	// Define clipping plane for scene reflections
	vec4 clippingPlane = vec4(0.0f, 1.0f, 0.0f, -(_renderBus.getSceneReflectionHeight() + _renderBus.getSceneReflectionOffset()));

	// Bind shader
	_shader.bind();

	// Vertex shader uniforms
	_shader.uploadUniform("u_cameraPosition", _renderBus.getCameraPosition());
	_shader.uploadUniform("u_viewMatrix",	  _renderBus.getViewMatrix());
	_shader.uploadUniform("u_projMatrix",	  _renderBus.getProjectionMatrix());
	_shader.uploadUniform("u_clippingPlane",  clippingPlane);

	// Fragment shader uniforms
	_shader.uploadUniform("u_fogMinDistance",	_renderBus.getFogMinDistance());
	_shader.uploadUniform("u_fogMaxDistance",	_renderBus.getFogMaxDistance());
	_shader.uploadUniform("u_fogDefaultFactor",	_renderBus.getFogDefaultFactor());
	_shader.uploadUniform("u_fogColor",			_renderBus.getFogColor());
	_shader.uploadUniform("u_fogEnabled",		_renderBus.isFogEnabled());

	// Texture uniforms
	_shader.uploadUniform("u_sampler_diffuseMap", 0);

	// Depth testing
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CLIP_DISTANCE1);
	glDepthFunc(GL_LEQUAL);
}

void BillboardEntityRenderer::unbind()
{
	glDisable(GL_CLIP_DISTANCE1);
	glDisable(GL_DEPTH_TEST);
	_shader.unbind();
}

void BillboardEntityRenderer::render(const BillboardEntity* entity)
{
	if (entity->isVisible())
	{
		// Sprite animation
		vec2 uvMultiplier = vec2(1.0f);
		vec2 uvAdder = vec2(0.0f);
		if (entity->hasSpriteAnimation())
		{
			uvMultiplier = vec2(1.0f / float(entity->getTotalSpriteColumns()), 1.0f / float(entity->getTotalSpriteRows()));
			uvAdder = vec2(float(entity->getSpriteColumnIndex()) * uvMultiplier.x, float(entity->getSpriteRowIndex()) * uvMultiplier.y);
		}

		// Text UV repeat fix
		if (entity->getTextContent() != "")
		{
			uvMultiplier = vec2(1.0f, 0.9f);
		}

		// Shader uniforms
		_shader.uploadUniform("u_modelMatrix", entity->getModelMatrix());
		_shader.uploadUniform("u_isAlphaObject", entity->isTransparent());
		_shader.uploadUniform("u_noTexture", entity->getDiffuseMap() == 0);
		_shader.uploadUniform("u_color", entity->getColor());
		_shader.uploadUniform("u_lightness", entity->getLightness());
		_shader.uploadUniform("u_uvAdder", uvAdder);
		_shader.uploadUniform("u_uvMultiplier", uvMultiplier);
		_shader.uploadUniform("u_maxY", entity->getMaxY());

		// Texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap());

		// Bind
		glBindVertexArray(entity->getOglBuffer()->getVAO());

		// Render
		if (entity->getOglBuffer()->isInstanced()) // Instanced
		{
			_shader.uploadUniform("u_isInstanced", true);
			glDrawArraysInstanced(GL_TRIANGLES, 0, entity->getOglBuffer()->getVertexCount(), entity->getOglBuffer()->getInstancedOffsetCount());
			_renderBus.increaseTriangleCount((entity->getOglBuffer()->getInstancedOffsetCount() * entity->getOglBuffer()->getVertexCount()) / 3);
		}
		else // Non-instanced
		{
			_shader.uploadUniform("u_isInstanced", false);
			glDrawArrays(GL_TRIANGLES, 0, entity->getOglBuffer()->getVertexCount());
			_renderBus.increaseTriangleCount(entity->getOglBuffer()->getVertexCount() / 3);
		}

		// Unbind
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
	}
}