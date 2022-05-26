#include "terrain_color_renderer.hpp"
#include "configuration.hpp"
#include "tools.hpp"

using std::to_string;

void TerrainColorRenderer::bind()
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
	_shaderBuffer->uploadUniform("u_shadowBias", _renderStorage->getShadowBias());
	_shaderBuffer->uploadUniform("u_shadowPcfCount", _renderStorage->getShadowPcfCount());
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

void TerrainColorRenderer::unbind()
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

void TerrainColorRenderer::processPointlights(const unordered_map<string, shared_ptr<Pointlight>> & pointlights)
{
	vector<shared_ptr<Pointlight>> visiblePointlights = {};

	for(const auto & [pointlightId, pointlight] : pointlights)
	{
		if(pointlight->isVisible())
		{
			visiblePointlights.push_back(pointlight);
		}
	}

	for(int index = 0; index < static_cast<int>(visiblePointlights.size()); index++)
	{
		_shaderBuffer->uploadUniform("u_pointlightPositions[" + to_string(index) + "]", visiblePointlights[index]->getPosition());
		_shaderBuffer->uploadUniform("u_pointlightColors[" + to_string(index) + "]", visiblePointlights[index]->getColor());
		_shaderBuffer->uploadUniform("u_pointlightIntensities[" + to_string(index) + "]", visiblePointlights[index]->getIntensity());
		_shaderBuffer->uploadUniform("u_pointlightRadiuses[" + to_string(index) + "]", visiblePointlights[index]->getRadius());
		_shaderBuffer->uploadUniform("u_pointlightShapes[" + to_string(index) + "]", static_cast<int>(visiblePointlights[index]->getShape()));
	}

	_shaderBuffer->uploadUniform("u_pointlightCount", static_cast<int>(visiblePointlights.size()));
}

void TerrainColorRenderer::processSpotlights(const unordered_map<string, shared_ptr<Spotlight>> & spotlights)
{
	vector<shared_ptr<Spotlight>> visibleSpotlights = {};

	for(const auto & [spotlightId, spotlight] : spotlights)
	{
		if(spotlight->isVisible())
		{
			visibleSpotlights.push_back(spotlight);
		}
	}

	for(int index = 0; index < static_cast<int>(visibleSpotlights.size()); index++)
	{
		_shaderBuffer->uploadUniform("u_spotlightPositions[" + to_string(index) + "]", visibleSpotlights[index]->getPosition());
		_shaderBuffer->uploadUniform("u_spotlightFronts[" + to_string(index) + "]", visibleSpotlights[index]->getFront());
		_shaderBuffer->uploadUniform("u_spotlightColors[" + to_string(index) + "]", visibleSpotlights[index]->getColor());
		_shaderBuffer->uploadUniform("u_spotlightIntensities[" + to_string(index) + "]", visibleSpotlights[index]->getIntensity());
		_shaderBuffer->uploadUniform("u_spotlightAngles[" + to_string(index) + "]", cosf(Mathematics::convertToRadians(visibleSpotlights[index]->getAngle())));
		_shaderBuffer->uploadUniform("u_spotlightDistances[" + to_string(index) + "]", visibleSpotlights[index]->getDistance());
	}

	_shaderBuffer->uploadUniform("u_spotlightCount", static_cast<int>(visibleSpotlights.size()));
}

void TerrainColorRenderer::render(const shared_ptr<Terrain> terrain)
{
	glEnable(GL_CULL_FACE);

	if(terrain->isWireframed())
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	_shaderBuffer->uploadUniform("u_isWireframed", terrain->isWireframed());
	_shaderBuffer->uploadUniform("u_isSpecular", terrain->isSpecular());
	_shaderBuffer->uploadUniform("u_textureRepeat", terrain->getTextureRepeat());
	_shaderBuffer->uploadUniform("u_redTextureRepeat", terrain->getRedTextureRepeat());
	_shaderBuffer->uploadUniform("u_greenTextureRepeat", terrain->getGreenTextureRepeat());
	_shaderBuffer->uploadUniform("u_blueTextureRepeat", terrain->getBlueTextureRepeat());
	_shaderBuffer->uploadUniform("u_lightness", terrain->getLightness());
	_shaderBuffer->uploadUniform("u_specularShininess", terrain->getSpecularShininess());
	_shaderBuffer->uploadUniform("u_specularIntensity", terrain->getSpecularIntensity());
	_shaderBuffer->uploadUniform("u_hasDiffuseMap", (terrain->getDiffuseTextureBuffer() != nullptr));
	_shaderBuffer->uploadUniform("u_hasNormalMap", (terrain->getNormalTextureBuffer() != nullptr));
	_shaderBuffer->uploadUniform("u_hasBlendMap", (terrain->getBlendTextureBuffer() != nullptr));
	_shaderBuffer->uploadUniform("u_hasRedDiffuseMap", (terrain->getRedDiffuseTextureBuffer() != nullptr));
	_shaderBuffer->uploadUniform("u_hasGreenDiffuseMap", (terrain->getGreenDiffuseTextureBuffer() != nullptr));
	_shaderBuffer->uploadUniform("u_hasBlueDiffuseMap", (terrain->getBlueDiffuseTextureBuffer() != nullptr));
	_shaderBuffer->uploadUniform("u_hasRedNormalMap", (terrain->getRedNormalTextureBuffer() != nullptr));
	_shaderBuffer->uploadUniform("u_hasGreenNormalMap", (terrain->getGreenNormalTextureBuffer() != nullptr));
	_shaderBuffer->uploadUniform("u_hasBlueNormalMap", (terrain->getBlueNormalTextureBuffer() != nullptr));
	_shaderBuffer->uploadUniform("u_wireframeColor", terrain->getWireframeColor());
	_shaderBuffer->uploadUniform("u_color", terrain->getColor());
	_shaderBuffer->uploadUniform("u_minX", max(_renderStorage->getMinClipPosition().x, terrain->getMinClipPosition().x));
	_shaderBuffer->uploadUniform("u_minY", max(_renderStorage->getMinClipPosition().y, terrain->getMinClipPosition().y));
	_shaderBuffer->uploadUniform("u_minZ", max(_renderStorage->getMinClipPosition().z, terrain->getMinClipPosition().z));
	_shaderBuffer->uploadUniform("u_maxX", min(_renderStorage->getMaxClipPosition().x, terrain->getMaxClipPosition().x));
	_shaderBuffer->uploadUniform("u_maxY", min(_renderStorage->getMaxClipPosition().y, terrain->getMaxClipPosition().y));
	_shaderBuffer->uploadUniform("u_maxZ", min(_renderStorage->getMaxClipPosition().z, terrain->getMaxClipPosition().z));

	if(terrain->getDiffuseTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, terrain->getDiffuseTextureBuffer()->getTboId());
	}

	if(terrain->getNormalTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, terrain->getNormalTextureBuffer()->getTboId());
	}

	if(terrain->getBlendTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, terrain->getBlendTextureBuffer()->getTboId());
	}

	if(terrain->getRedDiffuseTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, terrain->getRedDiffuseTextureBuffer()->getTboId());
	}

	if(terrain->getGreenDiffuseTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE5);
		glBindTexture(GL_TEXTURE_2D, terrain->getGreenDiffuseTextureBuffer()->getTboId());
	}

	if(terrain->getBlueDiffuseTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE6);
		glBindTexture(GL_TEXTURE_2D, terrain->getBlueDiffuseTextureBuffer()->getTboId());
	}

	if(terrain->getRedNormalTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE7);
		glBindTexture(GL_TEXTURE_2D, terrain->getRedNormalTextureBuffer()->getTboId());
	}

	if(terrain->getGreenNormalTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE8);
		glBindTexture(GL_TEXTURE_2D, terrain->getGreenNormalTextureBuffer()->getTboId());
	}

	if(terrain->getBlueNormalTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE9);
		glBindTexture(GL_TEXTURE_2D, terrain->getBlueNormalTextureBuffer()->getTboId());
	}

	glBindVertexArray(terrain->getVertexBuffer()->getVaoId());
	glDrawArrays(GL_TRIANGLES, 0, terrain->getVertexBuffer()->getVertexCount());
	glBindVertexArray(0);

	if(terrain->getDiffuseTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	if(terrain->getNormalTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	if(terrain->getBlendTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	if(terrain->getRedDiffuseTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	if(terrain->getGreenDiffuseTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE5);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	if(terrain->getBlueDiffuseTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE6);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	if(terrain->getRedNormalTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE7);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	if(terrain->getGreenNormalTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE8);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	if(terrain->getBlueNormalTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE9);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	if(terrain->isWireframed())
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glDisable(GL_CULL_FACE);

	_renderStorage->increaseTriangleCount(terrain->getVertexBuffer()->getVertexCount() / 3);
}