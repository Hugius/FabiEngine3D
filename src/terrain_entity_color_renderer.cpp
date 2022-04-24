#include "terrain_entity_color_renderer.hpp"
#include "configuration.hpp"
#include "tools.hpp"

using std::to_string;
using std::min;
using std::max;

void TerrainEntityColorRenderer::bind()
{
	_shaderBuffer->bind();

	_shaderBuffer->uploadUniform("u_cameraView", _camera->getView());
	_shaderBuffer->uploadUniform("u_cameraProjection", _camera->getProjection());
	_shaderBuffer->uploadUniform("u_shadowView", _renderStorage->getShadowView());
	_shaderBuffer->uploadUniform("u_shadowProjection", _renderStorage->getShadowProjection());
	_shaderBuffer->uploadUniform("u_cameraPosition", _camera->getPosition());
	_shaderBuffer->uploadUniform("u_ambientLightingColor", _renderStorage->getAmbientLightingColor());
	_shaderBuffer->uploadUniform("u_ambientLightingIntensity", _renderStorage->getAmbientLightingIntensity());
	_shaderBuffer->uploadUniform("u_directionalLightingColor", _renderStorage->getDirectionalLightingColor());
	_shaderBuffer->uploadUniform("u_directionalLightingPosition", _renderStorage->getDirectionalLightingPosition());
	_shaderBuffer->uploadUniform("u_directionalLightingIntensity", _renderStorage->getDirectionalLightingIntensity());
	_shaderBuffer->uploadUniform("u_minFogDistance", _renderStorage->getMinFogDistance());
	_shaderBuffer->uploadUniform("u_maxFogDistance", _renderStorage->getMaxFogDistance());
	_shaderBuffer->uploadUniform("u_fogThickness", _renderStorage->getFogThickness());
	_shaderBuffer->uploadUniform("u_fogColor", _renderStorage->getFogColor());
	_shaderBuffer->uploadUniform("u_isFogEnabled", _renderStorage->isFogEnabled());
	_shaderBuffer->uploadUniform("u_isAmbientLightingEnabled", _renderStorage->isAmbientLightingEnabled());
	_shaderBuffer->uploadUniform("u_isDirectionalLightingEnabled", _renderStorage->isDirectionalLightingEnabled());
	_shaderBuffer->uploadUniform("u_shadowSize", _renderStorage->getShadowSize());
	_shaderBuffer->uploadUniform("u_shadowLookat", _renderStorage->getShadowLookat());
	_shaderBuffer->uploadUniform("u_shadowLightness", _renderStorage->getShadowLightness());
	_shaderBuffer->uploadUniform("u_isShadowsEnabled", _renderStorage->isShadowsEnabled());
	_shaderBuffer->uploadUniform("u_isShadowCircleEnabled", _renderStorage->isShadowCircleEnabled());
	_shaderBuffer->uploadUniform("u_shadowMap", 0);
	_shaderBuffer->uploadUniform("u_diffuseMap", 1);
	_shaderBuffer->uploadUniform("u_normalMap", 2);
	_shaderBuffer->uploadUniform("u_blendMap", 3);
	_shaderBuffer->uploadUniform("u_redDiffuseMap", 4);
	_shaderBuffer->uploadUniform("u_greenDiffuseMap", 5);
	_shaderBuffer->uploadUniform("u_blueDiffuseMap", 6);
	_shaderBuffer->uploadUniform("u_redNormalMap", 7);
	_shaderBuffer->uploadUniform("u_greenNormalMap", 8);
	_shaderBuffer->uploadUniform("u_blueNormalMap", 9);

	if(_renderStorage->getShadowTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _renderStorage->getShadowTextureBuffer()->getTboId());
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

	if(_renderStorage->getShadowTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	_shaderBuffer->unbind();
}

void TerrainEntityColorRenderer::processPointlightEntities(const unordered_map<string, shared_ptr<PointlightEntity>> & entities)
{
	vector<shared_ptr<PointlightEntity>> visibleEntities;
	for(const auto & [entityId, entity] : entities)
	{
		if(entity->isVisible())
		{
			visibleEntities.push_back(entity);
		}
	}

	for(unsigned int index = 0; index < static_cast<unsigned int>(visibleEntities.size()); index++)
	{
		_shaderBuffer->uploadUniform("u_pointlightPositions[" + to_string(index) + "]", visibleEntities[index]->getPosition());
		_shaderBuffer->uploadUniform("u_pointlightColors[" + to_string(index) + "]", visibleEntities[index]->getColor());
		_shaderBuffer->uploadUniform("u_pointlightIntensities[" + to_string(index) + "]", visibleEntities[index]->getIntensity());
		_shaderBuffer->uploadUniform("u_pointlightRadiuses[" + to_string(index) + "]", visibleEntities[index]->getRadius());
		_shaderBuffer->uploadUniform("u_pointlightShapes[" + to_string(index) + "]", static_cast<int>(visibleEntities[index]->getShape()));
	}

	_shaderBuffer->uploadUniform("u_pointlightCount", static_cast<int>(visibleEntities.size()));
}

void TerrainEntityColorRenderer::processSpotlightEntities(const unordered_map<string, shared_ptr<SpotlightEntity>> & entities)
{
	vector<shared_ptr<SpotlightEntity>> visibleEntities;
	for(const auto & [entityId, entity] : entities)
	{
		if(entity->isVisible())
		{
			visibleEntities.push_back(entity);
		}
	}

	for(unsigned int index = 0; index < static_cast<unsigned int>(visibleEntities.size()); index++)
	{
		_shaderBuffer->uploadUniform("u_spotlightPositions[" + to_string(index) + "]", visibleEntities[index]->getPosition());
		_shaderBuffer->uploadUniform("u_spotlightFronts[" + to_string(index) + "]", visibleEntities[index]->getFront());
		_shaderBuffer->uploadUniform("u_spotlightColors[" + to_string(index) + "]", visibleEntities[index]->getColor());
		_shaderBuffer->uploadUniform("u_spotlightIntensities[" + to_string(index) + "]", visibleEntities[index]->getIntensity());
		_shaderBuffer->uploadUniform("u_spotlightAngles[" + to_string(index) + "]", cosf(Mathematics::convertToRadians(visibleEntities[index]->getAngle())));
		_shaderBuffer->uploadUniform("u_spotlightDistances[" + to_string(index) + "]", visibleEntities[index]->getDistance());
	}

	_shaderBuffer->uploadUniform("u_spotlightCount", static_cast<int>(visibleEntities.size()));
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

	_shaderBuffer->uploadUniform("u_isWireframed", entity->isWireframed());
	_shaderBuffer->uploadUniform("u_isSpecular", entity->isSpecular());
	_shaderBuffer->uploadUniform("u_textureRepeat", static_cast<int>(entity->getTextureRepeat()));
	_shaderBuffer->uploadUniform("u_redTextureRepeat", static_cast<int>(entity->getRedTextureRepeat()));
	_shaderBuffer->uploadUniform("u_greenTextureRepeat", static_cast<int>(entity->getGreenTextureRepeat()));
	_shaderBuffer->uploadUniform("u_blueTextureRepeat", static_cast<int>(entity->getBlueTextureRepeat()));
	_shaderBuffer->uploadUniform("u_lightness", entity->getLightness());
	_shaderBuffer->uploadUniform("u_specularShininess", entity->getSpecularShininess());
	_shaderBuffer->uploadUniform("u_specularIntensity", entity->getSpecularIntensity());
	_shaderBuffer->uploadUniform("u_hasDiffuseMap", (entity->getDiffuseTextureBuffer() != nullptr));
	_shaderBuffer->uploadUniform("u_hasNormalMap", (entity->getNormalTextureBuffer() != nullptr));
	_shaderBuffer->uploadUniform("u_hasBlendMap", (entity->getBlendTextureBuffer() != nullptr));
	_shaderBuffer->uploadUniform("u_hasRedDiffuseMap", (entity->getRedDiffuseTextureBuffer() != nullptr));
	_shaderBuffer->uploadUniform("u_hasGreenDiffuseMap", (entity->getGreenDiffuseTextureBuffer() != nullptr));
	_shaderBuffer->uploadUniform("u_hasBlueDiffuseMap", (entity->getBlueDiffuseTextureBuffer() != nullptr));
	_shaderBuffer->uploadUniform("u_hasRedNormalMap", (entity->getRedNormalTextureBuffer() != nullptr));
	_shaderBuffer->uploadUniform("u_hasGreenNormalMap", (entity->getGreenNormalTextureBuffer() != nullptr));
	_shaderBuffer->uploadUniform("u_hasBlueNormalMap", (entity->getBlueNormalTextureBuffer() != nullptr));
	_shaderBuffer->uploadUniform("u_wireframeColor", entity->getWireframeColor());
	_shaderBuffer->uploadUniform("u_minX", max(_renderStorage->getMinClipPosition().x, entity->getMinClipPosition().x));
	_shaderBuffer->uploadUniform("u_minY", max(_renderStorage->getMinClipPosition().y, entity->getMinClipPosition().y));
	_shaderBuffer->uploadUniform("u_minZ", max(_renderStorage->getMinClipPosition().z, entity->getMinClipPosition().z));
	_shaderBuffer->uploadUniform("u_maxX", min(_renderStorage->getMaxClipPosition().x, entity->getMaxClipPosition().x));
	_shaderBuffer->uploadUniform("u_maxY", min(_renderStorage->getMaxClipPosition().y, entity->getMaxClipPosition().y));
	_shaderBuffer->uploadUniform("u_maxZ", min(_renderStorage->getMaxClipPosition().z, entity->getMaxClipPosition().z));

	if(entity->getDiffuseTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, entity->getDiffuseTextureBuffer()->getTboId());
	}
	if(entity->getNormalTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, entity->getNormalTextureBuffer()->getTboId());
	}
	if(entity->getBlendTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, entity->getBlendTextureBuffer()->getTboId());
	}
	if(entity->getRedDiffuseTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, entity->getRedDiffuseTextureBuffer()->getTboId());
	}
	if(entity->getGreenDiffuseTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE5);
		glBindTexture(GL_TEXTURE_2D, entity->getGreenDiffuseTextureBuffer()->getTboId());
	}
	if(entity->getBlueDiffuseTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE6);
		glBindTexture(GL_TEXTURE_2D, entity->getBlueDiffuseTextureBuffer()->getTboId());
	}
	if(entity->getRedNormalTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE7);
		glBindTexture(GL_TEXTURE_2D, entity->getRedNormalTextureBuffer()->getTboId());
	}
	if(entity->getGreenNormalTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE8);
		glBindTexture(GL_TEXTURE_2D, entity->getGreenNormalTextureBuffer()->getTboId());
	}
	if(entity->getBlueNormalTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE9);
		glBindTexture(GL_TEXTURE_2D, entity->getBlueNormalTextureBuffer()->getTboId());
	}

	glBindVertexArray(entity->getVertexBuffer()->getVaoId());

	glDrawArrays(GL_TRIANGLES, 0, entity->getVertexBuffer()->getVertexCount());
	_renderStorage->increaseTriangleCount(entity->getVertexBuffer()->getVertexCount() / 3);

	glBindVertexArray(0);

	if(entity->getDiffuseTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if(entity->getNormalTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if(entity->getBlendTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if(entity->getRedDiffuseTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if(entity->getGreenDiffuseTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE5);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if(entity->getBlueDiffuseTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE6);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if(entity->getRedNormalTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE7);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if(entity->getGreenNormalTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE8);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if(entity->getBlueNormalTextureBuffer() != nullptr)
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