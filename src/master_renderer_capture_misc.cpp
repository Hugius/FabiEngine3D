#include "master_renderer.hpp"
#include "render_bus.hpp"

void MasterRenderer::_captureWorldDepth(RenderBus& renderBus, EntityBus& entityBus)
{
	auto modelEntities = entityBus.getModelEntities();
	auto billboardEntities = entityBus.getBillboardEntities();
	float clippingY = numeric_limits<float>::lowest();
	const bool waterDepthNeeded = (entityBus.getWaterEntity() != nullptr) && (entityBus.getWaterEntity()->getTransparency() > 0.0f);
	bool isUnderWater = false;

	if(waterDepthNeeded)
	{
		auto waterEntity = entityBus.getWaterEntity();
		float waveHeight = (waterEntity->hasDisplacementMap() ? waterEntity->getWaveHeight() : 0.0f);
		isUnderWater = (renderBus.getCameraPosition().y < (waterEntity->getHeight() + waveHeight));
		isUnderWater = (isUnderWater && (renderBus.getCameraPosition().x > (waterEntity->getSize() / 2.0f)));
		isUnderWater = (isUnderWater && (renderBus.getCameraPosition().x < (waterEntity->getSize() / 2.0f)));
		isUnderWater = (isUnderWater && (renderBus.getCameraPosition().z > (waterEntity->getSize() / 2.0f)));
		isUnderWater = (isUnderWater && (renderBus.getCameraPosition().z < (waterEntity->getSize() / 2.0f)));

		if(isUnderWater)
		{
			clippingY = waterEntity->getHeight();
		}
		else
		{
			clippingY = (waterEntity->getHeight() + waveHeight);
		}
	}

	if(renderBus.isDofEnabled() || renderBus.isLensFlareEnabled() || waterDepthNeeded)
	{
		_worldDepthCaptor->bind();
		glClear(GL_DEPTH_BUFFER_BIT);

		if(entityBus.getTerrainEntity() != nullptr)
		{
			_terrainEntityDepthRenderer.bind(_terrainEntityDepthShader, renderBus);

			_terrainEntityDepthRenderer.render(_terrainEntityDepthShader, entityBus.getTerrainEntity());

			_terrainEntityDepthRenderer.unbind(_terrainEntityDepthShader);
		}

		if(!modelEntities.empty())
		{
			_modelEntityDepthRenderer.bind(_modelEntityDepthShader, renderBus);

			for(const auto& [key, modelEntity] : modelEntities)
			{
				if(modelEntity->isDepthMapIncluded())
				{
					if(modelEntity->isLevelOfDetailed())
					{
						auto foundPair = modelEntities.find(modelEntity->getLevelOfDetailEntityID());
						if(foundPair != modelEntities.end())
						{
							auto levelOfDetailEntity = foundPair->second;

							fvec3 initialPosition = levelOfDetailEntity->getBasePosition();
							fvec3 initialRotation = levelOfDetailEntity->getBaseRotation();
							fvec3 initialSize = levelOfDetailEntity->getBaseSize();
							bool initialVisibility = levelOfDetailEntity->isVisible();

							levelOfDetailEntity->setBasePosition(modelEntity->getBasePosition());
							levelOfDetailEntity->setBaseRotation(modelEntity->getBaseRotation());
							levelOfDetailEntity->setBaseSize((modelEntity->getBaseSize() / modelEntity->getLevelOfDetailSize()) * initialSize);
							levelOfDetailEntity->setVisible(modelEntity->isVisible());
							levelOfDetailEntity->updateTransformationMatrix();

							_modelEntityDepthRenderer.render(_modelEntityDepthShader, renderBus, levelOfDetailEntity, clippingY, isUnderWater);

							levelOfDetailEntity->setBasePosition(initialPosition);
							levelOfDetailEntity->setBaseRotation(initialRotation);
							levelOfDetailEntity->setBaseSize(initialSize);
							levelOfDetailEntity->setVisible(initialVisibility);
							levelOfDetailEntity->updateTransformationMatrix();
						}
						else
						{
							Logger::throwError("MasterRenderer::_captureWorldDepth");
						}
					}
					else
					{
						_modelEntityDepthRenderer.render(_modelEntityDepthShader, renderBus, modelEntity, clippingY, isUnderWater);
					}
				}
			}

			_modelEntityDepthRenderer.unbind(_modelEntityDepthShader);
		}

		if(!billboardEntities.empty())
		{
			_billboardEntityDepthRenderer.bind(_billboardEntityDepthShader, renderBus);

			for(const auto& [key, entity] : billboardEntities)
			{
				if(entity->isDepthMapIncluded())
				{
					_billboardEntityDepthRenderer.render(_billboardEntityDepthShader, renderBus, entity, clippingY, isUnderWater);
				}
			}

			_billboardEntityDepthRenderer.unbind(_billboardEntityDepthShader);
		}

		_worldDepthCaptor->unbind();

		renderBus.setDepthMap(_worldDepthCaptor->getTexture(0));
	}
	else
	{
		renderBus.setDepthMap(0);
	}
}

void MasterRenderer::_captureDOF(RenderBus& renderBus)
{
	if(renderBus.isDofEnabled())
	{
		_dofBlurRenderer.bind(_blurShader, renderBus);
		renderBus.setDofMap(_dofBlurRenderer.blurTexture(_blurShader, _renderQuad, renderBus.getFinalSceneMap(), 2, 1.0f, BlurDirection::BOTH));
		_dofBlurRenderer.unbind(_blurShader);

		_dofCaptor->bind();
		_dofRenderer.bind(_dofShader, renderBus);
		_dofRenderer.render(_renderQuad);
		_dofRenderer.unbind(_dofShader);
		_dofCaptor->unbind();
		renderBus.setFinalSceneMap(_dofCaptor->getTexture(0));
	}
	else
	{
		renderBus.setDofMap(0);
	}
}

void MasterRenderer::_captureLensFlare(RenderBus& renderBus)
{
	if(renderBus.isLensFlareEnabled())
	{
		_lensFlareCaptor->bind();
		_lensFlareRenderer.bind(_lensFlareShader, renderBus);
		_lensFlareRenderer.render(_renderQuad);
		_lensFlareRenderer.unbind(_lensFlareShader);
		_lensFlareCaptor->unbind();
		renderBus.setFinalSceneMap(_lensFlareCaptor->getTexture(0));
	}
}

void MasterRenderer::_captureMotionBlur(RenderBus& renderBus)
{
	if(renderBus.isMotionBlurEnabled())
	{
		float xDifference = (_cameraYawDifference * renderBus.getMotionBlurStrength());
		float yDifference = (_cameraPitchDifference * renderBus.getMotionBlurStrength());

		bool hasMoved = false;
		BlurDirection direction;

		if(xDifference != 0.0f || yDifference != 0.0f)
		{
			if(xDifference >= yDifference)
			{
				hasMoved = true;
				direction = BlurDirection::HORIZONTAL;
				renderBus.setMotionBlurMixValue(xDifference);
			}
			else
			{
				hasMoved = true;
				direction = BlurDirection::VERTICAL;
				renderBus.setMotionBlurMixValue(yDifference);
			}
		}

		if(hasMoved)
		{
			_motionBlurBlurRenderer.bind(_blurShader, renderBus);
			renderBus.setMotionBlurMap(_motionBlurBlurRenderer.blurTexture(_blurShader, _renderQuad, renderBus.getFinalSceneMap(), 5, 1.0f, direction));
			_motionBlurBlurRenderer.unbind(_blurShader);
		}
		else
		{
			renderBus.setMotionBlurMixValue(0.0f);
			renderBus.setMotionBlurMap(0);
		}

		_motionBlurCaptor->bind();
		_motionBlurRenderer.bind(_motionBlurShader, renderBus);
		_motionBlurRenderer.render(_renderQuad);
		_motionBlurRenderer.unbind(_motionBlurShader);
		_motionBlurCaptor->unbind();
		renderBus.setFinalSceneMap(_motionBlurCaptor->getTexture(0));
	}
	else
	{
		renderBus.setMotionBlurMap(0);
	}
}

void MasterRenderer::_captureAntiAliasing(RenderBus& renderBus)
{
	if(renderBus.isAntiAliasingEnabled())
	{
		_antiAliasingCaptor->bind();
		_antiAliasingRenderer.bind(_antiAliasingShader, renderBus);
		_antiAliasingRenderer.render(_renderQuad);
		_antiAliasingRenderer.unbind(_antiAliasingShader);
		_antiAliasingCaptor->unbind();
		renderBus.setFinalSceneMap(_antiAliasingCaptor->getTexture(0));
	}
}

void MasterRenderer::_captureBloom(RenderBus& renderBus)
{
	if(renderBus.isBloomEnabled() && renderBus.getBloomBlurCount() > 0 && renderBus.getBloomIntensity() > 0.0f)
	{
		shared_ptr<TextureBuffer> textureToBlur = nullptr;
		if(renderBus.getBloomType() == BloomType::EVERYTHING)
		{
			textureToBlur = renderBus.getPrimarySceneMap();
		}
		else
		{
			textureToBlur = renderBus.getSecondarySceneMap();
		}

		_bloomBlurRendererHighQuality.bind(_blurShader, renderBus);
		renderBus.setBloomMap(_bloomBlurRendererHighQuality.blurTexture(_blurShader, _renderQuad, textureToBlur,
							  renderBus.getBloomBlurCount(), renderBus.getBloomIntensity(), BlurDirection::BOTH));
		_bloomBlurRendererHighQuality.unbind(_blurShader);

		_bloomBlurRendererLowQuality.bind(_blurShader, renderBus);
		renderBus.setBloomMap(_bloomBlurRendererLowQuality.blurTexture(_blurShader, _renderQuad, renderBus.getBloomMap(),
							  renderBus.getBloomBlurCount(), renderBus.getBloomIntensity(), BlurDirection::BOTH));
		_bloomBlurRendererLowQuality.unbind(_blurShader);

		_bloomCaptor->bind();
		_bloomRenderer.bind(_bloomShader, renderBus);
		_bloomRenderer.render(_renderQuad);
		_bloomRenderer.unbind(_bloomShader);
		_bloomCaptor->unbind();
		renderBus.setFinalSceneMap(_bloomCaptor->getTexture(0));
	}
	else
	{
		renderBus.setBloomMap(0);
	}
}

void MasterRenderer::_captureShadows(RenderBus& renderBus, EntityBus& entityBus)
{
	if(renderBus.isShadowsEnabled())
	{
		auto modelEntities = entityBus.getModelEntities();
		auto billboardEntities = entityBus.getBillboardEntities();

		_shadowCaptor->bind();
		glClear(GL_DEPTH_BUFFER_BIT);

		if(!modelEntities.empty())
		{
			_modelEntityShadowRenderer.bind(_modelEntityShadowShader, renderBus);

			for(const auto& [key, modelEntity] : modelEntities)
			{
				if(modelEntity->isLevelOfDetailed())
				{
					auto foundPair = modelEntities.find(modelEntity->getLevelOfDetailEntityID());
					if(foundPair != modelEntities.end())
					{
						auto levelOfDetailEntity = foundPair->second;

						fvec3 initialPosition = levelOfDetailEntity->getBasePosition();
						fvec3 initialRotation = levelOfDetailEntity->getBaseRotation();
						fvec3 initialSize = levelOfDetailEntity->getBaseSize();
						bool initialVisibility = levelOfDetailEntity->isVisible();

						levelOfDetailEntity->setBasePosition(modelEntity->getBasePosition());
						levelOfDetailEntity->setBaseRotation(modelEntity->getBaseRotation());
						levelOfDetailEntity->setBaseSize((modelEntity->getBaseSize() / modelEntity->getLevelOfDetailSize()) * initialSize);
						levelOfDetailEntity->setVisible(modelEntity->isVisible());
						levelOfDetailEntity->updateTransformationMatrix();

						_modelEntityShadowRenderer.render(_modelEntityShadowShader, levelOfDetailEntity);

						levelOfDetailEntity->setBasePosition(initialPosition);
						levelOfDetailEntity->setBaseRotation(initialRotation);
						levelOfDetailEntity->setBaseSize(initialSize);
						levelOfDetailEntity->setVisible(initialVisibility);
						levelOfDetailEntity->updateTransformationMatrix();
					}
					else
					{
						Logger::throwError("MasterRenderer::_captureShadows");
					}
				}
				else
				{
					_modelEntityShadowRenderer.render(_modelEntityShadowShader, modelEntity);
				}
			}

			_modelEntityShadowRenderer.unbind(_modelEntityShadowShader);
		}

		if(!billboardEntities.empty())
		{
			_billboardEntityShadowRenderer.bind(_billboardEntityShadowShader, renderBus);

			for(const auto& [key, entity] : entityBus.getBillboardEntities())
			{
				_billboardEntityShadowRenderer.render(_billboardEntityShadowShader, entity);
			}

			_billboardEntityShadowRenderer.unbind(_billboardEntityShadowShader);
		}

		_shadowCaptor->unbind();
		renderBus.setShadowMap(_shadowCaptor->getTexture(0));
	}
	else
	{
		renderBus.setShadowMap(0);
	}
}