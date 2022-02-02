#include "terrain_entity_color_renderer.hpp"
#include "configuration.hpp"
#include "tools.hpp"

using std::to_string;
using std::min;
using std::max;

void TerrainEntityColorRenderer::bind()
{
	_shader->bind();

	_shader->uploadUniform("u_cameraView", _renderStorage->getCameraView());
	_shader->uploadUniform("u_cameraProjection", _renderStorage->getCameraProjection());
	_shader->uploadUniform("u_shadowView", _renderStorage->getShadowView());
	_shader->uploadUniform("u_shadowProjection", _renderStorage->getShadowProjection());
	_shader->uploadUniform("u_cameraPosition", _renderStorage->getCameraPosition());
	_shader->uploadUniform("u_ambientLightingColor", _renderStorage->getAmbientLightingColor());
	_shader->uploadUniform("u_ambientLightingIntensity", _renderStorage->getAmbientLightingIntensity());
	_shader->uploadUniform("u_directionalLightingColor", _renderStorage->getDirectionalLightingColor());
	_shader->uploadUniform("u_directionalLightingPosition", _renderStorage->getDirectionalLightingPosition());
	_shader->uploadUniform("u_directionalLightingIntensity", _renderStorage->getDirectionalLightingIntensity());
	_shader->uploadUniform("u_minFogDistance", _renderStorage->getMinFogDistance());
	_shader->uploadUniform("u_maxFogDistance", _renderStorage->getMaxFogDistance());
	_shader->uploadUniform("u_fogThickness", _renderStorage->getFogThickness());
	_shader->uploadUniform("u_fogColor", _renderStorage->getFogColor());
	_shader->uploadUniform("u_isFogEnabled", _renderStorage->isFogEnabled());
	_shader->uploadUniform("u_isAmbientLightingEnabled", _renderStorage->isAmbientLightingEnabled());
	_shader->uploadUniform("u_isDirectionalLightingEnabled", _renderStorage->isDirectionalLightingEnabled());
	_shader->uploadUniform("u_shadowSize", _renderStorage->getShadowSize());
	_shader->uploadUniform("u_shadowLookat", _renderStorage->getShadowLookat());
	_shader->uploadUniform("u_shadowLightness", _renderStorage->getShadowLightness());
	_shader->uploadUniform("u_isShadowsEnabled", _renderStorage->isShadowsEnabled());
	_shader->uploadUniform("u_isShadowCircleEnabled", _renderStorage->isShadowCircleEnabled());
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

	if(_renderStorage->getShadowMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _renderStorage->getShadowMap()->getId());
	}

	glEnable(GL_CLIP_DISTANCE0);
	glEnable(GL_CLIP_DISTANCE1);
	glEnable(GL_CLIP_DISTANCE2);
	glEnable(GL_CLIP_DISTANCE3);
	glEnable(GL_CLIP_DISTANCE4);
	glEnable(GL_CLIP_DISTANCE5);
	glEnable(GL_DEPTH_TEST);
}

void TerrainEntityColorRenderer::unbind()
{
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CLIP_DISTANCE0);
	glDisable(GL_CLIP_DISTANCE1);
	glDisable(GL_CLIP_DISTANCE2);
	glDisable(GL_CLIP_DISTANCE3);
	glDisable(GL_CLIP_DISTANCE4);
	glDisable(GL_CLIP_DISTANCE5);

	if(_renderStorage->getShadowMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

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
		_shader->uploadUniform("u_spotlightFronts[" + to_string(i) + "]", visibleEntities[i]->getFront());
		_shader->uploadUniform("u_spotlightColors[" + to_string(i) + "]", visibleEntities[i]->getColor());
		_shader->uploadUniform("u_spotlightIntensities[" + to_string(i) + "]", visibleEntities[i]->getIntensity());
		_shader->uploadUniform("u_spotlightAngles[" + to_string(i) + "]", cosf(Math::convertToRadians(visibleEntities[i]->getAngle())));
		_shader->uploadUniform("u_spotlightDistances[" + to_string(i) + "]", visibleEntities[i]->getDistance());
	}

	_shader->uploadUniform("u_spotlightCount", static_cast<int>(visibleEntities.size()));
}

void TerrainEntityColorRenderer::render(const shared_ptr<TerrainEntity> entity)
{
	if(!entity->isVisible())
	{
		return;
	}

	glEnable(GL_CULL_FACE);

	if(entity->isWireframed())
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	_shader->uploadUniform("u_isWireframed", entity->isWireframed());
	_shader->uploadUniform("u_isSpecular", entity->isSpecular());
	_shader->uploadUniform("u_textureRepeat", entity->getTextureRepeat());
	_shader->uploadUniform("u_redTextureRepeat", entity->getRedTextureRepeat());
	_shader->uploadUniform("u_greenTextureRepeat", entity->getGreenTextureRepeat());
	_shader->uploadUniform("u_blueTextureRepeat", entity->getBlueTextureRepeat());
	_shader->uploadUniform("u_lightness", entity->getLightness());
	_shader->uploadUniform("u_specularShininess", entity->getSpecularShininess());
	_shader->uploadUniform("u_specularIntensity", entity->getSpecularIntensity());
	_shader->uploadUniform("u_hasDiffuseMap", (entity->getDiffuseMap() != nullptr));
	_shader->uploadUniform("u_hasNormalMap", (entity->getNormalMap() != nullptr));
	_shader->uploadUniform("u_hasBlendMap", (entity->getBlendMap() != nullptr));
	_shader->uploadUniform("u_hasRedDiffuseMap", (entity->getRedDiffuseMap() != nullptr));
	_shader->uploadUniform("u_hasGreenDiffuseMap", (entity->getGreenDiffuseMap() != nullptr));
	_shader->uploadUniform("u_hasBlueDiffuseMap", (entity->getBlueDiffuseMap() != nullptr));
	_shader->uploadUniform("u_hasRedNormalMap", (entity->getRedNormalMap() != nullptr));
	_shader->uploadUniform("u_hasGreenNormalMap", (entity->getGreenNormalMap() != nullptr));
	_shader->uploadUniform("u_hasBlueNormalMap", (entity->getBlueNormalMap() != nullptr));
	_shader->uploadUniform("u_wireframeColor", entity->getWireframeColor());
	_shader->uploadUniform("u_minX", _renderStorage->getMinPosition().x);
	_shader->uploadUniform("u_maxX", _renderStorage->getMaxPosition().x);
	_shader->uploadUniform("u_minY", _renderStorage->getMinPosition().y);
	_shader->uploadUniform("u_maxY", _renderStorage->getMaxPosition().y);
	_shader->uploadUniform("u_minZ", _renderStorage->getMinPosition().z);
	_shader->uploadUniform("u_maxZ", _renderStorage->getMaxPosition().z);

	if(entity->getDiffuseMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap()->getId());
	}
	if(entity->getNormalMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, entity->getNormalMap()->getId());
	}
	if(entity->getBlendMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, entity->getBlendMap()->getId());
	}
	if(entity->getRedDiffuseMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, entity->getRedDiffuseMap()->getId());
	}
	if(entity->getGreenDiffuseMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE5);
		glBindTexture(GL_TEXTURE_2D, entity->getGreenDiffuseMap()->getId());
	}
	if(entity->getBlueDiffuseMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE6);
		glBindTexture(GL_TEXTURE_2D, entity->getBlueDiffuseMap()->getId());
	}
	if(entity->getRedNormalMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE7);
		glBindTexture(GL_TEXTURE_2D, entity->getRedNormalMap()->getId());
	}
	if(entity->getGreenNormalMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE8);
		glBindTexture(GL_TEXTURE_2D, entity->getGreenNormalMap()->getId());
	}
	if(entity->getBlueNormalMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE9);
		glBindTexture(GL_TEXTURE_2D, entity->getBlueNormalMap()->getId());
	}

	glBindVertexArray(entity->getMesh()->getVaoId());

	glDrawArrays(GL_TRIANGLES, 0, entity->getMesh()->getVertexCount());
	_renderStorage->increaseTriangleCount(entity->getMesh()->getVertexCount() / 3);

	glBindVertexArray(0);

	if(entity->getDiffuseMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if(entity->getNormalMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if(entity->getBlendMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if(entity->getRedDiffuseMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if(entity->getGreenDiffuseMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE5);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if(entity->getBlueDiffuseMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE6);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if(entity->getRedNormalMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE7);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if(entity->getGreenNormalMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE8);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if(entity->getBlueNormalMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE9);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	if(entity->isWireframed())
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glDisable(GL_CULL_FACE);
}