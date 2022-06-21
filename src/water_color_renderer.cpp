#include "water_color_renderer.hpp"
#include "tools.hpp"

using std::to_string;

void WaterColorRenderer::bind()
{
	_shaderBuffer->bind();
	_shaderBuffer->uploadUniform("u_cameraView", _camera->getView());
	_shaderBuffer->uploadUniform("u_cameraProjection", _camera->getProjection());
	_shaderBuffer->uploadUniform("u_shadowView", _renderStorage->getShadowView());
	_shaderBuffer->uploadUniform("u_shadowProjection", _renderStorage->getShadowProjection());
	_shaderBuffer->uploadUniform("u_ambientLightingColor", _renderStorage->getAmbientLightingColor());
	_shaderBuffer->uploadUniform("u_ambientLightingIntensity", _renderStorage->getAmbientLightingIntensity());
	_shaderBuffer->uploadUniform("u_isAmbientLightingEnabled", _renderStorage->isAmbientLightingEnabled());
	_shaderBuffer->uploadUniform("u_directionalLightingColor", _renderStorage->getDirectionalLightingColor());
	_shaderBuffer->uploadUniform("u_directionalLightingPosition", _renderStorage->getDirectionalLightingPosition());
	_shaderBuffer->uploadUniform("u_cameraPosition", _camera->getPosition());
	_shaderBuffer->uploadUniform("u_minFogDistance", _renderStorage->getMinFogDistance());
	_shaderBuffer->uploadUniform("u_maxFogDistance", _renderStorage->getMaxFogDistance());
	_shaderBuffer->uploadUniform("u_fogThickness", _renderStorage->getFogThickness());
	_shaderBuffer->uploadUniform("u_fogColor", _renderStorage->getFogColor());
	_shaderBuffer->uploadUniform("u_isFogEnabled", _renderStorage->isFogEnabled());
	_shaderBuffer->uploadUniform("u_cameraNear", _camera->getNear());
	_shaderBuffer->uploadUniform("u_cameraFar", _camera->getFar());
	_shaderBuffer->uploadUniform("u_isDirectionalLightingEnabled", _renderStorage->isDirectionalLightingEnabled());
	_shaderBuffer->uploadUniform("u_directionalLightingIntensity", _renderStorage->getDirectionalLightingIntensity());
	_shaderBuffer->uploadUniform("u_isReflectionsEnabled", _renderStorage->isReflectionsEnabled());
	_shaderBuffer->uploadUniform("u_isRefractionsEnabled", _renderStorage->isRefractionsEnabled());
	_shaderBuffer->uploadUniform("u_shadowSize", _renderStorage->getShadowSize());
	_shaderBuffer->uploadUniform("u_shadowLookat", _renderStorage->getShadowLookat());
	_shaderBuffer->uploadUniform("u_shadowLightness", _renderStorage->getShadowLightness());
	_shaderBuffer->uploadUniform("u_shadowBias", _renderStorage->getShadowBias());
	_shaderBuffer->uploadUniform("u_shadowPcfCount", _renderStorage->getShadowPcfCount());
	_shaderBuffer->uploadUniform("u_isShadowsEnabled", _renderStorage->isShadowsEnabled());
	_shaderBuffer->uploadUniform("u_isShadowCircleEnabled", _renderStorage->isShadowCircleEnabled());
	_shaderBuffer->uploadUniform("u_reflectionMap", 0);
	_shaderBuffer->uploadUniform("u_refractionMap", 1);
	_shaderBuffer->uploadUniform("u_edgeMap", 2);
	_shaderBuffer->uploadUniform("u_dudvMap", 3);
	_shaderBuffer->uploadUniform("u_normalMap", 4);
	_shaderBuffer->uploadUniform("u_heightMap", 5);
	_shaderBuffer->uploadUniform("u_shadowMap", 6);
	_shaderBuffer->uploadUniform("u_hasReflectionMap", (_renderStorage->getWaterReflectionTextureBuffer() != nullptr));
	_shaderBuffer->uploadUniform("u_hasRefractionMap", (_renderStorage->getWaterRefractionTextureBuffer() != nullptr));

	if(_renderStorage->getWaterReflectionTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _renderStorage->getWaterReflectionTextureBuffer()->getTboId());
	}

	if(_renderStorage->getWaterRefractionTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, _renderStorage->getWaterRefractionTextureBuffer()->getTboId());
	}

	if(_renderStorage->getWaterEdgeTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, _renderStorage->getWaterEdgeTextureBuffer()->getTboId());
	}

	if(_renderStorage->getShadowTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE6);
		glBindTexture(GL_TEXTURE_2D, _renderStorage->getShadowTextureBuffer()->getTboId());
	}

	glEnable(GL_CLIP_DISTANCE0);
	glEnable(GL_CLIP_DISTANCE1);
	glEnable(GL_CLIP_DISTANCE2);
	glEnable(GL_CLIP_DISTANCE3);
	glEnable(GL_CLIP_DISTANCE4);
	glEnable(GL_CLIP_DISTANCE5);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
}

void WaterColorRenderer::unbind()
{
	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CLIP_DISTANCE0);
	glDisable(GL_CLIP_DISTANCE1);
	glDisable(GL_CLIP_DISTANCE2);
	glDisable(GL_CLIP_DISTANCE3);
	glDisable(GL_CLIP_DISTANCE4);
	glDisable(GL_CLIP_DISTANCE5);

	if(_renderStorage->getWaterReflectionTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	if(_renderStorage->getWaterRefractionTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	if(_renderStorage->getWaterEdgeTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	if(_renderStorage->getShadowTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE6);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	_shaderBuffer->unbind();
}

void WaterColorRenderer::processPointlights(const unordered_map<string, shared_ptr<Pointlight>> & pointlights)
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

void WaterColorRenderer::processSpotlights(const unordered_map<string, shared_ptr<Spotlight>> & spotlights)
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

void WaterColorRenderer::render(const shared_ptr<Water> water)
{
	if(water->isWireframed())
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	_shaderBuffer->uploadUniform("u_isWireframed", water->isWireframed());
	_shaderBuffer->uploadUniform("u_rippleOffset", water->getRippleOffset());
	_shaderBuffer->uploadUniform("u_waveOffset", water->getWaveOffset());
	_shaderBuffer->uploadUniform("u_waveHeight", water->getWaveHeight());
	_shaderBuffer->uploadUniform("u_maxDepth", water->getMaxDepth());
	_shaderBuffer->uploadUniform("u_height", water->getHeight());
	_shaderBuffer->uploadUniform("u_textureRepeat", water->getTextureRepeat());
	_shaderBuffer->uploadUniform("u_specularShininess", water->getSpecularShininess());
	_shaderBuffer->uploadUniform("u_specularIntensity", water->getSpecularIntensity());
	_shaderBuffer->uploadUniform("u_isEdged", water->isEdged());
	_shaderBuffer->uploadUniform("u_isSpecular", water->isSpecular());
	_shaderBuffer->uploadUniform("u_isReflective", water->isReflective());
	_shaderBuffer->uploadUniform("u_isRefractive", water->isRefractive());
	_shaderBuffer->uploadUniform("u_color", water->getColor());
	_shaderBuffer->uploadUniform("u_lightness", water->getLightness());
	_shaderBuffer->uploadUniform("u_distortionSize", water->getDistortionSize());
	_shaderBuffer->uploadUniform("u_distortionFactor", water->getDistortionFactor());
	_shaderBuffer->uploadUniform("u_minX", max(_renderStorage->getMinClipPosition().x, water->getMinClipPosition().x));
	_shaderBuffer->uploadUniform("u_minY", max(_renderStorage->getMinClipPosition().y, water->getMinClipPosition().y));
	_shaderBuffer->uploadUniform("u_minZ", max(_renderStorage->getMinClipPosition().z, water->getMinClipPosition().z));
	_shaderBuffer->uploadUniform("u_maxX", min(_renderStorage->getMaxClipPosition().x, water->getMaxClipPosition().x));
	_shaderBuffer->uploadUniform("u_maxY", min(_renderStorage->getMaxClipPosition().y, water->getMaxClipPosition().y));
	_shaderBuffer->uploadUniform("u_maxZ", min(_renderStorage->getMaxClipPosition().z, water->getMaxClipPosition().z));
	_shaderBuffer->uploadUniform("u_hasHeightMap", (water->getHeightTextureBuffer() != nullptr));
	_shaderBuffer->uploadUniform("u_hasDudvMap", (water->getDudvTextureBuffer() != nullptr));
	_shaderBuffer->uploadUniform("u_hasNormalMap", (water->getNormalTextureBuffer() != nullptr));
	_shaderBuffer->uploadUniform("u_wireframeColor", water->getWireframeColor());

	if(water->getDudvTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, water->getDudvTextureBuffer()->getTboId());
	}

	if(water->getNormalTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, water->getNormalTextureBuffer()->getTboId());
	}

	if(water->getHeightTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE5);
		glBindTexture(GL_TEXTURE_2D, water->getHeightTextureBuffer()->getTboId());
	}

	if(water->getHeightTextureBuffer() != nullptr)
	{
		glBindVertexArray(water->getHighQualityVertexBuffer()->getVaoId());
	}
	else
	{
		glBindVertexArray(water->getLowQualityVertexBuffer()->getVaoId());
	}

	if(water->getHeightTextureBuffer() != nullptr)
	{
		glDrawArrays(GL_TRIANGLES, 0, water->getHighQualityVertexBuffer()->getVertexCount());
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, water->getLowQualityVertexBuffer()->getVertexCount());
	}

	glBindVertexArray(0);

	if(water->getDudvTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	if(water->getNormalTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	if(water->getHeightTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE5);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	if(water->isWireframed())
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	if(water->getHeightTextureBuffer() != nullptr)
	{
		_renderStorage->increaseTriangleCount(water->getHighQualityVertexBuffer()->getVertexCount() / 3);
	}
	else
	{
		_renderStorage->increaseTriangleCount(water->getLowQualityVertexBuffer()->getVertexCount() / 3);
	}
}