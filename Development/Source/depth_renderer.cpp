#include "depth_renderer.hpp"
#include "render_bus.hpp"
#include "configuration.hpp"

void DepthRenderer::bind()
{
	// Bind shader
	_shader.bind();

	// Vertex shader uniforms
	_shader.uploadUniform("u_projMatrix", _renderBus.getProjectionMatrix());

	// Texture uniforms
	_shader.uploadUniform("u_sampler_diffuseMap", 0);

	// Depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CLIP_DISTANCE1);
}

void DepthRenderer::unbind()
{
	glDisable(GL_CLIP_DISTANCE1);
	glDisable(GL_DEPTH_TEST);

	_shader.unbind();
}

void DepthRenderer::render(const shared_ptr<TerrainEntity> entity)
{
	if (entity->isVisible())
	{
		// Faceculling
		glEnable(GL_CULL_FACE);

		// Shader uniforms
		_shader.uploadUniform("u_viewMatrix", _renderBus.getViewMatrix());
		_shader.uploadUniform("u_modelMatrix", Matrix44(1.0f));
		_shader.uploadUniform("u_isAlphaObject", false);
		_shader.uploadUniform("u_isInstanced", false);
		_shader.uploadUniform("u_isBillboard", false);
		_shader.uploadUniform("u_maxY", (std::numeric_limits<float>::max)());

		// Bind
		glBindVertexArray(entity->getOglBuffer()->getVAO());

		// Render
		glDrawArrays(GL_TRIANGLES, 0, entity->getOglBuffer()->getVertexCount());

		// Unbind
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);

		// Face culling
		glDisable(GL_CULL_FACE);
	}
}

void DepthRenderer::render(const shared_ptr<WaterEntity> entity)
{
	if (entity->isVisible())
	{
		// Shader uniforms
		Matrix44 modelMatrix = Matrix44::createTranslation(entity->getPosition().x, entity->getPosition().y, entity->getPosition().z);
		_shader.uploadUniform("u_modelMatrix", modelMatrix);
		_shader.uploadUniform("u_isAlphaObject", false);
		_shader.uploadUniform("u_isInstanced", false);

		// Bind
		glBindVertexArray(entity->getSimplifiedOglBuffer()->getVAO());

		// Render
		glDrawArrays(GL_TRIANGLES, 0, entity->getSimplifiedOglBuffer()->getVertexCount());

		// Unbind
		glBindVertexArray(0);
	}
}

void DepthRenderer::render(const shared_ptr<GameEntity> entity)
{
	if (entity->isVisible())
	{
		// Faceculling
		if (entity->isFaceCulled())
		{
			glEnable(GL_CULL_FACE);
		}

		// Shader uniforms
		_shader.uploadUniform("u_isAlphaObject", entity->isTransparent());
		_shader.uploadUniform("u_currentY", entity->getTranslation().y);
		_shader.uploadUniform("u_maxY", entity->getMaxY());
		_shader.uploadUniform("u_isBillboard", false);

		// Check if entity is static to the camera view
		if (entity->isCameraStatic())
		{
			_shader.uploadUniform("u_viewMatrix", Matrix44(Matrix33(_renderBus.getViewMatrix())));
		}
		else
		{
			_shader.uploadUniform("u_viewMatrix", _renderBus.getViewMatrix());
		}

		// Bind & render
		unsigned int index = 0;
		for (auto& buffer : entity->getOglBuffers())
		{
			// Model matrix
			_shader.uploadUniform("u_modelMatrix", entity->getModelMatrix(index));

			// Diffuse map
			if (entity->hasDiffuseMap())
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap(index));
			}

			// VAO
			glBindVertexArray(buffer->getVAO());

			// Render
			if (buffer->isInstanced())
			{
				_shader.uploadUniform("u_isInstanced", true);
				glDrawArraysInstanced(GL_TRIANGLES, 0, buffer->getVertexCount(), buffer->getInstancedOffsetCount());
			}
			else
			{
				_shader.uploadUniform("u_isInstanced", false);
				glDrawArrays(GL_TRIANGLES, 0, buffer->getVertexCount());
			}

			index++;
		}

		// Unbind
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);

		// Face culling
		if (entity->isFaceCulled())
		{
			glDisable(GL_CULL_FACE);
		}
	}
}

void DepthRenderer::render(const shared_ptr<BillboardEntity> entity)
{
	if (entity->isVisible())
	{
		// Sprite animation
		Vec2 uvMultiplier = Vec2(1.0f);
		Vec2 uvAdder = Vec2(0.0f);
		if (entity->hasSpriteAnimation())
		{
			uvMultiplier = Vec2(1.0f / float(entity->getTotalSpriteColumns()), 1.0f / float(entity->getTotalSpriteRows()));
			uvAdder = Vec2(float(entity->getSpriteColumnIndex()) * uvMultiplier.x, float(entity->getSpriteRowIndex()) * uvMultiplier.y);
		}

		// Text UV repeat fix
		if (entity->getTextContent() != "")
		{
			uvMultiplier = Vec2(1.0f, 0.9f);
		}

		// Shader uniforms
		_shader.uploadUniform("u_modelMatrix", entity->getModelMatrix());
		_shader.uploadUniform("u_isAlphaObject", entity->isTransparent());
		_shader.uploadUniform("u_currentY", entity->getTranslation().y);
		_shader.uploadUniform("u_maxY", entity->getMaxY());
		_shader.uploadUniform("u_uvAdder", uvAdder);
		_shader.uploadUniform("u_uvMultiplier", uvMultiplier);
		_shader.uploadUniform("u_isBillboard", true);
		_shader.uploadUniform("u_isInstanced", false);

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

void DepthRenderer::render(const shared_ptr<AabbEntity> entity)
{
	if (entity->isVisible())
	{
		// Shader uniforms
		_shader.uploadUniform("u_modelMatrix", entity->getModelMatrix());

		// VAO
		glBindVertexArray(entity->getOglBuffer()->getVAO());

		// Render
		glDrawArrays(GL_LINE_STRIP, 0, entity->getOglBuffer()->getVertexCount());

		// Unbind
		glBindVertexArray(0);
	}
}