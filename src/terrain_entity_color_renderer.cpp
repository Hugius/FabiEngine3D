#include "terrain_entity_color_renderer.hpp"
#include "configuration.hpp"
#include "tools.hpp"

using std::to_string;

void TerrainEntityColorRenderer::bind()
{
	_shader->bind();

	_shader->uploadUniform("u_viewMatrix", _renderBus->getViewMatrix());
	_shader->uploadUniform("u_projectionMatrix", _renderBus->getProjectionMatrix());
	_shader->uploadUniform("u_shadowMatrix", _renderBus->getShadowMatrix());
	_shader->uploadUniform("u_clippingPlane", _renderBus->getClippingPlane());
	_shader->uploadUniform("u_cameraPosition", _renderBus->getCameraPosition());
	_shader->uploadUniform("u_ambientLightingColor", _renderBus->getAmbientLightingColor());
	_shader->uploadUniform("u_ambientLightingIntensity", _renderBus->getAmbientLightingIntensity());
	_shader->uploadUniform("u_directionalLightingColor", _renderBus->getDirectionalLightingColor());
	_shader->uploadUniform("u_directionalLightPosition", _renderBus->getDirectionalLightingPosition());
	_shader->uploadUniform("u_directionalLightingIntensity", _renderBus->getDirectionalLightingIntensity());
	_shader->uploadUniform("u_fogMinDistance", _renderBus->getFogMinDistance());
	_shader->uploadUniform("u_fogMaxDistance", _renderBus->getFogMaxDistance());
	_shader->uploadUniform("u_fogThickness", _renderBus->getFogThickness());
	_shader->uploadUniform("u_fogColor", _renderBus->getFogColor());
	_shader->uploadUniform("u_isFogEnabled", _renderBus->isFogEnabled());
	_shader->uploadUniform("u_isAmbientLightingEnabled", _renderBus->isAmbientLightingEnabled());
	_shader->uploadUniform("u_isDirectionalLightingEnabled", _renderBus->isDirectionalLightingEnabled());
	_shader->uploadUniform("u_shadowSize", _renderBus->getShadowSize());
	_shader->uploadUniform("u_shadowCenter", _renderBus->getShadowCenterPosition());
	_shader->uploadUniform("u_shadowLightness", _renderBus->getShadowLightness());
	_shader->uploadUniform("u_isShadowsEnabled", _renderBus->isShadowsEnabled());
	_shader->uploadUniform("u_isShadowFrameRenderEnabled", _renderBus->isShadowFrameRenderingEnabled());
	_shader->uploadUniform("u_shadowMap", 0);
	_shader->uploadUniform("u_diffuseMap", 1);
	_shader->uploadUniform("u_normalMap", 2);
	_shader->uploadUniform("u_blendMap", 3);
	_shader->uploadUniform("u_redDiffuseMap", 4);
	_shader->uploadUniform("u_greenDiffuseMap", 5);
	_shader->uploadUniform("u_blueDiffuseMap", 6);
	_shader->uploadUniform("u_redNormalMap", 7);
	_shader->uploadUniform("u_greenNormalMap", 8);
	_shader->uploadUniform("u_blueNormalMap", 9);

	if(_renderBus->getShadowMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _renderBus->getShadowMap()->getId());
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void TerrainEntityColorRenderer::unbind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_DEPTH_TEST);

	_shader->unbind();
}

void TerrainEntityColorRenderer::processPointlightEntities(const unordered_map<string, shared_ptr<PointlightEntity>>& entities)
{
	vector<shared_ptr<PointlightEntity>> visibleEntities;
	for(const auto& [key, entity] : entities)
	{
		if(entity->isVisible())
		{
			visibleEntities.push_back(entity);
		}
	}

	for(size_t i = 0; i < visibleEntities.size(); i++)
	{
		_shader->uploadUniform("u_pointlightPositions[" + to_string(i) + "]", visibleEntities[i]->getPosition());
		_shader->uploadUniform("u_pointlightColors[" + to_string(i) + "]", visibleEntities[i]->getColor());
		_shader->uploadUniform("u_pointlightIntensities[" + to_string(i) + "]", visibleEntities[i]->getIntensity());
		_shader->uploadUniform("u_pointlightRadiuses[" + to_string(i) + "]", visibleEntities[i]->getRadius());
		_shader->uploadUniform("u_pointlightShapes[" + to_string(i) + "]", static_cast<int>(visibleEntities[i]->getShape()));
	}

	_shader->uploadUniform("u_pointlightCount", static_cast<int>(visibleEntities.size()));
}

void TerrainEntityColorRenderer::processSpotlightEntities(const unordered_map<string, shared_ptr<SpotlightEntity>>& entities)
{
	vector<shared_ptr<SpotlightEntity>> visibleEntities;
	for(const auto& [key, entity] : entities)
	{
		if(entity->isVisible())
		{
			visibleEntities.push_back(entity);
		}
	}

	for(size_t i = 0; i < visibleEntities.size(); i++)
	{
		_shader->uploadUniform("u_spotlightPositions[" + to_string(i) + "]", visibleEntities[i]->getPosition());
		_shader->uploadUniform("u_spotlightFrontVectors[" + to_string(i) + "]", visibleEntities[i]->getFrontVector());
		_shader->uploadUniform("u_spotlightColors[" + to_string(i) + "]", visibleEntities[i]->getColor());
		_shader->uploadUniform("u_spotlightIntensities[" + to_string(i) + "]", visibleEntities[i]->getIntensity());
		_shader->uploadUniform("u_spotlightAngles[" + to_string(i) + "]", cosf(Math::convertToRadians(visibleEntities[i]->getAngle())));
		_shader->uploadUniform("u_spotlightDistances[" + to_string(i) + "]", visibleEntities[i]->getDistance());
	}

	_shader->uploadUniform("u_spotlightCount", static_cast<int>(visibleEntities.size()));
}

void TerrainEntityColorRenderer::render(const shared_ptr<TerrainEntity> entity)
{
	if(entity->isVisible())
	{
		if(entity->isWireframed())
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}

		glEnable(GL_CULL_FACE);

		_shader->uploadUniform("u_isWireframed", (entity->isWireframed() || _renderBus->isWireframeRenderingEnabled()));
		_shader->uploadUniform("u_isSpecular", entity->isSpecular());
		_shader->uploadUniform("u_textureRepeat", entity->getTextureRepeat());
		_shader->uploadUniform("u_redTextureRepeat", entity->getRedTextureRepeat());
		_shader->uploadUniform("u_greenTextureRepeat", entity->getGreenTextureRepeat());
		_shader->uploadUniform("u_blueTextureRepeat", entity->getBlueTextureRepeat());
		_shader->uploadUniform("u_lightness", entity->getLightness());
		_shader->uploadUniform("u_specularShininess", entity->getSpecularShininess());
		_shader->uploadUniform("u_specularIntensity", entity->getSpecularIntensity());
		_shader->uploadUniform("u_hasDiffuseMap", entity->hasDiffuseMap());
		_shader->uploadUniform("u_hasNormalMap", entity->hasNormalMap());
		_shader->uploadUniform("u_hasBlendMap", entity->hasBlendMap());
		_shader->uploadUniform("u_hasRedDiffuseMap", entity->hasRedDiffuseMap());
		_shader->uploadUniform("u_hasGreenDiffuseMap", entity->hasGreenDiffuseMap());
		_shader->uploadUniform("u_hasBlueDiffuseMap", entity->hasBlueDiffuseMap());
		_shader->uploadUniform("u_hasRedNormalMap", entity->hasRedNormalMap());
		_shader->uploadUniform("u_hasGreenNormalMap", entity->hasGreenNormalMap());
		_shader->uploadUniform("u_hasBlueNormalMap", entity->hasBlueNormalMap());
		_shader->uploadUniform("u_wireframeColor", entity->getWireframeColor());

		if(entity->hasDiffuseMap())
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap()->getId());
		}
		if(entity->hasNormalMap())
		{
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, entity->getNormalMap()->getId());
		}
		if(entity->hasBlendMap())
		{
			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, entity->getBlendMap()->getId());
		}
		if(entity->hasRedDiffuseMap())
		{
			glActiveTexture(GL_TEXTURE4);
			glBindTexture(GL_TEXTURE_2D, entity->getRedDiffuseMap()->getId());
		}
		if(entity->hasGreenDiffuseMap())
		{
			glActiveTexture(GL_TEXTURE5);
			glBindTexture(GL_TEXTURE_2D, entity->getGreenDiffuseMap()->getId());
		}
		if(entity->hasBlueDiffuseMap())
		{
			glActiveTexture(GL_TEXTURE6);
			glBindTexture(GL_TEXTURE_2D, entity->getBlueDiffuseMap()->getId());
		}
		if(entity->hasRedNormalMap())
		{
			glActiveTexture(GL_TEXTURE7);
			glBindTexture(GL_TEXTURE_2D, entity->getRedNormalMap()->getId());
		}
		if(entity->hasGreenNormalMap())
		{
			glActiveTexture(GL_TEXTURE8);
			glBindTexture(GL_TEXTURE_2D, entity->getGreenNormalMap()->getId());
		}
		if(entity->hasBlueNormalMap())
		{
			glActiveTexture(GL_TEXTURE9);
			glBindTexture(GL_TEXTURE_2D, entity->getBlueNormalMap()->getId());
		}

		glBindVertexArray(entity->getMesh()->getVaoID());

		glDrawArrays(GL_TRIANGLES, 0, entity->getMesh()->getVertexCount());
		_renderBus->increaseTriangleCount(entity->getMesh()->getVertexCount() / 3);

		glBindVertexArray(0);

		if(entity->hasDiffuseMap())
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		if(entity->hasNormalMap())
		{
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		if(entity->hasBlendMap())
		{
			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		if(entity->hasRedDiffuseMap())
		{
			glActiveTexture(GL_TEXTURE4);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		if(entity->hasGreenDiffuseMap())
		{
			glActiveTexture(GL_TEXTURE5);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		if(entity->hasBlueDiffuseMap())
		{
			glActiveTexture(GL_TEXTURE6);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		if(entity->hasRedNormalMap())
		{
			glActiveTexture(GL_TEXTURE7);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		if(entity->hasGreenNormalMap())
		{
			glActiveTexture(GL_TEXTURE8);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		if(entity->hasBlueNormalMap())
		{
			glActiveTexture(GL_TEXTURE9);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		glDisable(GL_CULL_FACE);

		if(entity->isWireframed())
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}
}