#include "game_entity_renderer.hpp"
#include "configuration.hpp"
#include "tools.hpp"

using std::to_string;

void GameEntityRenderer::bind()
{
	// Define clipping plane for scene reflections
	Vec4 clippingPlane = Vec4(0.0f, 1.0f, 0.0f, -(_renderBus.getSceneReflectionHeight() + _renderBus.getSceneReflectionOffset()));

	// Bind shader
	_shader.bind();

	// Vertex shader uniforms
	_shader.uploadUniform("u_projMatrix",        _renderBus.getProjectionMatrix());
	_shader.uploadUniform("u_skyRotationMatrix", _renderBus.getSkyRotationMatrix());
	_shader.uploadUniform("u_shadowMatrix",      _renderBus.getShadowMatrix());
	_shader.uploadUniform("u_clippingPlane",	 clippingPlane);
	
	// Fragment shader uniforms
	_shader.uploadUniform("u_cameraPosition",			   _renderBus.getCameraPosition());
	_shader.uploadUniform("u_cameraFront",				   _renderBus.getCameraFront());
	_shader.uploadUniform("u_ambientLightColor",		   _renderBus.getAmbientLightColor());
	_shader.uploadUniform("u_ambientLightIntensity",	   _renderBus.getAmbientLightIntensity());
	_shader.uploadUniform("u_directionalLightColor",	   _renderBus.getDirectionalLightColor());
	_shader.uploadUniform("u_directionalLightPosition",	   _renderBus.getDirectionalLightPosition());
	_shader.uploadUniform("u_directionalLightIntensity",   _renderBus.getDirectionalLightIntensity());
	_shader.uploadUniform("u_spotLightColor",			   _renderBus.getSpotLightColor());
	_shader.uploadUniform("u_spotLightIntensity",	       _renderBus.getSpotLightIntensity());
	_shader.uploadUniform("u_maxSpotLightDistance",		   _renderBus.getMaxSpotLightDistance());
	_shader.uploadUniform("u_maxSpotlightAngle",		   cosf(Tools::getInst().degreeToRadians(_renderBus.getMaxSpotLightAngle())));
	_shader.uploadUniform("u_fogMinDistance",			   _renderBus.getFogMinDistance());
	_shader.uploadUniform("u_fogMaxDistance",			   _renderBus.getFogMaxDistance());
	_shader.uploadUniform("u_fogDefaultFactor",			   _renderBus.getFogDefaultFactor());
	_shader.uploadUniform("u_fogColor",					   _renderBus.getFogColor());
	_shader.uploadUniform("u_fogEnabled",				   _renderBus.isFogEnabled());
	_shader.uploadUniform("u_ambientLightEnabled",		   _renderBus.isAmbientLightingEnabled());
	_shader.uploadUniform("u_directionalLightEnabled",	   _renderBus.isDirectionalLightingEnabled());
	_shader.uploadUniform("u_spotLightEnabled",		       _renderBus.isSpotLightingEnabled());
	_shader.uploadUniform("u_specularLightEnabled",	       _renderBus.isSpecularLightingEnabled());
	_shader.uploadUniform("u_pointLightEnabled",		   _renderBus.isPointLightingEnabled());
	_shader.uploadUniform("u_lightMappingEnabled",		   _renderBus.isLightMappingEnabled());
	_shader.uploadUniform("u_normalMappingEnabled",		   _renderBus.isNormalMappingEnabled());
	_shader.uploadUniform("u_skyReflectionsEnabled",	   _renderBus.isSkyReflectionsEnabled());
	_shader.uploadUniform("u_sceneReflectionsEnabled",	   _renderBus.isSceneReflectionsEnabled());
	_shader.uploadUniform("u_shadowAreaSize",			   _renderBus.getShadowAreaSize());
	_shader.uploadUniform("u_shadowAreaCenter",			   _renderBus.getShadowAreaCenter());
	_shader.uploadUniform("u_shadowsEnabled",			   _renderBus.isShadowsEnabled());
	_shader.uploadUniform("u_shadowFrameRenderingEnabled", _renderBus.isShadowFrameRenderingEnabled());
	_shader.uploadUniform("u_skyReflectionFactor",		   _renderBus.getSkyReflectionFactor());
	_shader.uploadUniform("u_sceneReflectionFactor",	   _renderBus.getSceneReflectionFactor());
	_shader.uploadUniform("u_shadowMapSize",			   _renderBus.getShadowMapSize());
	
	// Texture uniforms
	_shader.uploadUniform("u_sampler_diffuseMap", 0);
	_shader.uploadUniform("u_sampler_lightMap", 1);
	_shader.uploadUniform("u_sampler_normalMap", 2);
	_shader.uploadUniform("u_sampler_skyReflectionMap", 3);
	_shader.uploadUniform("u_sampler_sceneReflectionMap", 4);
	_shader.uploadUniform("u_sampler_shadowMap", 5);
	_shader.uploadUniform("u_sampler_skyMap", 6);

	// Depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CLIP_DISTANCE1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Texture binding
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, _renderBus.getSceneReflectionMap());
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, _renderBus.getShadowMap());
	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _renderBus.getSkyReflectionCubeMap());
}

void GameEntityRenderer::unbind()
{
	glDisable(GL_BLEND);
	glDisable(GL_CLIP_DISTANCE1);
	glDisable(GL_DEPTH_TEST);
	_shader.unbind();
}

void GameEntityRenderer::renderLightEntities(const vector<shared_ptr<LightEntity>>& entities)
{
	_shader.uploadUniform("u_pointLightCount", static_cast<int>(entities.size()));

	// Render all lights
	for (size_t i = 0; i < entities.size(); i++)
	{
		if (entities[i]->isVisible())
		{
			_shader.uploadUniform("u_pointLightPositions[" + to_string(i) + "]", entities[i]->getPosition());
			_shader.uploadUniform("u_pointLightColors[" + to_string(i) + "]", entities[i]->getColor());
			_shader.uploadUniform("u_pointLightIntensities[" + to_string(i) + "]", entities[i]->getIntensity());
			_shader.uploadUniform("u_pointLightDistanceFactors[" + to_string(i) + "]", entities[i]->getDistanceFactor());
		}
		else
		{
			_shader.uploadUniform("u_pointLightPositions[" + to_string(i) + "]", Vec3(0.0f));
			_shader.uploadUniform("u_pointLightColors[" + to_string(i) + "]", Vec3(0.0f));
			_shader.uploadUniform("u_pointLightIntensities[" + to_string(i) + "]", 0.0f);
			_shader.uploadUniform("u_pointLightDistanceFactors[" + to_string(i) + "]", 0.0f);
		}
	}
}

void GameEntityRenderer::render(const shared_ptr<GameEntity> entity)
{
	if (entity->isVisible())
	{
		// Faceculling
		if (entity->isFaceCulled())
		{
			glEnable(GL_CULL_FACE);
		}

		// Shader uniforms
		auto normalModelMatrix = entity->getModelMatrix();
		normalModelMatrix.transpose();
		normalModelMatrix.invert();
		_shader.uploadUniform("u_normalModelMatrix", Matrix33(normalModelMatrix));
		_shader.uploadUniform("u_modelMatrix", entity->getModelMatrix());
		_shader.uploadUniform("u_color", entity->getColor());
		_shader.uploadUniform("u_specularLightFactor", entity->getSpecularFactor());
		_shader.uploadUniform("u_specularLightIntensity", entity->getSpecularIntensity());
		_shader.uploadUniform("u_isTransparent", entity->isTransparent());
		_shader.uploadUniform("u_isLightMapped", entity->isLightMapped());
		_shader.uploadUniform("u_isNormalMapped", entity->isNormalMapped());
		_shader.uploadUniform("u_isSkyReflective", entity->isSkyReflective());
		_shader.uploadUniform("u_isSceneReflective", entity->isSceneReflective());
		_shader.uploadUniform("u_isSpecularLighted", entity->isSpecularLighted());
		_shader.uploadUniform("u_lightness", entity->getLightness());
		_shader.uploadUniform("u_maxY", entity->getMaxY());
		_shader.uploadUniform("u_customAlpha", entity->getAlpha());
		_shader.uploadUniform("u_isShadowed", entity->isShadowed());
		_shader.uploadUniform("u_uvRepeat", entity->getUvRepeat());
		_shader.uploadUniform("u_hasDiffuseMap", entity->hasDiffuseMap());
		
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
		int index = 0;
		for (auto& buffer : entity->getOglBuffers())
		{
			// Diffuse map
			if (entity->hasDiffuseMap())
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap(index));
			}

			// Light map
			if (entity->hasLightMap())
			{
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, entity->getLightMap(index));
			}

			// Normal map
			if (entity->hasNormalMap())
			{
				glActiveTexture(GL_TEXTURE2);
				glBindTexture(GL_TEXTURE_2D, entity->getNormalMap(index));
			}

			// Reflection map for sky reflections
			if (entity->hasReflectionMap())
			{
				glActiveTexture(GL_TEXTURE3);
				glBindTexture(GL_TEXTURE_2D, entity->getReflectionMap(index));
			}

			// Bind
			glBindVertexArray(buffer->getVAO());

			// Render
			if (buffer->isInstanced())
			{
				_shader.uploadUniform("u_isInstanced", true);
				glDrawArraysInstanced(GL_TRIANGLES, 0, buffer->getVertexCount(), buffer->getInstancedOffsetCount());
				_renderBus.increaseTriangleCount((buffer->getInstancedOffsetCount() * buffer->getVertexCount()) / 3);
			}
			else
			{
				_shader.uploadUniform("u_isInstanced", false);
				glDrawArrays(GL_TRIANGLES, 0, buffer->getVertexCount());
				_renderBus.increaseTriangleCount(buffer->getVertexCount() / 3);
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