#include "sky_entity_renderer.hpp"

void SkyEntityRenderer::bind()
{
	// Bind shader
	_shader.bind();

	// Shader uniforms
	_shader.uploadUniform("u_viewMatrix", Matrix44(Matrix33(_renderBus.getViewMatrix())));
	_shader.uploadUniform("u_projectionMatrix", _renderBus.getProjectionMatrix());
	_shader.uploadUniform("u_rotationMatrix", _renderBus.getSkyRotationMatrix());

	// Texture uniforms
	_shader.uploadUniform("u_sampler_mainCubeMap", 0);
	_shader.uploadUniform("u_sampler_mixCubeMap", 1);
	
	// Depth testing
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_CLAMP_NV);
	glDepthFunc(GL_LEQUAL);
}

void SkyEntityRenderer::unbind()
{
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_DEPTH_CLAMP_NV);
	_shader.unbind();
}

void SkyEntityRenderer::render(const shared_ptr<SkyEntity> mainEntity, const shared_ptr<SkyEntity> mixEntity)
{
	if (mainEntity->isVisible())
	{
		// Check if a second skybox should be mixed with the main skybox
		bool secondEnabled = ((mixEntity != nullptr) && mixEntity->isVisible());

		// Shader uniforms
		_shader.uploadUniform("u_mixValue", _renderBus.getSkyMixValue());
		_shader.uploadUniform("u_mainLightness", mainEntity->getLightness());		
		_shader.uploadUniform("u_mainColor", mainEntity->getColor());
		if (secondEnabled)
		{
			_shader.uploadUniform("u_mixLightness", mixEntity->getLightness());
			_shader.uploadUniform("u_mixColor", mixEntity->getColor());
		}
		
		// Bind textures
		if (mainEntity->hasCubeMap())
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, mainEntity->getCubeMap());
		}
		if (secondEnabled && mixEntity->hasCubeMap())
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_CUBE_MAP, mixEntity->getCubeMap());
		}

		// Check if entity has a render buffer
		if (!mainEntity->getRenderBuffers().empty())
		{
			// Bind buffer
			glBindVertexArray(mainEntity->getRenderBuffer()->getVAO());

			// Render
			if (!mainEntity->getRenderBuffers().empty())
			{
				glDrawArrays(GL_TRIANGLES, 0, mainEntity->getRenderBuffer()->getVertexCount());
				_renderBus.increaseTriangleCount(mainEntity->getRenderBuffer()->getVertexCount() / 3);
			}

			// Unbind buffer
			glBindVertexArray(0);
		}

		// Unbind textures
		if (mainEntity->hasCubeMap())
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		}
		if (secondEnabled && mixEntity->hasCubeMap())
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		}
		glActiveTexture(GL_TEXTURE0);
	}
}