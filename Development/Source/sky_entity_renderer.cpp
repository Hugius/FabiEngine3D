#include "sky_entity_renderer.hpp"

void SkyEntityRenderer::bind()
{
	// Bind shader
	_shader.bind();

	// Vertex shader uniforms
	_shader.uploadUniform("u_viewMatrix", Matrix44(Matrix33(_renderBus.getViewMatrix())));
	_shader.uploadUniform("u_projectionMatrix", _renderBus.getProjectionMatrix());
	_shader.uploadUniform("u_rotationMatrix", _renderBus.getSkyRotationMatrix());

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

		// Uniforms
		_shader.uploadUniform("u_mixValue", _renderBus.getSkyMixValue());
		_shader.uploadUniform("u_mainLightness", mainEntity->getLightness());		
		_shader.uploadUniform("u_mainColor", mainEntity->getColor());
		if (secondEnabled)
		{
			_shader.uploadUniform("u_mixLightness", mixEntity->getLightness());
			_shader.uploadUniform("u_mixColor", mixEntity->getColor());
		}
		
		// Textures
		_shader.uploadUniform("u_sampler_mainCubeMap", 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, mainEntity->getCubeMap());
		if (secondEnabled)
		{
			_shader.uploadUniform("u_sampler_mixCubeMap", 1);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_CUBE_MAP, mixEntity->getCubeMap());
		}

		// Bind
		glBindVertexArray(mainEntity->getOglBuffer()->getVAO());

		// Render
		glDrawArrays(GL_TRIANGLES, 0, mainEntity->getOglBuffer()->getVertexCount());
		_renderBus.increaseTriangleCount(mainEntity->getOglBuffer()->getVertexCount() / 3);

		// Unbind
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		glBindVertexArray(0);
	}
}